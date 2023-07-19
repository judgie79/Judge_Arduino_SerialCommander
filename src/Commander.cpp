#include "Arduino.h"
#include "Commander.h"

Commander::Commander()
{
};

void Commander::begin(CommandStream* serialCommand)
{
    this->serialCmd = serialCommand;
}

void Commander::read()
{
    if (!this->serialCmd->isCommandReady()) {
        this->serialCmd->readCmd();
    } else {
        Command cmd = this->serialCmd->getCommand();
        readCmd(cmd.key, cmd.value.c_str(), cmd.value.length());
        this->serialCmd->resetCommand();
    }
}

void Commander::readCmd(char key, const char * data, uint8_t valueLength)
{
    // Serial.println("TEST");
    if (key != (char)CommandKey::HELLO && !_isConnected)
    {
        // no connection, only allow hello
        return;
    }

    switch (key)
    {
    case (char)CommandKey::HELLO:
        onHelloCommand(data);
        break;
    case (char)CommandKey::ALREADY_CONNECTED:
        onAlreadyConnectedCommand(data);
        break;
    case (char)CommandKey::DEBUG:
        onDebugCommand(data);
        break;
    case (char)CommandKey::RECEIVED:
        break;
    case (char)CommandKey::BYE:
        onByeCommand(data);
        break;
    case (char)CommandKey::ERROR:
        onErrorCommand(data);
        break;
    default:
        break;
    }
}

void Commander::onHelloCommand(const char * value)
{
    if (strcmp(value, CommandToken.c_str()) != 0)
    {
        serialCmd->writeCommand(CommandKey::ERROR, value);
        return;
    }

    if (!_isConnected)
    {
        _isConnected = true;
        serialCmd->writeCommand(CommandKey::RECEIVED, CommandToken.c_str());
    }
    else
    {
        serialCmd->writeCommand(CommandKey::ALREADY_CONNECTED, CommandToken.c_str());
    }
}

void Commander::onByeCommand(const char * value)
{
    if (strcmp(value, CommandToken.c_str()) != 0)
    {
        serialCmd->writeCommand(CommandKey::ERROR, "invalid_token");
        return;
    }

    _isConnected = false;
}

void Commander::onAckCommand(const char * value)
{
}

void Commander::onAlreadyConnectedCommand(const char * value)
{
}

void Commander::onDebugCommand(const char * value)
{
  serialCmd->debugPrintln(value);
}

void Commander::onErrorCommand(const char * value)
{
    serialCmd->debugPrintln(value);
}

bool Commander::isConnected()
{
    return _isConnected;
}

String Commander::getValue(const char * data, uint16_t dataLength, char separator, uint8_t index)
{
    uint8_t maxIndex = dataLength - 1;
    uint8_t j = 0;
    String chunkVal = "";

    for (size_t i = 0; i <= maxIndex && j <= index; i++)
    {
        chunkVal.concat(data[i]);

        if (data[i] == separator)
        {
            j++;

            if (j > index)
            {
                chunkVal.trim();
                return chunkVal;
            }

            chunkVal = "";
        }
        else if ((i == maxIndex) && (j < index))
        {
            chunkVal = "";
            return chunkVal;
        }
    }

    return chunkVal;
}
