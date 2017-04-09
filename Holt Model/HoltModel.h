#pragma once

#include <map>

#include "Graph.h"

template <typename T>
bool isGraphHaveCycles(std::multimap<T, T> edges)
{
	AJIOB::Graph<T> graph(edges);
	return graph.isHaveCycles();
}
