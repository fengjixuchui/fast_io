#pragma once

namespace fast_io::details::streambuf_hack
{

/*
https://github.com/microsoft/STL/blob/master/stl/inc/fstream#L775

    const _Cvt* _Pcvt; // pointer to codecvt facet (may be null)
    _Elem _Mychar; // putback character, when _Ungetc fails
    bool _Wrotesome; // true if homing sequence may be needed
    typename _Traits::state_type _State; // current conversion state
    bool _Closef; // true if C stream must be closed
    FILE* _Myfile; // pointer to C stream

*/

template<typename char_type,typename traits_type>
inline FILE* fp_hack(std::basic_filebuf<char_type,traits_type>* fbuf) noexcept
{
	FILE* fp{};
	// we can only do this or ubsanitizer will complain. Do not do down_cast
	memcpy(std::addressof(fp),reinterpret_cast<std::byte*>(fbuf)+sizeof(std::basic_filebuf<char_type, traits_type>)-3*sizeof(std::uintptr_t),sizeof(fp));
	return fp;
}

#ifdef __cpp_rtti
template<typename T>
requires (std::same_as<T,std::basic_streambuf<typename T::char_type,typename T::traits_type>>)
inline FILE* fp_hack(T* cio)
{
	using filebuf_type = std::basic_filebuf<typename T::char_type,typename T::traits_type>;
	return fp_hack(std::addressof(dynamic_cast<filebuf_type&>(*cio)));
}
#endif
}