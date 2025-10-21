//final?
#include "turing_machine.h"
#include "uppercase.h"
#include "crash.h"
#include "string_play.h"

#include <fstream>
#include <sstream>
#include <iostream>

turing_machine::turing_machine(std::string definition_file_name)
{
    used = false;
    valid = true;
    accepted = false;
    rejected = false;

    std::ifstream definition(definition_file_name.c_str());
    if (!definition)
    {
        std::cout << "Error: Could NOT Open: " << definition_file_name << std::endl;
        valid = false;
        return;
    }

    // Load each section
    definition.clear(); definition.seekg(0);
    states_data.load(definition, valid); if (!valid) return;

    definition.clear(); definition.seekg(0);
    input_alphabet_data.load(definition, valid); if (!valid) return;

    definition.clear(); definition.seekg(0);
    tape_alphabet_data.load(definition, valid); if (!valid) return;

    definition.clear(); definition.seekg(0);
    transition_function_data.load(definition, valid); if (!valid) return;

    // Load initial state
    std::string line, keyword;
    std::streampos pos = definition.tellg();
    while (std::getline(definition, line) && trim(line, " \t").empty());

    std::stringstream parse_line(line);
    parse_line >> keyword;

    if (uppercase_string(keyword) != "INITIAL_STATE:")
    {
        definition.seekg(pos, std::ios::beg);
        std::cout << "ERROR: Initial State NOT Defined. " << std::endl;
        valid = false;
        return;
    }
    else
    {
        parse_line >> initial_state;
    }

    definition.clear(); definition.seekg(0);
    tape_data.load(definition, valid); if (!valid) return;

    definition.clear(); definition.seekg(0);
    final_states_data.load(definition, valid); if (!valid) return;

    // Additional Validation
    if (valid)
    {
        if (!states_data.is_element(initial_state))
        {
            valid = false;
            std::cout << "Initial State '" << initial_state << "' is NOT in the Set-of-States. " << std::endl;
        }

        if (input_alphabet_data.is_element(tape_data.get_blank_character()))
        {
            valid = false;
            std::cout << "Input Alphabet should NOT contain the Blank Character. " << std::endl;
        }

        if (!tape_alphabet_data.is_element(tape_data.get_blank_character()))
        {
            valid = false;
            std::cout << "Tape Alphabet MUST contain the Blank Character. " <<std::endl;
        }

        transition_function_data.validate(tape_alphabet_data, states_data, final_states_data, valid);
    }

    std::cout << std::endl;
    //std::cout << "Turing Machine " << definition_file_name << (valid ? " Successfully Loaded.\n" : " Failed to Load Due to Errors. \n");

    definition.close();
}

void turing_machine::view_definition() const
{
    std::cout << "Definition of Turing Machine:\n";
    states_data.view();
    input_alphabet_data.view();
    tape_alphabet_data.view();
    transition_function_data.view();
    std::cout << "q0 = " << initial_state << "\n\n";
    tape_data.view();
    final_states_data.view();
}

void turing_machine::view_instantaneous_description(int max_cells) const
{
    std::cout << tape_data.left(max_cells)
              << "[" << current_state << "]"
              << tape_data.right(max_cells) << "\n\n";
}

bool turing_machine::initialize(std::string input)
{
    if (used)
    {
        std::cout << "You Must Terminate the Currently Running Machine to Start a New One " << std::endl;
        std::cout << std::endl;
        return false;
    }

    original_input_string = input;
    current_state = initial_state;
    tape_data.initialize(input);

    number_of_transitions = 0;
    operating = true;
    used = true;
    accepted = false;
    rejected = false;

    return true;
}

void turing_machine::perform_transitions(int max_transitions)
{
    if (final_states_data.is_element(current_state))
    {
        operating = false;
        accepted = true;
        used = false;
        return;
    }

    std::string next_state;
    char write_char;
    direction move_dir;
    bool found = false;

    for (int i = 0; i < max_transitions && operating; i++)
    {
        transition_function_data.find_transition(
            current_state,
            tape_data.current_character(),
            next_state,
            write_char,
            move_dir,
            found
        );

        if (!found)
        {
            rejected = true;
            operating = false;
            used = false;
            return;
        }

        number_of_transitions++;
        tape_data.update(write_char, move_dir);
        current_state = next_state;

        if (final_states_data.is_element(current_state))
        {
            operating = false;
            accepted = true;
            used = false;
            return;
        }
    }
}

void turing_machine::terminate_operation()
{
    if (operating)
    {
        operating = false;
        used = false;
        accepted = false;
        rejected = false;
    }
}

std::string turing_machine::input_string() const
{
    return original_input_string;
}

int turing_machine::total_number_of_transitions() const
{
    return number_of_transitions;
}

bool turing_machine::is_valid_definition() const
{
    return valid;
}

bool turing_machine::is_valid_input_string(std::string value) const
{
    for (char ch : value)
    {
        if (!input_alphabet_data.is_element(ch))
            return false;
    }
    return true;
}

bool turing_machine::is_used() const
{
    return used;
}

bool turing_machine::is_operating() const
{
    return operating;
}

bool turing_machine::is_accepted_input_string() const
{
    return accepted;
}

bool turing_machine::is_rejected_input_string() const
{
    return rejected;
}
