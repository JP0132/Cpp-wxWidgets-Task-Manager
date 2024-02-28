#include "Task.h"
#include <string>
#include <vector>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <algorithm>


//Save the tasks to a file
void SaveTasksToFile(const std::vector<Task>& tasks, const std::string& fileName)
{
    std::ofstream file(fileName); //Out file stream for the file
    file << tasks.size(); //Write number of tasks to the file

    //Looping through the tasks
    for (const Task& task : tasks) {
        std::string description = task.description;
        std::replace(description.begin(), description.end(), ' ', '_'); //Replaces the spaces with underscore for easier writing

        file << '\n' << description << ' ' << task.done; //Writing the task to the file
    }

    file.close();

   
}

//Gets the tasks from the file and return them in a vector
std::vector<Task> LoadTasksFromFile(const std::string& fileName)
{   

    //exists avaliable in only C++ 17
    if(!std::filesystem::exists(fileName)) {
        return std::vector<Task>();
    }
    
    std::vector<Task> tasks;
    std::ifstream istream(fileName);

    int n;
    istream >> n;

    for (int i = 0; i < n; i++) {
        std::string description;
        bool done;

        istream >> description >> done;
        std::replace(description.begin(), description.end(), '_', ' ');
        tasks.push_back(Task{ description, done });
    }

    return tasks;

}
