#include "fileLogger.h"

FileLogger::FileLogger()
{
  FileLogger(DEFAULT_FILE_NAME);
  /*
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
    if (!robotsd->exists(prntfname))
    {
      uint8_t myTestData[ 100 ];
      for(int i=0;i<100;i++) 
      {
        myTestData[i] = i * 2;
      }
      robotsd->savefile(prntfname, myTestData, sizeof(myTestData));
    }
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
  }*/
}

FileLogger::FileLogger(char* filename)
{
  brain* brn = &Brain;
  robotBrain = brn;
  screenLog = new ScreenLogger();
  brain::sdcard *sd = &robotBrain->SDcard;
  robotsd = sd;
  prntfname = filename;

  bool hasSd = robotsd->isInserted();
  if (hasSd)                              
  {
    screenLog->WriteLine(1, "SD card inserted");
    if(!sd->exists(filename))             //If there is no file by the given name
    {
      screenLog->WriteLine(2, "File can not be Opened");
      exit(1);
    }
    else
    {
      screenLog->WriteLine(2, "File exists");
    }
  }
  else                                    //If there is no SD card inserted
  {
    //Throw error
    screenLog->WriteLine(1, "SD Card not found");
    exit(1);
  }
}

FileLogger::~FileLogger()
{
    delete screenLog;
}

//Clears the file
void FileLogger::ClearAll()
{
  robotsd->savefile(prntfname, 0, 0);         //Save an empty buffer to the file?
}

//Prints the line at the bottom of the file
void FileLogger::AppendLine(char* text)
{
  uint8_t data[ 100 ];
      for(int i=0;i<100;i++) 
      {
        data[i] = i * 2;
      }
  Brain.SDcard.savefile(prntfname, data, sizeof(data));
  screenLog->AppendLine("Saved File");
  /*uint8_t data[ 100 ];
  robotsd->loadfile(prntfname, data, sixeof(data));
  screenLog->AppendLine((char*)data);*/
}