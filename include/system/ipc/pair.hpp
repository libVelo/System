#ifndef VELO_SYSTEM_PAIR_HPP
#define VELO_SYSTEM_PAIR_HPP

namespace system::ipc
{
	template<typename Protocol, typename Executor1, typename Executor2>
	void connect_pair(basic_socket <Protocol, Executor1>& socket1, basic_socket <Protocol, Executor2>& socket2);

	template<typename Protocol, typename Executor1, typename Executor2>
	void connect_pair(basic_socket <Protocol, Executor1>& socket1, basic_socket <Protocol, Executor2>& socket2);

	template<typename Protocol, typename Executor1, typename Executor2>
	inline void connect_pair(basic_socket <Protocol, Executor1>& socket1, basic_socket <Protocol, Executor2>& socket2)
	{
		boost::system::error_code ec;
		connect_pair(socket1, socket2, ec);
		boost::asio::detail::throw_error(ec, "connect_pair");
	}

	template<typename Protocol, typename Executor1, typename Executor2>
	inline void connect_pair(basic_socket <Protocol, Executor1>& socket1, basic_socket <Protocol, Executor2>& socket2)
	{
		// Check that this function is only being used with a UNIX domain socket.
		boost::asio::local::basic_endpoint <Protocol>* tmp = static_cast<typename Protocol::endpoint*>(0);
		(void)tmp;

		Protocol                         protocol;
		boost::asio::detail::socket_type sv[2];
		if(boost::asio::detail::socket_ops::socketpair(protocol.family(), protocol.type(), protocol.protocol(), sv, ec) ==
			boost::asio::detail::socket_error_retval)
			BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);

		socket1.assign(protocol, sv[0], ec);
		if(ec)
		{
			boost::system::error_code                   temp_ec;
			boost::asio::detail::socket_ops::state_type state[2] = {0, 0};
			boost::asio::detail::socket_ops::close(sv[0], state[0], true, temp_ec);
			boost::asio::detail::socket_ops::close(sv[1], state[1], true, temp_ec);
			BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
		}

		socket2.assign(protocol, sv[1], ec);
		if(ec)
		{
			boost::system::error_code temp_ec;
			socket1.close(temp_ec);
			boost::asio::detail::socket_ops::state_type state = 0;
			boost::asio::detail::socket_ops::close(sv[1], state, true, temp_ec);
			BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
		}

		BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
	}
}

#endif
