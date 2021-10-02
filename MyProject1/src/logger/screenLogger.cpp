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
    
    
void ScreenLogger::WriteLine(int line, std::string text)
{
  robotBrain->Screen.setCursor(line,0);
  std::string theText = text;
  robotBrain->Screen.print(theText);
}

