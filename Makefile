# -----------------------------------------------
#                Variables
# -----------------------------------------------
# Choose of std option
STD              = '-std=c99'
# to compile files
PHILO            = 'Pt1/sources/philosophers.c'
BUFFER           = 'Pt1/sources/buffer.c'
RW               = 'Pt1/sources/rw.c'
CPHILO            = 'Pt2/sources/customPhilosophers.c'
CBUFFER           = 'Pt2/sources/customBuffer.c'
CRW               = 'Pté/sources/customRW.c'
# executables name
PHILO_EXEC       = 'philosophers'
BUFFER_EXEC		 = 'buffer'
RW_EXEC 		 = 'rw'
CPHILO_EXEC      = 'customPhilosophers'
CBUFFER_EXEC	 = 'customBuffer'
CRW_EXEC 		 = 'custoMRW'
# all built files go here
DIR_NAME         = 'built'
EXEC_PHILO_PATH  = 'built/philosophers'
EXEC_BUFFER_PATH = 'built/buffer'
EXEC_RW_PATH     = 'built/rw'
EXEC_CPHILO_PATH  = 'built/customPhilosophers'
EXEC_CBUFFER_PATH = 'built/customBuffer'
EXEC_CRW_PATH     = 'built/customRW'
# test if already built dir exist
LOCKER			 = 'Pt2/sources/locker.c'
SEM  			 = 'Pt2/sources/semaphore.c'
TEST             = `ls | grep $(DIR_NAME) | wc -w | xargs`
DATA_TEST		 = `ls | grep csv | wc -l | xargs`

# -----------------------------------------------
#                Arguments
# -----------------------------------------------

N = 4 # number of philosophers
C = 4 # number of consumers
P = 2 # number of producers
W = 2 # number of writers
R = 4 # number of readers

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

all: clean build csv benchmark # default 'make' command with defaults arguments

run: philo buffer rw

philo:
	-./$(EXEC_PHILO_PATH) $(N)

buffer:
	-./$(EXEC_BUFFER_PATH) $(P) $(C)

rw:
	-./$(EXEC_RW_PATH) $(W) $(R)

cphilo:
	-./$(EXEC_CPHILO_PATH) $(N)

cbuffer:
	-./$(EXEC_CBUFFER_PATH) $(P) $(C)

crw:
	-./$(EXEC_CRW_PATH) $(W) $(R)

clean: clean_build clean_data

clean_build:
	@if [ $(TEST) == 1 ];\
	then rm -r $(DIR_NAME);\
	fi

clean_data:
	@if [ $(DATA_TEST) == 1 ];\
	then rm -r csv;\
	fi

build: build_philo build_buffer build_rw  build_cphilo build_cbuffer build_crw

build_philo:
	@if [ $(TEST) == 0 ];\
	then mkdir $(DIR_NAME);\
	fi
	-gcc $(PHILO) -o $(PHILO_EXEC) $(STD) -lpthread
	-mv -f $(PHILO_EXEC) $(EXEC_PHILO_PATH)

build_buffer:
	@if [ $(TEST) == 0 ];\
	then mkdir $(DIR_NAME);\
	fi
	-gcc $(BUFFER) -o $(BUFFER_EXEC) $(STD) -lpthread
	-mv -f $(BUFFER_EXEC) $(EXEC_BUFFER_PATH)

build_rw:
	@if [ $(TEST) == 0 ];\
	then mkdir $(DIR_NAME);\
	fi
	-gcc $(RW) -o $(RW_EXEC) $(STD) -lpthread
	-mv -f $(RW_EXEC) $(EXEC_RW_PATH)

build_cphilo:
	@if [ $(TEST) == 0 ];\
	then mkdir $(DIR_NAME);\
	fi
	-gcc $(CPHILO) $(LOCKER) -o $(CPHILO_EXEC) -lpthread
	-mv -f $(CPHILO_EXEC) $(EXEC_CPHILO_PATH)

build_cbuffer:
	@if [ $(TEST) == 0 ];\
	then mkdir $(DIR_NAME);\
	fi
	-gcc $(CBUFFER) $(LOCKER) $(SEM) -o $(CBUFFER_EXEC) -lpthread
	-mv -f $(CBUFFER_EXEC) $(EXEC_CBUFFER_PATH)

build_crw:
	@if [ $(TEST) == 0 ];\
	then mkdir $(DIR_NAME);\
	fi
	-gcc $(CRW) $(LOCKER) $(SEM) -o $(CRW_EXEC) -lpthread
	-mv -f $(CRW_EXEC) $(EXEC_CRW_PATH)

csv:
	-./script.sh

benchmark:
	-echo 'incoming soon!'


