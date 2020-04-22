#include"../../../include/fast_io.h"
#include"../../../include/fast_io_device.h"
#include<thread>
#include<span>
#include"../../timer.h"

template<std::integral ch_type>
inline constexpr void print_out(fast_io::basic_ospan<std::span<ch_type>>* osp,std::size_t from,std::size_t to)
{
	fast_io::basic_ospan<std::span<ch_type>> bas{*osp};
	for(;from!=to;++from)
		println(bas,from);
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
	fast_io::timer t("output");
	std::vector<span_raii<char8_t>> vec;

	constexpr std::size_t N{10000000};
	constexpr std::size_t thread_number{
#ifdef THREAD_NUMBER
THREAD_NUMBER
#else
40
#endif
};
	constexpr std::size_t max_length{22};
	constexpr std::size_t range{N/thread_number};
	constexpr std::size_t allocation_size{range*max_length};
	vec.reserve(thread_number);
	{
	std::vector<std::jthread> jth;
	for(std::size_t i{};i!=thread_number;++i)
		jth.emplace_back(print_out<char8_t>,std::addressof(vec.emplace_back(new char8_t[allocation_size],allocation_size).osp),i*range,(i+1)*range);
	}

	fast_io::u8obuf_file onv("parallel.txt");
	for(auto& e : vec)
		write(onv,e.osp.span().data(),e.osp.span().data()+osize(e.osp));
}