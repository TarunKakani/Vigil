CC	:= gcc
CFLAGS	:= -Wall -Wextra

main: sysinfo/main.c
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -rf main
