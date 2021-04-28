#include <iostream>
#include <thread>

static void thread_print(int print_num, int sleep, std::thread *thread_join)
{
	std::this_thread::sleep_for(std::chrono::seconds(sleep));
	std::cout << print_num << std::endl;

	if (thread_join != nullptr)
	{
		thread_join->join();
	}
}
int main()
{
	std::thread thread1(thread_print, 1, 3, nullptr);
	std::thread thread2(thread_print, 2, 0, &thread1);
	std::thread thread3(thread_print, 3, 0, &thread2);
	thread3.join();
	return 0;
}

