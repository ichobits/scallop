#include "hyper_set.h"
#include "config.h"
#include <algorithm>

int hyper_set::clear()
{
	nodes.clear();
	edges.clear();
	return 0;
}

int hyper_set::add_node_list(const set<int> &s)
{
	vector<int> v(s.begin(), s.end());
	sort(v.begin(), v.end());
	for(int i = 0; i < v.size(); i++) v[i]++;
	if(nodes.find(v) == nodes.end()) nodes.insert(PVII(v, 1));
	else nodes[v]++;
	return 0;
}

int hyper_set::build(directed_graph &gr, MEI& e2i)
{
	build_edges(gr, e2i);
	build_index();
	purify();
	build_index();
	return 0;
}

int hyper_set::build_edges(directed_graph &gr, MEI& e2i)
{
	edges.clear();
	for(MVII::iterator it = nodes.begin(); it != nodes.end(); it++)
	{
		int c = it->second;
		if(c < min_router_count) continue;

		const vector<int> &vv = it->first;
		vector<int> ve;
		bool b = true;
		for(int k = 0; k < vv.size() - 1; k++)
		{
			PEB p = gr.edge(vv[k], vv[k + 1]);
			if(p.second == false) b = false;
			if(b == false) break;
			ve.push_back(e2i[p.first]);
		}
		if(b == false) continue;
		edges.push_back(ve);
	}

	return 0;
}

int hyper_set::build_index()
{
	e2s.clear();
	for(int i = 0; i < edges.size(); i++)
	{
		vector<int> &v = edges[i];
		for(int j = 0; j < v.size(); j++)
		{
			int e = v[j];
			if(e2s.find(e) == e2s.end())
			{
				set<int> s;
				s.insert(i);
				e2s.insert(PISI(e, s));
			}
			else
			{
				e2s[e].insert(i);
			}
		}
	}
	return 0;
}

set<int> hyper_set::get_intersection(const vector<int> &v)
{
	set<int> ss;
	if(v.size() == 0) return ss;
	if(e2s.find(v[0]) == e2s.end()) return ss;
	ss = e2s[v[0]];
	vector<int> vv(ss.size());
	for(int i = 1; i < v.size(); i++)
	{
		set<int> s;
		if(e2s.find(v[i]) == e2s.end()) return s;
		s = e2s[v[i]];
		vector<int>::iterator it = set_intersection(ss.begin(), ss.end(), s.begin(), s.end(), vv.begin());
		ss = set<int>(vv.begin(), it);
	}
	return ss;
}

set<int> hyper_set::get_successors(int e)
{
	set<int> s;
	if(e2s.find(e) == e2s.end()) return s;
	set<int> &ss = e2s[e];
	for(set<int>::iterator it = ss.begin(); it != ss.end(); it++)
	{
		vector<int> &v = edges[*it];
		for(int i = 0; i < v.size(); i++)
		{
			if(v[i] == e && i < v.size() - 1) s.insert(v[i + 1]);
		}
	}
	return s;
}

vector<PI> hyper_set::get_routes(int x, directed_graph &gr, MEI &e2i)
{
	edge_iterator it1, it2;
	vector<PI> v;
	for(tie(it1, it2) = gr.in_edges(x); it1 != it2; it1++)
	{
		assert(e2i.find(*it1) != e2i.end());
		int e = e2i[*it1];
		set<int> s = get_successors(e);
		for(set<int>::iterator it = s.begin(); it != s.end(); it++)
		{
			PI p(e, *it);
			v.push_back(p);
		}
	}
	return v;
}

int hyper_set::purify()
{
	VVI vv;
	for(int i = 0; i < edges.size(); i++)
	{
		vector<int> &v = edges[i];
		set<int> s = get_intersection(v);
		assert(s.find(i) != s.end());
		for(set<int>::iterator it = s.begin(); it != s.end(); it++)
		{
			if((*it) == i) continue;
			bool b = consecutive_subset(edges[*it], v);
			assert(b == true);
		}
		if(s.size() >= 2) continue;
		vv.push_back(v);
	}
	edges = vv;
	return 0;
}

int hyper_set::print()
{
	//printf("PRINT HYPER_SET\n");
	for(MVII::iterator it = nodes.begin(); it != nodes.end(); it++)
	{
		const vector<int> &v = it->first;
		int c = it->second;
		printf("hyper-edge (nodes), counts = %d, list = ( ", c); 
		printv(v);
		printf(")\n");
	}

	for(int i = 0; i < edges.size(); i++)
	{
		printf("hyper-edge (edges) %d: ( ", i);
		printv(edges[i]);
		printf(")\n");
	}
	return 0;
}