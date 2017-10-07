#pragma once
#include<string>
class KMP
{
private:
	static const int R = 128;
	std::string pat;
	int**dfa;
public:
	KMP(std::string pat)
	{
		this->pat = pat;
		int M = pat.size();
		dfa = new int*[R];
		for (int i = 0; i < R; ++i)
			dfa[i] = new int[M]();
		dfa[pat[0]][0] = 1;
		for (int X = 0, j = 1; j < M; ++j)
		{
			for (int c = 0; c < R; ++c)
				dfa[c][j] = dfa[c][X];
			dfa[pat[j]][j] = j + 1;
			X = dfa[pat[j]][X];
		}
	}
	~KMP()
	{
		for (int i = 0; i < R; ++i)
			delete[] dfa[i];
		delete[]dfa;
	}
	int search(std::string txt)
	{
		int i, j, M = txt.size(), N = pat.size();
		for (i = 0, j = 0; i < M&&j < N; ++i)
			j = dfa[txt[i]][j];
		if (j == N)
			return i - N;
		else
			return M;
	}
};