#ifndef VELO_MESSAGE_QUEUE_HPP
#define VELO_MESSAGE_QUEUE_HPP

#include <string_view>

namespace os
{
	class message_queue
	{
		public:
			enum flags { READ, WRIRE, READ_WRITE };

			message_queue(std::string_view, flags);

			virtual ~message_queue();

			std::size_t read();

			std::size_t write();

		private:
			int descriptor;
	};
}

#endif
