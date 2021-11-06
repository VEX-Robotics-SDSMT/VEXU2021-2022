#ifndef _SCREENLOGGER_H
#define _SCREENLOGGER_H

#include "baseLogger.h"
const int MAX_SCREENLINE = 15;

class ScreenLogger : public BaseLogger
{
  public:
    ScreenLogger();
    ScreenLogger(brain &);
    ~ScreenLogger();
    void ClearAll();
    void ClearLine(int line);
    void WriteLine(int line, char* text);
    void AppendLine(char* text);

  private:
    brain *robotBrain;
    int appendLine;
};

#endif