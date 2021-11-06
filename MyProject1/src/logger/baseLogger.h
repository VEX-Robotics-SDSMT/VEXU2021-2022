#ifndef _BASELOGGER_H
#define _BASELOGGER_H

#include "vex.h"

class BaseLogger {

public:
   virtual void ClearAll() = 0;
   virtual void AppendLine(char* text) = 0;

private:
};

#endif