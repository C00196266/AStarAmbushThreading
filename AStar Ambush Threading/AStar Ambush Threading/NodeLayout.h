#pragma once

#include "stdafx.h"
#include "Node.h"
#include "Arc.h"

#include <queue>

class NodeLayout {
public:
	NodeLayout() {}
	//NodeLayout(std::vector<Vector> &nodeData);

	void addNode(Vector pos, std::string id);

	void setNodesPerLine(int num);

	int getNoOfNodes();

	std::vector<Node*> getNodes();

	void draw(SDL_Renderer *renderer);

	void addArcs(); // adds connections between nodes

private:
	std::vector<Node*> m_nodes;

	int m_nodesPerLine;
};