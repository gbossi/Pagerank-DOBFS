#include "dobfs.hpp"
#include <list>
#include <algorithm>


void chooseDirection(bool &currentDirection, long int sizeGraph, long int sizeFrontier, long int sizeNext, int alpha,int beta){

	int edgesToCheck;
	double branching_factor=(sizeNext-sizeFrontier)/sizeFrontier;

	//this is the case we the graph is growing
	if(branching_factor>0){
		edgesToCheck = sizeNext * branching_factor;
		currentDirection=(edgesToCheck<(sizeGraph*branching_factor/alpha));
	//Here the graph is shrinking
	}else{
		edgesToCheck=sizeFrontier;
		currentDirection=(sizeFrontier<(sizeGraph/beta));
	}

	std::cout << "Size of next frontier \t" << sizeNext << "\n";
	std::cout << "Branching Factor \t" << branching_factor << "\n";
	std::cout << "Graph Dimension \t" << sizeGraph << "\n";
	std::cout << "Number of edges to check \t" <<  edgesToCheck << "\n";
}


void bottom_up_step(Graph &g, Graph invGraph, std::list<size_t> &frontier, std::list<size_t> &next, long int distance){
	
	std::cout << "\n\nStarting Bottom Up \n";
	//For each vertex of the graph
	auto vs = boost::vertices(g);
	for (auto vit = vs.first; vit != vs.second; ++vit) {

		if(g[*vit].distance < 0){
		
			//Iterator for the ingoing edges the vertex 
	  		std::pair<adjacency_iterator, adjacency_iterator> neighbors = boost::adjacent_vertices(*vit, invGraph);
			for(; neighbors.first != neighbors.second; ++neighbors.first){
			
			//if neighbors.first is in the frontier
			if(std::find(frontier.begin(), frontier.end(), *neighbors.first) != frontier.end()){
				g[*vit].distance = distance;
  				next.push_back(*vit);
  				break;
				}
  			}
  		}
  	}

}

void top_down_step(Graph &g, std::list<size_t> &frontier, std::list<size_t> &next, long int distance){
	
	std::cout << "\n\nStarting Top Down \n";

	//For each element of the frontier
	for (auto const& nodeIdx : frontier) {
    	
    	//Iterator for the outgoing edges the vertex 
  		std::pair<adjacency_iterator, adjacency_iterator> neighbors = boost::adjacent_vertices(vertex(nodeIdx,g), g);

 		//for each outgoing edges 
  		for(; neighbors.first != neighbors.second; ++neighbors.first){
  			if(g[*neighbors.first].distance < 0){
  				g[*neighbors.first].distance = distance;
  				next.push_back(*neighbors.first);
  			}
    	}
    }
}

void dobfs(Graph &g,size_t index, int alpha, int beta){
	
	std::list<size_t> frontier;
	std::list<size_t> next;
	bool directionDown = true;
	
	//Inverse Graph needed for Bottom up step to iterate over ingoing vertices
	Graph invGraph;
	boost::copy_graph(boost::make_reverse_graph(g), invGraph);
	size_t sizeGraph = boost::num_vertices(g);


	long unsigned distance=0;
	g[index].distance = distance;
	distance++;
	frontier.push_back(index);

	
	while(frontier.size() !=0){
		if(directionDown){
			top_down_step(g, frontier, next, distance);
		}else{
			bottom_up_step(g, invGraph, frontier, next, distance);
		}

		sizeGraph = sizeGraph - next.size();  //number of vertices with distance = -1
		chooseDirection(directionDown, sizeGraph, frontier.size(), next.size(), alpha, beta);
		frontier.clear();
		frontier=next;
		next.clear();
		distance++;
	}
	invGraph.clear();
}


