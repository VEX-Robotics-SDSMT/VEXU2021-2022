#ifndef _SCREENLOGGER_H
#define _SCREENLOGGER_H

#include "vex.h"
#include "baseLogger.h"

class ScreenLogger : public BaseLogger
{
  brain *robotBrain;

  public:
    ScreenLogger();
    ScreenLogger(brain &);
    void ClearAll();
    void ClearLine(int line);
    void WriteLine(int line, std::string text);

  private:

};

#endif