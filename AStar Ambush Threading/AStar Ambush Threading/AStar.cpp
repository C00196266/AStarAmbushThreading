#include "AStar.h"

AStar::AStar() {
	m_nodeLayout = new NodeLayout;
	m_changedNode = false;
}

void AStar::update() {
	if (m_changedNode == true) {
		m_changedNode = false;
	}

	int indexClosestToPlayer = 0;
	float closestDistPlayer = 99999;

	for (int i = 0; i < m_nodeLayout->getNoOfNodes(); i++) {
		float distPlayer = magnitude(m_nodeLayout->getNodes().at(i)->getPos(), m_player->getPos());

		if (distPlayer < closestDistPlayer) {
			closestDistPlayer = distPlayer;
			indexClosestToPlayer = i;
		}
	}

	if (m_nodeLayout->getNodes().at(m_nodeNearestToPLayer) != m_start) {
		m_start = m_nodeLayout->getNodes().at(m_nodeNearestToPLayer);
		m_changedNode = true;
	}
}

void AStar::calculatePath(Node *dest, std::vector<Node*>& path) {
	if (m_start == NULL) {
		m_start = m_nodeLayout->getNodes().at(0);
	}

	if (m_start != NULL) {
		ucs(dest, m_start, path);

		for (int i = 0; i < m_nodeLayout->getNoOfNodes() - 1; i++) {
			m_nodeLayout->getNodes()[i]->setHeuristic(m_nodeLayout->getNodes()[i]->getCost() * 0.9);
			m_nodeLayout->getNodes()[i]->setCost(99999);
		}

		std::priority_queue<Node*, std::vector<Node*>, NodeSearchCostComparerAStar> priorityQueue;

		m_start->setCost(0);
		m_start->setMarked(true);

		priorityQueue.push(m_start);

		while (priorityQueue.size() != 0 && priorityQueue.top() != dest) {
			auto iter = priorityQueue.top()->getArcs().begin();
			auto endIter = priorityQueue.top()->getArcs().end();

			for (; iter != endIter; iter++) {
				float distC = priorityQueue.top()->getCost() + (*iter).getWeight();

				if (distC < (*iter).getNode()->getCost()) {
					(*iter).getNode()->setCost(distC);
					(*iter).getNode()->setPrevious(priorityQueue.top());
				}

				if ((*iter).getNode()->getMarked() == false) {
					priorityQueue.push((*iter).getNode());
					(*iter).getNode()->setMarked(true);
				}

				if ((*iter).getNode() == dest) {
					Node* temp = dest;

					if (distC <= (*iter).getNode()->getCost()) {
						if (path.empty() != true) {
							path.clear();
						}

						while (temp != m_start) {
							path.push_back(temp);
							temp = temp->getPrevious();
						}
						path.push_back(m_start);
					}
				}
			}

			priorityQueue.pop(); // occasionally throws exception in debug
		}
	}

	for (int i = 0; i < m_nodeLayout->getNoOfNodes() - 1; i++) {
		m_nodeLayout->getNodes()[i]->setMarked(false);
	}
}

void AStar::ucs(Node *start, Node *dest, std::vector<Node*>& path) {
	if (start != NULL) {
		for (int i = 0; i < m_nodeLayout->getNoOfNodes() - 1; i++) {
			m_nodeLayout->getNodes()[i]->setCost(99999);
		}

		std::priority_queue<Node*, std::vector<Node*>, NodeSearchCostComparerUCS> priorityQueue;

		start->setCost(0);
		start->setMarked(true);

		priorityQueue.push(start);

		while (priorityQueue.size() != 0 && priorityQueue.top() != dest) {
			auto iter = priorityQueue.top()->getArcs().begin();
			auto endIter = priorityQueue.top()->getArcs().end();

			for (; iter != endIter; iter++) {
				float distC = priorityQueue.top()->getCost() + (*iter).getWeight();

				if (distC < (*iter).getNode()->getCost()) {
					(*iter).getNode()->setCost(distC);
					(*iter).getNode()->setPrevious(priorityQueue.top());
				}

				if ((*iter).getNode()->getMarked() == false) {
					priorityQueue.push((*iter).getNode());
					(*iter).getNode()->setMarked(true);
				}

				if ((*iter).getNode() == dest) {
					Node* temp = dest;
				
					if (distC <= (*iter).getNode()->getCost()) {
						if (path.empty() != true) {
							path.clear();
						}
				
						while (temp != start) {
							path.push_back(temp);
							temp = temp->getPrevious();
						}
						path.push_back(start);
					}
				}
			}
			priorityQueue.pop();
		}
	}

	for (int i = 0; i < m_nodeLayout->getNoOfNodes() - 1; i++) {
		m_nodeLayout->getNodes()[i]->setMarked(false);
	}
}

float AStar::magnitude(Vector v1, Vector v2) {
	return sqrt(((v2.x - v1.x) * (v2.x - v1.x)) + ((v2.y - v1.y) * (v2.y - v1.y)));
}

NodeLayout* AStar::getLayout() {
	return m_nodeLayout;
}

void AStar::addPlayer(Player *player) {
	m_player = player;
}

bool AStar::getChangedNode() {
	return m_changedNode;
}