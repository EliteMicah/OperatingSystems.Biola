#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
static volatile int glob = 0;
// Initialize mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void* threadFunc(void* arg) {
	int loops = *((int*)arg);
	for (int j = 0; j < loops; ++j) {
		// Lock mutex before accessing the variable
		pthread_mutex_lock(&mutex);
		glob++;
		// Unlock mutex after accessing the variable
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}
int main(int argc, char* argv[]) {
	pthread_t t1, t2;
	int loops, s;
	loops = (argc > 1) ? atoi(argv[1]) : 10000000;
	s = pthread_create(&t1, NULL, threadFunc, &loops);
	if (s != 0)
		printf("pthread_create");
	s = pthread_create(&t2, NULL, threadFunc, &loops);
	if (s != 0)
		printf("pthread_create");
	s = pthread_join(t1, NULL);
	if (s != 0)
		printf("pthread_join");
	s = pthread_join(t2, NULL);
	if (s != 0)
		printf("pthread_join");
	printf("glob = %d\n", glob);
	// Destroy the mutex
	pthread_mutex_destroy(&mutex);
	exit(EXIT_SUCCESS);
	return 0;
}
