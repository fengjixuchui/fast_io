#pragma once

namespace fast_io
{


inline void fast_terminate()
{
#ifndef FAST_IO_NOT_TERMINATE
	*(reinterpret_cast<char*>(0))=0;
#endif
	//create a null pointer hardware exception to terminate the program
//	fast_exit(-1);
}

}