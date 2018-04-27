#include "pagerank.hpp"

void pagerank(Graph &g, double alpha, int maxiteration){

	
	size_t vertexNum = num_vertices(g);
	const double tolerance = 1e-12;
 	double bias = (1.0 - alpha) / vertexNum;
	std::vector<int> outdegree(vertexNum);
	std::vector<double> memory(vertexNum);


	
	//set the number of outdegree and the std number for each vertex
	int stdvalue= 1;
	
	#pragma parallel for 
	for(int i = 0; i < vertexNum; i++){
		outdegree[i]=boost::out_degree(i,g);
		g[i].value=stdvalue;
	}


	int iter=0;
	double update;
	while (iter++ < maxiteration){

		#pragma parallel for 
		for (size_t i = 0; i < vertexNum; ++i){
			memory[i]=g[i].value;
			g[i].value=0;
		}

		#pragma parallel for 
		for (size_t i = 0; i < vertexNum; ++i){
			if(outdegree[i]>0){
				update = alpha * (memory[i]/outdegree[i]);
				//itererator for the outgoing edges the vertex 
				std::pair<adjacency_iterator, adjacency_iterator> neighbors = boost::adjacent_vertices(i, g);
				//for each outgoing edges
				for(; neighbors.first != neighbors.second; ++neighbors.first){
						#pragma omp atomic
						g[*neighbors.first].value += update;   //atomic op
				}
			}
		} 

		double error = 0.0;
        #pragma omp parallel for reduction(+:error)
        for (size_t i = 0; i < vertexNum; i++){
			g[i].value += bias;  //here it speeds up the computation / no lock needed
            error += fabs(g[i].value - memory[i]);
        }

        // if the error is smaller than the tollerance we break the while
        if (error < tolerance)
        	break;

        std::cout << "Pagerank step "<< iter << " ends with error " << error << "\n";
	} 
}