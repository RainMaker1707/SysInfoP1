#! /bin/bash
# todo add '/usr' before the bin path to run on linux

PHILO_PATH="built/philo.csv"
BUFFER_PATH="built/buffer.csv"
RW_PATH="built/rw.csv"

make clean
make build


echo "Thread number, compilation time" > ${PHILO_PATH}
for I in 2 3 4 5 6 7 8
do
  for _ in 1 2 3 4 5
  do
    /usr/bin/time -o ${PHILO_PATH} -a -f  "${I}, %e" make philo N=${I} -s
  done
done


echo "Thread number, compilation time" > ${BUFFER_PATH}
for I in 2 3 4 5 6 7 8
do
  for _ in 1 2 3 4 5
  do
    /usr/bin/time -o ${BUFFER_PATH} -a -f  "${I}, %e" make buffer P=${I} C=${I}$
  done
done

echo "Thread number, Compilation time" > ${RW_PATH}
for I in 2 3 4 5 6 7 8
do
  for _ in 1 2 3 4 5
  do
    /usr/bin/time -o ${RW_PATH} -a -f  "${I}, %e" make rw W=${I} R=${I} -s
  done
done