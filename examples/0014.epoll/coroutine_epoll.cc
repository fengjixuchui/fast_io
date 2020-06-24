#include"../../include/fast_io.h"
#include"../../include/fast_io_async.h"
#include"../../include/fast_io_device.h"
#include"../../include/fast_io_network.h"
#include<vector>
#include<coroutine>

struct epoll_task
{
struct promise_type
{
	auto get_return_object() { return epoll_task{}; }
	auto initial_suspend() { return std::suspend_never{}; }
	auto final_suspend() { return std::suspend_never{}; }
	void unhandled_exception() { std::terminate(); }
	void return_void() {}
};
};

struct awaitable
{
	fast_io::async_acceptor accept;
	std::coroutine_handle<> co_handle;
	template<typename... Args>
	requires std::constructible_from<fast_io::async_acceptor,Args...>
	awaitable(Args&& ...args):accept(std::forward<Args>(args)...){}
	bool await_ready() const {return false;}
	fast_io::async_acceptor await_resume() {return std::move(accept);}
	void await_suspend(std::coroutine_handle<> handle)
	{
		co_handle=handle;
	}
};

inline epoll_task listen(fast_io::async_tcp_server& acc)
{
	co_await awaitable(acc);
}

int main()
try
{
	fast_io::async_tcp_server server(2000);
	fast_io::epoll::handle_pool pool(1000);
	add_control(pool,server,fast_io::epoll::event::in);
	std::array<fast_io::epoll::events,1000> events_buffer;
	std::vector<awaitable> listeners;
//	std::vector<await_acceptor> clients;
	for(;;)
		for(auto const &ele : wait(pool,events_buffer))
			switch(get(ele))
			{
			case fast_io::epoll::event::in:
			if(fd(ele)==server.native_handle().native_handle())
			{
				listen(server);
			}
/*			auto it(std::find(listeners.cbegin(),listeners.cend(),ele));
		 	if(it==listeners.cend())
			{
				add_control(pool,listeners.emplace_back(server),fast_io::epoll::event::in|fast_io::epoll::event::out|fast_io::epoll::event::hup);
			}
			else
			{
				it->co_handle.resume();
				iter_swap(it,clients.end()-1);
				listeners.pop_back();
			}
			case fast_io::epoll::event::out:
			case fast_io::epoll::event::hup:
				for(auto it(clients.begin());it!=clients.end();++it)
					if(*it==ele)
					{
						if(get(ele)==fast_io::epoll::event::out)
							print(*it,u8"Hello World\n");
						iter_swap(it,clients.end()-1);
						clients.pop_back();
						break;
					}*/
			};
}
catch(std::exception const & e)
{
	perrln(e);
	return 1;
}
