#include <iostream>
#include <memory>
#include <system/ipc/stream.hpp>

using system::ipc::stream_protocol;

class session
{
	public:
		explicit session(stream_protocol::socket sock) : socket_(std::move(sock)) {}

		void start() { do_read(); }

	private:
		void do_read()
		{
			auto self(shared_from_this());
			socket_.async_read_some(boost::asio::buffer(data_),
											[this, self](boost::system::error_code ec, std::size_t length)
											{
												if(!ec)
													do_write(length);
											});
		}

		void do_write(std::size_t length)
		{
			auto self(shared_from_this());
			boost::asio::async_write(socket_,
											 boost::asio::buffer(data_, length),
											 [this, self](boost::system::error_code ec, std::size_t /*length*/)
											 {
												 if(!ec)
													 do_read();
											 });
		}

		// The socket used to communicate with the client.
		stream_protocol::socket socket_;

		// Buffer used to store data received from the client.
		std::array<char, 1024> data_;
};

class server
{
	public:
		server(const std::string& file) : acceptor(stream_protocol::endpoint(file))
		{
			do_accept();
		}

	private:
		void do_accept()
		{
			acceptor_.async_accept([this](boost::system::error_code ec, stream_protocol::socket socket)
										  {
											  if(!ec)
											  {
												  std::make_shared<session>(std::move(socket))->start();
											  }

											  do_accept();
										  });
		}

		stream_protocol::acceptor acceptor;
};

int main(int argc, char* argv[])
{
	try
	{
		if(argc != 2)
		{
			std::cerr << "Usage: stream_server <file>\n";
			std::cerr << "*** WARNING: existing file is removed ***\n";
			return 1;
		}

		std::remove(argv[1]);
		server s(argv[1]);
	}
	catch(std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
}
