#include "state.h"
#include <string>
#include <iostream>

using namespace std;

int main()
{
    const int success = 0;
    string name;

    state x;
    state y("s2");
    state z = y;
    state_pointer p = new state(z);

    x = *p;
    p->set_name("s3");
    delete p;

    x.get_name(name);
    cout << "Name of state x is " << name << ".\n";
    cout << "Total number of states is " << state::total_number_of_states() << ".\n";

    return success;
}
