#include <iostream>
#include <thread>
#include <mutex>

#define print(msg) (std::cout << msg << '\n')
#define read(var) (std::cout << "    > "); (std::cin >> var)
#define byte unsigned char

int current_thread_id = 0;
std::mutex mutex;

void WasteThread(int thread_id)
{
	while (true)
	{
		std::lock_guard<std::mutex> guard(mutex);
		if (current_thread_id != thread_id)
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
	print("waster v0.2");
	print("");

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
			// stop the previous threads
			mutex.lock();
			current_thread_id++;
			mutex.unlock();

			// get the new threads count from user
			int count;
			print("How many threads of CPU to waste?");
			read(count);
			print("");

			// create the new threads
			for (int i = 0; i < count; i++)
			{
				std::thread thread = std::thread(WasteThread, current_thread_id);
				thread.detach();
			}
		}
		else if (input == '2')
		{
			// free up the previously allocated memory
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

			// get the new allocation size from user
			int count;
			print("How many MBs of RAM to waste?");
			read(count);
			print("");

			// allocate
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