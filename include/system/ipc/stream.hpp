#ifndef VELO_SYSTEM_STREAM_HPP
#define VELO_SYSTEM_STREAM_HPP

namespace system::ipc
{
	class stream_protocol
	{
		public:
			using socket = basic_stream_socket<stream_protocol>;
			using acceptor = basic_socket_acceptor<stream_protocol>;
			using iostream = basic_socket_iostream<stream_protocol>;

			int type() const { return SOCK_STREAM; }
			int protocol() const { return 0; }
			int family() const { return AF_UNIX; }
	};
}

#endif
