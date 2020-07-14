#pragma once

namespace fast_io
{

template<std::integral char_type,typename Func>
inline void async_scatter_write_callback(io_uring_observer ring,basic_posix_io_observer<char_type> piob,
		std::span<io_scatter_t const> span,std::ptrdiff_t offset,Func&& callback)
{
	io_uring_overlapped over(std::in_place,std::forward<Func>(callback));
	auto sqe{io_uring_get_sqe(ring.ring)};
	for(;sqe==nullptr;sqe=io_uring_get_sqe(ring.ring))
		submit(ring);
	io_uring_prep_writev(sqe,piob.fd,reinterpret_cast<details::iovec_may_alias const*>(span.data()),span.size(),offset);
	io_uring_sqe_set_data(sqe,over.native_handle());
	over.release();
}

template<std::integral char_type,std::contiguous_iterator Iter,typename Func>
inline void async_write_callback(io_uring_observer ring, basic_posix_io_observer<char_type> piob,
	Iter begin,Iter end,std::ptrdiff_t offset,Func&& callback)
{
	io_uring_overlapped over(std::in_place,std::forward<Func>(callback));
	auto sqe{io_uring_get_sqe(ring.ring)};
	for(;sqe==nullptr;sqe=io_uring_get_sqe(ring.ring))
		submit(ring);
	fast_io::io_scatter_t const sct{const_cast<void*>(static_cast<void const*>(std::to_address(begin))),(end-begin)*sizeof(*begin)};
//	std::size_t to_write((std::to_address(end)-std::to_address(begin))*sizeof(*begin));
//	if constexpr(sizeof(std::size_t)>sizeof(unsigned))
//		if(to_write>static_cast<std::size_t>(std::numeric_limits<unsigned>::max()))
//			to_write=static_cast<std::size_t>(std::numeric_limits<unsigned>::max());
	io_uring_prep_writev(sqe,piob.fd,reinterpret_cast<details::iovec_may_alias const*>(std::addressof(sct)),1,offset);
	io_uring_sqe_set_data(sqe,over.native_handle());
	if(io_uring_submit(ring.ring)<0)
		throw_posix_error();
	over.release();
}

}

