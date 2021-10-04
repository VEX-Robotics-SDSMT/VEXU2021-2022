#include "fileLogger.h"

FileLogger::FileLogger()
{
  //Define a default file to output to please
  outfile.open("Kill me");
}

FileLogger::FileLogger(char* filename)
{
  brain *brn = &Brain;
  vex::brain::sdcard *sd = &brn->SDcard;
  bool hasSd = sd->isInserted();

}

void FileLogger::ClearAll()
{
  
}
    
void FileLogger::ClearLine(int line)
{
  
}
    
    
void FileLogger::WriteLine(int line, char* text)
{
  
}

void FileLogger::AppendLine(char* text)
{
  
}