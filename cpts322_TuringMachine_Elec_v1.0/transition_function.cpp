//final?
#include "transition_function.h"
#include "transition.h"
#include "tape_alphabet.h"
#include "states.h"
#include "final_states.h"
#include "direction.h"
#include "uppercase.h"
#include "string_play.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

void transition_function::load(ifstream& definition, bool& valid)
{
    string line;
    string token;
    stringstream parseme;

    // Look for "TRANSITION_FUNCTION:"
    while (getline(definition, line))
    {
        if (trim(line, " \t").empty()) continue;

        parseme.clear();
        parseme.str(line);
        parseme >> token;

        if (uppercase_string(token) == "TRANSITION_FUNCTION:")
            break;
    }

    if (uppercase_string(token) != "TRANSITION_FUNCTION:")
    {
        cout << "ERROR: Transition Function Section Either; NOT defined OR Incorrect Location. " << endl;
        valid = false;
        return;
    }

    // Load transitions
    while (getline(definition, line))
    {
        if (trim(line, " \t").empty())
            continue;

        parseme.clear();
        parseme.str(line);

        string source_state;
        char read_char;
        string destination_state;
        char write_char;
        string direction_token;

        if (!(parseme >> source_state >> read_char >> destination_state >> write_char >> direction_token))
        {
            if (uppercase_string(source_state) == "INITIAL_STATE:")
            {
                definition.seekg(-(streamoff)line.length() - 1, ios::cur);
                break;
            }

            cout << "ERROR: Malformed Transition Line: " << line << endl;
            valid = false;
            continue;
        }

        // Validate direction character
        char dir_char = toupper(direction_token[0]);
        if (dir_char != 'L' && dir_char != 'R' && dir_char != 'S')
        {
            cout << "ERROR: Invalid Direction Symbol in Transition: " << direction_token << " (line: " << line << ")" << endl;;
            valid = false;
            continue;
        }

        try
        {
            transition t(source_state, read_char, destination_state, write_char, dir_char);
            transitions.push_back(t);
        }
        catch (...)
        {
            cout << "ERROR: Exception Occurred While Creating Transition from Line: " << line << endl;
            valid = false;
        }
    }
}

void transition_function::validate(const tape_alphabet& tape_alphabet,
                                   const states& states,
                                   const final_states& final_states,
                                   bool& valid) const
{
    for (const auto& t : transitions)
    {
        if (final_states.is_element(t.source_state()))
        {
            cout << "Source State '" << t.source_state() << "' is IN final states. " << endl;
            valid = false;
        }
        if (!states.is_element(t.source_state()))
        {
            cout << "Source State '" << t.source_state() << "' is NOT in states. " << endl;
            valid = false;
        }
        if (!tape_alphabet.is_element(t.read_character()))
        {
            cout << "Read Character '" << t.read_character() << "' is NOT in tape alphabet. " << endl;
            valid = false;
        }
        if (!states.is_element(t.destination_state()))
        {
            cout << "Destination State '" << t.destination_state() << "' is NOT in states. " << endl;
            valid = false;
        }
        if (!tape_alphabet.is_element(t.write_character()))
        {
            cout << "Write Character '" << t.write_character() << "' is NOT in tape alphabet. " << endl;
            valid = false;
        }
    }
}

void transition_function::view() const
{
    cout << "Transitions: " << endl;
    for (const auto& t : transitions)
    {
        cout << "δ(" << t.source_state() << ", " << t.read_character() << ") = ("
             << t.destination_state() << ", " << t.write_character() << ", " << t.move_direction() << ")" << endl;
    }
    cout << endl;
}

void transition_function::find_transition(string source_state,
                                          char read_character,
                                          string& destination_state,
                                          char& write_character,
                                          direction& move_direction,
                                          bool& found) const
{
    for (const auto& t : transitions)
    {
        if (t.source_state() == source_state && t.read_character() == read_character)
        {
            destination_state = t.destination_state();
            write_character = t.write_character();
            move_direction = t.move_direction();
            found = true;
            return;
        }
    }
    found = false;
}
