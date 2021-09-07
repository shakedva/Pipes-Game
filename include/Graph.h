//----------------------------------include section---------------------------------
#pragma once
#include <vector>
#include <set>
#include <list>
#include "macros.h"
#include <iostream>
#include <SFML/Graphics.hpp>

//---------------------------------template class implementation-----------------------------
template <class T>
class Graph
{
public:
	Graph() = default;
	~Graph() = default;
	void addVertex(T*, int, int);
	void saveEdges();
	void updateAdjList(T*);
	void BFS(T*, T*);
	void resetTarget();
	void printGraph(sf::RenderWindow&) const;
	void clearGraph();
	T* getVertex(int, int) const;
	bool getIfFoundTarget() const;
	void setNumOfVertices(int, int);

private:
	int m_numOfVertices = INIT; //saves number of vertices in the game
	bool m_foundTarget = false; //if we reached the sink successfully this will be true
	std::vector<std::vector<T*>> m_vertices; // all the vertices
	std::map<T*, std::set<T*>> m_adjList; // all the vertices with their neighbors
};

// saves the the first adjacency list of the current level
template <class T>
void Graph<T>::saveEdges()
{
	// iterate through all the vertices and save its connected neighbors
	for (int i = 0; i < m_vertices.size(); i++)
	{
		for (int j = 0; j < m_vertices[i].size(); j++)
			m_adjList[m_vertices[i][j]] = m_vertices[i][j]->checkConnections();
	}
}
//receives a vertex and updates who his neighbors in his neighbors map
template <class T>
void Graph<T>::updateAdjList(T* vertex)
{
	// iterate through all the four directions, for all possible neightbors
	for (int i = 0; i < NUM_EXITS; i++)
	{
		T* t = vertex->getNeighbor(i); //save the neigbor in the exit i (direction)
		// if it is null then he does not have a neighbor in direction i
		if (t != nullptr)
		{
			m_adjList[t].clear(); 
			m_adjList[t] = t->checkConnections(); //save the new connections if they are pointing to each other
		}
	}
	// after saving all the new connection to all 4 possible neighbors, change it for the current vertex
	m_adjList[vertex].clear();
	m_adjList[vertex] = vertex->checkConnections();
}

// save a vertex in the graph and update its neighbors - they receive him (newVertex) and he receives its neighbors 
template <class T>
void Graph<T>::addVertex(T* newVertex, int row, int col)
{
	m_vertices[row].push_back(newVertex);
	// check if he has upper and or left neighbors and update accordingly
	if (row >= 1)
	{
		if (col >= 1)
		{
			// saving the upper and left neighbors for vertex [row][col]
			m_vertices[row][col]->addNeighbor(m_vertices[row - 1][col], UP);
			m_vertices[row][col]->addNeighbor(m_vertices[row][col - 1], LEFT);

			// saving the vertex [row][col] in its neighbors
			m_vertices[row-1][col]->addNeighbor(m_vertices[row][col], DOWN);
			m_vertices[row][col-1]->addNeighbor(m_vertices[row][col], RIGHT);
			return;
		}
		// currently in the first col: saving the upper neighbor for the vertex and saving the vertex in the upper neighbor
		m_vertices[row][col]->addNeighbor(m_vertices[row - 1][col], UP);
		m_vertices[row - 1][col]->addNeighbor(m_vertices[row][col], DOWN);
		return;
	}
	else if (col >= 1) // currently in the first row but not in the first col:
	{
		//saving the left neighbor for the vertex and saving the vertex in the left neighbor
		m_vertices[row][col]->addNeighbor(m_vertices[row][col-1], LEFT);
		m_vertices[row][col - 1]->addNeighbor(m_vertices[row][col], RIGHT);
	}
	
}

// BFS (Breadth-first search) algorithm on graph.
// it receivs a source and scan all the adjList in order to find the target
// if it finds the target it changes m_foundTarget to true and stop the algorithm.
template <class T>
void Graph<T>::BFS(T* source, T* target)
{
	// initializing in all the vertices to be unvisited
	for (int i = 0; i < m_vertices.size(); i++)
	{
		for (int j = 0; j < m_vertices[i].size(); j++)
		{
			m_vertices[i][j]->changeVisited(false);
		}
	}
	
	// create a list for BFS
	std::list<T*> queue;

	// mark the current node as visited and add it to the list
	source->changeVisited(true);
	queue.push_back(source);

	// iterate as long as there are vertices in the queue
	while (!queue.empty())
	{
		// save the current source to be the begining of the list 
		source = queue.front();
		// it1 now points to the set of neighbors of the source
		auto it1 = m_adjList[source]; 
		queue.pop_front(); // remove the source
		
		//iterate on the set of neighbors of the current source
		for(auto it2 = it1.begin(); it2 != it1.end() ; it2++)
		{
			// if we found the target - mark it as visited and finish the algorithm
			if (*it2 == target) 
			{
				target->changeVisited(true);
				m_foundTarget = true;
				return;
			}
			// if the neighbor *it2 was not visited- change it to visted and push it to the queue
			else if (!(*it2)->getVisited())
			{
				(*it2)->changeVisited(true);
				queue.push_back(*it2);
			}
		}
	}
	// if reached here - it did not find the target in the bfs.
}

// clears the graph and all its information
template <class T>
void Graph<T>::clearGraph()
{
	//initializes all data structurs before the next level
	m_numOfVertices = INIT;
	m_foundTarget = false;
	m_vertices.clear();
	m_adjList.clear();
}

// prints all the vertices in the graph
template <class T>
void Graph<T>::printGraph(sf::RenderWindow& window) const
{
	// iterate through all the vertices of the graph
	for (int i = 0; i < m_vertices.size(); i++)
	{
		for (int j = 0; j < m_vertices[i].size(); j++)
		{
			m_vertices[i][j]->draw(window);
		}
	}
}
// return the vertex [row][col] if exist
template <class T>
T* Graph<T>::getVertex(int row, int col) const
{
	if(row >= 0 && row <  m_vertices.size())
		if( col >= 0 && col < m_vertices[row].size())
			return m_vertices[row][col];
	return nullptr;
}

// after the main program received the bfs was successful it resets the found target to false
template <class T>
void Graph<T>::resetTarget()
{
	m_foundTarget = false;
}

template <class T>
bool Graph<T>::getIfFoundTarget() const
{
	return m_foundTarget;
}

// receives how many vertices the graph will have and reserve enough space for them
template <class T>
void Graph<T>::setNumOfVertices(int height, int width)
{
	m_numOfVertices = height * width;
	m_vertices.reserve(height);
	for (int i = 0; i < height; i++)
	{
		m_vertices.push_back(std::vector<T*>());
	}
}
