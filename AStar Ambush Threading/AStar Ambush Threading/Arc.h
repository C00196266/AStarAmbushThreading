#pragma once

#include "stdafx.h"

class Node; // stops circular dependency between arc and node
class Arc {
public:
	Arc() {}

	void setNode(Node *n);
	Node* getNode();

	void setWeight(float w);
	float getWeight();

	void drawLine(SDL_Renderer *renderer, Vector pos);

private:
	Node *m_node;
	int m_weight;
};