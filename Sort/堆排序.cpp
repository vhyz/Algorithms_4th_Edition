#include"∂—≈≈–Ú.h"

template<typename T>
inline MaxPQ<T>::MaxPQ(int maxN)
{
	pq.resize(maxN + 1);
	length = maxN + 1;
}
template<typename T>
MaxPQ<T>::~MaxPQ()
{
	delete[] pq;
}

template<typename T>
bool MaxPQ<T>::IsEmpty()
{
	return N == 0;
}


template<typename T>
int MaxPQ<T>::Size()
{
	return N;
}


template<typename T>
void MaxPQ<T>::Insert(T v)
{
	if (N + 1 == length)
		resize(2 * length);
	pq[++N] = v;
	swim(N);
}

template<typename T>
T MaxPQ<T>::DelMax()
{
	
	T max = pq[1];
	Exchange(1, N--);
	if (N > 0 && N < length / 4)
		resize(length / 2);
	sink(1);
	return max;
}

template<typename T>
void MaxPQ<T>::resize(int max)
{
	T * temp = new T[max];
	for (int i = 1; i <= N; i++)
		temp[i] = pq[i];
	delete[] pq;
	pq = temp;
	length = max;
}