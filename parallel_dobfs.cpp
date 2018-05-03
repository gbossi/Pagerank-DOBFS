#include "parallel_dobfs.hpp"
#include <list>
#include <algorithm>


void parallel_chooseDirection(bool &currentDirection, long int sizeGraph, long int sizeFrontier, long int sizeNext, int alpha, int beta){

	int edgesToCheck;
	double branching_factor=(double) (sizeNext-sizeFrontier)/sizeFrontier;

	//this is the case we the graph is growing
	if(currentDirection && branching_factor>0){
		edgesToCheck = sizeNext * branching_factor;
		currentDirection=(edgesToCheck<(sizeGraph*branching_factor/alpha));
	//Here the graph is shrinking
	}else if(!currentDirection && branching_factor<0){
		edgesToCheck=sizeFrontier;
		currentDirection=(sizeFrontier<(sizeGraph/beta));
	}

	std::cout << "Size of next frontier \t" << sizeNext << "\n";
	std::cout << "Branching Factor \t" << branching_factor << "\n";
	std::cout << "Graph Dimension \t" << sizeGraph << "\n";
	std::cout << "Number of edges to check \t" <<  edgesToCheck << "\n";
}


void parallel_bottom_up_step(Graph &g, Graph invGraph, std::vector<size_t> &frontier, std::vector<size_t> &next, long int distance){
	std::cout << "\n\nStarting Bottom Up \n";
	//For each vertex of the graph
	size_t total_vertices = boost::num_vertices(g);
		//iterate over the entire graph
	#pragma omp parallel for
	for (size_t i =0; i < total_vertices ; i++) {
		if(g[i].distance < 0){
	
			//Iterator for the outgoing edges the vertex 
			std::pair<adjacency_iterator, adjacency_iterator> neighbors = boost::adjacent_vertices(i, invGraph);
			for(; neighbors.first != neighbors.second; ++neighbors.first){
		
			//if *neighbors.first is in the frontier
				if(std::find(frontier.begin(), frontier.end(), *neighbors.first) != frontier.end()){
					g[i].distance = distance;
					#pragma omp critical
  					next.push_back(i);
  					break;
				}
  			}
   		}
  	}  	
}

void parallel_top_down_step(Graph &g, std::vector<size_t> &frontier, std::vector<size_t> &next, long int distance){
	
	std::cout << "\n\nStarting Top Down \n";
	size_t frontier_size = frontier.size();
	//For each element of the frontier
	#pragma omp parallel for
	for (size_t i=0; i < frontier_size; i++) {

   		//Iterator for the outgoing edges the vertex 
		std::pair<adjacency_iterator, adjacency_iterator> neighbors = boost::adjacent_vertices(frontier[i], g);
		//for each outgoing edges
		for(; neighbors.first != neighbors.second; ++neighbors.first){
			#pragma omp critical(adding)
			{
				if(g[*neighbors.first].distance < 0){
					g[*neighbors.first].distance = distance;
					next.push_back(*neighbors.first);
				}
   			}
   		}
   	}	
}

void parallel_dobfs(Graph &g,size_t index, int alpha, int beta){
	
	std::vector<size_t> frontier;
	std::vector<size_t> next;
	bool directionDown = true;
	
	Graph invGraph;
	boost::copy_graph(boost::make_reverse_graph(g), invGraph);
	size_t sizeGraph = boost::num_vertices(g);


	long int distance=0;
	g[index].distance = distance;
	frontier.push_back(index);
	distance++;

	
	while(frontier.size() !=0){
		if(directionDown){
			parallel_top_down_step(g, frontier, next, distance);
		}else{
			parallel_bottom_up_step(g, invGraph, frontier, next, distance);
		}

		sizeGraph -= next.size(); //number of vertices with distance = -1
		parallel_chooseDirection(directionDown, sizeGraph, frontier.size(), next.size(), alpha, beta);
		frontier.clear();
		frontier=next;
		next.clear();
		distance++;
	}
	invGraph.clear();
}


