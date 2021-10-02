#ifndef _CSVLOGGER_H
#define _CSVLOGGER_H

#include "baseLogger.h"

class CSVLogger : public BaseLogger
{
  public:
    CSVLogger();
    void ClearAll();
    void ClearLine(int line);
    void WriteLine(int line, std::string text);

  private:

};

#endif