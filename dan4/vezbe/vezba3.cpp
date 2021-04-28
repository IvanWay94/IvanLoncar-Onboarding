#include <iostream>
#include <thread>
#include <mutex>
#include <cstdlib>
#include <condition_variable>
#include <array>

constexpr auto RING_SIZE = 128;
constexpr auto SLEEP = 50;
constexpr auto SLEEP1 = 100;
constexpr auto SLEEP2 = 10;

using namespace std;

struct Semaphore {
	Semaphore() = default;
	Semaphore(int x) : m_s(x) {}
	void signal() {
		std::unique_lock<std::mutex> lock(m_mut);
		m_s += 1;
		m_cv.notify_one();
	}
	void wait() {
		std::unique_lock<std::mutex> lock(m_mut);
		m_cv.wait(lock, [this]() { return m_s != 0; });
		m_s -= 1;
	}
private:
	int m_s = 0;
	std::mutex m_mut;
	std::condition_variable m_cv;
};

struct ring_buffer {
	void write(unsigned char x);
	int read();
private:
	std::array<int, 10> m_buff;
	int m_w = 0;
	int m_r = 0;
	Semaphore m_empty{ 10 };
	Semaphore m_full;
	std::mutex m_mut;
};

void ring_buffer::write(unsigned char x) {
	m_empty.wait();
	std::lock_guard<std::mutex> l(m_mut);
	m_buff[m_w] = x;
	m_w = m_w % 10 == 9 ? 0 : m_w + 1;
	m_full.signal();
}

int ring_buffer::read() {
	m_full.wait();
	std::lock_guard<std::mutex> l(m_mut);
	int res = m_buff[m_r];
	m_r = m_r % 10 == 9 ? 0 : m_r + 1;
	m_empty.signal();
	return res;
}


static ring_buffer inputArr[RING_SIZE];
static ring_buffer outputArr[RING_SIZE];

/*mutex in;
mutex out;
condition_variable cv_in;
condition_variable cv_out;*/

static void InputThread() {
	unsigned char l;
	while (1) {
		l = rand() % 26 + 'a';
		//unique_lock<mutex> locki(in);
		//cv_in.wait(locki);
		inputArr->write(l);
		cout << "Input Thread lowcase letter:" << l << endl;
		//cv_in.notify_one();
		std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP2));
	}
}
static void ProcessingThread() {
	unsigned char l;
	while (1) {
		//unique_lock<mutex> locki(in);
		//cv_in.wait(locki);
		l = inputArr->read();
		//cv_in.notify_one();

		l -= 32;

		//unique_lock<mutex> locko(out);
		//cv_out.wait(locko);
		outputArr->write(l);
		//cv_out.notify_one();

		std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP));
	}
}
static void OutputThread() {
	unsigned char l;
	while (1) {
		//unique_lock<mutex> locko(out);
		//cv_out.wait(locko);
		l = outputArr->read();
		//cv_out.notify_one();
		cout << "Output Thread capital letter:" << l << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP1));
	}
}

int main()
{
	thread thread1(InputThread);
	thread thread2(ProcessingThread);
	thread thread3(OutputThread);

	thread1.join();
	thread2.join();
	thread3.join();
	return 0;
}

