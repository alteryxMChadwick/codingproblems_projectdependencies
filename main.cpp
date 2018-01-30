#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using std::cout;
using std::string;
using std::unordered_map;
using std::vector;

struct project
{
	vector<project*> depends_on{};
	string name{"DEFAULT"};
	bool built{false};

	project() = default;

	project(string _n)
		: name(move(_n))
	{}

	void add_dependency(project& p)
	{
		if(this == &p) return;

		depends_on.push_back(&p);
		depends_on.erase(unique(begin(depends_on), end(depends_on)), end(depends_on));
	}

	void build()
	{
		if(built) return;

		for(auto* dep : depends_on)
		{
			dep->build();
		}

		cout << name << ' ';
		built = true;
	}
};

int main(const int /*argc*/, const char *const []/*argv*/)
{
	unordered_map<string, project> projects{
		{{"a"}, project{"a"}}
		, {{"b"}, project{"b"}}
		, {{"c"}, project{"c"}}
		, {{"d"}, project{"d"}}
		, {{"e"}, project{"e"}}
		, {{"f"}, project{"f"}}
	};

	projects["d"].add_dependency(projects["a"]);
	projects["b"].add_dependency(projects["f"]);
	projects["d"].add_dependency(projects["b"]);
	projects["a"].add_dependency(projects["f"]);
	projects["c"].add_dependency(projects["d"]);

	for(auto& p : projects)
	{
		p.second.build();
	}

	cout << '\n';
	return 0;
}
