#! /bin/bash
# todo add '/usr' before the bin path to run on linux

PHILO_PATH="csv/philo.csv"
BUFFER_PATH="csv/buffer.csv"
RW_PATH="csv/rw.csv"
CORE=$(grep -c ^processor /proc/cpuinfo)

make clean
make build

if [ $(ls | grep csv | wc -l | xargs) == 0 ]
then mkdir csv
fi

echo "Thread number, Compilation time" > ${PHILO_PATH}
for (( I=2; I<=CORE*2; I++))
do
  for _ in {1..5}
  do
    /usr/bin/time -o ${PHILO_PATH} -a -f  "${I}, %e" make philo N=${I} -s
  done
done


echo "Thread number, Producer number, Consumer number, Compilation time" > ${BUFFER_PATH}
for (( I=1; I<=CORE; I++))
do
  for (( J=1; J<=CORE; J++))
  do
    for _ in {1..5}
    do
      V=$((${I} + ${J}))
      /usr/bin/time -o ${BUFFER_PATH} -a -f  "${V}, ${I}, ${J},  %e" make buffer P="${I}" C="${J}" -s
    done
  done
done

echo "Thread number, Write number, Reader number, Compilation time" > ${RW_PATH}
for (( I=2; I<=CORE; I++))
do
  for (( J=1; J<=CORE; J++))
  do
    for _ in {1..5}
    do
      V=$((${I} + ${J}))
      /usr/bin/time -o ${RW_PATH} -a -f  "${V}, ${I}, ${J}, %e" make rw W=${I} R=${J} -s
    done
  done
done

make clean_build