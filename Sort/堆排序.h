#include<vector>
using namespace std;
template<typename T>
class MaxPQ
{
private:
	int*pq;
	int N = 0;
	int length;
	bool Less(int i, int j)
	{
		return pq[i] < pq[j];
	}
	void Exchange(int i, int j)
	{
		T temp = pq[i];
		pq[i] = pq[j];
		pq[j] = temp;
	}
	void Swim(int k)
	{
		while (k > 1 && less(k/2, k))
		{
			Exchange(k / 2, k);
			k /= 2;
		}
	}
	void Sink(int k)
	{
		while (2 * k <= N)
		{
			int j = 2 * k;
			if (j < N&&less(j, j + 1))
				j++;
			if (less(j, k))
				break;
			Exchange(j, k);
			k = j;
		}
	}
	void resize(int max);
public:
	MaxPQ(int maxN);
	~MaxPQ();
	bool IsEmpty();
	int Size();
	void Insert(T v);
	T DelMax();
}; 