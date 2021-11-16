# -----------------------------------------------
#                Variables
# -----------------------------------------------
# Choose of std option
STD              = '-std=c99'
# to compile files
PHILO            = 'philosophers.c'
BUFFER           = 'buffer.c'
RW               = 'rw.c'
# executables name
PHILO_EXEC       = 'philosophers'
BUFFER_EXEC		 = 'buffer'
RW_EXEC 		 = 'rw'
# all build files go here
DIR_NAME         = 'built'
EXEC_PHILO_PATH  = 'built/philosophers'
EXEC_BUFFER_PATH = 'built/buffer'
EXEC_RW_PATH     = 'built/rw'
# test if already built dir exist
TEST             = `ls | grep $(DIR_NAME) | wc -w | xargs`

# -----------------------------------------------
#                Arguments
# -----------------------------------------------

N = 4 # number of philosophers
P = 2 # number of producers
C = 2 # number of consumers
W = 2 # number of writers
R = 2 # number of readers

# -----------------------------------------------
#                Parameters
# -----------------------------------------------
ifndef VERBOSE
.SILENT: # silent by default, set to false to make it verbose
endif
.DEFAULT_GOAL: all
.PHONY: help all clean build csv benchmark
SHELL := /bin/bash

# -----------------------------------------------
#                 Functions
# -----------------------------------------------

all: clean build run # default 'make' command with defaults arguments

run: philo buffer rw

philo:
	-./$(EXEC_PHILO_PATH) $(N)

buffer:
	-./$(EXEC_BUFFER_PATH) $(P) $(C)

rw:
	-./$(EXEC_RW_PATH) $(W) $(R)

clean:
	@if [ $(TEST) == 1 ];\
	then rm -r $(DIR_NAME);\
	fi

build: build_philo build_buffer build_rw

build_philo:
	@if [ $(TEST) == 0 ];\
	then mkdir $(DIR_NAME);\
	fi
	-gcc -lpthread -O $(PHILO) -o $(PHILO_EXEC) $(STD)
	-mv -f $(PHILO_EXEC) $(EXEC_PHILO_PATH)

build_buffer:
	@if [ $(TEST) == 0 ];\
	then mkdir $(DIR_NAME);\
	fi
	-gcc -lpthread -O $(BUFFER) -o $(BUFFER_EXEC) $(STD)
	-mv -f $(BUFFER_EXEC) $(EXEC_BUFFER_PATH)

build_rw:
	@if [ $(TEST) == 0 ];\
	then mkdir $(DIR_NAME);\
	fi
	-gcc -lpthread -O $(RW) -o $(RW_EXEC) $(STD)
	-mv -f $(RW_EXEC) $(EXEC_RW_PATH)

csv:
	-echo 'incoming soon!'

benchmark:
	-echo 'incoming soon!'


