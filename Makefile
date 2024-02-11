#AUTHOR: Otakar Kočí
#DATE: 11/2/2024
#DESCRIPTION: Makefile for veggie lottery

CC=gcc
CFLAGS_DEBUG=-std=c99 -Wall -Wextra -Werror -g
CFLAGS_RELEASE=-std=c99 -Wall -Wextra -Werror -O2

#debug - default
debug: veggie_debug.o message_debug.o
	$(CC) $(CFLAGS_DEBUG) main.c veggie_debug.o message_debug.o -o debug
veggie_debug.o: veggie.c
	$(CC) $(CFLAGS_DEBUG) -c veggie.c -o veggie_debug.o
message_debug.o: message.c
	$(CC) $(CFLAGS_DEBUG) -c message.c -o message_debug.o
#release
release: veggie_release.o message_release.o
	$(CC) $(CFLAGS_RELEASE) main.c veggie_release.o message_release.o -o release
veggie_release.o: veggie.c
	$(CC) $(CFLAGS_RELEASE) -c veggie.c -o veggie_release.o
message_release.o: message.c
	$(CC) $(CFLAGS_RELEASE) -c message.c -o message_release.o
#clean
clean:
	rm *.o debug release
