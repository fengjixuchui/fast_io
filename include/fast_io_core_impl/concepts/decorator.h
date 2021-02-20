#pragma once

namespace fast_io
{

template<typename to_value_type,typename T>
concept decorator=requires(T t)
{
	typename T::char_type;
}
&&requires(T t,typename T::char_type const* ptr,to_value_type* dest,std::size_t size)
{
	{deco_reserve_size(io_reserve_type<to_value_type,T>,t,size)}->std::same_as<std::size_t>;
	{deco_reserve_define(io_reserve_type<to_value_type,T>,t,ptr,ptr,dest)}->std::convertible_to<to_value_type*>;
};

template<typename to_value_type,typename T>
concept maybe_noop_decorator=decorator<to_value_type,T>&&requires(T t)
{
	{deco_maybe_noop(io_reserve_type<to_value_type,T>,t)}->std::convertible_to<bool>;
};

template<typename to_value_type,typename T>
concept always_noop_decorator=decorator<to_value_type,T>&&requires()
{
	deco_always_noop(io_reserve_type<to_value_type,T>);//must be consteval
};

template<typename to_value_type,typename T>
concept reserve_inverse_size_decorator=decorator<to_value_type,T>&&requires(T t,std::size_t size)
{
	{deco_reserve_inverse_size(io_reserve_type<to_value_type,T>,t,size)}->std::same_as<std::size_t>;
};

template<typename T>
concept value_based_decorator = requires(T t)
{
	{deco_value_handle(t)};
};

template<typename to_value_type,typename T>
concept unshift_decorator = requires(T t,to_value_type const* from_iter,to_value_type const* to_iter)
{
	{deco_unshift_size(io_reserve_type<to_value_type,T>,t)};
	{deco_unshift_define(io_reserve_type<to_value_type,T>,t,from_iter,to_iter)};
};

template<typename T>
concept no_need_construct_decorator = requires(T t)
{
	{deco_no_need_construct(t)};
};


}