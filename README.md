sysInfoP1

### Philosophers problem
The number of philosphers is an arguments of the c program.\
This program create and run a number of threads equal to the 
number of philosophers and use a mutex_lock and unlock to simulate
the chopsticks on the table.\
Each philosophers has to do 10'000 cycles 'to think -> to eat'.\
No sleeped time, we want to be accurate with the benchmark.

### Automated Benchmark
The project want us to implement a bash script which take the C program
in argument and run the compilation and the program several time to make
as much data as possible on time used.\
After this part we have to implement a python script using matplotlib
to make a benchmark of these data we collected with the bash script.

### Makefile
- make
- make clean
- make benchmark (call python and bash scripts)
