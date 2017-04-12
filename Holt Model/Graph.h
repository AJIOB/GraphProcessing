#pragma once

#include <map>
#include <set>

#include "Namespace.h"
#include "Node.h"


NAMESPACE_BEGIN

template <typename T>
class Graph
{
	std::set<Node<T>*> nodes;

	Node<T>* findOrCreateNode(const T& nodeID);

public:
	/**
	 * Build the non-oriented graph with edges.
	 * Key in multimap - starting node.
	 * Value in multimap - ending node.
	 */
	explicit Graph(const std::multimap<T, T>& edges = std::multimap<T, T>());
	Graph(const Graph& other);
	~Graph();

	Graph& operator=(const Graph& other);

	bool isHaveCycles() const;

	void addEdge(const T& begin, const T& end);
	void removeEdge(const T& begin, const T& end);
};


template <typename T>
Node<T>* Graph<T>::findOrCreateNode(const T& nodeID)
{
	auto it = std::find_if(nodes.begin(), nodes.end(),
		[&nodeID](Node<T>* elem)
		{
			return (nodeID == elem->getId());
		});
	if (it != nodes.end())
	{
		return *it;
	}

	Node<T>* res = new Node<T>(nodeID);
	nodes.insert(res);
	return res;
}

template <typename T>
Graph<T>::Graph(const std::multimap<T, T>& edges)
{
	for (auto it = edges.begin(); it != edges.end(); ++it)
	{
		findOrCreateNode(it->first)->addConnection(findOrCreateNode(it->second));
	}
}

template <typename T>
Graph<T>::Graph(const Graph& other)
{
	for (auto node : other.nodes)
	{
		auto connectedNodeIDs = node->getConnectedIDs();
		for (auto rightNodeID : connectedNodeIDs)
		{
			findOrCreateNode(node.getID())->addConnection(findOrCreateNode(rightNodeID));
		}
	}
}

template <typename T>
Graph<T>::~Graph()
{
	for (auto it = nodes.begin(); it != nodes.end(); ++it)
	{
		delete *it;
	}
}

template <typename T>
Graph<T>& Graph<T>::operator=(const Graph& other)
{
	if (&other == this)
	{
		return *this;
	}

	for (auto node : nodes)
	{
		delete node;
	}

	for (auto node : other.nodes)
	{
		auto connectedNodeIDs = node->getConnectedIDs();
		for (auto rightNodeID : connectedNodeIDs)
		{
			findOrCreateNode(node.getID())->addConnection(findOrCreateNode(rightNodeID));
		}
	}

	return *this;
}

template <typename T>
bool Graph<T>::isHaveCycles() const
{
	std::set<Node<T>*> nodesToCheck = nodes;

	while (!nodesToCheck.empty())
	{
		std::set<Node<T>*> noCycleElements;

		if ((*nodesToCheck.begin())->isInCycle(std::set<Node<T>*>(), noCycleElements))
		{
			return true;
		}

		//remove all elements, that not in cycles
		for (auto it = noCycleElements.begin(); it != noCycleElements.end(); ++it)
		{
			nodesToCheck.erase(*it);
		}
	}

	return false;
}

template <typename T>
void Graph<T>::addEdge(const T& begin, const T& end)
{
	findOrCreateNode(begin)->addConnection(findOrCreateNode(end));
}

template <typename T>
void Graph<T>::removeEdge(const T& begin, const T& end)
{
	findOrCreateNode(begin)->removeConnection(findOrCreateNode(end));
}

NAMESPACE_END
