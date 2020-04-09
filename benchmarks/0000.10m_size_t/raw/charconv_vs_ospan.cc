#include"../timer.h"
#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"
#include<charconv>

int main()
{
	constexpr std::size_t N(10000000);

	std::size_t osp_total{};
	{
		fast_io::timer t("ospan");
		std::array<char,50> array;
		for(std::size_t i{};i!=100000000;++i)
		{
			fast_io::ospan osp(array);
			println(osp,i);
			osp_total+=osize(osp);
		}
	}
	std::size_t charconv_total{};
	{
		fast_io::timer t("array");
		std::array<char,50> array;
		for(std::size_t i{};i!=100000000;++i)
		{
			auto [p,ec]=std::to_chars(array.data(),array.data()+array.size(),i);
			*p=u8'\n';
			charconv_total+=++p-array.data();
		}
	}
	println("charconv_total:",charconv_total," osp_total:",osp_total);
}
