//final?
#include "turing_machine.h"
#include "visible.h"

#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <cctype>

using namespace std;

// --- Utility Functions ---
//C++
char get_key_input()
{
    char str[1024];
    cin.getline(str, 1024);
    if (str[0] == '\0') return '-';
    if (str[1] != '\0') return '\0';
    return str[0];
}

void show_help()
{
    cout << endl;
    cout << "---------------------------------------------------------------" << endl;
    cout << "Input Chars |Commands    |Description                          " << endl;
    cout << "---------------------------------------------------------------" << endl;
    cout << "    (D)     |Delete      |Delete input string from list        " << endl;
    cout << "    (X)     |Exit        |Exit application                     " << endl;
    cout << "    (H)     |Help        |Help user                            " << endl;
    cout << "    (I)     |Insert      |Insert input string into list        " << endl;
    cout << "    (L)     |List        |List input strings                   " << endl;
    cout << "    (Q)     |Quit        |Quit operation of Turing machine     " << endl;
    cout << "    (R)     |Run         |Run Turing machine on input string   " << endl;
    cout << "    (E)     |Set         |Set number of transitions to perform " << endl;
    cout << "    (W)     |Show        |Show status of application           " << endl;
    cout << "    (T)     |Truncate    |Truncate instantaneous descriptions  " << endl;
    cout << "    (V)     |View        |View Turing machine definition       " << endl;
    cout << "---------------------------------------------------------------" << endl;
    cout << endl;
}

void show_banner()
{
    cout << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "  ********  CPT_S 322 Turing Machine Simulator  *********   " << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "         Created by: Raul Y. Martinez, 4/8/2025             " << endl;
    cout << "    for CPT_S 322 S2025 w/ Dr. Niel B. Corrigan @ WSU-TC    " << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl;
}

void show_loading_animation(const string& message = "Loading", int dots = 4)
{
    cout << message;
    cout.flush();
    for (int i = 0; i < dots; ++i)
    {
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << "." << flush;
    }
    cout << endl << endl;
}

bool read_index(const string& prompt, int& index)
{
    cout << prompt;
    cin >> index;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid Input, Please Enter an Integer." << endl;
        return false;
    }
    cin.ignore();
    return true;
}

// --- Main Program ---

int main(int argc, char* argv[])
{
    const int success = 0;

    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " tm" << endl;
        cout << "NOTE: The Proper Way to Start This Program is With './tm anbn', (anbn) Will Automatically Link Both .def and .str Files of Name anbn.def/.str." << endl;
        return success;
    }

    try
    {
        int transitions_per_run = 1;
        bool help_enabled = true;
        int max_characters = 32;

        vector<string> list_of_input_strings;
        string def_file = string(argv[1]) + ".def";
        string str_file = string(argv[1]) + ".str";

        turing_machine tm(def_file);
        if (!tm.is_valid_definition()) return success;

        cout << endl;
        show_loading_animation();
        cout << endl;
        show_banner();
        show_help();
        cout << endl;
        cout << "Turing Machine Loaded Successfully! " << endl;
        cout << endl;

        ifstream input_stream(str_file);
        if (input_stream.good())
        {
            string line;
            int line_num = 1;
            while (getline(input_stream, line))
            {
                if (tm.is_valid_input_string(line))
                    list_of_input_strings.push_back(line);
                else
                    cout << "Input File: Ignored Bad Line: # " << line_num << endl;
                ++line_num;
            }
            input_stream.close();
        }

        char command;
        bool changes_made = false;

        do
        {
            cout << "COMMAND: ";
            command = tolower(get_key_input());

            int index = 0;
            int new_value = 0;
            bool init_success = true;
            string input;

            switch (command)
            {
                case 'd':
                    if (help_enabled)
                        cout << "Enter an Index (1 - " << list_of_input_strings.size() << ") to Delete:" << endl;
                    if (read_index("Delete Index: ", index) &&
                        index >= 1 && index <= list_of_input_strings.size())
                    {
                        list_of_input_strings.erase(list_of_input_strings.begin() + index - 1);
                        changes_made = true;
                    }
                    else cout << "Invalid Index." << endl;
                    break;

                case 'x':
                    break;

                case 'h':
                    help_enabled = !help_enabled;
                    cout << "Help " << (help_enabled ? "Enabled" : "Disabled") << "." << endl;
                    if (help_enabled) show_help();
                    break;

                case 'i':
                    if (help_enabled)
                        cout << "Enter a String With Valid Input Alphabet Characters:" << endl;
                    cout << "Enter String: ";
                    getline(cin, input);
                    if (tm.is_valid_input_string(input))
                    {
                        list_of_input_strings.push_back(input);
                        changes_made = true;
                        cout << "String Inserted at Position " << list_of_input_strings.size() << endl;
                    }
                    else cout << "Invalid Input String." << endl;
                    break;

                case 'l':
                    if (help_enabled)
                        cout << "List of Input Strings:" << endl;
                    for (size_t i = 0; i < list_of_input_strings.size(); ++i)
                        cout << (i + 1) << ": " << visible(list_of_input_strings[i]) << endl;
                    break;

                case 'q':
                    if (help_enabled)
                        cout << "Terminating Current Turing Machine" << endl;
                    tm.terminate_operation();
                    cout << "Quitting. ";
                    if (tm.is_accepted_input_string())
                        cout << "String Accepted";
                    else if (tm.is_rejected_input_string())
                        cout << "String Rejected";
                    else
                        cout << "String Not Accepted, OR Rejected ";
                    cout << " In " << tm.total_number_of_transitions() << " Transitions." << endl;
                    break;

                case 'r':
                    if (help_enabled)
                        cout << "Running Turing Machine..." << endl;
                    if (!tm.is_used())
                    {
                        if (list_of_input_strings.empty())
                            cout << "No Input Strings Available." << endl;
                        else
                        {
                            if (help_enabled)
                                {
                                    cout << "Select a String Index to Run:" << endl;
                                    cout << endl;
                                    cout << "List of Input Strings:" << endl;
                                    for (size_t i = 0; i < list_of_input_strings.size(); ++i)
                                        cout << (i + 1) << ": " << visible(list_of_input_strings[i]) << endl << endl;
                                }
                                
                            if (read_index("Select Input String: ", index) &&
                                index >= 1 && index <= list_of_input_strings.size())
                            {
                                init_success = tm.initialize(list_of_input_strings[index - 1]);
                            }
                            else
                            {
                                cout << "Invalid Index." << endl;
                                break;
                            }
                        }
                    }
                    if (tm.is_used() && init_success)
                    {
                        if (tm.total_number_of_transitions() == 0)
                        {
                            cout << "0. ";
                            tm.view_instantaneous_description(max_characters);
                        }
                        tm.perform_transitions(transitions_per_run);
                        cout << tm.total_number_of_transitions() << ". ";
                        tm.view_instantaneous_description(max_characters);
                        if (!tm.is_operating())
                        {
                            cout << (tm.is_accepted_input_string() ? "Accepted " : "Rejected ")
                                 << "String \"" << tm.input_string() << "\" in "
                                 << tm.total_number_of_transitions() << " Transitions." << endl;
                        }
                    }
                    break;

                case 'e':
                    if (help_enabled)
                        cout << "Set Transitions Per Run (Current: " << transitions_per_run << "):" << endl;
                    if (read_index("New Nalue: ", new_value) && new_value > 0)
                        transitions_per_run = new_value;
                    else cout << "Value MUST be a Positive Integer." << endl;
                    break;

                case 'w':
                    if (help_enabled) cout << endl;
                    cout << "------ Program Info ------" << endl;
                    cout << "CPT_S 322 - Spring 2025" << endl;
                    cout << "Dr. Corrigan @ WSU Tri-Cities" << endl;
                    cout << "Author: Raul Y. Martinez" << endl;
                    cout << "Help: " << (help_enabled ? "ON" : "OFF") << endl;
                    cout << "Max Characters Displayed: " << max_characters << endl;
                    cout << "Transitions Per Run: " << transitions_per_run << endl;
                    cout << "Version: 1.0 Beta" << endl;
                    cout << "Current String: \"" << tm.input_string() << "\" after " << tm.total_number_of_transitions() << " transitions." << endl;
                    break;

                case 't':
                    if (help_enabled)
                        cout << "Set Display Truncation (Current: " << max_characters << "):" << endl;
                    if (read_index("New Truncation: ", new_value) && new_value > 0)
                        max_characters = new_value;
                    else cout << "Must be a Positive Integer." << endl;
                    break;

                case 'v':
                    if (help_enabled)
                        cout << "Turing Machine Definition: " << endl;
                    tm.view_definition();
                    break;

                case '-':
                    break;

                default:
                    cout << "Unknown Command." << endl;
                    if (!help_enabled)
                        cout << "HINT: Press 'h' to Enable Help." << endl;
                    break;
            }

            cout << endl;
        }
        while (command != 'x');

        show_loading_animation("Exiting");

        if (changes_made)
        {
            ofstream out(str_file);
            for (const string& str : list_of_input_strings)
                out << str << endl;
            cout << "Saved Updated Input Strings To: " << str_file << endl;
        }
    }
    catch (exception& e)
    {
        cout << "Exception: " << e.what() << endl;
    }

    return success;
}
