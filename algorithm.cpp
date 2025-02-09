#include "pch.h"
#include "Algorithm.h"
#include <iostream>
#include <queue>

Algorithm::Algorithm()
{
	previousNode = NULL;
	wayValue = NULL;
}

Algorithm::~Algorithm()
{
}

Algorithm::Algorithm(int m_start, int m_end, Graph<Node> m_g, std::vector<int> *m_previousNode, std::vector<double> *m_wayValue)
{
	previousNode = NULL;
	wayValue = NULL;
	start = m_start;
	end = m_end;
	g = m_g;
	previousNode = m_previousNode;
	wayValue = m_wayValue;
	wayValue->assign(g.getNodesAmount(), DBL_MAX); //making vector with nodesAmount positions, all values set as DBL_MAX
	previousNode->assign(g.getNodesAmount(), INT_MAX);
}

int Algorithm::aStar()
{
	std::priority_queue<QueueValue, std::vector<QueueValue>, std::greater<QueueValue>> p_queue; 

	p_queue.emplace(0, start); 	//add the start node to queue

	previousNode->at(start) = start; //set initial values
	wayValue->at(start) = 0;
	int currentNode;

	while (p_queue.empty()==0) {

		currentNode = p_queue.top().second;//take a node from the queue and set it as current
		p_queue.pop(); //take a node with the lowest (current way + predicted way)

		if (currentNode == end) {
			return 0;//end node found, leave this method;
		}

		for (int next : g.getDirectConnections(currentNode)) { //next is a number of every node that is in direct connection to the current node
			double newVal = wayValue->at(currentNode) + g.nodeDistance(currentNode, next); //newVal = the shortest length to the current node + length form current node to the next node

			if (wayValue->at(next) == DBL_MAX || newVal < wayValue->at(next)) { //if we haven't visited "next" node, or we found a shorter way to it
				wayValue->at(next) = newVal; 

				double toQueue = newVal + g.nodeDistance(next, end); //newValue + heuristic
				//g.nodeDistance(next, end) - heuristic function
				previousNode->at(next) = currentNode; //save current node as "the best predecessor" on the way to the "next" node
				p_queue.emplace(toQueue, next);//put toQueue, next, to priority_queue
			}
		}
	}
	//no connection
	return 1;
}

int Algorithm::Dijkstra()
{
	std::priority_queue<QueueValue, std::vector<QueueValue>, std::greater<QueueValue>> p_queue;

	p_queue.emplace(0, start); 	//add the start node to queue

	previousNode->at(start) = start; //set initial values
	wayValue->at(start) = 0;
	int currentNode;

	while (p_queue.empty()==0) {

		currentNode = p_queue.top().second;//take a node from the queue and set it as current
		p_queue.pop(); //take a node with the lowest (current way + predicted way)

		if (currentNode == end) {
			return 0;//end node found, leave this method;
		}

		for (int next : g.getDirectConnections(currentNode)) { //next is a number of every node that is in direct connection to the current node
			double newVal = wayValue->at(currentNode) + g.nodeDistance(currentNode, next); //newVal = the shortest length to the current node + length form current node to the next node

			if (wayValue->at(next) == DBL_MAX || newVal < wayValue->at(next)) { //if we haven't visited "next" node, or we found a shorter way to it
				wayValue->at(next) = newVal;
				previousNode->at(next) = currentNode; //save current node as "the best predecessor" on the way to the "next" node
				p_queue.emplace(newVal, next);//put newVal, next, to priority_queue
			}
		}
	}
	 //no connection
	return 1;
}

std::vector<int>* Algorithm::buildTheWay(int start, int end)
{
	int currentNode=end;
	inOrderWay.push_back(end);
	while (!(currentNode == start)) {
		
		inOrderWay.push_back(previousNode->at(currentNode));
		currentNode = previousNode->at(currentNode);
	}
	std::reverse(inOrderWay.begin(), inOrderWay.end());

	return &inOrderWay;

}

double Algorithm::getWayLength()
{
	return wayValue->at(end);
}
