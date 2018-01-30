#include <algorithm>
#include <iostream>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

#include "project.h"

using std::cout;
using std::string;
using std::unordered_map;

int main(const int /*argc*/, const char *const []/*argv*/)
{
	auto projects = unordered_map<string, project>{
		{{"a"}, project{"a"}}
		, {{"b"}, project{"b"}}
		, {{"c"}, project{"c"}}
		, {{"d"}, project{"d"}}
		, {{"e"}, project{"e"}}
		, {{"f"}, project{"f"}}
	};

	projects["d"].add_dependency(projects["a"]);
	projects["a"].add_dependency(projects["d"]);
	projects["b"].add_dependency(projects["f"]);
	projects["d"].add_dependency(projects["b"]);
	projects["a"].add_dependency(projects["f"]);
	projects["c"].add_dependency(projects["d"]);

	auto print_build_visitor = [](project& p)
	{ 
		cout << p.unique_id << ' ';
	};

	for(auto& p : projects)
	{
		p.second.build(print_build_visitor);
	}

	cout << '\n';
	return 0;
}
