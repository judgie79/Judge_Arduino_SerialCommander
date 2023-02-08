#include "Stream.h"
#include "Arduino.h"
#include "CommandStream.h"
#include "Commands.h"

CommandStream::CommandStream(char *knownCommands, uint16_t knownCommandsLength)
{
  this->knownCommands = knownCommands;
  this->knownCommandsLength = knownCommandsLength;
}

void CommandStream::setOutput(Stream *output) {
  this->output = output;
}

bool CommandStream::isAvailable() {
  return this->output->available() > 0;
}

int CommandStream::available() {
  return this->output->available();
}

void CommandStream::readCmd()
{
  if (isAvailable()) {
    
    if (this->commandReady == false && this->currentIndex == 0)
    {
      // beginning of the transmission
      char cmdChar = this->output->peek();
      for (size_t i = 0; i < knownCommandsLength; i++) {
        if (knownCommands[i] == cmdChar) {
          // found command, create new
          cmdChar = this->output->read();
          this->currentCmdChar = cmdChar;
          this->currentIndex++;
        }
      }
    } else if (this->currentCmdChar != '\0' && this->commandReady == false && this->currentIndex > 0) {

      while (isAvailable()) {
          char next = this->output->read();
          if (next == CommandSeparator) {
            // do nothing
          } else if (next == '\n') {
            this->commandReady = true;
            lastStoredCmdChar = currentCmdChar;
            lastStoredCmdValue = currentCmdValue;
          } else {
            this->currentCmdValue += String(next);
          }
          this->currentIndex++;
        }
    } 
    
    if (this->currentCmdChar == '\0') {
      while (isAvailable()) {
        // echo loop for now
        // TODO allow hooks maybe
        String temp = this->output->readStringUntil('\n');
        
        temp.trim();
        if (temp != "") {
          debugPrintln(temp);
        }
      }
    }
  }
}
  bool CommandStream::isCommandReady()
  {
    return this->commandReady;
  }
  Command CommandStream::getCommand()
  {
    return Command(lastStoredCmdChar, lastStoredCmdValue);
  }
  void CommandStream::resetCommand()
  {
    this->commandReady = false;
    this->currentCmdChar = '\0';
    this->currentCmdValue = "";
    this->currentIndex = 0;
  }

void CommandStream::writeCommand(CommandKey key, String value) {
  this->output->println(GetCommand((char)key, value));
}

void CommandStream::writeCommand(char key, String value) {
  this->output->println(GetCommand(key, value));
}

void CommandStream::debugPrintln(String msg) {
  this->output->println(GetCommand((char)CommandKey::DEBUG, msg));
}