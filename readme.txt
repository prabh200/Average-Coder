Compilation:
Type 'make all' into a terminal.
Type 'make clean' to clear all the object files.
If compilation fails, try changing the first line in the Makefile.
    CC = clang++
to
    CC = g++

Running the program:
Type './main' or 'make run' into a terminal.

cURL:
Type 'curl' into a terminal.
If your computer says that the command doesn't exist, follow it's instructions on how to install cURL.


The program will leak 16 bytes of memory every time it is used to get directions. Make sure you restart the program every million uses.