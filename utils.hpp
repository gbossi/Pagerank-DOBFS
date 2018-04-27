#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include "graph.hpp"

//The class translator provide a map between the keys of ID vertex index
class Translator{
	public:
		Translator(Graph g);
		size_t getID(size_t index);
		size_t getIndex(size_t ID);
	private:
		std::vector<size_t> fromIDtoIndex;
		std::vector<size_t> fromIndextoID;
};

void help_main();
void help_test();

#endif 


   
