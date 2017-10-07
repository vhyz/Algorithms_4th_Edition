#pragma once
#include<string>
class Rabin_Karp
{
private:
	std::string pat;
	int M;
	long long Q;
	static const int R = 128;
	long long RM;
	long long patHash;
public:
	Rabin_Karp(std::string pat)
	{
		this->pat = pat;
		M = pat.size();
		Q = 23333333333333333;
		RM = 1;
		for (int i = 1; i < M - 1; ++i)
			RM = (R*RM)%Q;
		patHash = hash(pat, M);
	}
	long long hash(std::string& key, int M)
	{
		long long h = 0;
		for (int i = 0; i < M; ++i)
			h = (R*h + key[i])%Q;
		return h;
	}
	int search(std::string txt)
	{
		int N = txt.size();
		long long txtHash = hash(txt, N);
		if (patHash == txtHash)
			return 0;
		for (int i = M; i < N; ++i)
		{
			txtHash = (txtHash + Q - RM*txt[i - M] % Q) % Q;
			txtHash = (txtHash*R + txt[i]) % Q;
			if (patHash == txtHash)
				return i - M + 1;
		}
		return N;
	}
};