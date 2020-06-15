#include"../../include/fast_io_device.h"
class dummy_output
{
public:
using char_type = char;
};

template<std::contiguous_iterator Iter>
constexpr void write(dummy_output,Iter,Iter){}


int main()
{
	static_assert(!fast_io::input_stream<fast_io::basic_obuf<dummy_output>>);
	static_assert(fast_io::buffer_input_stream<fast_io::basic_obuf<fast_io::ibuf_file>>);
	static_assert(fast_io::dynamic_buffer_output_stream<fast_io::internal_temporary_buffer<char>>);
}