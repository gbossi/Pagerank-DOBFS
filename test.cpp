#include "graph.hpp"
#include "dobfs.hpp"
#include "parallel_dobfs.hpp"
#include "pagerank.hpp"
#include "fixed_pagerank.hpp"
#include "utils.hpp"
#include <chrono>

#define RMAT_FILE "out.dot"
#define TEST_LOG "test_log.txt"
#define BFS_START_ID 0
#define MAX_ALPHA 24


int main(int argc, char* argv[]){
	std::string filename_IN = RMAT_FILE;
	std::string filename_OUT=TEST_LOG;

	size_t initialVertexID= BFS_START_ID; 
	bool testBFS=true;
	bool testPagerank=true;

	int iteration = 100;

	Graph g;

	try{

		// Getting required input parameters.
		for( int iii = 1; iii < argc; ++iii ) {
			if( !strcmp(argv[iii], "-i") && iii != argc-1)
				filename_IN = std::string(argv[iii+1]);
			else if( !strcmp(argv[iii], "-id") && iii != argc-1)
				initialVertexID = std::stod( std::string(argv[iii+1]));
			else if( !strcmp(argv[iii], "-noTestBFS"))
				testBFS = false;
			else if( !strcmp(argv[iii], "-noTestPagerank"))
				testPagerank = false;
			else if( !strcmp(argv[iii], "-o") && iii != argc-1)
				filename_OUT =  std::string(argv[iii+1]) ;
			else if( !strcmp(argv[iii], "-iter") && iii != argc-1)
				iteration = std::stoull( std::string(argv[iii+1]) );
			else if( !strcmp(argv[iii], "-h")){
				help_test();
				return 0;
			}
		}


   	std::cout << "Using the standard file "<< RMAT_FILE << std::endl;
   	std::cout << "Using as starting ID " << BFS_START_ID << std::endl;
  	std::cout << "Getting the graph from " << filename_IN << std::endl;
	buildGraph(g, filename_IN);
	std::cout << "Setting up a Translator between vertex Index and ID" << std::endl;
	Translator t(g);
	size_t index = t.getIndex(initialVertexID);


	//Here we assume that we can take as argument the type of search
	//requested between DOBFS and Pagerank
	//normally it will give you a id
	using namespace std::chrono;
	high_resolution_clock::time_point t1;
	high_resolution_clock::time_point t2;
	std::ofstream testlog;
	testlog.open(filename_OUT);

	if(testBFS){
		for(int alpha=2;alpha<MAX_ALPHA;alpha+=2){
			int beta=alpha*2;
			t1 = high_resolution_clock::now();
			parallel_dobfs(g,index,alpha,beta);
			t2 = high_resolution_clock::now();
			auto durationBFS = duration_cast<microseconds>( t2 - t1 ).count();
			testlog << "Parallel DOBFS with parameter alpha=" << alpha << " and beta=" << beta << " ";
			testlog << "has requested ";
			testlog << "\t" << durationBFS <<" microsec\n";
			resetValue(g);
		}
	}

	if(testPagerank){
		for(float damping=0.95;damping>0;damping-=0.05){
			
			t1 = high_resolution_clock::now();
			pagerank(g, damping, iteration);
			t2 = high_resolution_clock::now();
			auto durationFLP = duration_cast<microseconds>( t2 - t1 ).count();
			testlog << "Pagerank algortihm with damping factor="<<damping<<" using floating point arithmetic requested ";
			testlog << "\t" << durationFLP <<" microsec\n";
			

			t1 = high_resolution_clock::now();
			fixed_pagerank(g, damping, iteration);
			t2 = high_resolution_clock::now();
			auto durationFXP = duration_cast<microseconds>( t2 - t1 ).count();
			testlog << "Pagerank algorithm with damping factor="<<damping<<" using fixed point arithmetic requested ";
			testlog << "\t" << durationFXP <<" microsec\n";
			

			resetValue(g);
		}
	}
	testlog.close();

	return 0;
	}
	catch(...) {
		std::cerr << "An exception has occurred during the initialization." << "\n" << "Exiting." << std::endl;
		return( EXIT_FAILURE );
	}
}
