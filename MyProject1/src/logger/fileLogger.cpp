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
  prntfname = filename;
  if (hasSd)                              
  {
    outfile.open(filename);
    if (!outfile.is_open())               //If the file does not exist
    {
      //Throw error
      exit(1);
    }
  }
  else                                    //If there is no SD card inserted
  {
    //Throw error
    exit(1);
  }
}

FileLogger::~FileLogger()
{
  outfile.close();
}

//Clears the file
void FileLogger::ClearAll()
{
  std::ofstream truncfile;
  outfile.close();                                                      //Close the old file
  truncfile.open(prntfname, std::ofstream::out | std::ofstream::trunc); //Open the file clearing what's not added
  truncfile.close();                                                    //Close it, clearing the data
  outfile.open(prntfname);                                              //Reopen the output file to resume writing
}

//Removes the text at the given line
void FileLogger::ClearLine(int line)
{
  
}
    
//Inserts the line in the middle of the file at the given line 
//(but why would you use this over append?)
void FileLogger::WriteLine(int line, char* text)
{
  
}

//Prints the line at the bottom of the file
void FileLogger::AppendLine(char* text)
{
  outfile << text << '\n';
}