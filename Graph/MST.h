#include"Bag.h"
#include"Gragh.h"
#include<queue>
#include"Minpq.h"
class Edge
{
private:
	int v; //����֮һ
	int w; //����һ������
	double weight;//Ȩ��
public:
	Edge(int V,int W,int Weight):
		v(V),w(W),weight(Weight) {}
	double getWeight()const { return weight; }
	int either() { return v; }
	int other(int vertex);
	int comparTo(Edge E) ;
	bool operator < (const Edge & E) { return getWeight() < E.getWeight(); }
	bool operator > (const Edge & E) { return getWeight() > E.getWeight(); }
};
class edgeWeightedGraph 
{
private:
	int V; //�������
	int E;//����
	Bag<Edge*> * adj;
public:
	edgeWeightedGraph(int v);
	int getV() { return V; }
	int getE() { return E; }
	void addEdge(Edge *e);
	std::vector<Edge*> getValve(int v);
};
class lazyPrim
{
private:
	bool* marked;
	std::queue<Edge*>mst;
	Minpq<Edge*>pq;
public:
	lazyPrim(edgeWeightedGraph & G);
	~lazyPrim() { delete marked; }
	void visit(edgeWeightedGraph&G, int v);
	std::queue<Edge*> edges() { return mst; }
};
class UF
{
private:
	int* id;
	int count;
public:
	UF(int size);
	~UF() { delete[] id; }
	int getCount() { return count; }
	bool isConnected(int &p, int &q);
	int find(int & p);
	void Union(int&p, int&q);
};
class Kruskal
{
private:
	std::queue<Edge*>mst;
public:
	Kruskal();
	std::queue<Edge*> GetEdges();
};