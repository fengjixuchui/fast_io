#pragma once

#if defined(__WINNT__) || defined(_MSC_VER)
#include <winsock2.h>
#else
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include <sys/types.h>
#include <netdb.h>
#endif

namespace fast_io
{
namespace sock
{
enum class family
{
unspec = AF_UNSPEC,
local = 1,
ipx = AF_IPX,
apple_talk = AF_APPLETALK, 
ipv4 = AF_INET,
ipv6 = AF_INET6,
bluetooth = 
#ifdef AF_BLUETOOTH
AF_BLUETOOTH
#elif defined(AF_BTH)
AF_BTH
#else
AF_UNSPEC
#endif
};

enum class type
{
stream = SOCK_STREAM,
datagrams =SOCK_DGRAM,
sequence_packet = SOCK_SEQPACKET,
raw = SOCK_RAW,
reliable_datagram_layer=SOCK_RDM,
};

enum class protocal
{
none = 0,
ipv4 = IPPROTO_IP,
ipv6 = IPPROTO_IPV6,
tcp = IPPROTO_TCP,
udp = IPPROTO_UDP,
icmp = IPPROTO_ICMP,
icmpv6 = IPPROTO_ICMPV6
};

}

}

#if defined(__WINNT__) || defined(_MSC_VER)
#include "win32_socket.h"
#else
#include "posix_socket.h"
#endif
#include"address.h"
#include"message_flags.h"
#include"socket.h"
#include"dns.h"
#include"http.h"
//#include"thread_pool.h"