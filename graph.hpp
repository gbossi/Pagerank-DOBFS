#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_

//STL
#include <iostream>
#include <string>
#include <fstream>

//BOOST
#include <boost/graph/adjacency_list.hpp> // for customizable graphs
#include <boost/graph/graphviz.hpp>   //for print a graph
#include <boost/graph/detail/read_graphviz_new.hpp>  //new read graphviz function
#include <boost/property_map/transform_value_property_map.hpp>  
#include <boost/graph/reverse_graph.hpp> //to reverse the graph in  dobfs
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/copy.hpp>  //in order to copy the graph



//Bundled properties of the vertex
struct Vertex{
	int id;
	double value = 0;
	int fixed_value = 0;
	int distance = -1;
};

//Adiancence list for graph representation
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS, Vertex> Graph;
typedef boost::graph_traits<Graph>::adjacency_iterator adjacency_iterator;

//Functions declaration
void buildGraph(Graph&, std::string);
void writeGraph(Graph, std::string);
void resetValue(Graph&);




#endif	