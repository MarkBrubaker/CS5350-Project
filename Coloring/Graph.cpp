#include "Graph.hpp"

Graph::~Graph() {
	Clear();
}

void Graph::Establish(const int V) {
	edges = new Edge * [V];;

	//vertices.reserve(size);
	for(int x = 0; x < V; x++) {
		edges[x] = nullptr;
		vertices.emplace_back();
		vertices[x].id = x;
		vertices[x].edges.reserve(V);
		for(int y = 0; y < V; y++) {
			vertices[x].edges.insert(vertices[x].edges.end(), false);
		}
	}

	size = V;
}

void Graph::Clear() {
	for(int x = 0; x < size; x++) {
		delete edges[x];
	}
	delete[] edges;

	vertices.clear();
	ordering.clear();
}

void Graph::AddEdge(const int vertex1, const int vertex2) {
	Edge* e = new Edge(vertex2, edges[vertex1]);
	edges[vertex1] = e;
	vertices[vertex1].degree++;
	vertices[vertex1].edges[vertex2] = true;
}

Graph::Edge* Graph::GetEdge(const int vertex1, const int vertex2) {
	Edge* curr = edges[vertex1];
	while(curr != nullptr) {
		if(curr->dest == vertex2) return curr;
		curr = curr->next;
	}

	return nullptr;
}

void Graph::CreateCompleteGraph() {
	for(int x = 0; x < size; x++) { //n
		for(int y = 0; y < size; y++) { //n
			if(x == y) continue; //constant
			AddEdge(x, y); //constant
		}
	}
}

void Graph::CreateCycle() {

	for(int x = 0; x < size - 1; x++) { //n - 1
		AddEdge(x, x + 1); //constant
		AddEdge(x + 1, x); //constant
	}
	//1
	AddEdge(size - 1, 0);
	AddEdge(0, size - 1);
}

void Graph::CreateEvenDistribution(const int E) {
	int v1 = 0;
	int v2 = 0;
	int maxEdges = size * (size - 1) / 2;
	int attempts = 0;

	if(E > maxEdges) {
		throw "ERROR: edges exceeds max possible edges";
	} else if(E > maxEdges / 2) {
		std::cout << "WARNING: a fuller graph will take longer to create" << std::endl;
	}
	//std::cout << "The final graph will have " << (double)E / maxEdges * 100 << "% of the edges of a complete graph" << std::endl;

	for(int x = 0; x < E; x++) {
		v1 = (int)RandomNumberGenerator::getRandomNumber(0, size);
		v2 = (int)RandomNumberGenerator::getRandomNumber(0, size);
		attempts++;

		if(v1 == v2 || vertices[v1].edges[v2]) {
			//Edge already exist and a new one need to be chosen
			x--;
			continue;
		}

		AddEdge(v1, v2);
		AddEdge(v2, v1);
	}

	//std::cout << "The success reate for creating edges is: " << (double)E / attempts * 100 << "%" << std::endl;
}

void Graph::CreateSkewedDistribution(const int E) {
	int v1 = 0;
	int v2 = 0;
	int maxEdges = size * (size - 1) / 2;
	int attempts = 0;

	if(E > maxEdges) {
		throw "ERROR: edges exceeds max possible edges";
	} else if(E > maxEdges / 2) {
		std::cout << "WARNING: a fuller graph will take longer to create" << std::endl;
	}
	//std::cout << "The final graph will have " << (double)E / maxEdges * 100 << "% of the edges of a complete graph" << std::endl;

	for(int x = 0; x < E; x++) {
		v1 = (int)(size * (1 - sqrt(RandomNumberGenerator::getRandomNumber(0, 1))));
		v2 = (int)(size * (1 - sqrt(RandomNumberGenerator::getRandomNumber(0, 1))));

		attempts++;

		if(v1 == v2 || vertices[v1].edges[v2]) {
			//Edge already exist and a new one need to be chosen
			x--;
			continue;
		}

		AddEdge(v1, v2);
		AddEdge(v2, v1);
	}

	//std::cout << "The success reate for creating edges is: " << (double)E / attempts * 100 << "%" << std::endl;
}

void Graph::CreateModifiedNormalDistribution(const int E) {
	int v1 = 0;
	int v2 = 0;
	int maxEdges = size * (size - 1) / 2;
	int attempts = 0;

	if(E > maxEdges) {
		throw "ERROR: edges exceeds max possible edges";
	} else if(E > maxEdges / 2) {
		//std::cout << "WARNING: a fuller graph will take longer to create" << std::endl;
	}
	//std::cout << "The final graph will have " << (double)E / maxEdges * 100 << "% of the edges of a complete graph" << std::endl;

	for(int x = 0; x < E; x++) {
		v1 = (int)RandomNumberGenerator::getNormalNumber(size);
		v2 = (int)RandomNumberGenerator::getRandomNumber(0, size);
		attempts++;

		bool inRange = (v1 < 0 || v1 >= size || v2 < 0 || v2 >= size);
		if(inRange || v1 == v2 || vertices[v1].edges[v2]) {
			//Edge already exist and a new one need to be chosen
			x--;
			continue;
		}

		AddEdge(v1, v2);
		AddEdge(v2, v1);
	}

	//std::cout << "The success reate for creating edges is: " << (double)E / attempts * 100 << "%" << std::endl;
}

void Graph::RandomOrder() {
	//constant
	if(ordering.empty()) {
		//linear
		for(Vertex& v : vertices) {
			ordering.emplace_back(&v);
		}
	}

	//guaranteed linear by the standard library
	std::shuffle(ordering.begin(), ordering.end(), RandomNumberGenerator::m_rng);
}

void Graph::SmallestLastVertexOrder() {
	std::vector<Vertex*> degreeList(size);
	std::vector<int> modifiedDegree(size);
	std::vector<bool> removed(size);

	int index = 0;
	for(Vertex& v : vertices) {
		if(degreeList[v.degree] != nullptr) {
			degreeList[v.degree]->prev = &v;
			v.next = degreeList[v.degree];
		}
		degreeList[v.degree] = &v;
		modifiedDegree[index] = v.degree;
		index++;
	}

	for(unsigned int x = 0; x < degreeList.size(); x++) {
		if(degreeList[x] == nullptr) continue;

		Vertex* v1 = degreeList[x];

		//remove node from list
		ordering.emplace_back(v1);
		degreeList[x] = v1->next;
		if(v1->next != nullptr) v1->next->prev = nullptr;
		v1->next = nullptr;
		removed[v1->id] = true;
		//modifiedDegree[v1->id] = -1;


		//decrease degree of neighbors and move them down
		Edge* curr = edges[v1->id];
		while(curr != nullptr) {
			int v2 = curr->dest;

			//If the vertex has already been removed then skip it
			if(removed[v2] == true) {
				curr = curr->next;
				continue;
			}

			//Remove the vertex from the linked ilist it is in
			if(vertices[v2].next != nullptr) vertices[v2].next->prev = vertices[v2].prev;
			if(vertices[v2].prev != nullptr) {
				vertices[v2].prev->next = vertices[v2].next;
			} else {
				degreeList[modifiedDegree[v2]] = vertices[v2].next;
			}

			//Reduce the degree of the vertex
			modifiedDegree[v2]--;

			//Put the vertex at the head of the correct linked list
			vertices[v2].prev = nullptr;
			vertices[v2].next = degreeList[modifiedDegree[v2]];
			if(degreeList[modifiedDegree[v2]] != nullptr) degreeList[modifiedDegree[v2]]->prev = &vertices[v2];
			degreeList[modifiedDegree[v2]] = &vertices[v2];

			curr = curr->next;
		}

		//decrease degree to look for by 1
		if(x == 0) {
			x--;
			continue;
		}
		x -= 2;
	}
	std::reverse(ordering.begin(), ordering.end());
}

void Graph::SmallestOriginalDegreeOrder() {
	std::vector<Vertex*> degreeList(size);

	for(Vertex& v : vertices) {
		v.next = degreeList[v.degree];
		degreeList[v.degree] = &v;
	}

	for(Vertex* v : degreeList) {
		Vertex* curr = v;
		while(curr != nullptr) {
			ordering.push_back(curr);
			curr = curr->next;
		}
	}

	std::reverse(ordering.begin(), ordering.end());
}

void Graph::LargestLastVertexOrder() {
	SmallestLastVertexOrder();
	std::reverse(ordering.begin(), ordering.end());
}

void Graph::OutsideInOrder() {
	std::vector<Vertex*> degreeList(size);
	int bottom = 0;
	int top = size - 1;

	for(Vertex& v : vertices) {
		v.next = degreeList[v.degree];
		degreeList[v.degree] = &v;
	}

	bool flip = true;
	for(int x = 0; x < size; x++) {
		if(flip) {
			while(degreeList[bottom] == nullptr) bottom++;
			ordering.push_back(degreeList[bottom]);
			degreeList[bottom] = degreeList[bottom]->next;
			flip = false;
		} else {
			while(degreeList[top] == nullptr) top--;
			ordering.push_back(degreeList[top]);
			degreeList[top] = degreeList[top]->next;
			flip = true;
		}
	}
}

void Graph::BreadthFirstSearchOrder() {
	std::vector<Vertex*> unadded;
	std::vector<bool> found(size);
	std::queue<Vertex*> q;

	for(Vertex& v : vertices) {
		unadded.emplace_back(&v);
	}

	while(unadded.size()) {
		if(q.empty()) {
			Vertex* max = *std::max_element(unadded.begin(), unadded.end(), [](Vertex* v1, Vertex* v2) {return v1->degree < v2->degree; });
			q.push(max);
		}

		Vertex* v = q.front();
		unadded.erase(std::remove(unadded.begin(), unadded.end(), v), unadded.end());
		ordering.push_back(v);
		q.pop();


		Edge* curr = edges[v->id];
		while(curr != nullptr) {
			if(!found[curr->dest]) q.push(&vertices[curr->dest]);
			found[curr->dest] = true;
			curr = curr->next;
		}

		found[v->id] = true;
	}
}

void Graph::ColorGraph() {
	for(Vertex* v : ordering) {
		v->color = Color(v);
		if(v->color > maxColor) {
			maxColor = v->color;
		}
	}
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
