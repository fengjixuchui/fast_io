#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"

int main()
try
{
	fast_io::u8ibuf_file ibf("error_list.txt");
	std::vector<std::u8string> lines;
	for(std::u8string str;scan<true>(ibf,fast_io::line(str));lines.emplace_back(std::move(str)));
	{
	fast_io::u8obuf_file obf("nt_error_what.h");
	for(std::size_t i{};i<lines.size();i+=6)
		print(obf,u8"case ",lines.at(i),u8":\treturn R\"(NT_",lines.at(i+2),u8")\";\n");
	print(obf,u8"default:return \"[nt:unknown]\";\n");
	}
	{
	fast_io::u8obuf_file obf("nt_error_message.h");
	for(std::size_t i{};i<lines.size();i+=6)
		print(obf,u8"case ",lines.at(i),u8":\treturn u8R\"(nt[",lines.at(i),u8"(",lines.at(i+2),u8")]",lines.at(i+4),u8")\";\n");
	print(obf,u8"default:return u8\"[nt:unknown]\";\n");
	}
}
catch(std::exception const& e)
{
	println(fast_io::err,e);
	return 1;
}