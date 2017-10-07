#include"Bag.h"
#include<stack>
#include<queue>
class Graph
{
protected:
	int V;//顶点个数
	int E;//边的数目
	Bag<int> *adj;
public:
	Graph(int v);
	virtual ~Graph();
	int GetV() { return V; }
	int GetE() { return E; }
	virtual void AddEdge(int w, int v);
	std::vector<int> GetBagValve(int w);
};
class DirectGraph :public Graph
{
public:
	DirectGraph(int v) :
		Graph(v) {}
	void AddEdge(int w, int v) override;
	DirectGraph reverse();
};
class base
{
protected:
	bool*marked;
	int*EdgeTo;
	int s;
public:
	base() = default;
	base(int s, Graph &G);
	virtual ~base(){delete[] marked;delete[] EdgeTo;}
	bool HasPathTo(int v);
	std::vector<int> PathTo(int v);
};
class DFS:public base
{
public:
	DFS(int s, Graph &G)
		:base(s, G) {dfs(G, s);}
	void dfs(Graph&G, int w);
};
class BFS:public base
{
public:
	BFS(int x,Graph&G):
		base(x, G) {bfs(G, x);}
	void bfs(Graph&G,int x);
};