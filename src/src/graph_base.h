#ifndef __GRAPH_BASE_H__
#define __GRAPH_BASE_H__

#include <vector>
#include <map>

#include "vertex_base.h"
#include "edge_base.h"

using namespace std;

class graph_base
{
public:
	graph_base();
	graph_base(const graph_base &gr);
	virtual ~graph_base();

protected:
	vector<vertex_base*> vv;
	set<edge_base*> se;

public:
	// modify the graph
	virtual int add_vertex();
	virtual edge_descriptor add_edge(int s, int t);
	virtual int remove_edge(edge_base *e);
	virtual int remove_edge(int s, int t);
	virtual int move_edge(edge_base *e, int x, int y);
	virtual int clear_vertex(int v);
	virtual int clear();

	// access functions
	virtual PEB edge(int s, int t) const;
	virtual size_t num_vertices() const;
	virtual size_t num_edges() const;
	virtual int degree(int v) const;
	virtual int in_degree(int v) const;
	virtual int out_degree(int v) const;
	virtual PEE edges() const;
	virtual PEE in_edges(int v) const;
	virtual PEE out_edges(int v) const;
	virtual set<int> adjacent_vertices(int v) const;

	// algorithms
	virtual int bfs(int s, vector<int> &v) const;
	virtual int bfs_reverse(int t, vector<int> &v) const;

	// test
	virtual int print() const;
	static int test();
};

typedef map<edge_descriptor, bool> MEB;
typedef map<edge_descriptor, double> MED;
typedef pair<edge_descriptor, double> PED;
typedef map<edge_descriptor, int> MEI;
typedef pair<edge_descriptor, int> PEI;
typedef vector<edge_descriptor> VE;

#endif