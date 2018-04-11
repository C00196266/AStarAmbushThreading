#pragma once

#include "stdafx.h"
#include "Node.h"
#include "Arc.h"

#include <queue>

class Graph {
public:
	Graph() {}
	Graph(std::vector<Vector> &nodeData);

	int getNoOfNodes();

	Node* getNodes();

private:
	Node* m_nodes; // pointer to array of pointers to nodes

	int m_noOfNodes;

	void addArcs(); // adds connections between nodes
};