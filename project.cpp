#include "project.h"

#include <algorithm>
#include <exception>
#include <unordered_set>

using std::function;
using std::runtime_error;
using std::string;
using std::unordered_set;

project::project(string _n)
  : unique_id(move(_n))
{
}

void
project::depends_on(project &p)
{
  if(this == &p)
  {
    throw runtime_error("self dependency detected");
  }

  if(end(p.depends) != find(begin(p.depends), end(p.depends), this))
  {
    throw runtime_error(string{"circular dependency detected; "}.append(unique_id).append(" depends on ").append(p.unique_id).append(" which depends on ").append(unique_id));
  }

  depends.push_back(&p);
  depends.erase(unique(begin(depends), end(depends)), end(depends));
}

void
do_build(project &p, function<void(project &)> visitor, unordered_set<project *>& ids_so_far)
{
  if(p.built) return;

  {
    const auto itr = ids_so_far.find(&p);
    if (ids_so_far.find(&p) != ids_so_far.end())
    {
      throw runtime_error(string{"circular dependency detected; "}.append(p.unique_id).append(" eventually depends on itself"));
    }
    ids_so_far.emplace_hint(itr, &p);
  }

  for(auto *dep : p.depends)
  {
    do_build(*dep, visitor, ids_so_far);
  }
  visitor(p);
  p.built = true;
}

void
project::build(function<void(project &)> visitor)
{
  auto ids_so_far = unordered_set<project *>{};

  do_build(*this, visitor, ids_so_far);
}
