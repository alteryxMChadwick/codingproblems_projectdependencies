#include <algorithm>
#include <iostream>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

#include "project.h"

using std::cout;
using std::runtime_error;
using std::string;
using std::unordered_map;

int main(const int /*argc*/, const char *const []/*argv*/)
{
	try
	{
		auto projects = unordered_map<string, project>{
			{{"a"}, project{"a"}}
			, {{"b"}, project{"b"}}
			, {{"c"}, project{"c"}}
			, {{"d"}, project{"d"}}
			, {{"e"}, project{"e"}}
			, {{"f"}, project{"f"}}
		};
		
		projects["c"].depends_on(projects["d"]);
		projects["d"].depends_on(projects["a"]);
		projects["a"].depends_on(projects["f"]);

		projects["d"].depends_on(projects["b"]);
		projects["b"].depends_on(projects["f"]);


		auto print_build_visitor = [](project &p)
		{ 
			cout << p.unique_id << ' ';
		};

		for(auto &p : projects)
		{
			p.second.build(print_build_visitor);
		}
	}
	catch(runtime_error e)
	{
		cout << "FAILED: " << e.what();
	}

	cout << '\n';
	return 0;
}
