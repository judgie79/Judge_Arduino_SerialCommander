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
	void onHelloCommand(String value);
	void onByeCommand(String value);
	void onAckCommand(String value);
	void onAlreadyConnectedCommand(String value);
	void onErrorCommand(String value);
	void onDebugCommand(String value);

	Command *command;
	bool commandReady = false;

	bool _isConnected = false;
protected:
	CommandStream* serialCmd;
	String getValue(String data, char separator, uint16_t index);
	virtual void readCmd(char key, String data);
};

#endif