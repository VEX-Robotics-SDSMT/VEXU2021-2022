#include "fileLogger.h"

FileLogger::FileLogger()
{
  //Define a default file to output to please
}

FileLogger::FileLogger(char* filename)
{
  brain *brn = &Brain;
  vex::brain::sdcard *sd = &brn->SDcard;
  bool hasSd = sd->isInserted();
}

void FileLogger::ClearAll()
{
  2 + 2;
}
    
void FileLogger::ClearLine(int line)
{
  2 + 2;
}
    
    
void FileLogger::WriteLine(int line, char* text)
{
  2 + 2;
}

void FileLogger::AppLine(char* text)
{
  2 + 2;
}