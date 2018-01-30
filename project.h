#pragma once

#include <functional>
#include <string>
#include <vector>

struct project
{
	std::vector<project *> depends{};
	std::string unique_id{"DEFAULT"};
	bool built{false};

	project() = default;

	project(std::string _n);

	void depends_on(project & p);

	void build(std::function<void(project &)> visitor);
};