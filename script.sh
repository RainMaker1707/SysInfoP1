#! /bin/bash
# todo add '/usr' before the bin path to run on linux

PHILO="built/philo.csv"
make clean
make build

echo "Thread number, compilation time" > ${PHILO}
for I in [1 2 4 8 16]
do
  /usr/bin/time -o ${PHILO} -a -f  "${I}, %e" make philo N="${I}"-s -j "${I}"
done
