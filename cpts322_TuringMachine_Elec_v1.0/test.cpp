/*

#include "tape.h"
#include "direction.h"

#include <exception>
#include <string>
#include <iostream>


using namespace std;

int main()
{
    const int success(0);
    tape tape;
    tape.initialize("AABB");
    try
    {
        tape.update('B','L');
    }
    catch(const exception& error)
    {
        cerr << error.what() << '\n';
    }
    tape.view();
    return success;
}


*/
//ask which one it is

/*
#include "state.h"
#include <string>
#include <iostream>

using namespace std;

int main()
{
    const int success = 0;
    string name;
    state first_state;
    state second_state = "s2";
    state third_state = second_state;
    state_pointer fourth_state_pointer = new state(third_state);
    first_state = *fourth_state_pointer;
    fourth_state_pointer -> set_name("s3");
    delete fourth_state_pointer;
    first_state.get_name(name);

    cout << "Name of First State is " << name << endl;
    cout << "Total NUmber of States is " << state::total_number_of_states() << endl;

    return success;
}
*/