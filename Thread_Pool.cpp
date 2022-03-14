#include "Thread_Pool.h"

Thread_Pool::Thread_Pool(const size_t numOfThread)
:eventStopping(false)
{
		if(numOfThread > std::thread::hardware_concurrency() || numOfThread < 1)
		{
				std::cout << "this amount of thread is not supported by hardware, it was set to default" << std::endl;
				threads_count = std::thread::hardware_concurrency();
		}
		else
				threads_count = numOfThread;
		
		start_work();
}

void Thread_Pool::push_task(Task task)
{
		{
				std::unique_lock<std::mutex> ul(mtx);
				work_queue.emplace(std::move(task));
		}

		eventCond.notify_one();
}

void Thread_Pool::reset(const size_t numOfThread)
{

}

std::thread::id Thread_Pool::get_id_of_thread()
{
		std::thread::id id_of_thread = std::this_thread::get_id();
		return id_of_thread;
}

void Thread_Pool::start_work()
{
		for(size_t i = 0 ; i < threads_count ; ++i)
		{
				vecOfThreads.emplace_back([=]
				{
						while(true)
						{
								Task task;
								{
										std::unique_lock<std::mutex> ul(mtx);
										eventCond.wait(ul , [=] { return eventStopping || !work_queue.empty();});

										if(eventStopping && work_queue.empty())
												break;
										
										task = std::move(work_queue.front());
										work_queue.pop();
								}
								task();
						}
				});
		}
}


Thread_Pool::~Thread_Pool()
{
		for(size_t i = 0 ; i < threads_count ; ++i)
		{
				vecOfThreads[i].join();
		}
}


