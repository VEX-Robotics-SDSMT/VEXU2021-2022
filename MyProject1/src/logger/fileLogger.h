#ifndef _FILELOGGER_H
#define _FILELOGGER_H

#include "baseLogger.h"
#include <fstream>
#include <string>
const std::string DEFAULT_FILE_NAME = "DrivebaseLog.txt";

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
    std::ofstream outfile;
    char* prntfname;


};

#endif