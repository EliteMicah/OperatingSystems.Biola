#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <cstring> // Used for getting current time stamp
#include <string>
using namespace std;
string timeStamp();
int main() {
	pid_t pid = fork(); // Get pid's
	if (pid == -1) { // Fork failed
		cout << "Fork failed.\n";
		exit(1);
	}
	if (pid == 0) { // Child processes
		cout << "I am a child process: my pid = " << pid << "| Time = ";
		cout << timeStamp() << "\n";
		sleep(3);
		cout << "I am a child process: my pid = " << pid << "| Time = ";
		cout << timeStamp();
		exit(0);
	}
	else { // Parent process
		waitpid(-1, 0, 0); // Wait for the child process to finish
		cout << "I am a parent process: child pid = " << pid << "| Time = ";
		cout << timeStamp() << "\n";
		exit(0);
	}
	return 0;
}
string timeStamp() {
	time_t timeStamp = time(0); // Get timestamp
	return ctime(&timeStamp); // Return timestamp in string format
}
