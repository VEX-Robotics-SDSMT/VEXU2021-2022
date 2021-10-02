#ifndef _SCREENLOGGER_H
#define _SCREENLOGGER_H

#include "vex.h"

class ScreenLogger
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