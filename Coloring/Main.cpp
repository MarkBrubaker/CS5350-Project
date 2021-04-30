#include "Graph.hpp"

void BIGGRAPHENERGY() {
	Graph* graph = new Graph;

	graph->Establish(10000);
	graph->CreateCompleteGraph();
	graph->RandomOrder();
	std::cout << "Colors needed: " << graph->ColorGraph() << std::endl;
}

int main(int argc, char* argv[]) {

	std::cout << "Time: " << Time(BIGGRAPHENERGY) << "ms" << std::endl;

	//graph->PrintDistribution();
	//graph->ReadIn("graph.txt");
	//graph->Print("out.txt");

	return 0;
}