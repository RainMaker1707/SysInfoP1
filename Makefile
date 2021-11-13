# -----------------------------------------------
#                Variables
# -----------------------------------------------
STD = '-std=c99'       # Choose of std option
MAIN = 'main.c'        # to compile file
EXEC = 'main'          # executable name
DIR_NAME = 'built' # all build files go here
EXEC_PATH = 'built/main'
TEST = `ls | grep $(DIR_NAME) | wc -w | xargs`

# -----------------------------------------------
#                Parameters
# -----------------------------------------------
ifndef VERBOSE
.SILENT: # true is silent by default, set to false to make it verbose
endif
# -----------------------------------------------
#                 Functions
# -----------------------------------------------
all: build run # default 'make' command

clean:
	@if [ $(TEST) = 1 ];\
	then rm -r $(DIR_NAME);\
	fi

build:
	@if [ $(TEST) == 0 ];\
	then mkdir $(DIR_NAME);\
	fi
	gcc -O $(MAIN) -o $(EXEC) $(STD)
	mv -f $(EXEC) $(EXEC_PATH)

run:
	@if [ $(TEST) == 0 ];\
	then make build;\
	fi
	-./$(EXEC_PATH)


benchmark:
	-echo 'incoming soon!'


