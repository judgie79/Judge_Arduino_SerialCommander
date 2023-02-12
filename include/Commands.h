#ifndef COMMANDS_H
#define COMMANDS_H

#include "Arduino.h"

// Define the Commands that can be sent and received
enum class CommandKey: char {
  HELLO = 'h',              // Hello order to initiate communication with the Arduino
  ALREADY_CONNECTED = 'c',  // Already connected to the Arduino
  ERROR = 'e',
  RECEIVED = 'r',  // Aknowlegment message
  BYE = 'x',  // close
  DEBUG = 'l', // debug message
};

const char CommandSeparator = '#';
const char CommandValueSeparator = ',';
const String CommandToken = "2425";

const char * GetCommand(char key, String value);

struct Command
{
  Command(  char mKey, String mValue)
  {
    key = mKey;
    value = mValue;
  }
  void AddToValue(char newChar)
  {
    value += String(newChar);
  }

  char key;
  String value;
};

#endif