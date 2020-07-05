#pragma once

//fast_io_network.h deals with sockets
#include<thread>
#include<condition_variable>
#include"fast_io_hosted.h"
#if !defined(__WINNT__) && !defined(_MSC_VER)
#include <netinet/in.h>
#endif
#if __cpp_impl_coroutine >= 201902
#include<coroutine>
#include"fast_io_hosted/async_coro.h"
#include"fast_io_freestanding_impl/generator.h"
#endif
#include"fast_io_network/network.h"

namespace fast_io
{
using tcp_server = basic_tcp_server<false>;
using acceptor = basic_acceptor<char,false>;
using tcp_client = basic_tcp_client<char,false>;
using ibuf_acceptor = basic_ibuf<acceptor>;
using ibuf_tcp_client = basic_ibuf<tcp_client>;



using async_tcp_server = basic_tcp_server<true>;
using async_acceptor = basic_acceptor<char,true>;

/*
using u8tcp_acceptor = basic_acceptor<char8_t,false>;
using u8tcp_client = basic_client<char8_t,false>;
using u8tcp_acceptor_buf = basic_ibuf<u8acceptor>;
using u8tcp_client_buf = basic_ibuf<u8client>;*/
}