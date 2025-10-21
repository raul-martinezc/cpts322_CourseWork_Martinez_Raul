//final?
#include "input_alphabet.h"
#include "string_play.h"
#include "uppercase.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

void input_alphabet::load(std::ifstream& definition, bool& valid)
{
    std::string line;
    std::stringstream parseme;
    std::string current;

    // Search for INPUT_ALPHABET: line
    while (std::getline(definition, line))
    {
        if (trim(line, " \t").empty())
            continue;

        parseme.clear();
        parseme.str(line);
        parseme >> current;

        if (to_uppercase_string(current) == "INPUT_ALPHABET:")
            break;
    }

    if (to_uppercase_string(current) != "INPUT_ALPHABET:")
    {
        std::cout << "Input Alphabet Not Defined." << std::endl;
        valid = false;
        return;
    }

    // Read rest of the line for characters
    while (parseme >> current)
    {
        if (current.length() != 1)
        {
            std::cout << "Invalid Symbol in Input Alphabet: \"" << current << "\"" << std::endl;
            valid = false;
        }
        else if (!is_element(current[0]))
        {
            alphabet.push_back(current[0]);
        }
    }
}

void input_alphabet::view() const
{
    std::cout << "\u03A3 = { ";
    if (!alphabet.empty())
    {
        std::cout << alphabet[0];
        for (size_t i = 1; i < alphabet.size(); ++i)
        {
            std::cout << ", " << alphabet[i];
        }
    }
    std::cout << " }" << std::endl << std::endl;
}

bool input_alphabet::is_element(const char& value) const
{
    for (char ch : alphabet)
    {
        if (ch == value)
            return true;
    }
    return false;
}
