#include "fixed_pagerank.hpp"
#define FIXED 16777216  //Fixed Point 8:24


void fixed_pagerank(Graph &g, double alpha, int maxiteration){

	size_t vertexNum = num_vertices(g);
	const int tolerance = 1;
 	int bias = ((1.0 - alpha) / vertexNum)* FIXED;
	std::vector<int> outdegree(vertexNum);
	std::vector<int> memory(vertexNum);
	int fixed_alpha = alpha * FIXED;


	
	//set the number of outdegree and the std number for each vertex
	int stdfixed_value = FIXED;
	
	#pragma omp parallel for 
	for(size_t i = 0; i < vertexNum; i++){
		outdegree[i]=boost::out_degree(i,g)*FIXED;
		g[i].fixed_value=stdfixed_value;
	}


	int iter=0;
	int update;
	while (iter++ < maxiteration){

		#pragma omp parallel for 
		for (size_t i = 0; i < vertexNum; ++i){
			memory[i]=g[i].fixed_value;
			g[i].fixed_value=0;
		}

		#pragma omp parallel for 
		for (size_t i = 0; i < vertexNum; ++i){
			if(outdegree[i]>0){
				update = (fixed_alpha*memory[i])/outdegree[i];
				//itererator for the outgoing edges the vertex 
				std::pair<adjacency_iterator, adjacency_iterator> neighbors = boost::adjacent_vertices(i, g);
				//for each outgoing edges
				for(; neighbors.first != neighbors.second; ++neighbors.first){
						#pragma omp atomic
						g[*neighbors.first].fixed_value += update;   //atomic op
				}
			}
		} 

		long unsigned int error = 0;
        #pragma omp parallel for reduction(+:error)
        for (size_t i = 0; i < vertexNum; i++){
			g[i].fixed_value += bias;  //here it speeds up the computation / no lock needed
            error += fabs(g[i].fixed_value - memory[i]);
        }

        std::cout << "Pagerank step "<< iter << " ends with error " << (double)error/FIXED << "\n";

        // if the error is smaller than the tollerance we break the while
        if (error < tolerance)
        	break;

	} 
}