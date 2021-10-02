#include "screenLogger.h"


ScreenLogger::ScreenLogger()
{
  brain *bra = &Brain;
  robotBrain = bra;
}

ScreenLogger::ScreenLogger(brain &b)
{
  brain *bra = &b;
  robotBrain = bra;
}

void ScreenLogger::ClearAll()
{
  robotBrain->Screen.clearScreen();
}
    
void ScreenLogger::ClearLine(int line)
{
  robotBrain->Screen.clearLine(line);
}
    
    
void ScreenLogger::WriteLine(int line, char* text)
{
  robotBrain->Screen.setCursor(line,2);
  robotBrain->Screen.print(text);
}

