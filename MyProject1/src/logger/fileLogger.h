#ifndef _FILELOGGER_H
#define _FILELOGGER_H

#include "baseLogger.h"
#include <fstream>

class FileLogger : public BaseLogger
{
  public:
    FileLogger();
    FileLogger(char* filename);
    void ClearAll();
    void ClearLine(int line);
    void WriteLine(int line, char* text);
    void AppLine(char* text);

  private:
    std::ofstream outfile;

};

#endif