#include<ostream>
#include"../../include/fast_io.h"
#include"../../include/fast_io_legacy_impl/cpp/streambuf_io_observer.h"

namespace fast_io
{
template<typename T>
inline std::ostream& wrapped_function(std::ostream& out,T v)
{
	fast_io::streambuf_io_observer iob{out.rdbuf()};
	print(iob,v);
	return out;
}
}

extern "C" std::ostream& __wrap__ZNSolsEi(std::ostream& out,int v)
{
	return fast_io::wrapped_function(out,v);
}

extern "C" std::ostream& __wrap__ZNSo9_M_insertIyEERSoT_(std::ostream& out,unsigned long long v)
{
	return fast_io::wrapped_function(out,v);
}

extern "C" void __wrap__ZNSt14basic_ofstreamIcSt11char_traitsIcEED1Ev(std::ofstream& out)
{
//	fast_io::filebuf_io_observer fiob{out.rdbuf()};

//	static_cast<>
//	fast_io::c_file cf{static_cast<>};
}