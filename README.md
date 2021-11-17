sysInfoP1

### Philosophers problem
The number of philosphers is an arguments of the c program.\
This program create and run a number of threads equal to the 
number of philosophers and use a mutex_lock and unlock to simulate
the chopsticks on the table.\
Each philosophers has to do 10'000 cycles 'to think -> to eat'.\
No sleeped time, we want to be accurate with the benchmark.

### Producer-Consumer problem
    todo...

### Reader-Writer memory access problem
    todo...

### Automated Benchmark
The project want us to implement a bash script which take the C program
in argument and run the compilation and the program several time to make
as much data as possible on time used.\
After this part we have to implement a python script using matplotlib
to make a benchmark of these data we collected with the bash script.
#### Bash script: data collect
#### Python script: plotting and computing

### Makefile
- **make**: clean build and run all program
- **make**: clean 
- **make build**: build: all program
- **make run**: run all: program
- **make build_philo**: explicit
- **make build_buffer**: explicit
- **make build_rw**: explicit
- **make philo**: run philo
- **make buffer**: run buffer
- **make rw**: run rw
- **make csv**: write out the runtime data get by bash script in .csv file
- **make benchmark**: call python and bash scripts
