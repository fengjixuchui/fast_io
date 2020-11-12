#pragma once

namespace fast_io
{

struct posix_wait_status
{
	int wait_loc{};
};

inline constexpr posix_wait_reason reason(posix_wait_status pws) noexcept
{
#ifdef WIFEXITED
	if(WIFEXITED(pws.wait_loc))
		return posix_wait_reason::if_exited;
#endif
#ifdef WIFSIGNALED
	if(WIFSIGNALED(pws.wait_loc))
		return posix_wait_reason::if_signaled;
#endif
#ifdef WIFCORED
	if(WIFCORED(pws.wait_loc))
		return posix_wait_reason::if_core_dump;
#endif
	if(WIFSTOPPED(pws.wait_loc))
		return posix_wait_reason::if_stopped;
	return posix_wait_reason::none;
}

inline constexpr int native_code(posix_wait_status pws) noexcept
{
	return pws.wait_loc;
}

inline constexpr std::uintmax_t code(posix_wait_status pws) noexcept
{
	return static_cast<std::uintmax_t>(pws.wait_loc);
}

template<std::integral char_type>
inline constexpr std::size_t print_reserve_size(io_reserve_type_t<char_type,posix_wait_status>) noexcept
{
	return sizeof(u8"reason:")+print_reserve_size(io_reserve_type<char_type,posix_wait_reason>)
		+sizeof(u8" native_code:")+print_reserve_size(io_reserve_type<char_type,int>);
}

template<std::integral char_type,std::random_access_iterator Iter>
inline constexpr Iter print_reserve_define(io_reserve_type_t<char_type,posix_wait_status>,Iter iter,posix_wait_status pws) noexcept
{
	if constexpr(std::same_as<char_type,char>)
		iter=details::copy_string_literal("reason:",iter);
	else if constexpr(std::same_as<char_type,wchar_t>)
		iter=details::copy_string_literal(L"reason:",iter);
	else if constexpr(std::same_as<char_type,char16_t>)
		iter=details::copy_string_literal(u"reason:",iter);
	else if constexpr(std::same_as<char_type,char32_t>)
		iter=details::copy_string_literal(U"reason:",iter);
	else
		iter=details::copy_string_literal(u8"reason:",iter);
	iter=print_reserve_define(io_reserve_type<char_type,posix_wait_reason>,iter,reason(pws));
	if constexpr(std::same_as<char_type,char>)
		iter=details::copy_string_literal(" native_code:",iter);
	else if constexpr(std::same_as<char_type,wchar_t>)
		iter=details::copy_string_literal(L" native_code:",iter);
	else if constexpr(std::same_as<char_type,char16_t>)
		iter=details::copy_string_literal(u" native_code:",iter);
	else if constexpr(std::same_as<char_type,char32_t>)
		iter=details::copy_string_literal(U" native_code:",iter);
	else
		iter=details::copy_string_literal(u8" native_code:",iter);
	return print_reserve_define(io_reserve_type<char_type,int>,iter,pws.wait_loc);
}

namespace details
{

inline pid_t posix_fork()
{
	pid_t pid{	
	#if defined(__linux__)
		system_call<__NR_fork,pid_t>()
	#else
		::fork()
	#endif
	};
	system_call_throw_error(pid);
	return pid;
}

inline posix_wait_status posix_waitpid(pid_t pid)
{
	posix_wait_status status;
	system_call_throw_error(
	#if defined(__linux__)
		system_call<__NR_wait4,int>(pid,std::addressof(status.wait_loc),0,nullptr)
	#else
		waitpid(pid,std::addressof(status.wait_loc),0)
	#endif
	);
	return status;
}

inline void posix_waitpid_noexcept(pid_t pid) noexcept
{
#if defined(__linux__)
	system_call<__NR_wait4,int>(pid,nullptr,0,nullptr);
#else
	waitpid(pid,nullptr,0);
#endif
}

[[noreturn]] inline void posix_execveat(int dirfd,char const* path,char const* const* argv,char const* const* envp) noexcept
{
#ifdef __linux__
	system_call<__NR_execveat,int>(dirfd,path,argv,envp,AT_SYMLINK_NOFOLLOW);
	fast_terminate();
#else
	int fd{::openat(dirfd,path,O_RDONLY|O_EXCL,0644)};
	if(fd==-1)
		fast_terminate();
	::fexecve(fd,const_cast<char* const*>(argv),const_cast<char* const*>(envp));
	fast_terminate();
#endif
}

inline int child_process_deal_with_process_io(posix_io_redirection const& red,int fd) noexcept
{
	bool is_stdin{fd==0};
	if(red.pipe_fds)
	{
		auto v{red.pipe_fds[!is_stdin]};
		if(v!=-1)
			fd=v;
		int& closefd{red.pipe_fds[is_stdin]};
		if(closefd!=-1)
		{
			sys_close(closefd);
			closefd=-1;
		}
	}
	else if(red.fd!=-1)
		fd=red.fd;
	else if(red.dev_null)
		fd=-1;
	return fd;
}


inline void child_process_execveat(int dirfd,cstring_view csv,char const* const* args_ptr,char const* const* envp_ptr,posix_process_io const& pio) noexcept
{
	int in_fd{child_process_deal_with_process_io(pio.in,0)};
	int out_fd{child_process_deal_with_process_io(pio.out,1)};
	int err_fd{child_process_deal_with_process_io(pio.err,2)};
	if((in_fd==-1)|(out_fd==-1)|(err_fd==-1))
	{
		posix_file pf{my_posix_open<true>("/dev/null",O_RDWR,0644)};
		if(in_fd==-1)
			sys_dup2<true>(pf.fd,0);
		if(out_fd==-1)
			sys_dup2<true>(pf.fd,1);
		if(err_fd==-1)
			sys_dup2<true>(pf.fd,2);
	}
	if((in_fd!=-1)&(in_fd!=0))
		sys_dup2<true>(in_fd,0);
	if((out_fd!=-1)&(out_fd!=1))
		sys_dup2<true>(out_fd,1);
	if((err_fd!=-1)&(err_fd!=2))
		sys_dup2<true>(err_fd,2);	
	posix_execveat(dirfd,csv.c_str(),args_ptr,envp_ptr);
};


template<bool is_stdin>
inline void parent_process_deal_with_process_io(posix_io_redirection const& red) noexcept
{
	if(red.pipe_fds)
	{
		int& fd{red.pipe_fds[!is_stdin]};
		if(fd!=-1)
		{
			sys_close(fd);
			fd=-1;
		}
	}
}


inline pid_t posix_fork_execveat_impl(int dirfd,cstring_view csv,char const* const* args,char const* const* envp,posix_process_io const& pio)
{
	pid_t pid{posix_fork()};
	if(pid)
	{
		parent_process_deal_with_process_io<true>(pio.in);
		parent_process_deal_with_process_io<false>(pio.out);
		parent_process_deal_with_process_io<false>(pio.err);
		return pid;
	}
	child_process_execveat(dirfd,csv,args,envp,pio);
	fast_terminate();
}

}

class posix_process_observer
{
public:
	using native_handle_type = pid_t;
	pid_t pid{-1};
	constexpr auto& native_handle() noexcept
	{
		return pid;
	}
	constexpr auto& native_handle() const noexcept
	{
		return pid;
	}
	explicit inline constexpr operator bool() const noexcept
	{
		return pid!=-1;
	}
	inline constexpr pid_t release() noexcept
	{
		auto temp{pid};
		pid=-1;
		return temp;
	}
};

inline constexpr void detach(posix_process_observer& ppob) noexcept
{
	ppob.pid=-1;
}

inline posix_wait_status wait(posix_process_observer& ppob)
{
	posix_wait_status status{details::posix_waitpid(ppob.pid)};
	ppob.pid=-1;
	return status;
}

inline constexpr bool operator==(posix_process_observer a,posix_process_observer b) noexcept
{
	return a.pid==b.pid;
}

inline constexpr auto operator<=>(posix_process_observer a,posix_process_observer b) noexcept
{
	return a.pid<=>b.pid;
}

namespace details
{
template<std::random_access_iterator Iter>
inline
#if __cpp_constexpr_dynamic_alloc >= 201907L
	constexpr
#endif
char const* const* dup_enviro_impl(Iter begin,Iter end)
{
	std::size_t const size{static_cast<std::size_t>(end-begin)};
	std::unique_ptr<char const*[]> uptr(new char const*[size+1]);
	if constexpr(requires(std::iter_value_t<Iter> v)
	{
		{v.c_str()}->std::convertible_to<char const*>;
	})
	{
		for(char const* it{uptr.get()};begin!=end;++begin)
		{
			*it=begin->c_str();
			++it;
		}
	}
	else
		non_overlapped_copy_n(begin,size,uptr.get());
	uptr[size]=nullptr;
	return uptr.release();
}

template<std::random_access_iterator Iter>
inline 
#if __cpp_constexpr_dynamic_alloc >= 201907L
	constexpr
#endif
char const* const* dup_enviro_entry(Iter begin,Iter end)
{
	if constexpr(std::contiguous_iterator<Iter>)
		return dup_enviro_impl(std::to_address(begin),std::to_address(end));
	else
		return dup_enviro_impl(begin,end);
}


}


struct posix_process_args
{
	char const* const* args{};
	bool is_dynamic_allocated{};
	inline constexpr posix_process_args(char const* const* envir) noexcept:args(envir){}
	template<std::random_access_iterator Iter>
	requires (std::convertible_to<std::iter_value_t<Iter>,char const*>||requires(std::iter_value_t<Iter> v)
	{
		{v.c_str()}->std::convertible_to<char const*>;
	})
	inline constexpr posix_process_args(Iter begin,Iter end):
		args(details::dup_enviro_entry(begin,end)),is_dynamic_allocated(true)
	{}
	template<std::ranges::random_access_range range>
	requires (std::convertible_to<std::ranges::range_value_t<range>,char const*>||requires(std::ranges::range_value_t<range> v)
	{
		{v.c_str()}->std::convertible_to<char const*>;
	})
	inline constexpr posix_process_args(range&& rg):posix_process_args(std::ranges::cbegin(rg),std::ranges::cend(rg))
	{}
	inline constexpr posix_process_args(std::initializer_list<char const*> ilist):
		posix_process_args(ilist.begin(),ilist.end()){}
	posix_process_args(posix_process_args const&)=delete;
	posix_process_args& operator=(posix_process_args const&)=delete;
#if __cpp_constexpr_dynamic_alloc >= 201907L
	inline constexpr
#endif
	~posix_process_args()
	{
		if(is_dynamic_allocated)
			delete[] args;
	}
};


class posix_process:public posix_process_observer
{
public:
	using native_handle_type = pid_t;
	explicit constexpr posix_process() noexcept =default;
	template<typename native_hd>
	requires std::same_as<native_handle_type,std::remove_cvref_t<native_hd>>
	explicit constexpr posix_process(native_hd pid) noexcept:
		posix_process_observer{pid}{}
	posix_process(posix_at_entry pate,cstring_view filename,posix_process_args const& args,posix_process_args const& envp,posix_process_io const& pio):
		posix_process_observer{details::posix_fork_execveat_impl(pate.fd,filename,args.args,envp.args,pio)}{}
	posix_process(cstring_view filename,posix_process_args const& args,posix_process_args const& envp,posix_process_io const& pio):
		posix_process_observer{details::posix_fork_execveat_impl(AT_FDCWD,filename,args.args,envp.args,pio)}{}
	posix_process(posix_process const&)=delete;
	posix_process& operator=(posix_process const&)=delete;
	constexpr posix_process(posix_process&& other) noexcept:posix_process_observer{other.pid}
	{
		other.pid=-1;
	}
	posix_process& operator=(posix_process&& other) noexcept
	{
		if(std::addressof(other)==this)
			return *this;
		details::posix_waitpid_noexcept(this->pid);
		this->pid=other.pid;
		other.pid=-1;
		return *this;
	}
	~posix_process()
	{
		details::posix_waitpid_noexcept(this->pid);
	}
};

}