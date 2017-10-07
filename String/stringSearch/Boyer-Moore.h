#pragma once
#include<string>
class Boyer_Moore
{
private:
	static const int R = 128;
	int* right;
	std::string pat;
public:
	Boyer_Moore(std::string pat)
	{
		this->pat = pat;
		int M = pat.size();
		right = new int[R]();
		for (int i = 0; i < R; ++i)
			right[i] = -1;
		for (int i = 0; i < M; ++i)
			right[pat[i]] = i;
	}
	~Boyer_Moore()
	{
		delete[] right;
	}
	int search(std::string txt)
	{
		int M = pat.size();
		int N = txt.size();
		int skip;
		for (int i = 0; i <= N-M; i+=skip)
		{
			skip = 0;
			for (int j = M - 1; j >= 0; --j)
				if (pat[j] != txt[i + j])
				{
					skip = j - right[txt[i + j]];
					if (skip < 1)
						skip = 1;
					break;
				}
			if (skip == 0)
				return i;
		}
		return N;
	}
};