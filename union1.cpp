#include <iostream>
#include <conio.h>
#include <bits/stdc++.h>

using namespace std;


struct Edge {
	int source, destination;
};


struct Graph {

	int V, E;


	struct Edge* edge;
};

struct sub {
	int root;
	int rank;
};


struct Graph* createGraph(int V, int E)
{
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
	graph->V = V;
	graph->E = E;

	graph->edge = (struct Edge*)malloc(graph->E * sizeof(struct Edge));

	return graph;
}


int find(struct sub subsets[], int i)
{

	if (subsets[i].root != i)
		subsets[i].root = find(subsets, subsets[i].root);

	return subsets[i].root;
}


void Union(struct sub subsets[], int xroot, int yroot)
{


	if (subsets[xroot].rank < subsets[yroot].rank)
		subsets[xroot].root = yroot;
	else if (subsets[xroot].rank > subsets[yroot].rank)
		subsets[yroot].root = xroot;


	else {
		subsets[yroot].root = xroot;
		subsets[xroot].rank++;
	}
}


int loop (struct Graph* graph)
{
	int V = graph->V;
	int E = graph->E;

	struct sub* subsets
		= (struct sub*)malloc(V * sizeof(struct sub));

	for (int v = 0; v < V; ++v) {
		subsets[v].root = v;
		subsets[v].rank = 0;
	}


	for (int e = 0; e < E; ++e) {
		int x = find(subsets, graph->edge[e].source);
		int y = find(subsets, graph->edge[e].destination);

		if (x == y)
			return 1;

		Union(subsets, x, y);
	}
	return 0;
}


int main()
{

	int V = 3, E = 3;
	struct Graph* graph = createGraph(V, E);


	graph->edge[0].source = 0;
	graph->edge[0].destination = 1;


	graph->edge[1].source = 1;
	graph->edge[1].destination = 2;


	graph->edge[2].source = 0;
	graph->edge[2].destination = 2;

	graph->edge[3].source = 2;
	graph->edge[3].destination = 3;


	if (loop(graph))
		cout << "Graph contains cycle";
	else
		cout << "Graph doesn't contain cycle";

	return 0;
}

