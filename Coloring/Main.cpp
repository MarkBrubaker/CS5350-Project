#include <functional>
#include "Graph.hpp"

void TIMEGRAPHENERGY(const int x) {
	Graph graph;

	std::cout << "Establish:         " << TimeClass(&graph, &Graph::Establish, x) << "ms" << std::endl;
	std::cout << "Distribution:      " << TimeClass(&graph, &Graph::CreateModifiedNormalDistribution, x * 200) << "ms" << std::endl;
	std::cout << "Order:             " << TimeClass(&graph, &Graph::SmallestLastVertexOrder, nullptr) << "ms" << std::endl;
	std::cout << "Color Graph:       " << TimeClass(&graph, &Graph::ColorGraph, nullptr) << "ms" << std::endl;
	//std::cout << "Print:             " << TimeClass(&graph, &Graph::Print, "graph.txt") << "ms" << std::endl;
	std::cout << "Colors used:       " << graph.maxColor << std::endl;
}

int main(int argc, char* argv[]) {
	const int size = 10000;

	//double time = Time(TIMEGRAPHENERGY, size);
	//std::cout << "Total time:        " << time << "ms" << std::endl;

	Graph graph;
	graph.Establish(size);
	graph.CreateCompleteGraph();
	graph.PrintDistribution();


	return 0;
}