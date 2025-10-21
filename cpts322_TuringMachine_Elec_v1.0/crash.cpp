//verified on 4/14

#include "crash.h"

#include <stdexcept>
#include <string>

using namespace std;

crash::crash(string reason):
    runtime_error(reason.c_str())
    {

    }