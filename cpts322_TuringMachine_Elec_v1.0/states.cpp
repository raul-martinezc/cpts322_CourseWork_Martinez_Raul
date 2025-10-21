//final?
#include "states.h"
#include "state.h"
#include "crash.h"
#include "uppercase.h"
#include "string_play.h"

#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

void states::load(std::ifstream& definition, bool& valid)
{
    std::string line;
    std::string token;

    // Look for the "STATES:" line
    while (std::getline(definition, line))
    {
        line = trim(line, " \t");
        if (line.empty()) continue;

        std::stringstream parseme(line);
        parseme >> token;

        if (uppercase_string(token) == "STATES:")
        {
            // Load states from the same line
            while (parseme >> token)
            {
                state st(token);
                state_list.push_back(st);
            }

            return; // Successfully loaded
        }
    }

    std::cout << "ERROR: States Not Defined " << std::endl;
    valid = false;
}

void states::view() const
{
    std::cout << "Q = { ";
    if (!state_list.empty())
    {
        std::cout << element(0);
        for (int i = 1; i < size(); ++i)
        {
            std::cout << ", " << element(i);
        }
    }
    std::cout << " }\n\n";
}

int states::size() const
{
    return static_cast<int>(state_list.size());
}

std::string states::element(int index) const
{
    if (index >= size())
        throw crash("States' Index Out-of-Bounds. ");

    std::string name;
    state_list[index].get_name(name);
    return name;
}

bool states::is_element(const std::string& state_name) const
{
    std::string target = uppercase_string(state_name);
    for (int i = 0; i < size(); ++i)
    {
        std::string name;
        state_list[i].get_name(name);
        if (uppercase_string(name) == target)
            return true;
    }
    return false;
}
