#include"MST.h"
int Edge::other(int vertex)
{
	if (v == vertex)
		return w;
	else
		return v;
}
int Edge::comparTo(Edge E)
{
	if (getWeight() < E.getWeight())
		return -1;
	else if (getWeight() > E.getWeight())
		return 1;
	else
		return 0;
}
edgeWeightedGraph::edgeWeightedGraph(int v)
{
	V = v;
	E = 0;
	adj = new Bag<Edge*>[v]();
}
void edgeWeightedGraph::addEdge(Edge * e)
{
	int v = e->either();
	int w = e->other(v);
	adj[v].put(e);
	adj[w].put(e);
	++E;
}
std::vector<Edge*> edgeWeightedGraph::getValve(int v)
{
	return adj[v].Travel();
}

lazyPrim::lazyPrim(edgeWeightedGraph & G)
{
	marked = new bool[G.getV()]();
	visit(G, 0);
	while (!pq.isEmpty())
	{
		Edge * e = pq.DeleteMin();
		int v = e->either(), w = e->other(v);
		if (marked[v] && marked[w])
			continue;
		mst.push(e);
		if (!marked[w])
			visit(G, v);
		if (!marked[w])
			visit(G, w);
	}
}

void lazyPrim::visit(edgeWeightedGraph & G, int v)
{
	marked[v] = true;
	std::vector<Edge*> tmp = G.getValve(v);
	for (int i = 0; i < tmp.size(); ++i)
		if (!marked[tmp[i]->other(v)])
			pq.put(tmp[i]);
}

UF::UF(int size)
{
	count = size;
	id = new int[size]();
	for (int i = 0; i < size; ++i)
		id[i] = i;
}

bool UF::isConnected(int & p, int & q)
{
	return find(p) == find(q);
}

int UF::find(int & p)
{
	while (p != id[p])
		p = id[p];
	return p;
}

void UF::Union(int & p,int & q)
{
	int pRoot = find(p);
	int qRoot = find(q);
	if (pRoot == qRoot)
		return;
	id[qRoot] = pRoot;
	--count;
}

Kruskal::Kruskal()
{

}

std::queue<Edge*> Kruskal::GetEdges()
{
	return std::queue<Edge*>();
}
