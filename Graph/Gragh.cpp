#include "Gragh.h"
using std::cout;
using std::endl;
Graph::Graph(int v)
{
	V = v;
	E = 0;
	adj = new Bag<int>[V]();
}
void Graph::AddEdge(int w, int v)
{
	adj[w].put(v);
	adj[v].put(w);
	++E;
}
Graph::~Graph()
{
	delete[] adj;
	cout << endl;
	cout << "delete Graph";
	
}
std::vector<int> Graph::GetBagValve(int w)
{
	return adj[w].Travel();
}
void DFS::dfs(Graph & G, int w)
{
	//cout << w << endl;
	marked[w] = true;
	std::vector<int> temp = G.GetBagValve(w);
	for (int i = 0; i < temp.size(); ++i)
		if (!marked[temp[i]])
		{
			EdgeTo[temp[i]] = w;
			dfs(G, temp[i]);
		}
}
bool base::HasPathTo(int v)
{
	return marked[v];
}
std::vector<int> base::PathTo(int v)
{
	if (!HasPathTo(v))
		return std::vector<int>();
	Bag<int>temp;
	while (v != s)
	{
		temp.put(v);
		v = EdgeTo[v];
	}
	temp.put(s);
	return temp.Travel();
}
base::base(int s, Graph & G)
{
	marked = new bool[G.GetV()]();
	EdgeTo = new int[G.GetV()]();
	this->s = s;
}
void BFS::bfs(Graph&G,int s)
{
	std::queue<int>q;
	q.push(s);
	//cout << s << endl;
	marked[s] = true;
	while (!q.empty())
	{
		s = q.front();
		q.pop();
		std::vector<int>temp = G.GetBagValve(s);
		for (auto it = temp.begin(); it != temp.end(); ++it)
			if (!marked[*it])
			{
				//cout << *it << endl;
				EdgeTo[*it] = s;
				marked[*it] = true;
				q.push(*it);
			}
	}
}
void DirectGraph::AddEdge(int w, int v)
{
	adj[w].put(v);
	++E;
}
DirectGraph DirectGraph::reverse()
{
	DirectGraph R(V);
	for (int v = 0; v < V; v++)
	{
		std::vector<int>temp = GetBagValve(v);
		for (int i = 0; i < temp.size(); ++i)
			R.AddEdge(temp[i], v);
	}
	return R;
}