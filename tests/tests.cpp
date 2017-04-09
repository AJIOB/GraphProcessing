#include <gtest/gtest.h>

#include "../Holt Model/HoltModel.h"

TEST(Node_tests, connection_to_itself)
{
	typedef int T;
	AJIOB::Node<T> node(1);
	node.addConnection(&node);

	EXPECT_TRUE(node.isInCycle(std::set<AJIOB::Node<T>*>(), std::set<AJIOB::Node<T>*>()));
}

TEST(Node_tests, noConnections)
{
	typedef std::string T;
	AJIOB::Node<T> node("1");

	EXPECT_FALSE(node.isInCycle(std::set<AJIOB::Node<T>*>(), std::set<AJIOB::Node<T>*>()));
}

TEST(Node_tests, simple_cycle)
{
	typedef std::string T;
	AJIOB::Node<T> node1("1"), node2("q"), node3("w"), node4("r");
	node1.addConnection(&node2);
	node2.addConnection(&node3);
	node3.addConnection(&node1);

	node1.addConnection(&node4);
	node2.addConnection(&node4);

	EXPECT_TRUE(node1.isInCycle(std::set<AJIOB::Node<T>*>(), std::set<AJIOB::Node<T>*>()));
	EXPECT_FALSE(node4.isInCycle(std::set<AJIOB::Node<T>*>(), std::set<AJIOB::Node<T>*>()));
}

TEST(Graph_tests, empty_graph)
{
	typedef std::string T;
	std::multimap<T, T> edges;

	AJIOB::Graph<T> graph(edges);
	EXPECT_FALSE(graph.isHaveCycles());
}

TEST(Graph_tests, connection_to_itself)
{
	typedef int T;
	std::multimap<T, T> edges;

	edges.insert(std::make_pair(1, 1));

	AJIOB::Graph<T> graph(edges);
	EXPECT_TRUE(graph.isHaveCycles());
}

TEST(Function_test, almost_cycle)
{
	typedef int T;
	std::multimap<T, T> edges;
	edges.insert(std::make_pair(1, 2));
	edges.insert(std::make_pair(2, 3));
	edges.insert(std::make_pair(1, 3));

	EXPECT_FALSE(isGraphHaveCycles(edges));
}

TEST(Function_test, simple_cycle)
{
	typedef int T;
	std::multimap<T, T> edges;
	edges.insert(std::make_pair(1, 2));
	edges.insert(std::make_pair(2, 3));
	edges.insert(std::make_pair(3, 1));

	EXPECT_TRUE(isGraphHaveCycles(edges));
}

TEST(Function_test, from_lecture)
{
	typedef char T;
	std::multimap<T, T> edges;
	edges.insert(std::make_pair('1', 'A'));
	edges.insert(std::make_pair('A', '2'));
	edges.insert(std::make_pair('C', '1'));
	edges.insert(std::make_pair('C', '2'));
	edges.insert(std::make_pair('F', '2'));
	edges.insert(std::make_pair('6', 'F'));
	edges.insert(std::make_pair('D', '2'));
	edges.insert(std::make_pair('D', '3'));
	edges.insert(std::make_pair('B', '3'));
	edges.insert(std::make_pair('3', 'E'));
	edges.insert(std::make_pair('E', '5'));
	edges.insert(std::make_pair('5', 'G'));
	edges.insert(std::make_pair('G', '4'));
	edges.insert(std::make_pair('4', 'D'));

	EXPECT_TRUE(isGraphHaveCycles(edges));
}

TEST(Function_test, from_lecture_modified)
{
	typedef char T;
	std::multimap<T, T> edges;
	edges.insert(std::make_pair('1', 'A'));
	edges.insert(std::make_pair('A', '2'));
	edges.insert(std::make_pair('C', '1'));
	edges.insert(std::make_pair('C', '2'));
	edges.insert(std::make_pair('F', '2'));
	edges.insert(std::make_pair('6', 'F'));
	edges.insert(std::make_pair('D', '2'));
	edges.insert(std::make_pair('D', '6'));
	edges.insert(std::make_pair('B', '3'));
	edges.insert(std::make_pair('3', 'E'));
	edges.insert(std::make_pair('E', '5'));
	edges.insert(std::make_pair('5', 'G'));
	edges.insert(std::make_pair('G', '4'));
	edges.insert(std::make_pair('4', 'D'));

	EXPECT_FALSE(isGraphHaveCycles(edges));
}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
