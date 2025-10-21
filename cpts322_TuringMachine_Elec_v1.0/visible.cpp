//final?
#include "visible.h"
#include <string>
using namespace std;

// makes empty strings that are the strings to run on visible
string visible(string value)
{
    const string lambda("\\");
    if(value.empty())
        value=lambda;
    return value;
}
