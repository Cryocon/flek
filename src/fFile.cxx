#include <Flek/fFile.h>

void LoToHi (ulong *buffer, int len)
{
  char* cbuffer = (char*)buffer;
  register ulong  value;
  for (register int i=0; i<len; i++, cbuffer+=4)
    {
      value = buffer[i];
      cbuffer[0] = ((value >> 24) & 0xff);
      cbuffer[1] = ((value >> 16) & 0xff);
      cbuffer[2] = ((value >> 8) & 0xff);
      cbuffer[3] = ((value & 0xff));
    }
}
