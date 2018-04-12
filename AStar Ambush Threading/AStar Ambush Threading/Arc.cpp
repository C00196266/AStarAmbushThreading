#include "Arc.h"

void Arc::setNode(Node *n) {
	m_node = n;
}

Node* Arc::getNode() {
	return m_node;
}

void Arc::setCorrespondingArc(Arc *arc) {
	m_correspondingArc = arc;
}

Arc* Arc::getCorrespondingArc() {
	return m_correspondingArc;
}

void Arc::setWeight(float w) {
	m_weight = w;
	m_initialWeight = w;
}

int Arc::getWeight() {
	return m_weight;
}

void Arc::incrementWeight() {
	m_weight++;
}

void Arc::decrementWeight() {
	if (m_weight != m_initialWeight) {
		m_weight--;
	}
}

void Arc::resetWeight() {
	m_weight = m_initialWeight;
}