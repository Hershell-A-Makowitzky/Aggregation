#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<openssl/sha.h>
#include<pthread.h>

#define THREAD_COUNT 8
#define STR_LEN 64

static int done = 0;
static const char* input;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static _Thread_local unsigned char result[SHA256_DIGEST_LENGTH];
static const unsigned long long int increment = 10000000ULL;
static const unsigned long long int increment_arr[THREAD_COUNT] = 
{	
	increment,
	increment << 2,
	increment << 4,
	increment << 6,
	increment << 8,
	increment << 10,
	increment << 12,
	increment << 14,
};

static void* 
calc(void* arg) 
{
	unsigned long long int increment = *(unsigned long long int*) arg;
	size_t string_length = 0;
	size_t increment_length = 0;
	const char* argv_iterator = input;
	char sha_input[STR_LEN] = {'\0'};

	while (*(argv_iterator) != 0) 
	{
		string_length++, argv_iterator++;
	}

	strcpy(sha_input, input);

	for (;;) 
	{
		increment_length = sprintf((sha_input + string_length), "%llu", increment);
		SHA256((unsigned char*) sha_input, (string_length + increment_length), result);
		
		if (result[0] == 0 && result[1] == 0 && result[2] == 0 && result[3] < 64 && result[3] > 31) 
		{	
			printf("Append: %llu\n", increment);
			pthread_mutex_lock(&mutex);
			done = 1;
			pthread_mutex_unlock(&mutex);
			pthread_cond_signal(&cond);
			return NULL;
		}
		increment++;
	}
}

int
main(int argc, char** argv)
{
	size_t string_length;
	pthread_t thread_arr[THREAD_COUNT];

	if (argc != 2)
	{
		printf("Usage: <%s> <string>\n", argv[0]);
		return (1);
	}
	
	if ((string_length = strlen(argv[1])) > 63)
	{
		printf("Maximal string length < %d (You've provided string of size %zu)\n", STR_LEN, string_length);
		return (1);
	}

	input = argv[1];
	puts("Calculating...");
	
	for (size_t i = 0; i < THREAD_COUNT; i++)
	{
		pthread_create(&thread_arr[i], NULL, &calc, (void*) &increment_arr[i]);
	}

	for (size_t i = 0; i < THREAD_COUNT; i++)
	{
		pthread_detach(thread_arr[i]);
	}

	pthread_mutex_lock(&mutex);
	while (!done)
	{
		pthread_cond_wait(&cond, &mutex);
	}
	pthread_mutex_unlock(&mutex);

	return (0);
}
