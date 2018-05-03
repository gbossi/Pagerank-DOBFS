OMP_NUM_THREADS=2 ./test -i test.dot -o log_2.txt 
OMP_NUM_THREADS=4 ./test -i test.dot -o log_4.txt
OMP_NUM_THREADS=8 ./test -i test.dot -o log_8.txt
OMP_NUM_THREADS=16 ./test -i test.dot -o log_16.txt
OMP_NUM_THREADS=24 ./test -i test.dot -o log_24.txt
