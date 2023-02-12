#include "Commands.h"


const char * GetCommand(char key, String value)
{
  char temp[2 + value.length() - 1] = "";
  temp[0] = key;
  temp[1] = CommandSeparator;
  for (size_t i = 2; i < value.length() - 1; i++)
  {
    
    temp[i] = value[i];
  }
  

  return temp;
}