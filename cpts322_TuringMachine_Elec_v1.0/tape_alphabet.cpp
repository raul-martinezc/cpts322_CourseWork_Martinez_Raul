//final?
#include "tape_alphabet.h"
#include "string_play.h"
#include "uppercase.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

void tape_alphabet::load(std::ifstream & definition, bool & valid)
{
    std::string line;
    std::stringstream parseme;
    std::string current;

    // Search for "TAPE_ALPHABET:"
    while (std::getline(definition, line))
    {
        if (trim(line, " \t").empty()) continue;

        parseme.clear();
        parseme.str(line);
        parseme >> current;

        if (uppercase_string(current) == "TAPE_ALPHABET:")
            break;
    }

    if (uppercase_string(current) != "TAPE_ALPHABET:")
    {
        std::cout << "ERROR: Tape Alphabet Not Defined or Misplaced. " << std:: endl;
        valid = false;
        return;
    }

    // Load symbols from the rest of the line
    while (parseme >> current)
    {
        if (!current.empty())
        {
            alphabet.push_back(current[0]);
        }
    }
}

void tape_alphabet::view() const
{
    std::cout << "\u0393 = { ";
    if (!alphabet.empty())
    {
        std::cout << alphabet[0];
        for (size_t i = 1; i < alphabet.size(); ++i)
        {
            std::cout << ", " << alphabet[i];
        }
    }
    std::cout << " }\n\n";
}

bool tape_alphabet::is_element(const char & value) const
{
    for (char ch : alphabet)
    {
        if (ch == value)
            return true;
    }
    return false;
}
