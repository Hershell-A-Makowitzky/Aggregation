#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "openssl/sha.h"
#include <pthread.h>

#define ULL_WIDTH 20
#define number unsigned long long int
#define STR_LEN 64

#ifndef THREAD_COUNT
#define THREAD_COUNT 6
#endif

static const char* cmd_in;
static const number bii = 10000000ULL;
static number bia[THREAD_COUNT];

static void init(void) {
	if (THREAD_COUNT > 0 && THREAD_COUNT <=16 ) {
		for (size_t i = 0; i < THREAD_COUNT; i++) {
			if (i == 0) {
				bia[i] = bii;
			}
			bia[i] = bii << (i * 2);
		}
	} else {
		printf("THREADS EXHAUSTED!");
		exit(1);
	}
}

static void* calc(void* arg) {

	unsigned char result[SHA256_DIGEST_LENGTH];
	number bii = *(number *) arg;
	const number limit = bii << 2;
	size_t cmd_in_str_len = 0;
	const char* argv_iterator = cmd_in;
	char sha_in[STR_LEN + ULL_WIDTH] = {'\0'};
	size_t counter = 0;
	size_t sha_in_len = counter;

	#ifdef DEBUG
	printf("%llu\n", bii);
	#endif

	while (*(argv_iterator) != 0) {
		sha_in[cmd_in_str_len] = *argv_iterator;
		cmd_in_str_len++, argv_iterator++;
	}

	while (bii < limit) {

		number local = bii;

		while (local > 0) {
			counter++;
			local /= 10;
		}

		local = bii;
		counter += cmd_in_str_len;
		sha_in_len = counter;

		while (local > 0) {
			sha_in[--counter] = local % 10 + 48;
			local /= 10;
		}

		SHA256((unsigned char*) sha_in, sha_in_len, result);

		#ifdef DEBUG
		printf("SHA_IN: %s\n", sha_in);
		printf("SHA_LENGTH: %zu\n", sha_in_len);
		printf("RESULT: %d\n", result[0] == 0 && result[1] == 0 && result[2] == 0 && result[3] > 31 && result[3] < 64);
		printf("Append: %llu\n", bii);
		for (size_t i = 0; i < SHA256_DIGEST_LENGTH; i++) {
			printf("%02x", result[i]);
		}
		exit(1);
		#endif

		if (result[0] == 0 && result[1] == 0 && result[2] == 0 && result[3] > 31 && result[3] < 64) {

			printf("Append: %llu\n", bii);

			for (size_t i = 0; i < SHA256_DIGEST_LENGTH; i++) {
				printf("%02x", result[i]);
			}

			printf("\n");
			exit(0);
		}

		bii++;
		counter = 0;
	}

	#ifdef DEBUG
	puts("DONE");
	#endif
	return NULL;
}

int main(int argc, char** argv) {

	init();

	size_t cmd_in_str_len;
	pthread_t thread_arr[THREAD_COUNT];

	if (argc != 2) {
		printf("Usage: <%s> <string>\n", argv[0]);
		return 1;
	}

	if ((cmd_in_str_len = strlen(argv[1])) > 63) {
		printf("Maximal string length < %d (You've provided string of size %zu)\n", STR_LEN, cmd_in_str_len);
		return 1;
	}

	cmd_in = argv[1];
	puts("Calculating...");

	for (size_t i = 0; i < THREAD_COUNT; i++) {
		pthread_create(&thread_arr[i], NULL, &calc, (void *) &bia[i]);
		pthread_detach(thread_arr[i]);
	}

	while (1) {}

	return 0;
}
