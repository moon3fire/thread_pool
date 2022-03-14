#include "Thread_Pool.h"
#include <string>
#include <sstream>
#include <chrono>

std::string idToString()
{
		std::stringstream ss;
		ss << std::this_thread::get_id();
		int id_num;
		ss >> id_num;
		return std::to_string(id_num);
}

int main()
{
		Thread_Pool obj(25);
		for(size_t i = 0 ; i < 3000 ; ++i)
		{
				obj.push_task([&]()
				{
						int num = rand() % 100 + 1;
						std::cout << std::to_string(num) + " | thread ID - " + idToString() + "\n";

				});
		}
}
