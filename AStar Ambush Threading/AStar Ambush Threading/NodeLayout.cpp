#include "NodeLayout.h"

std::vector<Node*> NodeLayout::getNodes() {
	return m_nodes;
}

void NodeLayout::addNode(Vector pos, std::string id) {
	m_nodes.push_back(new Node(pos, id));
}

void NodeLayout::setNodesPerLine(int num) {
	m_nodesPerLine = num;
}

int NodeLayout::getNoOfNodes() {
	return m_nodes.size();
}

void NodeLayout::draw(SDL_Renderer *renderer) {
	for (int i = 0; i < m_nodes.size(); i++) {
		m_nodes.at(i)->draw(renderer);
	}
}

void NodeLayout::addArcs() {
	int col = 1;

	for (int i = 0; i < m_nodes.size(); i++) {
		if (i == (m_nodesPerLine * col)) {
			col++;
		}

		if ((i + m_nodesPerLine) < m_nodes.size()) {
			m_nodes.at(i)->addArc(m_nodes.at(i + m_nodesPerLine));
			m_nodes.at(i + m_nodesPerLine)->addArc(m_nodes.at(i));

			m_nodes.at(i)->getArcs().back().setCorrespondingArc(&m_nodes.at(i + m_nodesPerLine)->getArcs().back());
			m_nodes.at(i + m_nodesPerLine)->getArcs().back().setCorrespondingArc(&m_nodes.at(i)->getArcs().back());
		}

		if ((i + 1) < m_nodes.size()) {
			if (i < (m_nodesPerLine * col) - 1) {
				m_nodes.at(i)->addArc(m_nodes.at(i + 1));
				m_nodes.at(i + 1)->addArc(m_nodes.at(i));

				m_nodes.at(i)->getArcs().back().setCorrespondingArc(&m_nodes.at(i + 1)->getArcs().back());
				m_nodes.at(i + 1)->getArcs().back().setCorrespondingArc(&m_nodes.at(i)->getArcs().back());
			}
		}

		if (i + 1 + m_nodesPerLine < m_nodes.size()) {
			if (i < (m_nodesPerLine * col) - 1) {
				m_nodes.at(i)->addArc(m_nodes.at(i + 1 + m_nodesPerLine));
				m_nodes.at(i + 1 + m_nodesPerLine)->addArc(m_nodes.at(i));

				m_nodes.at(i)->getArcs().back().setCorrespondingArc(&m_nodes.at(i + 1 + m_nodesPerLine)->getArcs().back());
				m_nodes.at(i + 1 + m_nodesPerLine)->getArcs().back().setCorrespondingArc(&m_nodes.at(i)->getArcs().back());
			}
		}

		if ((i + 1) - m_nodesPerLine >= 0) {
			m_nodes.at(i)->addArc(m_nodes.at((i + 1) - m_nodesPerLine));
			m_nodes.at((i + 1) - m_nodesPerLine)->addArc(m_nodes.at(i));

			m_nodes.at(i)->getArcs().back().setCorrespondingArc(&m_nodes.at((i + 1) - m_nodesPerLine)->getArcs().back());
			m_nodes.at((i + 1) - m_nodesPerLine)->getArcs().back().setCorrespondingArc(&m_nodes.at(i)->getArcs().back());
		}
	}
}