#ifndef VELO_NETWORK_IPC_BASIC_ENDPOINT_HPP
#define VELO_NETWORK_IPC_BASIC_ENDPOINT_HPP

namespace system::ipc
{
	template<typename Protocol>
	class basic_endpoint
	{
		public:
			using protocol_type = Protocol;
			using data_type = boost::asio::detail::socket_addr_type;

			basic_endpoint() {}

			basic_endpoint(string_view path_name) {}

			basic_endpoint(const basic_endpoint& other)
			{
				if(path_length > sizeof(data_.local.sun_path) - 1)
				{
					// The buffer is not large enough to store this address.
					boost::system::error_code ec(boost::asio::error::name_too_long);
					boost::asio::detail::throw_error(ec);
				}

				using namespace std; // For memcpy.
				data_.local            = boost::asio::detail::sockaddr_un_type();
				data_.local.sun_family = AF_UNIX;
				if(path_length > 0)
					memcpy(data_.local.sun_path, path_name, path_length);
				path_length_ = path_length;

				// NUL-terminate normal path names. Names that start with a NUL are in the
				// UNIX domain protocol's "abstract namespace" and are not NUL-terminated.
				if(path_length > 0 && data_.local.sun_path[0] == 0)
					data_.local.sun_path[path_length] = 0;
			}

			basic_endpoint(basic_endpoint&& other) : impl_(other.impl_) {}

			basic_endpoint& operator=(const basic_endpoint& other)
			{
				impl_ = other.impl_;
				return *this;
			}

			basic_endpoint& operator=(basic_endpoint&& other)
			{
				impl_ = other.impl_;
				return *this;
			}

			protocol_type protocol() const
			{
				return protocol_type();
			}

			data_type* data()
			{
				return impl_.data();
			}

			const data_type* data() const
			{
				return impl_.data();
			}

			std::size_t size() const
			{
				return impl_.size();
			}

			void resize(std::size_t new_size)
			{
				impl_.resize(new_size);
			}

			std::size_t capacity() const
			{
				return impl_.capacity();
			}

			std::string path() const
			{
				return impl_.path();
			}

			void path(const char* p)
			{
				impl_.path(p);
			}

			void path(const std::string& p)
			{
				impl_.path(p);
			}

			friend bool operator==(const basic_endpoint<Protocol>& e1, const basic_endpoint<Protocol>& e2)
			{
				return e1.impl_ == e2.impl_;
			}

			friend bool operator!=(const basic_endpoint<Protocol>& e1, const basic_endpoint<Protocol>& e2)
			{
				return !(e1.impl_ == e2.impl_);
			}

			friend bool operator<(const basic_endpoint<Protocol>& e1, const basic_endpoint<Protocol>& e2)
			{
				return e1.impl_ < e2.impl_;
			}

			friend bool operator>(const basic_endpoint<Protocol>& e1, const basic_endpoint<Protocol>& e2)
			{
				return e2.impl_ < e1.impl_;
			}

			friend bool operator<=(const basic_endpoint<Protocol>& e1, const basic_endpoint<Protocol>& e2)
			{
				return !(e2 < e1);
			}

			friend bool operator>=(const basic_endpoint<Protocol>& e1, const basic_endpoint<Protocol>& e2)
			{
				return !(e1 < e2);
			}

		private:
			union data_union
			{
				boost::asio::detail::socket_addr_type base;
				boost::asio::detail::sockaddr_un_type local;
			} data_;

			std::size_t path_length_;
	};

	template<typename Elem, typename Traits, typename Protocol>
	std::basic_ostream<Elem, Traits>&
	operator<<(std::basic_ostream<Elem, Traits>& os, const basic_endpoint<Protocol>& endpoint)
	{
		os << endpoint.path();
		return os;
	}

}

#endif
