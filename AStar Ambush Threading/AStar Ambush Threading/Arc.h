#pragma once

#include "stdafx.h"

class Node; // stops circular dependency between arc and node
class Arc {
public:
	Arc() {}

	void setNode(Node *n);
	Node* getNode();

	void setWeight(float w);
	int getWeight();

	void setCorrespondingArc(Arc* arc);
	Arc* getCorrespondingArc();

	void incrementWeight();
	void decrementWeight();
	void resetWeight();

private:
	Node* m_node;
	Arc* m_correspondingArc;
	int m_weight;
	int m_initialWeight;
};