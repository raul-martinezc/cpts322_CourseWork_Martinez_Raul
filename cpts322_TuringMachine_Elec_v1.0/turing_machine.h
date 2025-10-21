//verified on 4/14
#ifndef turing_machine_h
#define turing_machine_h

#include "tape.h"
#include "input_alphabet.h"
#include "tape_alphabet.h"
#include "transition_function.h"
#include "states.h"
#include "final_states.h"

#include <string>
#include <vector>

using namespace std;

class turing_machine
{
private:
    tape tape_data;
    input_alphabet input_alphabet_data;
    tape_alphabet tape_alphabet_data;
    transition_function transition_function_data;
    states states_data;
    final_states final_states_data;
    vector<string> description;
    string initial_state;
    string current_state;
    string original_input_string;
    int number_of_transitions;
    bool valid;
    bool used;
    bool operating;
    bool accepted;
    bool rejected;

public:
    turing_machine(string definition_file_name);

    void view_definition() const;
    void view_instantaneous_description(int maximum_number_of_cells) const;
    bool initialize(string input_string);
    void perform_transitions(int maximum_number_of_transitions);
    void terminate_operation();

    string input_string() const;
    int total_number_of_transitions() const;
    bool is_valid_definition() const;
    bool is_valid_input_string(string value) const;
    bool is_used() const;
    bool is_operating() const;
    bool is_accepted_input_string() const;
    bool is_rejected_input_string() const;
};

#endif
