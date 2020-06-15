#include"../timer.h"

int main()
{
	constexpr std::uint32_t N(10000000);
	std::size_t value{};
	{
	fast_io::timer t("fast_io::concat");
	using namespace std::string_literals;
	for(std::uint32_t i{};i!=N;++i)
	{
		value+=fast_io::concat("Hello sdagjajdsgoijewopgjqwopegjewpogjqweopgjeqwopgjqewopgjqewpogjeqwopgjqewopgjeqwopgeqjwopgjqewoputopwqeutopqewtuqepwotuqewotpuw"s,"World","asgfas","dsgds","dgsdhdshdsh").size();
	}
	}

	println("value:",value);

	using namespace std::string_literals;
	print(fast_io::concat("Hello sdagjajdsgoijewopgjqwopegj"s,"dsg23523532523532532532"));
}