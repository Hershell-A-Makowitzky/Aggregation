/* Compilation: cc -Wall -Werror -pedantic -O2 \ */
/* -I <path to openssl include> \ */
/* -L <path to openssl lib> \ */
/* -lcrypto -pthread -o sha sha_v1.c */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "openssl/sha.h"
#include <pthread.h>

#define THREAD_COUNT 8
#define STR_LEN 64
#define ULL_WIDTH 21

static const char* commandline_input;
static _Thread_local unsigned char result[SHA256_DIGEST_LENGTH];
static const unsigned long long int bruteforce_incremented_integer = 10000000ULL;
static const unsigned long long int bruteforce_incremented_arr[THREAD_COUNT] = {
	bruteforce_incremented_integer,
	bruteforce_incremented_integer << 2,
	bruteforce_incremented_integer << 4,
	bruteforce_incremented_integer << 6,
	bruteforce_incremented_integer << 8,
	bruteforce_incremented_integer << 10,
	bruteforce_incremented_integer << 12,
	bruteforce_incremented_integer << 14,
};

static void* calc(void* arg) {

	unsigned long long int bruteforce_incremented_integer = *(unsigned long long int *) arg;
	const unsigned long long int limit = bruteforce_incremented_integer << 2;
	size_t commnadline_input_string_length = 0;
	const char* argv_iterator = commandline_input;
	char sha_input[STR_LEN + ULL_WIDTH] = {'\0'};
	size_t counter = 0;
	size_t sha_input_length = counter;

	while (*(argv_iterator) != 0) {
		sha_input[commnadline_input_string_length] = *argv_iterator;
		commnadline_input_string_length++, argv_iterator++;
	}

	for (;bruteforce_incremented_integer < limit;) {

		unsigned long long int local = bruteforce_incremented_integer;

		while (local > 0) {
			counter++;
			local /= 10;
		}

		local = bruteforce_incremented_integer;
		counter += commnadline_input_string_length;
		sha_input_length = counter;

		while (local > 0) {
			sha_input[--counter] = local % 10 + 48;
			local /= 10;
		}

		SHA256((unsigned char*) sha_input, sha_input_length, result);

		if (result[0] == 0 && result[1] == 0 && result[2] == 0 && result[3] < 64 && result[3] > 31) {

			printf("Append: %llu\n", bruteforce_incremented_integer);

			for (size_t i = 0; i < SHA256_DIGEST_LENGTH; i++) {
				printf("%02x", result[i]);
			}

			printf("\n");
			exit(0);
		}

		bruteforce_incremented_integer++;
		counter = 0;
	}

	return NULL;
}

int main(int argc, char** argv) {

	size_t commnadline_input_string_length;
	pthread_t thread_arr[THREAD_COUNT];

	if (argc != 2) {
		printf("Usage: <%s> <string>\n", argv[0]);
		return 1;
	}

	if ((commnadline_input_string_length = strlen(argv[1])) > 63) {
		printf("Maximal string length < %d (You've provided string of size %zu)\n", STR_LEN, commnadline_input_string_length);
		return 1;
	}

	commandline_input = argv[1];
	puts("Calculating...");

	for (size_t i = 0; i < THREAD_COUNT; i++) {
		pthread_create(&thread_arr[i], NULL, &calc, (void *) &bruteforce_incremented_arr[i]);
	}

	for (size_t i = 0; i < THREAD_COUNT; i++) {
		pthread_detach(thread_arr[i]);
	}

	while (1) {}

	return 0;
}
