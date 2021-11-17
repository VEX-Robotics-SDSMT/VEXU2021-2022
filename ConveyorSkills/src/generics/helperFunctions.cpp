#include "helperFunctions.h"

bool pressButton(bool press, bool &debounce)
{
	if(press)
    {
        if(!debounce)
        {
            debounce = true;
            return true;
        }
    }
    else
    {
        debounce = false;
    }

    return false;
}


