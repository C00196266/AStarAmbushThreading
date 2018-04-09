#pragma once

#include "NodeLayout.h"
#include "NodeCostComparer.h"
#include "Player.h"
#include <queue>

class AStar {
public:
	AStar();

	void update();

	void calculatePath(Node* pDest, std::vector<Node*>& path);

	NodeLayout* getLayout();

	void addPlayer(Player* player);

	bool getChangedNode();

private:
	NodeLayout* m_nodeLayout;

	Player* m_player;
	Node* m_start;
	int m_nodeNearestToPLayer;
	bool m_changedNode;

	void ucs(Node* pStart, Node* pDest, std::vector<Node*>& path);

	float magnitude(Vector v1, Vector v2);
};