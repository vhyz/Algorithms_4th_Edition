#pragma once
#include<string>
using std::string;
class StringSort
{
private:
	static const int N = 256;
	static const int M = 15;
	string*aux;
	int charAt(string &s, int &d);
public:
	StringSort() = default;
	StringSort(const StringSort&) = delete;
	~StringSort(){delete[] aux;}
	void sort(string*a,int N);
	void sort(string*a, int lo, int hi, int d);
};
int StringSort::charAt(string & s, int & d)
{
	if (d < s.size())
		return s[d];
	else
		return -1;
}
inline void StringSort::sort(string * a,int N)
{
	aux = new string[N]();
	sort(a, 0, N - 1, 9);
}
inline void StringSort::sort(string * a, int lo, int hi, int d)
{
	if (hi <= lo)
		return;
	int count[N + 2];
	for (int i = lo; i <= hi; ++i)
		++count[charAt(a[i], d) + 2];
	for (int i = lo; i < N+1; ++i)
		count[i + 1] += count[i];
	for (int i = lo; i <= hi; ++i)
		aux[count[charAt(a[i], d) + 1]++] = a[i];
	for (int i = lo; i <= hi; ++i)
		a[i] = aux[i];
	for (int i = 0; i < N + 2; ++i)
		sort(a, lo + count[i], lo + count[i + 1] - 1, d + 1);
}