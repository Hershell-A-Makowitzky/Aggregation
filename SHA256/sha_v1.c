#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "openssl/sha.h"
#include <pthread.h>

#define THREAD_COUNT 8
#define STR_LEN 64
#define WIDTH 21

static const char* input;
/* static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; */
/* static pthread_cond_t cond = PTHREAD_COND_INITIALIZER; */
static _Thread_local unsigned char result[SHA256_DIGEST_LENGTH];
/* static _Thread_local char table[WIDTH] = {'\0'}; */
/* static _Thread_local size_t counter = 0; */
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

/* inline static void size(unsigned long long int ull, size_t* counter) { */
/* 	while (ull > 0) { */
/* 		counter++; */
/* 		ull /= 10; */
/* 	} */
/* } */

/* inline static void ping(unsigned long long int ull, size_t counter, char* table) { */
/* 	while (ull > 0) { */
/* 		table[--counter] = ull % 10 + 48; */
/* 		ull /= 10; */
/* 	} */
/* } */

static void*
calc(void* arg) 
{
	unsigned long long int increment = *(unsigned long long int*) arg;
	/* printf("Argument = %llu\n", increment); */
	size_t string_length = 0;
	const char* argv_iterator = input;
	char sha_input[STR_LEN] = {'\0'};
	size_t counter = 0;
	/* char table[WIDTH] = {'\0'}; */
	/* while (increment > 0) { */
	/* 	counter++; */
	/* 	increment /= 10; */
	/* } */
	size_t increment_length = counter;
	/* printf("Counter = %zu\n", counter); */
	/* printf("Increment = %zu\n", increment_length); */

	while (*(argv_iterator) != 0) 
	{
		sha_input[string_length] = *argv_iterator;
		string_length++, argv_iterator++;
	}

	/* counter += string_length; */
	/* while (increment > 0) { */
	/* 	sha_input[--counter] = increment % 10 + 48; */
	/* 	increment /= 10; */
	/* } */
	/* ping(increment, string_length + counter, table); */
	/* strcpy(sha_input, input); */

	for (;;)
	{
		unsigned long long int local = increment;
		while (local > 0) {
			counter++;
			local /= 10;
		}
		/* printf("Counter = %zu\n", counter); */
		local = increment;
		/* printf("Local = %zu\n", counter); */
		counter += string_length;
		/* printf("Counter = %zu\n", counter); */
		increment_length = counter;
		while (local > 0) {
			sha_input[--counter] = local % 10 + 48;
			local /= 10;
		}
		/* printf("Counter after down = %zu\n", counter); */
		/* printf("%s\n", sha_input); */
		/* increment_length = sprintf((sha_input + string_length), "%llu", increment); */
		SHA256((unsigned char*) sha_input, increment_length, result);
		
		if (result[0] == 0 && result[1] == 0 && result[2] == 0 && result[3] < 64 && result[3] > 31) 
		{	
			printf("Append: %llu\n", increment);
			for (size_t i = 0; i < SHA256_DIGEST_LENGTH; i++) {
				printf("%02x", result[i]);
			}
			printf("\n");
			exit(0);
		}
		increment++;
		counter = 0;
	}
	exit(1);
}

int
main(int argc, char** argv)
{
	size_t string_length;
	/* pthread_t thread_arr[THREAD_COUNT]; */

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
	puts("Calculating in C programming language...");
	
	pthread_t th1;
	pthread_t th2;
	pthread_t th3;
	pthread_t th4;
	pthread_t th5;
	pthread_t th6;
	pthread_t th7;
	pthread_t th8;

	pthread_create(&th1, NULL, &calc, (void*) &increment_arr[0]);
	pthread_create(&th2, NULL, &calc, (void*) &increment_arr[1]);
	pthread_create(&th3, NULL, &calc, (void*) &increment_arr[2]);
	pthread_create(&th4, NULL, &calc, (void*) &increment_arr[3]);
	pthread_create(&th5, NULL, &calc, (void*) &increment_arr[4]);
	pthread_create(&th6, NULL, &calc, (void*) &increment_arr[5]);
	pthread_create(&th7, NULL, &calc, (void*) &increment_arr[6]);
	pthread_create(&th8, NULL, &calc, (void*) &increment_arr[7]);

	pthread_detach(th1);
	pthread_detach(th2);
	pthread_detach(th3);
	pthread_detach(th4);
	pthread_detach(th5);
	pthread_detach(th6);
	pthread_detach(th7);
	pthread_detach(th8);
	/* for (size_t i = 0; i < THREAD_COUNT; i++) */
	/* { */
	/* 	pthread_create(&thread_arr[i], NULL, &calc, (void*) &increment_arr[i]); */
	/* } */

	/* for (size_t i = 0; i < THREAD_COUNT; i++) */
	/* { */
	/* 	pthread_detach(thread_arr[i]); */
	/* } */

	/* pthread_mutex_lock(&mutex); */
	/* while (!done) */
	/* { */
	/* 	pthread_cond_wait(&cond, &mutex); */
	/* } */
	/* pthread_mutex_unlock(&mutex); */

	while (1) {}

	return (0);
}
