#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "project.h"

using std::cout;
using std::runtime_error;
using std::string;
using std::vector;

using flat_project_map = vector<project>;

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

int main(const int /*argc*/, const char *const []/*argv*/)
{
	try
	{
		auto projects = flat_project_map{
			project{"a"}
			, project{"b"}
			, project{"c"}
			, project{"d"}
			, project{"e"}
			, project{"f"}
		};

		project_with_id(projects, "c").depends_on(project_with_id(projects, "d"));
		project_with_id(projects, "d").depends_on(project_with_id(projects, "a"));
		project_with_id(projects, "a").depends_on(project_with_id(projects, "f"));

		project_with_id(projects, "d").depends_on(project_with_id(projects, "b"));
		project_with_id(projects, "b").depends_on(project_with_id(projects, "f"));

		auto print_build_visitor = [](project &p)
		{
			/*
			actual build code would go here
			*/
			cout << p.unique_id << ' ';
		};

		for(auto &p : projects)
		{
			p.build(print_build_visitor);
		}
	}
	catch(runtime_error e)
	{
		cout << "FAILED: " << e.what();
	}

	cout << '\n';
	return 0;
}
