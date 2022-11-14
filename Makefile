build:
	gcc -o linuxFileSystem *.c -g -Wall -Wextra
run:
	./linuxFileSystem
clean:
	rm -rf linuxFileSystem