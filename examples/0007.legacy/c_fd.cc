#include"../../include/fast_io_legacy.h"
#include"../../include/fast_io.h"
#include<cstdio>

int main()
{
	fast_io::c_io_observer fiob{stdout};
	println("stdout:",
		"\nFILE*:",fiob,
		"\nfd:",static_cast<fast_io::posix_io_observer>(fiob)
#if defined(__WINNT__) || defined(_MSC_VER)
		,"\nwin32 HANDLE:",static_cast<fast_io::win32_io_observer>(fiob),
		"\nnt HANDLE:",static_cast<fast_io::nt_io_observer>(fiob)
#endif
);
}