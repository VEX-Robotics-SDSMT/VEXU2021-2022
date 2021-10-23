#include "fileLogger.h"

FileLogger::FileLogger()
{
  std::string fileName = DEFAULT_FILE_NAME;
  int n = fileName.length();
  char char_array[n + 1];
  strcpy(char_array, fileName.c_str());

  brain* brn = &Brain;
  brain::sdcard *sd = &brn->SDcard;
  robotBrain = brn;
  robotsd = sd;
  prntfname = char_array;

  bool hasSd = robotsd->isInserted();
  if (hasSd)                              
  {
    /*if (!robotsd->exists(prntfname))
    {
      uint8_t myTestData[ 100 ];
      for(int i=0;i<100;i++) 
      {
        myTestData[i] = i * 2;
      }
      robotsd->savefile(prntfname, myTestData, sizeof(myTestData));
    }*/
    outfile.open(prntfname);
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

FileLogger::FileLogger(char* filename)
{
  brain* brn = &Brain;
  brain::sdcard *sd = &brn->SDcard;
  robotBrain = brn;
  robotsd = sd;
  prntfname = filename;

  bool hasSd = robotsd->isInserted();
  if (hasSd)                              
  {
    outfile.open(prntfname);
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