#ifndef _FILELOGGER_H
#define _FILELOGGER_H

#include "baseLogger.h"
#include "screenLogger.h"
#include <fstream>
#include <string>
const std::string DEFAULT_FILE_NAME = "DrivebaseLog.txt";

// Note: FileLogger does not work.
// Do not attempt to fix. The source of the issue is the VEX library. Issue as of December 2021
class FileLogger : public BaseLogger
{
  public:
    FileLogger();
    FileLogger(char* filename);
    ~FileLogger();
    void ClearAll();
    void AppendLine(char* text);

  private:
    brain *robotBrain;
    vex::brain::sdcard *robotsd;
    char* prntfname;
    ScreenLogger *screenLog;


};

#endif