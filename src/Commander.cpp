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
        readCmd(cmd.key, cmd.value);
        this->serialCmd->resetCommand();
    }
}

void Commander::readCmd(char key, String data)
{
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

void Commander::onHelloCommand(String value)
{
    if (value != CommandToken)
    {
        serialCmd->writeCommand(CommandKey::ERROR, "invalid_token");
        return;
    }

    if (!_isConnected)
    {
        _isConnected = true;
        serialCmd->writeCommand(CommandKey::RECEIVED, CommandToken);
    }
    else
    {
        serialCmd->writeCommand(CommandKey::ALREADY_CONNECTED, CommandToken);
    }
}

void Commander::onByeCommand(String value)
{
    if (value != CommandToken)
    {
        serialCmd->writeCommand(CommandKey::ERROR, "invalid_token");
        return;
    }

    _isConnected = false;
}

void Commander::onAckCommand(String value)
{
}

void Commander::onAlreadyConnectedCommand(String value)
{
}

void Commander::onDebugCommand(String value)
{
  serialCmd->debugPrintln(value);
}

void Commander::onErrorCommand(String value)
{
    serialCmd->debugPrintln(value);
}

bool Commander::isConnected()
{
    return _isConnected;
}

String Commander::getValue(String data, char separator, uint16_t index)
{
    uint16_t maxIndex = data.length() - 1;
    uint16_t j = 0;
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
