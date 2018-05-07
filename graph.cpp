#include "graph.hpp"


//This function handle the building of a graph
//Create a graph from a specified file produced by PaRMAT-m
//a modified version that creates .dot files 
void buildGraph(Graph &g, std::string filename){
 	boost::dynamic_properties dp(boost::ignore_other_properties);
    dp.property("node_id", boost::get(&Vertex::id,g));

    std::ifstream fin(filename.c_str());
    boost::read_graphviz(fin, g, dp);

  	std::cout << "There are " << boost::num_vertices(g) << " vertices." << std::endl;
 }



//This function handle the print of the graph
void writeGraph(Graph g, std::string filename){
	boost::dynamic_properties dp;
	dp.property("node_id", get(&Vertex::id, g));
	dp.property("distance", get(&Vertex::distance, g));
	dp.property("floating pagerank", get(&Vertex::value, g));
	dp.property("fixed pagerank", get(&Vertex::fixed_value, g));
	std::ofstream outputFile;
	outputFile.open(filename);
	write_graphviz_dp(outputFile, g, dp, "node_id");
}



void resetValue(Graph &g){
	size_t vertexNum = num_vertices(g);

	#pragma omp parallel for
	for (size_t i = 0; i < vertexNum; ++i)
	{
		g[i].value=0;
		g[i].fixed_value=0;
		g[i].distance=-1;
	}
}