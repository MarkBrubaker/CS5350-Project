#include <functional>
#include "Graph.hpp"

void BIGGRAPHENERGY(int x) {
	Graph graph;

	graph.Establish(x);
	graph.CreateEvenDistribution(x * 200);
	std::cout << "Graph made" << std::endl;
	graph.RandomOrder();
	std::cout << "Graph ordered" << std::endl;
	graph.ColorGraph();
	std::cout << "Colors needed: " << graph.maxColor << std::endl;
	graph.PrintDistribution();
}

void TIMEGRAPHENERGY(const int x) {
	Graph graph;

	std::cout << "Establish:         " << TimeClass(&graph, &Graph::Establish, x) << "ms" << std::endl;
	std::cout << "Distribution:      " << TimeClass(&graph, &Graph::CreateModifiedNormalDistribution, x * 200) << "ms" << std::endl;
	std::cout << "Order:             " << TimeClass(&graph, &Graph::RandomOrder, nullptr) << "ms" << std::endl;
	std::cout << "ColorGraph:        " << TimeClass(&graph, &Graph::ColorGraph, nullptr) << "ms" << std::endl;
	//std::cout << "Print:             " << TimeClass(&graph, &Graph::Print, "graph.txt") << "ms" << std::endl;
	std::cout << "Colors used:       " << graph.maxColor << std::endl;
}

int main(int argc, char* argv[]) {
	const int size = 10000;

	double time = Time(TIMEGRAPHENERGY, size);
	std::cout << "Total time:        " << time << "ms" << std::endl;


	return 0;
}