all: algorithms test

algorithms: main.cpp  graph.cpp utils.cpp dobfs.cpp parallel_dobfs.cpp pagerank.cpp fixed_pagerank.cpp
	g++ --std=c++11 main.cpp graph.cpp utils.cpp dobfs.cpp parallel_dobfs.cpp pagerank.cpp fixed_pagerank.cpp -fopenmp -lboost_graph -o algorithms

test: test.cpp graph.cpp utils.cpp dobfs.cpp parallel_dobfs.cpp pagerank.cpp fixed_pagerank.cpp
	g++ --std=c++11 test.cpp graph.cpp utils.cpp dobfs.cpp parallel_dobfs.cpp pagerank.cpp fixed_pagerank.cpp -fopenmp -lboost_graph -o test


