#include <msvcrti.h>


void _purecall(void)
{
   _amsg_exit(_RT_PUREVIRT);
}
