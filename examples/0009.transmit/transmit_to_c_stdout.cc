#include"../../include/fast_io_legacy.h"

int main()
{
	transmit(fast_io::c_stdout,fast_io::in);
}
/*
Transmit from fast_io::in to C stdout (Which means exploit the internal implementation of C stdout's buffer)

Should be zero copy IO on linux.

However, without redirection, zero copy will not work.

My solution is that when zero copy fails, try to use default buffer copy scheme.
*/