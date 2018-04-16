/***********************************************************************
 * Component:
 *    Week 13, Graph
 * Author:
 *    Spencer Eccles
 *    Jonathan Sirrine
 *    Atsushi Jindo
 *    Eric Brich
************************************************************************/
#include "vertex.h"
#include "set.h"
#include "list.h"
#include "vector.h"

#ifndef GRAPH_H
#define GRAPH_H
/*****************************************************************
 * GRAPH
 *****************************************************************/
// template <class T>
class Graph
{
public:
	Graph(int numVertices) throw (const char *) : numVertices(numVertices) {}
	Graph (const Graph & rhs) { *this = rhs; }
	~Graph() {}
	Graph & operator = (const Graph & rhs) throw(const char *)
	{ 
		clear(); 
		for (int source = 0; source < rhs.size(); ++source)
   			for (int destination = 0; destination < rhs.size(); ++destination)
   				matrix[source][destination] = rhs.matrix[source][destination];
		numVertices = rhs.numVertices;
	}

	int size() const { return numVertices; }
	void clear() 
	{ 
		numVertices = 0; 
		for (int source = 0; source < 25; ++source)
   			for (int destination = 0; destination < 25; ++destination)
   				matrix[source][destination] = false;
	}
	
	void add(Vertex v1, Vertex v2) 
	{
		matrix[v1.index()][v2.index()] = true;
	}

	void add(Vertex v, custom :: set <Vertex> s) {
		for (custom :: set <Vertex> :: iterator it = s.begin(); it != s.end(); ++it)
		{
			matrix[v.index()][(*it).index()] = true;
		}
	}

	bool isEdge(Vertex v1, Vertex v2) const {
		bool edge = matrix[v1.index()][v2.index()];
		return edge;
	}

	// vector <Vertex> findPath(Vertex beg, Vertex end)
	// {

	// }

	typename custom :: set <Vertex> findEdges(Vertex v) {}
	typename custom :: vector <Vertex> findPath(Vertex v1, Vertex v2) {}

private:
	bool matrix[25][25];
	int numVertices;
};



#endif // GRAPH_H