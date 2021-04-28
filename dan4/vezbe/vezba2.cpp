#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

constexpr auto SLEEP = 100;

using namespace std;

struct pairs {
	int x;
	int y;
};
enum class THREAD_STATE
{
	PRODUCE,
	CONSUME
} ;

const pairs base = { 1, 2 };
pairs numbers = { 0 };
mutex m;
condition_variable cv;
THREAD_STATE state = THREAD_STATE::PRODUCE;


static void thread_sum()
{

	while (1)
	{
		unique_lock<mutex> lock(m);
		cv.wait(lock, []() { return state == THREAD_STATE::CONSUME; });
		cout << numbers.x + numbers.y << endl;
		state = THREAD_STATE::PRODUCE;
		cv.notify_one();
		std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP));
	}

}
static void thread_inseart()
{
	static int function_call = 0;
	while (1)
	{
		unique_lock<mutex> lock(m);
		cv.wait(lock, []() { return state == THREAD_STATE::PRODUCE; });
		if (function_call > 2) function_call = 0;
		numbers.x = base.x + 2 * function_call;
		numbers.y = base.y + 2 * function_call;
		function_call++;
		state = THREAD_STATE::CONSUME;
		cv.notify_one();
		std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP));
	}
}

int main()
{
	std::thread thread1(thread_inseart);
	std::thread thread2(thread_sum);
	thread1.join();
	thread2.join();
	return 0;
}

