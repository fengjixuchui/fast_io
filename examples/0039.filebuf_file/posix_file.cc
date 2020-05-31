#include"../../include/fast_io.h"
#include"../../include/fast_io_legacy_impl/cpp/filebuf_file.h"

int main()
{
	fast_io::posix_file nfl("posix_file.txt",fast_io::open_mode::binary|fast_io::open_mode::out);
	fast_io::filebuf_file fb(std::move(nfl),fast_io::open_mode::binary|fast_io::open_mode::out);
	std::ofstream out;
	out.std::ostream::rdbuf(fb.rdbuf());
	out<<"Hello world from std::ofstream\n";
	print(fb,"Hello World from fast_io\n");
	out<<"Hello world from std::ofstream again\n";
	print(fb,"Hello World from fast_io again\n");
}