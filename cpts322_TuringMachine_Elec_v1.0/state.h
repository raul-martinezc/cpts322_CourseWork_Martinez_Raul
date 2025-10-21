//verified 4/14
#ifndef state_h
#define state_h

#include "string_pointer.h"
#include <string>

using namespace std;

class state
{
    private:
        string_pointer name;
        static int number_of_states;

    public:
        state();
        state(string state_name);
        state(const state& state);
        virtual ~state();

        state& operator=(const state& state);

        void get_name(string& state_name) const;
        void set_name(string state_name);

        static int total_number_of_states();
};

typedef state *state_pointer;

#endif
