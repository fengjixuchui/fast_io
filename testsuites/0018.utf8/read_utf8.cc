#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"
#include"../../include/fast_io_legacy.h"

int main()
{
	constexpr std::size_t N{10000000};
	char32_t test_character(U'🚄');
	{
	fast_io::obuf_utf8_file<char32_t> fout("utf_file.txt");
	for(std::size_t i{};i!=N;++i)
		put(fout,test_character);
	print(fout,fast_io::fill_nc(N,test_character));
	}
	{
	fast_io::ibuf_utf8_file<char32_t> fin("utf_file.txt");
	std::size_t n{};
	for(auto ch:fast_io::igenerator(fin))
	{
		if(ch!=test_character)
		{
			print("failed: incorrect character {",ch,"}\n");
			return 1;
		}
		++n;
	}
	if(n==2*N)
		print("success\n");
	else
	{
		println("failed:incorrect number {",n,"}, should be ",N);
		return 2;
	}
	}
	{
	fast_io::ibuf_utf8_file<char32_t> fin("utf_file.txt");
	fast_io::obuf_utf8_file<char32_t> fout("utf2_file.txt");
	transmit(fout,fin);
	}
}