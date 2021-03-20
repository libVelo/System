#ifndef VWLO_SYSTEM_DATAGRAM_HPP
#define VWLO_SYSTEM_DATAGRAM_HPP

namespace local
{
	class datagram_protocol
	{
		public:
			using endpoint = basic_endpoint<datagram_protocol>;
			using socket = basic_datagram_socket<datagram_protocol>;

			int type() const { return SOCK_DGRAM; }
			int protocol() const { return 0; }
			int family() const { return AF_UNIX; }
	};
}

#endif
