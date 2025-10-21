//final?
#include "final_states.h"
#include "final_state.h"
#include "states.h"
#include "crash.h"
#include "string_play.h"
#include "uppercase.h"

#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

void final_states::load(std::ifstream& definition, bool& valid)
{
    std::string line;
    std::stringstream parseme;
    std::string current;

    // Search for the line starting with FINAL_STATES:
    while (std::getline(definition, line))
    {
        if (trim(line, " \t").empty())
            continue;

        parseme.clear();
        parseme.str(line);
        parseme >> current;

        if (to_uppercase_string(current) == "FINAL_STATES:")
            break;
    }

    if (to_uppercase_string(current) != "FINAL_STATES:")
    {
        std::cout << "Final States Not Defined." << std::endl;
        valid = false;
        return;
    }

    // Read the remaining tokens in the line as final states
    while (parseme >> current)
    {
        final_state st(current);
        state_list.push_back(st);
    }
}

void final_states::validate(const states& all_states, bool& valid) const
{
    for (size_t i = 0; i < state_list.size(); ++i)
    {
        std::string name;
        state_list[i].get_name(name);

        if (!all_states.is_element(name))
        {
            std::cout << "Error: Final State '" << name << "' is not declared in the list of states." << std::endl;
            valid = false;
        }

        for (size_t j = i + 1; j < state_list.size(); ++j)
        {
            std::string other_name;
            state_list[j].get_name(other_name);
            if (name == other_name)
            {
                std::cout << "Warning: duplicate final state '" << name << "' found." << std::endl;
                valid = false;
            }
        }
    }
}

void final_states::view() const
{
    std::cout << "F = { ";
    if (!state_list.empty())
    {
        std::string name;
        state_list[0].get_name(name);
        std::cout << name;
        for (size_t i = 1; i < state_list.size(); ++i)
        {
            state_list[i].get_name(name);
            std::cout << ", " << name;
        }
    }
    std::cout << " }" << std::endl << std::endl;
}

bool final_states::is_element(const std::string& state) const
{
    for (size_t i = 0; i < state_list.size(); ++i)
    {
        std::string name;
        state_list[i].get_name(name);
        if (name == state)
            return true;
    }
    return false;
}
