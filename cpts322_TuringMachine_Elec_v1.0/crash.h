//verified on 4/14

#ifndef crash_h
#define crash_h

#include <stdexcept>
#include <string>

using namespace std;

class crash:public runtime_error

{
    public: 
        crash(string reason);
};

#endif