#include"../../include/fast_io_device.h"

int main()
{
	constexpr std::size_t N{20};
	{
	fast_io::obuf_file obf("fast_io.cc");
	print(obf,"#include\"../../include/fast_io.h\"\n\nint main()\n{\n\tstd::size_t a,b;\n\tscan(a,b);\n");
	for(std::size_t i{};i!=N;++i)
		print(obf,"\tprintln(a+b);\n");
	put(obf,u8'}');
	}
	{
	fast_io::obuf_file obf("fast_io_c_io_observer.cc");
	print(obf,"#include\"../../include/fast_io.h\"\n\nint main()\n{\n\tstd::size_t a,b;\n\tscan(a,b);\n\tfast_io::c_io_observer stdout_iob{stdout};\n");
	for(std::size_t i{};i!=N;++i)
		print(obf,"\tprintln(stdout_iob,a+b);\n");
	put(obf,u8'}');
	}
	{
	fast_io::obuf_file obf("fmt.cc");
	print(obf,"#include<fmt/format.h>\n#include<cstdio>\nint main()\n{\n\tstd::size_t a,b;\n\tscanf(\"%zu%zu\",&a,&b);\n");
	for(std::size_t i{};i!=N;++i)
		print(obf,"\tfmt::print(stdout,\"{}\\n\",a+b);\n");
	put(obf,u8'}');
	}
	{
	fast_io::obuf_file obf("printf.cc");
	print(obf,"#include<cstdio>\nint main()\n{\n\tstd::size_t a,b;\n\tscanf(\"%zu%zu\",&a,&b);\n");
	for(std::size_t i{};i!=N;++i)
		print(obf,"\tprintf(\"%zu\\n\",a+b);\n");
	put(obf,u8'}');
	}
}