#include <iostream>
#include <memory>
#include <system/ipc/stream.hpp>

using system::ipc::stream_protocol;

constexpr std::size_t max_length = 1024;

int main(int argc, char* argv[])
{
	try
	{
		if(argc != 2)
		{
			std::cerr << "Usage: stream_client <file>\n";
			return 1;
		}

		stream_protocol::socket s;
		//s.connect(stream_protocol::endpoint(argv[1]));

		std::cout << "Enter message: ";

		//std::string str(max_length);

		//std::cin.getline(str);
		//s.write(buffer(str));

		char reply[max_length];

		//auto reply_length = s.read(buffer(reply, max_length));

		std::cout << "Reply is: ";
		//std::cout.write(reply, reply_length);
		std::cout << "\n";
	}
	catch(std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
