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
		cout << "\nFAILED: " << e.what();
	}

	cout << '\n';
	return 0;
}
