# define any directories containing header files other than /usr/include
#
INCLUDES = -I./inc
SRCPATH= ./src

# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
#
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#
# for C++ define  CC = g++
CC = gcc
CFLAGS  = -g -Wall 

# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#
default: ReadElf

# To create the executable file count we need the object files
#
ReadElf:  readelf.o files_Dir.o
	$(CC) $(CFLAGS) -o ReadElf readelf.o files_Dir.o



readelf.o:  $(SRCPATH)/readelf.c
	$(CC) $(CFLAGS)  $(INCLUDES) -c $<


files_Dir.o:  $(SRCPATH)/files_Dir.c
	$(CC) $(CFLAGS)  $(INCLUDES) -c $<


# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) count *.o *~
