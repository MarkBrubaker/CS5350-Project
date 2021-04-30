#include "Graph.hpp"

Graph::~Graph() {
	Clear();
}

void Graph::Establish(int verticies) {
	size = verticies;
	edges = new Edge * [size];;

	for(int x = 0; x < size; x++) {
		edges[x] = nullptr;
		vertices.emplace_back();
		vertices[x].id = x;
	}
}

void Graph::Clear() {
	for(int x = 0; x < size; x++) {
		delete edges[x];
	}
	delete[] edges;

	vertices.clear();
	ordering.clear();

}

void Graph::AddEdge(int vertex1, int vertex2) {
	//constant
	Edge* e = new Edge(vertex2, edges[vertex1]);
	//constant
	edges[vertex1] = e;
	//constant
	vertices[vertex1].degree++;
}

Graph::Edge* Graph::GetEdge(int vertex1, int vertex2) {
	Edge* curr = edges[vertex1];
	while(curr != nullptr) {
		if(curr->dest == vertex2) return curr;
		curr = curr->next;
	}

	return nullptr;
}

void Graph::CreateCompleteGraph() {
	//n
	for(int x = 0; x < size; x++) {
		//n
		for(int y = 0; y < size; y++) {
			//constant
			if(x == y) continue;
			//constant
			AddEdge(x, y);
		}
	}
}

void Graph::CreateCycle() {
	//n - 1
	for(int x = 0; x < size - 1; x++) {
		//constant
		AddEdge(x, x + 1);
		AddEdge(x + 1, x);
	}
	//1
	AddEdge(size - 1, 0);
	AddEdge(0, size - 1);
}

void Graph::CreateEvenDistribution(int E) {
	int v1 = 0;
	int v2 = 0;
	int maxEdges = size * (size - 1) / 2;

	if(E > maxEdges) {
		std::cout << "ERROR: edges exceeds max possible edges" << std::endl;
		throw;
	} else if(E > maxEdges / 2) {
		std::cout << "WARNING: a fuller graph will take longer to create" << std::endl;
	}

	for(int x = 0; x < E; x++) {
		v1 = (int)RandomNumberGenerator::getRandomNumber(0, size);
		v2 = (int)RandomNumberGenerator::getRandomNumber(0, size);

		if(GetEdge(v1, v2) != nullptr) {
			//Edge already exist and a new one need to be chosen
			x--;
			continue;
		}

		AddEdge(v1, v2);
	}
}

void Graph::CreateSkewedDistribution(int E) {
	int v1 = 0;
	int v2 = 0;
	int maxEdges = size * (size - 1) / 2;

	if(E > maxEdges) {
		std::cout << "ERROR: edges exceeds max possible edges" << std::endl;
		throw;
	} else if(E > maxEdges / 2) {
		std::cout << "WARNING: a fuller graph will take longer to create" << std::endl;
	}

	std::vector<int> i{0, size};
	std::vector<double> w{1, 0};
	std::piecewise_linear_distribution<> d(i.begin(), i.end(), w.begin());

	for(int x = 0; x < E; x++) {
		v1 = (int)d(RandomNumberGenerator::m_rng);
		v2 = (int)RandomNumberGenerator::getRandomNumber(0, size);

		if(GetEdge(v1, v2) != nullptr) {
			//Edge already exist and a new one need to be chosen
			x--;
			continue;
		}

		AddEdge(v1, v2);
	}
}

void Graph::CreateNormalDistribution(int E) {
	int v1 = 0;
	int v2 = 0;
	int maxEdges = size * (size - 1) / 2;

	if(E > maxEdges) {
		std::cout << "ERROR: edges exceeds max possible edges" << std::endl;
		throw;
	} else if(E > maxEdges / 2) {
		std::cout << "WARNING: a fuller graph will take longer to create" << std::endl;
	}

	std::normal_distribution<double> d(size / 2, size / 10);

	for(int x = 0; x < E; x++) {
		v1 = (int)d(RandomNumberGenerator::m_rng);
		v2 = (int)RandomNumberGenerator::getRandomNumber(0, size);

		bool inRange = v1 < 0 || v1 >= size || v1 < 0 || v1 >= size;
		//out of range values will error in GetEdge as well but the bool will always be checked first
		if(inRange || GetEdge(v1, v2) != nullptr) {
			//Edge already exist and a new one need to be chosen
			x--;
			continue;
		}

		AddEdge(v1, v2);
	}
}

void Graph::RandomOrder() {
	//constant
	if(ordering.size() == 0) {
		//linear
		for(Vertex& v : vertices) {
			ordering.emplace_back(&v);
		}
	}

	//guaranteed linear by the standard library
	std::shuffle(ordering.begin(), ordering.end(), RandomNumberGenerator::m_rng);
}

void Graph::SmallestLastVertexOrder() {
}

void Graph::SmallestOriginalDegreeOrder() {
	//constant
	if(ordering.size() == 0) {
		//linear
		for(Vertex& v : vertices) {
			ordering.emplace_back(&v);
		}
	}

	//guaranteed N log(N) by the standard library
	std::sort(ordering.begin(), ordering.end(), [](Vertex* v1, Vertex* v2) {return v1->degree < v2->degree; });
}

int Graph::ColorGraph() {
	std::iostream::sync_with_stdio(false);
	int maxColor = 0;
	for(Vertex* v : ordering) {
		v->color = Color(v);
		if(v->color > maxColor) {
			maxColor = v->color;
			std::cout << "New color used: " << maxColor << std::endl;
		}
	}

	return maxColor;
}

int Graph::Color(Vertex* v) {
	int minNeighborColor = 0;
	std::vector<int> neighborColors;

	Edge* curr = edges[v->id];
	//linear on the degree of v
	while(curr != nullptr) {
		neighborColors.emplace_back(vertices[curr->dest].color);
		curr = curr->next;
	}

	//from here we solve the first missing positive int problem
	//solved using this approach:
	//https://www.youtube.com/watch?v=hnV0IhnEqH4&t=264s
	unsigned int num = 0;
	for(unsigned int x = 0; x < neighborColors.size(); x++) {
		num = neighborColors[x];
		while(0 < num && num <= neighborColors.size() && neighborColors[num - 1] != num) {
			std::swap(neighborColors[x], neighborColors[num - 1]);
			num = neighborColors[x];
		}
	}
	for(unsigned int x = 0; x < neighborColors.size(); x++) {
		if(neighborColors[x] != x + 1) {
			return x + 1;
		}
	}
	return neighborColors.size() + 1;
}

void Graph::Print(std::string filename) {
	std::ofstream file(filename);

	file << size << std::endl;

	int currentLine = size + 1;
	for(int x = 0; x < size; x++) {
		file << currentLine << std::endl;
		currentLine += vertices[x].degree++;
	}

	for(int x = 0; x < size; x++) {
		Edge* curr = edges[x];
		while(curr != nullptr) {
			file << curr->dest << " " << std::endl;
			curr = curr->next;
		}
	}

	file.close();
}

void Graph::PrintDistribution(std::string filename) {
	std::ofstream file(filename);

	for(unsigned int x = 0; x < vertices.size(); x++) {
		file << x << " " << vertices[x].degree << std::endl;
	}

	file.close();
}

void Graph::ReadIn(std::string filename) {
	Clear();

	std::ifstream file(filename);

	file >> size;
	Establish(size);

	int degree = 0;
	std::vector<int> degrees;
	for(int x = 0; x < size; x++) {
		file >> degree;
		degrees.emplace_back(degree);
		if(x == 0) continue;
		degrees[x - 1] = degrees[x] - degrees[x - 1];
	}

	int vertex = 0;
	for(int x = 0; x < size - 1; x++) {
		for(int y = 0; y < degrees[x]; y++) {
			file >> vertex;
			AddEdge(x, vertex);
		}
	}
	while(file >> vertex) {
		AddEdge(size - 1, vertex);
	}
}
