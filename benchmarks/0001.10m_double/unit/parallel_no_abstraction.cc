#include"../../timer.h"
#include"../../../include/fast_io.h"
#include"../../../include/fast_io_device.h"
//#include"../../include/fast_io_crypto.h"
#include"../../../include/fast_io_legacy.h"
#include<random>
#include<thread>

template<std::integral ch_type>
inline constexpr void print_out(fast_io::basic_ospan<std::span<ch_type>>* osp,std::span<double> sp)
{
	fast_io::basic_ospan<std::span<ch_type>> bas{*osp};
	for(auto const & e : sp)
		println(bas,e);
	*osp=bas;
}

template<std::integral ch_type>
struct span_raii
{
	using ospan_type = fast_io::basic_ospan<std::span<ch_type>>;
	ospan_type osp;
//	constexpr span_raii()=default;
	template<typename... Args>
	requires std::constructible_from<ospan_type,Args...>
	constexpr span_raii(Args&& ...args) noexcept:osp(std::forward<Args>(args)...){}
	constexpr span_raii(span_raii const&)=delete;
	constexpr span_raii(span_raii&& other) noexcept:osp(other.osp)
	{
		other.osp.span()={};
	}
	constexpr span_raii& operator=(span_raii const&)=delete;
	constexpr span_raii& operator=(span_raii&& other) noexcept
	{
		if(std::addressof(other)==this)
			return *this;
		if(osp.span().data())[[likely]]
			delete[] osp.data();	
		osp.span()=other.osp.span();
		other.osp.span()={};
		return *this;
	}

	constexpr ~span_raii()
	{
		if(osp.span().data())[[likely]]
			delete[] osp.span().data();
	}
};

int main()
{
	constexpr std::size_t N(10000000);
	std::vector<double> vec;
	vec.reserve(N);
	std::random_device device;
	std::mt19937_64 eng;
	std::uniform_real_distribution dis(-10000.0,10000.0);
	for(std::size_t i(0);i!=N;++i)
		vec.emplace_back(dis(eng));
	{
	fast_io::timer t("obuf file normal output");
	fast_io::obuf_file obf("obuf_file.txt");
	for(std::size_t i{};i!=N;++i)
		println(obf,vec[i]);
	}

	fast_io::timer t("parrallel output");
	std::size_t thread_number{
#ifdef THREAD_NUMBER
THREAD_NUMBER
#else
std::thread::hardware_concurrency()
#endif
-1
};
	constexpr std::size_t max_length{25};
	std::size_t range{N/(1+thread_number)};
	std::size_t const module{N-range*(1+thread_number)};
	std::size_t allocation_size{range*max_length};
	fast_io::u8obuf_file onv("parrallel.txt");
	std::vector<span_raii<char8_t>> thread_result;
	thread_result.reserve(thread_number);
	{
	std::vector<std::jthread> jth;
	jth.reserve(thread_number);
	std::size_t const offset{(range<<1)+module};
	jth.emplace_back(print_out<char8_t>,std::addressof(thread_result.emplace_back(new char8_t[allocation_size],allocation_size).osp),
		std::span<double>{vec.data()+range,vec.data()+offset});
	for(std::size_t i{};i+1<thread_number;++i)
		jth.emplace_back(print_out<char8_t>,std::addressof(thread_result.emplace_back(new char8_t[allocation_size],allocation_size).osp),
		std::span<double>{vec.data()+offset+i*range,vec.data()+offset+(i+1)*range});
	for(std::size_t i{};i!=range;++i)
		println(onv,vec[i]);
	}

	for(auto& e : thread_result)
		write(onv,e.osp.span().data(),e.osp.span().data()+osize(e.osp));
}