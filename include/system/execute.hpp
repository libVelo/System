#ifndef CHATIQ_EXECUTE_H
#define CHATIQ_EXECUTE_H

#include <string>
#include <string_view>

namespace system::process
{
	std::string execute(std::string_view cmd)
	{
		char        buffer[128];
		std::string result;
		FILE* pipe = popen(cmd.data(), "r");

		if(!pipe)
			throw std::system_error(errno, std::system_category());
		try
		{
			while(!feof(pipe))
				if(fgets(buffer, 128, pipe) != nullptr)
					result += buffer;
		}
		catch(...)
		{
			pclose(pipe);
			throw;
		}

		pclose(pipe);
		return std::move(result);
	}
}

#endif //CHATIQ_EXECUTE_H
