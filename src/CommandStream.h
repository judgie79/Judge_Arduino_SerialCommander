#ifndef JSerial_h
#define JSerial_h

#include "Arduino.h"
#include "Commands.h"

class CommandStream
{
public:
  CommandStream(char *knownCommands, uint16_t knownCommandsLength);
  void setOutput(Stream * output);
  bool isAvailable();
  int available();

  void readCmd();
  bool isCommandReady();
  void resetCommand();
  Command getCommand();

  void writeCommand(CommandKey key, String value);
  void writeCommand(char key, String value);

  void debugPrintln(String s);

private:
  bool is_connected;
  Stream *output;

  char *knownCommands;
  uint16_t knownCommandsLength;

	bool commandReady = false;
  
  uint8_t currentIndex = 0;
  char currentCmdChar = '\0';
  String currentCmdValue;

  char lastStoredCmdChar = '\0';
  String lastStoredCmdValue;
};
#endif