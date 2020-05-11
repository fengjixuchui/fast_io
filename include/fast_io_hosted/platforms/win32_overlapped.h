#pragma once

namespace fast_io
{

namespace win32
{


enum class win32_overlapped_operations:std::uint8_t
{
read,
write,
transmit,
cancel
};
class win32_overlapped_base
{
public:
	overlapped over{};
	win32_overlapped_operations operations{};
	void (*function_ptr)(overlapped*,std::uintptr_t,std::size_t){};
};
template<typename Func>
class win32_overlapped
{
public:
	win32_overlapped_base base{};
	Func function{};
};

}

}