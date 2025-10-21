//final?
#include "final_state.h"
#include "string_pointer.h"

int final_state::number_of_states = 0;

final_state::final_state()
{
    name = new std::string;
    ++number_of_states;
}

final_state::final_state(const std::string& state_name)
{
    name = new std::string(state_name);
    ++number_of_states;
}

final_state::final_state(const final_state& other)
{
    name = new std::string(*other.name);
    ++number_of_states;
}

final_state::~final_state()
{
    delete name;
    --number_of_states;
}

final_state& final_state::operator=(const final_state& other)
{
    if (this != &other)
    {
        *name = *other.name;
    }
    return *this;
}

void final_state::get_name(std::string& state_name) const
{
    state_name = *name;
}

void final_state::set_name(const std::string& state_name)
{
    *name = state_name;
}

int final_state::total_number_of_states()
{
    return number_of_states;
}
