#include"../timer.h"

int main()
{
	constexpr std::uint32_t N(10000000);
	std::size_t value{};
	using namespace std::string_literals;
	{
	fast_io::timer t("fast_io::concat");
	for(std::uint32_t i{};i!=N;++i)
	{
		std::string str("Hello sdagjajdsgoijewopgjqwopegjewpogjqweopgjeqwopgjqewopgjqewpogjeqwopgjqewopgjeqwopgeqjwopgjqewoputopwqeutopqewtuqepwotuqewotpuw"s);
		str+="World";
		str+="asgfas";
		str+="dsgds";
		str+="dgsdhdshdsh";
		value+=str.size();
	}
	}
	println("value:",value);
}