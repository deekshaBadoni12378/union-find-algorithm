
from collections import defaultdict


class Graph:

	def __init__(self, vertx):
		self.vertx = vertx
		self.edges = defaultdict(list)

	
	def add_edge(self, u, v):
		self.edges[u].append(v)


class Sub:
	def __init__(self, rank, root):
		self.root = root
		self.rank = rank




def find(subsets, node):
	if subsets[node].root != node:
		subsets[node].root = find(subsets, subsets[node].root)
	return subsets[node].root




def union(subsets, u, v):

	 
	if subsets[u].rank > subsets[v].rank:
		subsets[v].root = u
	elif subsets[v].rank > subsets[u].rank:
		subsets[u].root = v

	
	else:
		subsets[v].root = u
		subsets[u].rank += 1




def loop(graph):

	
	subsets = []

	for u in range(graph.vertx):
		subsets.append(Sub(u, 0))

	
	for u in graph.edges:
		u_rep = find(subsets, u)

		for v in graph.edges[u]:
			v_rep = find(subsets, v)

			if u_rep == v_rep:
				return True
			else:
				union(subsets, u_rep, v_rep)



g = Graph(3)


g.add_edge(0, 1)


g.add_edge(1, 2)


g.add_edge(0, 2)

g.add_edge(1, 0)

if loop(g):
	print('Graph contains cycle')
else:
	print('Graph does not contain cycle')


