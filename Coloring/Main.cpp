#include <functional>
#include "Graph.hpp"

void Run(int x) {
	Graph graph;

	std::cout << "Establish:         " << TimeClass(&graph, &Graph::Establish, x) << "ms" << std::endl;
	std::cout << "Distribution:      " << TimeClass(&graph, &Graph::CreateModifiedNormalDistribution, x * 200) << "ms" << std::endl;
	std::cout << "Order:             " << TimeClass(&graph, &Graph::SmallestLastVertexOrder, nullptr) << "ms" << std::endl;
	std::cout << "Color Graph:       " << TimeClass(&graph, &Graph::ColorGraph, nullptr) << "ms" << std::endl;
	std::cout << "Colors used:       " << graph.maxColor << std::endl;
}

int main(int argc, char* argv[]) {
	std::ofstream file("colors.txt");

	for(int x = 500; x <= 5000; x += 500) {
		file << x << " ";
		std::cout << "Starting test for size: "  << x << std::endl;
		for(int y = 0; y < 10; y++) {
			Graph graph;
			std::cout << "Created" << std::endl;
			graph.Establish(x);
			std::cout << "Established" << std::endl;
			graph.CreateModifiedNormalDistribution(x * 200);
			std::cout << "Filled out" << std::endl;
			graph.SmallestLastVertexOrder();
			std::cout << "Ordered" << std::endl;
			graph.ColorGraph();
			std::cout << "Colored" << std::endl;
			file << graph.maxColor << " ";
		}
		file << std::endl;
	}

	file.close();

	return 0;
}