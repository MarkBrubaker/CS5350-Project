#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
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

		Vertex* prev = nullptr;
		Vertex* next = nullptr;
	};

	Edge** edges = nullptr;
	std::vector<Vertex> vertices;
	std::vector<Vertex*> ordering;

	int size = 0;

public:
	Graph() = default;
	~Graph();

	void Establish(int verticies);
	void Clear();
	void AddEdge(int vertex1, int vertex2);
	Graph::Edge* GetEdge(int vertex1, int vertex2);

	//Create differnt graphs and distrobutions
	void CreateCompleteGraph();
	void CreateCycle();
	void CreateEvenDistribution(int E);
	void CreateSkewedDistribution(int E);
	void CreateNormalDistribution(int E);

	//Create different ordering
	void RandomOrder();
	void SmallestLastVertexOrder();
	void SmallestOriginalDegreeOrder();

	int ColorGraph();
	int Color(Vertex* v);

	void Print(std::string filename = "graph.txt");
	void PrintDistribution(std::string filename = "distribution.txt");
	void ReadIn(std::string filename);
};