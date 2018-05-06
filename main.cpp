#include "graph.hpp"
#include "dobfs.hpp"
#include "parallel_dobfs.hpp"
#include "pagerank.hpp"
#include "fixed_pagerank.hpp"
#include "utils.hpp"
#include <time.h>

#define RMAT_FILE "out.dot"
#define OUTPUT_FILE "result.dot"
#define BFS_START_ID 0


int main(int argc, char* argv[]){
	std::string filename_IN = RMAT_FILE;
	std::string filename_OUT = OUTPUT_FILE;


	//vertex ID taken for DOBFS
	size_t initialVertexID= BFS_START_ID; 
	bool sequentialBFS=true;
	bool parallelBFS=true;
	int alpha = 12;
	int beta = 24;


	bool pagerankAlgorithm=true;
	bool fixed_pagerankAlgorithm=true;
	int iteration = 100;
	double damping = 0.85;

	Graph g;

	try{

		// Getting required input parameters.
		for( int iii = 1; iii < argc; ++iii ) {
			if( !strcmp(argv[iii], "-i") && iii != argc-1)
				filename_IN = std::string(argv[iii+1]);
			else if( !strcmp(argv[iii], "-o") && iii != argc-1)
				filename_OUT =  std::string(argv[iii+1]) ;
			else if( !strcmp(argv[iii], "-id") && iii != argc-1)
				initialVertexID = std::stoull( std::string(argv[iii+1]));
			else if( !strcmp(argv[iii], "-alpha") && iii != argc-1 )
				alpha = std::stoull( std::string(argv[iii+1]) );
			else if( !strcmp(argv[iii], "-beta") && iii != argc-1)
				beta = std::stoull( std::string(argv[iii+1]) );
			else if( !strcmp(argv[iii], "-noSequentialBFS"))
				sequentialBFS = false;
			else if( !strcmp(argv[iii], "-noParallelBFS"))
				parallelBFS = false;
			else if( !strcmp(argv[iii], "-noPagerank"))
				pagerankAlgorithm = false;
			 else if( !strcmp(argv[iii], "-noFixedPagerank"))
				fixed_pagerankAlgorithm = false;
			else if( !strcmp(argv[iii], "-df") && iii != argc-1)
				damping = std::stod( std::string(argv[iii+1]) );
			else if( !strcmp(argv[iii], "-iter") && iii != argc-1)
				iteration = std::stoull( std::string(argv[iii+1]) );
			else if( !strcmp(argv[iii], "-h")){
				help_main();
				return 0;
			}
		}


   	std::cout << "Using the input file "<< filename_IN << std::endl;
   	std::cout << "Using as starting ID " << initialVertexID << std::endl;
  	std::cout << "Output the graph in " << filename_OUT << std::endl;
	buildGraph(g, filename_IN);
	std::cout << "Setting up a Translator between vertex Index and ID" << std::endl;
	Translator t(g);
	size_t index = t.getIndex(initialVertexID);


	//Here we assume that we can take as argument the type of search
	//requested between DOBFS and Pagerank
	//normally it will give you a id

	clock_t begin_time_1;

	if(sequentialBFS){
		begin_time_1 = clock();
		dobfs(g, index,alpha,beta);
	}
	

	if(parallelBFS){
		if(sequentialBFS)
			resetValue(g);

		begin_time_1 = clock();
		parallel_dobfs(g,index,alpha,beta);
	}


	if(pagerankAlgorithm){

		begin_time_1 = clock();
		pagerank(g, damping, iteration);
	}

	if(fixed_pagerankAlgorithm){

		begin_time_1 = clock();
		fixed_pagerank(g, damping, iteration);
	}
	
	std::cout << "Writing the graph in " << filename_OUT << "\n";
	writeGraph(g, filename_OUT);

	return 0;
	}
	catch(...) {
		std::cerr << "An exception has occurred during the initialization." << "\n" << "Exiting." << std::endl;
		return( EXIT_FAILURE );
	}
}
