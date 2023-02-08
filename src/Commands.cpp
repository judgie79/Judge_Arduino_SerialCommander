#include "Commands.h"


String GetCommand(char key, String value)
{
  return String((char)key) + String((char)CommandSeparator) + String(value);
}