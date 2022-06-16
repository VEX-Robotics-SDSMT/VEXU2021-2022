#ifndef _NULLLOGGER_H
#define _NULLLOGGER_H

#include "baseLogger.h"

class NullLogger : public BaseLogger
{
  public:
    NullLogger();
    ~NullLogger();
    void ClearAll();
    void AppendLine(char* text);

  private:

};

#endif