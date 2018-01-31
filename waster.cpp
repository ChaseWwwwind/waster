#include <iostream>
#include <string>
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

int ReadInt(std::string& input)
{
	while (true)
	{
		read(input);
		print("");

		try { return std::stoi(input); }
		catch (std::out_of_range) { print("The entered number is too big. Please try again."); }
		catch (std::invalid_argument) { print("Please enter an integer number."); }
		catch (std::exception) { print("This is impossible. Please try again."); }
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
	print("waster v1.0");
	print("");

	_1MB ** allocations = nullptr;
	int allocations_count = 0;

	std::string input;

	while (true)
	{
		print("0. Exit");
		print("1. Waste CPU");
		print("2. Waste RAM");
		read(input);
		print("");

		if (input.compare("0") == 0)
		{
			print("Are you sure you want to exit? (y/n)");
			read(input);
			if (input[0] == 'y' || input[0] == 'Y' || input[0] == '1')
				return 0;
			else
				print("");
		}
		else if (input.compare("1") == 0)
		{
			// stop the previous threads
			mutex.lock();
			current_thread_id++;
			mutex.unlock();

			// get the new threads count from user
			print("How many threads of CPU to waste?");
			int count = ReadInt(input);

			// create the new threads
			for (int i = 0; i < count; i++)
			{
				std::thread thread = std::thread(WasteThread, current_thread_id);
				thread.detach();
			}
		}
		else if (input.compare("2") == 0)
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
			print("How many MBs of RAM to waste?");
			int count = ReadInt(input);

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
			print("");
		}
	}
}