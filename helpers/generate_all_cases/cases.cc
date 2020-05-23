#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"
#include<vector>

int main()
{
	fast_io::obuf_file obf("cinterface.cc");
	std::vector<std::string_view> vec{"char","short","int","long","long long",
	"char unsigned","short unsigned","int unsigned","long unsigned","long long unsigned",
	"double"};
	for(auto const& e : vec)
	{
		std::string str(e);
		for(auto& e : str)
			if(e==u8' ')
				e='_';
		print(obf,"void cxx_fast_io_fp_print_",str,"(std::FILE* d,",e," value){details2::c_interface_print<false,false>(d,value);}\n"
		"void cxx_fast_io_fp_println_",str,"(std::FILE* d,",e," value){details2::c_interface_print<false,true>(d,value);}\n"
		"void cxx_fast_io_fp_unlocked_print_",str,"(std::FILE* d,",e," value){details2::c_interface_print<true,false>(d,value);}\n"
		"void cxx_fast_io_fp_unlocked_println_",str,"(std::FILE* d,",e," value){details2::c_interface_print<true,true>(d,value);}\n");
	};
	print(obf,"void cxx_fast_io_fp_print_c_str(std::FILE* d,char const* value){details2::c_interface_print<false,false>(d,value);}\n"
	"void cxx_fast_io_fp_println_c_str(std::FILE* d,char const* value){details2::c_interface_print<false,true>(d,value);}\n"
	"void cxx_fast_io_fp_unlocked_print_c_str(std::FILE* d,char const* value){details2::c_interface_print<true,false>(d,value);}\n"
	"void cxx_fast_io_fp_unlocked_println_c_str(std::FILE* d,char const* value){details2::c_interface_print<true,true>(d,value);}\n");

	fast_io::obuf_file cpi("cinterface.h");
	for(auto const& e : vec)
	{
		std::string str(e);
		for(auto& e : str)
			if(e==u8' ')
				e='_';
		print(cpi,"void cxx_fast_io_fp_print_",str,"(FILE*,",e,");\n"
		"void cxx_fast_io_fp_println_",str,"(FILE*,",e,");\n"
		"void cxx_fast_io_fp_unlocked_print_",str,"(FILE*,",e,");\n"
		"void cxx_fast_io_fp_unlocked_println_",str,"(FILE*,",e,");\n");
	};
	print(cpi,"void cxx_fast_io_fp_print_c_str(FILE*,char const*);\n"
	"void cxx_fast_io_fp_println_c_str(FILE*,char const*);\n"
	"void cxx_fast_io_fp_unlocked_print_c_str(FILE*,char const*);\n"
	"void cxx_fast_io_fp_unlocked_println_c_str(FILE*,char const*);\n");

	print(cpi,"\n\n#define PRINT(fp,x) _Generic((x) ");
	for(auto const& e : vec)
	{
		std::string str(e);
		for(auto& e : str)
			if(e==u8' ')
				e='_';
		print(cpi,",",e,":cxx_fast_io_fp_print_",str,"\\\n");
	};
	print(cpi,",char const*:cxx_fast_io_fp_print_c_str)(fp,x)");

	print(cpi,"\n\n#define PRINTLN(fp,x) _Generic((x) ");
	for(auto const& e : vec)
	{
		std::string str(e);
		for(auto& e : str)
			if(e==u8' ')
				e='_';
		print(cpi,",",e,":cxx_fast_io_fp_println_",str,"\\\n");
	};
	print(cpi,",char const*:cxx_fast_io_fp_println_c_str)(fp,x)");

	print(cpi,"\n\n#define PRINT_UNLOCKED(fp,x) _Generic((x) ");
	for(auto const& e : vec)
	{
		std::string str(e);
		for(auto& e : str)
			if(e==u8' ')
				e='_';
		print(cpi,",",e,":cxx_fast_io_fp_print_unlocked_",str,"\\\n");
	};
	print(cpi,",char const*:cxx_fast_io_fp_print_unlocked_c_str)(fp,x)");

	print(cpi,"\n\n#define PRINTLN_UNLOCKED(fp,x) _Generic((x) ");
	for(auto const& e : vec)
	{
		std::string str(e);
		for(auto& e : str)
			if(e==u8' ')
				e='_';
		print(cpi,",",e,":cxx_fast_io_fp_unlocked_println_",str,"\\\n");
	};
	print(cpi,",char const*:cxx_fast_io_fp_unlocked_println_c_str)(fp,x)");
}