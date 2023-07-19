#ifndef Commander_h
#define Commander_h

#include "Arduino.h"
#include "CommandStream.h"
#include "Commands.h"

class Commander {
public:
	Commander();

	void begin(CommandStream* serialCommand);
	void read();
	bool isConnected();
private:
	void onHelloCommand(const char * value);
	void onByeCommand(const char * value);
	void onAckCommand(const char * value);
	void onAlreadyConnectedCommand(const char * value);
	void onErrorCommand(const char * value);
	void onDebugCommand(const char * value);

	Command *command;
	bool commandReady = false;

	bool _isConnected = false;
protected:
	CommandStream* serialCmd;
	String getValue(const char * data, uint16_t dataLength, char separator, uint8_t index);
	virtual void readCmd(char key, const char * data, uint8_t valueLength);
};

#endif