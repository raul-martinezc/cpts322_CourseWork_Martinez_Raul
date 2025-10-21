//final?
#ifndef final_states_h
#define final_states_h

#include "final_state.h"
#include "states.h"

#include <vector>
#include <fstream>
#include <string>

class final_states
{
public:
    void load(std::ifstream& definition, bool& valid);
    void validate(const states& all_states, bool& valid) const;
    void view() const;
    bool is_element(const std::string& state) const;

private:
    std::vector<final_state> state_list;
};

#endif
