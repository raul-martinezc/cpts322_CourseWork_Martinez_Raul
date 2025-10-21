//verified 4/14
#include "tape.h"
#include "input_alphabet.h"
#include "tape_alphabet.h"
#include "direction.h"
#include "uppercase.h"
#include "string_play.h"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

tape::tape(): //verified 4/14
    cells(" "),
    current_cell(0),
    blank_character(' ')
{
}

void tape::load(ifstream& definition, bool& valid) // verified 4/14
{
    definition.clear();           // Clear any EOF or fail flags
    definition.seekg(0);          // Rewind to beginning

    string line;
    while (getline(definition, line))
    {
        if (trim(line, " \t").empty())
            continue;

        stringstream parseme(line);
        string keyword, symbol;
        parseme >> keyword;

        if (to_uppercase_string(keyword) == "BLANK_CHARACTER:")
        {
            if ((parseme >> symbol) && (symbol.length() == 1) && (symbol[0] != '\\') && 
                (symbol[0] != '[') && (symbol[0] != ']') && (symbol[0] != '<') && 
                (symbol[0] != '>') && (symbol[0] >= '!') && (symbol[0] <= '~'))
            {
                blank_character = symbol[0];
                return;
            }
            else
            {
                cout << "ERROR: Illegal Blank Character. " << endl;
                valid = false;
                return;
            }
        }
    }

    cout << "ERROR: Missing or Incorrect BLANK_CHARACTER Keyword. " << endl;
    valid = false;
}

void tape::validate(const input_alphabet& input_alphabet,
                    const tape_alphabet& tape_alphabet,
                    bool& valid) const
{
    if (input_alphabet.is_element(blank_character))
    {
        cout << "Blank Character: " << blank_character << " is IN Input Alphabet. " << endl;
        valid = false;
    }

    if (!tape_alphabet.is_element(blank_character))
    {
        cout << "Blank Character: " << blank_character << " is NOT in Tape Alphabet." << endl;
        valid = false;
    }
}

void tape::view() const
{
    cout << "B = " << blank_character << "\n\n";
}

void tape::initialize(string input_string)
{
    cells = input_string + blank_character;
    current_cell = 0;
}

void tape::update(char write_character, direction move_direction)
{
    move_direction = toupper(move_direction);

    if ((move_direction == 'L') && (current_cell == 0))
        return;

    if ((move_direction == 'R') && (current_cell == cells.length() - 1))
    {
        cells += blank_character;
    }

    cells[current_cell] = write_character;

    if (move_direction == 'L')
        --current_cell;
    else
        ++current_cell;
}

string tape::left(int maximum_number_of_cells) const
{
    int first_cell = max(0, current_cell - maximum_number_of_cells);
    string value = cells.substr(first_cell, current_cell - first_cell);
    if (value.length() < static_cast<size_t>(current_cell))
        value.insert(0, "<");
    return value;
}

string tape::right(int maximum_number_of_cells) const
{
    int end_cell = cells.length() - 1;
    while ((end_cell >= current_cell) && (cells[end_cell] == blank_character))
        --end_cell;

    int last_cell = min(end_cell, current_cell + maximum_number_of_cells - 1);
    string value = cells.substr(current_cell, last_cell - current_cell + 1);

    if (value.length() < static_cast<size_t>(end_cell - current_cell + 1))
        value.append(">");
    return value;
}

char tape::current_character() const
{
    return cells[current_cell];
}

bool tape::is_first_cell() const
{
    return (current_cell == 0);
}

char tape::get_blank_character() const
{
    return blank_character;
}
