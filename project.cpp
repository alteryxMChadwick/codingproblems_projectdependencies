#include "project.h"

#include <algorithm>

using std::function;
using std::string;

project::project(string _n)
  : unique_id(move(_n))
{
}

void
project::add_dependency(project& p)
{
  if(this == &p) return;

  depends_on.push_back(&p);
  depends_on.erase(unique(begin(depends_on), end(depends_on)), end(depends_on));
}

void
project::build(function<void(project&)> visitor)
{
  if(built) return;

  for(auto* dep : depends_on)
  {
    dep->build(visitor);
  }
  visitor(*this);
  built = true;
}
