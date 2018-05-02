#include "utils.hpp"


Translator::Translator(Graph g){

    size_t numV = boost::num_vertices(g);
	auto index = boost::get(boost::vertex_index, g);
    auto id = boost::get(&Vertex::id, g);

	fromIDtoIndex.assign(numV,0);
	fromIndextoID.assign(numV,0);

	#pragma omp parallel for
	for (size_t i = 0; i < numV; ++i){
    	fromIndextoID[index[i]] = id[i];
    	fromIDtoIndex[id[i]]= index[i];
    }
}

size_t Translator::getID(size_t index){
	return fromIndextoID[index];
}

size_t Translator::getIndex(size_t id){
	return fromIDtoIndex[id];
}

void help_main(){
	std::string help= "Additional Argument:\n\
	\t *input file (default: out.dot). E.g., -i INfile.dot\n\
	\t *output file (default: result.dot). E.g., -o OUTfile.dot\n\
	\t *initial ID vertex for BFS (default 0). E.g., -id 9\n\
	\t *Sequential BFS (default true). E.g., -noSequentialBFS\n\
	\t *Parallel BFS (default true). E.g., -noParallelBFS\n\
	\t *Pagerank (default true). E.g., -noPagerank\n\
	\t *Fixed Pagerank (default true). E.g., -noFixedPagerank\n\
	\t *Alpha parameter DOBFS (default 12). E.g., -alpha\n\
	\t *Beta Parameter DOBFS (default 24). E.g., -beta\n\
	\t *Pagerank Damping Factor (default 0.85). E.g., -df 0.9\n\
	\t *Pagerank Iteration (default 100). E.g., -iter \n";

	std::cout << help;
}


void help_test(){
	std::string help= "Additional Argument:\n\
	\t *input file (default: out.dot). E.g., -i INfile.dot\n\
	\t *output file (default: test_log.txt). E.g., -o OUTfile.dot\n\
	\t *initial ID vertex for BFS (default 0). E.g., -id 9\n\
	\t *Test BFS (default true). E.g., -noTestBFS\n\
	\t *Test Pagerank (default true). E.g., -noTestPagerank\n\
	\t *Pagerank Iteration (default 100). E.g., -iter \n";

	std::cout << help;

}

