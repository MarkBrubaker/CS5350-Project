#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <queue>
#include "Util.hpp"

class Graph {
	struct Edge {
		int dest = -1;
		Edge* next = nullptr;
		Edge(int d, Edge* n) : dest(d), next(n) {}
		~Edge() { delete next; }
	};
	struct Vertex {
		int id = 0;
		int degree = 0;
		int color = 0;
		//Used only to check if an edge exists
		//an order of magnitude faster than the linked list
		std::vector<bool> edges;

		Vertex* prev = nullptr;
		Vertex* next = nullptr;
	};

	Edge** edges = nullptr;
	std::vector<Vertex> vertices;
	std::vector<Vertex*> ordering;

public:
	int size = 0;
	int maxColor = 0;

	Graph() = default;
	~Graph();

	void Establish(const int V);
	void Clear();
	void AddEdge(const int vertex1, const int vertex2);
	Graph::Edge* GetEdge(const int vertex1, const int vertex2);

	//Create differnt graphs and distrobutions
	void CreateCompleteGraph();
	void CreateCycle();
	void CreateEvenDistribution(const int E);
	void CreateSkewedDistribution(const int E);
	void CreateModifiedNormalDistribution(const int E);

	//Create different ordering
	void RandomOrder();
	void SmallestLastVertexOrder();
	void SmallestOriginalDegreeOrder();
	void LargestLastVertexOrder();
	void OutsideInOrder();
	void BreadthFirstSearchOrder();

	void ColorGraph();
	int Color(Vertex* v);

	void Print(std::string filename = "graph.txt");
	void PrintDistribution(std::string filename = "distribution.txt");
	void ReadIn(std::string filename = "graph.txt");
};