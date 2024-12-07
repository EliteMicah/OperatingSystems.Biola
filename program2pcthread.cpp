#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;
// Global Variables
// Shared buffer
int buffer = 0;
// Protect the buffer
mutex mtx;
condition_variable cv;
// Track if the buffer is full or empty
bool bufferFull = false;
void producer() {
	// Out of 10 items
	for (int i = 1; i <= 10; i++) {
		unique_lock<mutex> lock(mtx);
		// Wait until buffer is empty
		cv.wait(lock, [] { return !bufferFull; });
		buffer = i; // Produce an item
		cout << "In producer: buffer = " << buffer << endl;
		// Mark the buffer as full
		bufferFull = true;
		// Notify the consumer
		cv.notify_one();
	}
}
void consumer() {
	// Out of 10 items
	for (int i = 1; i <= 10; i++) {
		unique_lock<mutex> lock(mtx);
		// Wait until buffer is full
		cv.wait(lock, [] { return bufferFull; });
		cout << "In consumer: buffer = " << buffer << endl;
		// Consume the item
		buffer = 0;
		// Mark the buffer as empty
		bufferFull = false;
		// Notify the producer thread
		cv.notify_one();
	}
}
int main() {
	cout << "Threads started ..." << endl;
	thread prodThread(producer);
	thread consThread(consumer);
	prodThread.join();
	consThread.join();
	cout << "Ending main(): buffer = " << buffer << endl;
	return 0;
}
