DEBUG = -DDEBUG
THREADS = 6
OUTPUT = sha_v1
CC = cc
# alternatively an absolute path to openssl@1.1 installation root directory can be passed to make as OPENSSL=...'
OPENSSL = $(shell brew info openssl@1.1 | grep homebrew | head -1 | cut -d " " -f1)
CFLAGS = -Wall -Wextra -Werror -pedantic -DTHREAD_COUNT=$(THREADS) -pthread -Ofast
LIBS = -I$(OPENSSL)/include -L$(OPENSSL)/lib -lcrypto -o $(OUTPUT)

.PHONY: all debug

all: sha_v1.c
	$(CC) $(CFLAGS) $(LIBS) $<

debug: sha_v1.c
	$(CC) $(CFLAGS) $(DEBUG) $(LIBS) $<
