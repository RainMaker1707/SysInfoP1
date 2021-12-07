# sysInfoP1

### Makefile commands
- **make**: clean build run script and then run benchmark
- **make clean**: clean build and  data
- **make clean_data**: clean only data
- **make clean_build**: clean only  build
- **make build**: build: all program
    - you can build a program one by one using make build_\<progName\> i.e
    - **make build_philo**: explicit
    - **make build_buffer**: explicit
    - **make build_rw**: explicit
    - **make build_cphilo**: explicit
    - **make build_cbuffer**: explicit
    - **make build_crw**: explicit
- **make run**: run all programs with default arguments
    - **make philo**: run philo
    - **make buffer**: run buffer
    - **make rw**: run rw
    - **make cphilo**: run philo
    - **make cbuffer**: run buffer
    - **make crw**: run rw
- **make csv**: write out the runtime data get by bash script in .csv file
- **make benchmark**: call python script

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

