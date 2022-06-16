#include "screenLogger.h"


ScreenLogger::ScreenLogger()
{
  brain *bra = &Brain;
  robotBrain = bra;
  appendLine = 1;
}

ScreenLogger::ScreenLogger(brain &b)
{
  brain *bra = &b;
  robotBrain = bra;
  appendLine = 1;
}

ScreenLogger::~ScreenLogger()
{

}

void ScreenLogger::ClearAll()
{
  robotBrain->Screen.clearScreen();
  appendLine = 1;
}
    
void ScreenLogger::ClearLine(int line)
{
  if (line > MAX_SCREENLINE || line < 0)
  {
    return;
  }

  robotBrain->Screen.clearLine(line);
}
    
    
void ScreenLogger::WriteLine(int line, char* text)
{
  if (line > MAX_SCREENLINE || line < 0)
  {
    return;
  }

  robotBrain->Screen.clearLine(line);
  robotBrain->Screen.setCursor(line,2);
  robotBrain->Screen.print(text);
}

void ScreenLogger::AppendLine(char* text)
{
  if (appendLine > MAX_SCREENLINE)
  {
    ClearAll();
  }

  WriteLine(appendLine, text);
  appendLine++;
}

