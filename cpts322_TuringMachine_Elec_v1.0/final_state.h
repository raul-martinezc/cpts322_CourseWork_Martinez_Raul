//final?
#ifndef final_state_h
#define final_state_h

#include "string_pointer.h"
#include <string>

class final_state
{
private:
    string_pointer name;
    static int number_of_states;

public:
    final_state();
    final_state(const std::string& state_name);
    final_state(const final_state& other);
    virtual ~final_state();

    final_state& operator=(const final_state& other);

    void get_name(std::string& state_name) const;
    void set_name(const std::string& state_name);

    static int total_number_of_states();
};

typedef final_state* final_state_pointer;

#endif
