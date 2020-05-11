#pragma once

namespace fast_io
{

template<stream T,open_mode interface_mode>
class basic_file_wrapper:public T
{
public:
	using char_type = typename T::char_type;
	using native_handle_type = typename T::native_handle_type;
	constexpr basic_file_wrapper()=default;
	constexpr basic_file_wrapper(native_handle_type hd):T(hd){}
	template<typename ...Args>
	constexpr basic_file_wrapper(native_interface_t,Args&& ...args):
		T(native_interface,std::forward<Args>(args)...){}
	template<open_mode om,perms pm>
	constexpr basic_file_wrapper(std::string_view file,open_interface_t<om>,perms_interface_t<pm>):
		T(file,open_interface<om|interface_mode>,perms_interface<pm>){}
	template<open_mode om>
	constexpr basic_file_wrapper(std::string_view file,open_interface_t<om>):
		T(file,open_interface<om|interface_mode>){}
	template<perms pm>
	constexpr basic_file_wrapper(std::string_view file,perms_interface_t<pm>):
		T(file,open_interface<interface_mode>,perms_interface<pm>){}
	constexpr basic_file_wrapper(std::string_view file):
		T(file,open_interface<interface_mode>){}
	constexpr basic_file_wrapper(std::string_view file,open_mode m,perms p=static_cast<perms>(436)):
		T(file,m|interface_mode,p){}
	constexpr basic_file_wrapper(std::string_view file,std::string_view mode,perms p=static_cast<perms>(436)):
		basic_file_wrapper(file,fast_io::from_c_mode(mode),p){}
	constexpr basic_file_wrapper(std::string_view file,perms pm):T(file,open_interface<interface_mode>,pm){}
};

template<input_stream T>
using input_file_wrapper = basic_file_wrapper<T,open_mode::in|open_mode::binary>;
template<output_stream T>
using output_file_wrapper = basic_file_wrapper<T,open_mode::out|open_mode::binary>;
template<io_stream T>
using io_file_wrapper = basic_file_wrapper<T,open_mode::in|open_mode::out|open_mode::binary>;

template<stream T,open_mode interface_mode>
class basic_wrapper:public T
{
public:
	using char_type = typename T::char_type;
	using native_handle_type = typename T::native_handle_type;
	template<open_mode om>
	constexpr basic_wrapper(open_interface_t<om>):T(open_interface<om|interface_mode>){}
	constexpr basic_wrapper():T(open_interface<interface_mode>){}
	constexpr basic_wrapper(open_mode m):T(m|interface_mode){}
	constexpr basic_wrapper(std::string_view mode):basic_wrapper(from_c_mode(mode)){}
};

template<input_stream T>
using input_wrapper = basic_wrapper<T,open_mode::in|open_mode::binary>;
template<output_stream T>
using output_wrapper = basic_wrapper<T,open_mode::out|open_mode::binary>;
template<io_stream T>
using io_wrapper = basic_wrapper<T,open_mode::in|open_mode::out|open_mode::binary>;

}
