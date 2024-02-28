#pragma once
#include <string>
#include <vector>

//Struct makes the members public by default
struct Task
{
	std::string description;
	bool done;
};

void SaveTasksToFile(const std::vector<Task>& tasks, const std::string& fileName);
std::vector<Task> LoadTasksFromFile(const std::string& fileName);

