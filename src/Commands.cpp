#include "Commands.h"


const String GetCommand(char key, String value)
{
  String temp = String(key);
  temp += String(CommandSeparator);
  temp += String(value);

  return temp;
}