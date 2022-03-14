#pragma once
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <atomic>
#include <future>

class Thread_Pool {
public:
		using Task = std::function<void()>;
		explicit Thread_Pool(const size_t);
		void push_task(Task task);
		void reset(const size_t);
		std::thread::id get_id_of_thread();
		~Thread_Pool();
private:
		void start_work();
		std::mutex mtx;
		std::condition_variable eventCond;
		bool eventStopping;
		size_t threads_count;
		std::queue<Task> work_queue;
		std::vector<std::thread> vecOfThreads;

};
