#pragma once

namespace fast_io
{

template<std::integral ch_type>
struct basic_ctype_is
{
	using char_type = ch_type;
	using unsigned_char_type = std::make_unsigned_t<char_type>;
	using bitset_type = std::bitset<(1<<(8*sizeof(ch_type)))>;
	using storage_type = std::unique_ptr<bitset_type>;
	storage_type storage;
	constexpr bool operator()(char_type ch) const noexcept
	{
		return (*storage)[static_cast<unsigned_char_type>(ch)];
	}
};

template<std::integral ch_type>
struct basic_ctype_to
{
	using char_type = ch_type;
	using unsigned_char_type = std::make_unsigned_t<char_type>;
	using array_type = std::array<ch_type,(1<<(8*sizeof(ch_type)))>;
	using storage_type = std::unique_ptr<array_type>;
	storage_type storage;
	constexpr char_type operator()(char_type ch) const noexcept
	{
		return (*storage)[ch];
	}
};

using ctype_is = basic_ctype_is<char>;
using ctype_to = basic_ctype_to<char>;
}