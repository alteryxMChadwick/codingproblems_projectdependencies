#pragma once

#include <functional>
#include <string>
#include <vector>

struct project
{
	std::vector<project*> depends_on{};
	std::string unique_id{"DEFAULT"};
	bool built{false};

	project() = default;

	project(std::string _n);

	void add_dependency(project& p);

	void build(std::function<void(project&)> visitor);
};