#include "project.h"

#include <algorithm>
#include <exception>
#include <unordered_set>

using std::function;
using std::runtime_error;
using std::string;
using std::vector;

project&
project_with_id(flat_project_map &projects, const string project_unique_id)
{
	const auto itr = find_if(
		begin(projects)
		, end(projects)
		, [&project_unique_id](const flat_project_map::value_type & project_pair)
		{
			return project_pair.unique_id == project_unique_id;
		}
	);

	if (itr == end(projects))
	{
		throw runtime_error(string{"project with unique id '"}.append(project_unique_id).append("' does not exist"));
	}

	return *itr;
}

project::project(string _n)
  : unique_id(move(_n))
{
}

void
project::depends_on(project &p)
{
  if(this == &p)
  {
    throw runtime_error(string{"'"}.append(p.unique_id).append("' depends directly on itself"));
  }

  if(end(p.depends) != find(begin(p.depends), end(p.depends), this))
  {
    throw runtime_error(
      string{"circular dependency detected; '"}.append(unique_id).append("' depends on '").append(p.unique_id).append("' which depends on '").append(unique_id).append("'")
    );
  }

  depends.push_back(&p);
  depends.erase(unique(begin(depends), end(depends)), end(depends));
}

void
do_build(project &p, function<void(project &)> visitor, vector<project *>& ids_so_far)
{
  if(p.built) return;

  {
    const auto itr = find(begin(ids_so_far), end(ids_so_far), &p);
    if (end(ids_so_far) != itr)
    {
      throw runtime_error(string{"circular dependency detected; '"}.append((*itr)->unique_id).append("' eventually depends on itself"));
    }
    ids_so_far.push_back(&p);
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
  auto ids_so_far = vector<project *>{};

  do_build(*this, visitor, ids_so_far);
}
