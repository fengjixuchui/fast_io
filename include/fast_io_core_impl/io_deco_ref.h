#pragma once

namespace fast_io
{

template<typename decot>
struct deco_reference_wrapper
{
	using decorator_type = decot;
	decorator_type* ptr{};
};

template<typename decot>
constexpr deco_reference_wrapper<decot> deco_value_handle(deco_reference_wrapper<decot> wrap) noexcept
{
	return wrap;
}

template<typename decot>
inline constexpr auto io_deco_ref(decot& deco) noexcept
{
	if constexpr(value_based_decorator<std::remove_cvref_t<decot>>)
		return deco_value_handle(deco);
	else
		return deco_reference_wrapper<std::remove_cvref_t<decot>>{std::addressof(deco)};
}

template<std::integral to_char_type,typename decot>
requires decorator<to_char_type,decot>
constexpr std::size_t deco_reserve_size(io_reserve_type_t<to_char_type,deco_reference_wrapper<decot>>,deco_reference_wrapper<decot> deco,std::size_t size)
{
	return deco_reserve_size(io_reserve_type<to_char_type,decot>,*deco.ptr,size);
};

template<std::random_access_iterator srcIter,std::random_access_iterator toIter,typename decot>
requires decoratable<std::iter_value_t<srcIter>,std::iter_value_t<toIter>,decot>
constexpr toIter deco_reserve_define(io_reserve_type_t<std::iter_value_t<toIter>,deco_reference_wrapper<decot>>,deco_reference_wrapper<decot> deco,srcIter first,srcIter last,toIter iter)
{
	return deco_reserve_define(io_reserve_type<std::iter_value_t<toIter>,decot>,*deco.ptr,first,last,iter);
};

template<std::integral to_char_type,typename decot>
requires maybe_noop_decorator<to_char_type,decot>
constexpr bool deco_maybe_noop(io_reserve_type_t<to_char_type,deco_reference_wrapper<decot>>,deco_reference_wrapper<decot> deco)
{
	return deco_maybe_noop(io_reserve_type<to_char_type,decot>,*deco.ptr);
};

template<std::integral to_char_type,typename decot>
requires always_noop_decorator<to_char_type,decot>
constexpr void deco_always_noop(io_reserve_type_t<to_char_type,deco_reference_wrapper<decot>>,deco_reference_wrapper<decot> deco){};

template<std::integral to_char_type,typename decot>
requires reserve_inverse_size_decorator<to_char_type,decot>
constexpr std::size_t deco_reserve_inverse_size(io_reserve_type_t<to_char_type,deco_reference_wrapper<decot>>,deco_reference_wrapper<decot> deco,std::size_t size)
{
	return deco_reserve_inverse_size(io_reserve_type<to_char_type,decot>,*deco.ptr,size);
}

}

