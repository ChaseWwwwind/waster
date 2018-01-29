#include <iostream>
#include <thread>
#include <mutex>
#define print(msg) (std::cout << msg << '\n')
#define read(var) (std::cout << "    > "); (std::cin >> var)
#define byte unsigned char

bool should_terminate = false;
std::mutex mutex;
void WasteCPU()
{
	int a = 2;
	int b = 2;
	int c = 2;
	int d = 2;
	while (true)
	{
		a = a * 2;
		b = b * 2;
		c = c * 2;
		d = d * 2;
		a = a / 2;
		b = b / 2;
		c = c / 2;
		d = d / 2;

		std::lock_guard<std::mutex> guard(mutex);
		if (should_terminate)
			return;
	}
}

struct _1KB
{
	byte Bytes[1024];
};

struct _1MB
{
	_1KB KBs[1024];
};

int main()
{
	print("waster v0.1");
	print("");

	std::thread ** threads = nullptr;
	int threads_count = 0;

	_1MB ** allocations = nullptr;
	int allocations_count = 0;

	while (true)
	{
		char input;
		print("0. Exit");
		print("1. Waste CPU");
		print("2. Waste RAM");
		read(input);
		print("");

		if (input == '0')
		{
			print("Are you sure you want to exit? (y/n)");
			read(input);
			if (input == 'y' || input == 'Y' || input == '1')
				return 0;
			else
				print("");
		}
		else if (input == '1')
		{
			mutex.lock();
			should_terminate = true;
			mutex.unlock();

			if (threads_count > 0)
			{
				for (int i = 0; i < threads_count; i++)
				{
					threads[i]->join();
					delete threads[i];
				}
				delete[] threads;
				threads = nullptr;
				threads_count = 0;
			}

			mutex.lock();
			should_terminate = false;
			mutex.unlock();

			int count;
			print("How many threads of CPU to waste?");
			read(count);
			print("");

			if (count > 0)
			{
				threads = new std::thread*[count];
				threads_count = count;
				for (int i = 0; i < count; i++)
				{
					threads[i] = new std::thread(WasteCPU);
				}
			}
		}
		else if (input == '2')
		{
			if (allocations_count > 0)
			{
				for (int i = 0; i < allocations_count; i++)
				{
					delete allocations[i];
				}
				delete[] allocations;
				allocations = nullptr;
				allocations_count = 0;
			}

			int count;
			print("How many MBs of RAM to waste?");
			read(count);
			print("");

			if (count > 0)
			{
				allocations = new _1MB*[count];
				allocations_count = count;
				for (int i = 0; i < count; i++)
				{
					allocations[i] = new _1MB();
				}
			}
		}
		else
		{
			print("Not a valid input.");
		}
	}
}