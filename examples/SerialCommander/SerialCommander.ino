#include <CommandStream.h>
#include <Commands">

char knownCommands[3]={ (char)CommandKey::HELLO, (char)CommandKey::ERROR, (char)CommandKey::DEBUG };

CommandStream serialCmd(&Serial, knownCommands, 3);

void setup() {
    Serial.begin(9600);
    serialCmd.begin();
}

void loop() {
    if (serialCmd.isAvailable()) {
        serialCmd.debugPrintln(serialCmd.readCmd()->ToString());
    }
    delay(100);
}