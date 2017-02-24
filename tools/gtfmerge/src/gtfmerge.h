#ifndef __GTFMERGE_H__
#define __GTFMERGE_H__

#include "genome1.h"

using namespace std;

class gtfmerge
{
public:
	vector<genome1> genomes;

public:
	int add_genome(const string &file);
	int build_union(genome1 &gm);
	int print();
};

#endif