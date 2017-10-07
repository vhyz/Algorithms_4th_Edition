#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<algorithm>
using namespace std;
template<typename T>
void Sort(vector<T>&nums);
template<typename T>
void merge(vector<T>&nums, int lo, int hi, int mid);
template<typename T>
void UpToDownSort(vector<T>&nums, int lo, int hi);
template<typename T>
void InsertSort(vector<T>& nums, int lo, int hi);
template<typename T>
void CopyVector(vector<T>&Copy, vector<T>&Copied);
template<typename T>
void ShellSort(vector<T>& nums, int lo, int hi);
template<typename T>
void _Sort(vector<T>&nums);
template<typename T>
void Show(vector<T>&nums);
template<typename T>
int partition(vector<T>&nums, int lo, int hi);
template<typename T>
void QuickSort(vector<T>&nums, int lo, int hi);
template<typename T>
bool IsSort(vector<T>&nums);
template<typename T>
void QuickSort3Way(vector<T>&nums, int lo, int hi);
template<typename T>
void DuiSort(vector<T>&nums);
template<typename T>
void sink(vector<T>&nums, int k, int len);
template<typename T>
bool IsDuiSort(vector<T>&nums);
int*temp;
int main()
{
	srand((int)time(0));
	vector<int>nums1, nums2, nums3, nums4, nums, nums10,numsSTL;
	clock_t start, finish;
	for (int i = 0; i < 100000; i++)
	{
		nums1.push_back(rand());
	}
	int low = 0,high = nums1.size()-1;
	CopyVector(nums2, nums1);
	CopyVector(nums3, nums1);
	CopyVector(nums4, nums1);
	CopyVector(nums, nums1);
	CopyVector(nums10, nums1);
	CopyVector(numsSTL, nums1);
	cout << IsSort(nums1) << endl;
	cout << IsSort(nums2) << endl;
	cout << IsSort(nums3) << endl;
	cout << IsSort(nums4) << endl;
	cout << IsSort(nums) << endl;
	start = clock();
	Sort(nums1);
	finish = clock();
	cout << "自顶向下归并：" << (finish - start) << "/" << CLOCKS_PER_SEC << "s" << endl;
	delete [] temp;
	start = clock();
	QuickSort(nums2, low, high);
	finish = clock();
	cout << "快速排序：" << (finish - start) << "/" << CLOCKS_PER_SEC << "s" << endl;
	start = clock();
	ShellSort(nums3, low, high);
	finish = clock();
	cout << "希尔排序：" << (finish - start) << "/" << CLOCKS_PER_SEC << "s" << endl;
	start = clock();
	_Sort(nums4);
	finish = clock();
	cout << "自底向上归并：" << (finish - start) << "/" << CLOCKS_PER_SEC << "s"<<endl;
	delete[] temp;
	start = clock();
	QuickSort3Way(nums, low, high);
	finish = clock();
	cout << "三向快排：" << (finish - start) << "/" << CLOCKS_PER_SEC << "s" << endl;
	start = clock();
	DuiSort(nums10);
	finish = clock();
	cout << "堆排序：" << (finish - start) << "/" << CLOCKS_PER_SEC << "s" << endl;
	vector<int>nums5{ 14,53,41,74,12,1 };
	vector<int>nums6, nums7,nums8,nums9;
	CopyVector(nums6, nums5);
	CopyVector(nums7, nums5);
	CopyVector(nums8, nums5);
	CopyVector(nums9, nums5);
	_Sort(nums5);
	delete[] temp;
	Show(nums5);
	ShellSort(nums6, 0, 5);
	Show(nums6);
	Show(nums7);
	Sort(nums7);
	delete[] temp;
	QuickSort3Way(nums9, 0, 5);
	Show(nums7);
	Show(nums8);
	QuickSort(nums8, 0, 5);
	cout << IsSort(nums1) << endl;
	cout << IsSort(nums2) << endl;
	cout << IsSort(nums3) << endl;
	cout << IsSort(nums4) << endl;
	cout << IsSort(nums8) << endl;
	cout << IsSort(nums) << endl;
	cout << IsDuiSort(nums10) << endl;
	Show(nums8);
	cout << "\n\n\n";
	start = clock();
	sort(numsSTL.begin(), numsSTL.end());
	finish = clock();
	cout << "STL排序：" << finish - start << "/1000s" << endl;
	cout << IsSort(numsSTL);
	system("pause");
	return 0;
}
template<typename T>
void Sort(vector<T>&nums)
{
	temp = new int[nums.size()];
	UpToDownSort(nums, 0, nums.size() - 1);
}
template<typename T>
void merge(vector<T>&nums, int lo, int hi,int mid)
{
	int i = lo, j = mid + 1;
	for (int k = lo; k <= hi; k++)
		temp[k] = nums[k];
	for (int k = lo; k <= hi; k++)
	{
		if (i > mid)
			nums[k] = temp[j++];
		else if (j > hi)
			nums[k] = temp[i++];
		else if (temp[i] < temp[j])
			nums[k] = temp[i++];
		else
			nums[k] = temp[j++];
	}
}
template<typename T>
void UpToDownSort(vector<T>&nums, int lo, int hi)
{
	if (hi< 15)
	{
		InsertSort(nums, lo, hi);
		return;
	}
	if (hi <= lo)
		return;
	int mid = (lo + hi) / 2;
	UpToDownSort(nums, lo, mid);
	UpToDownSort(nums, mid + 1, hi);
	if(nums[mid]>nums[mid+1])
		merge(nums, lo, hi, mid);
}
template<typename T>
void InsertSort(vector<T>& nums, int lo, int hi)
{
	for (int i = lo; i <= hi; i++)
		for (int j = i; j > lo&&nums[j] < nums[j - 1]; j--)
			swap(nums[j], nums[j - 1]);
}

template<typename T>
void ShellSort(vector<T>& nums, int lo, int hi)
{
	int h = 1;
	while (h < (hi + 1) / 3)
		h = 3 * h + 1;
	while (h >= 1)
	{
		for (int i = h; i <= hi; i++)
			for (int j = i; j >= h&&nums[j - h] > nums[j]; j -= h)
				swap(nums[j - h], nums[j]);
		h /= 3;
	}
}
template<typename T>
void CopyVector(vector<T>&Copy, vector<T>&Copied)
{
	Copy.insert(Copy.end(), Copied.begin(), Copied.end());
}
template<typename T>
void _Sort(vector<T>&nums)
{
	int len = nums.size();
	temp = new int[len];
	for (int sz = 1; sz < len;sz=sz+sz)
		for (int lo = 0; lo < len - sz; lo += sz + sz)
			merge(nums, lo, lo + sz + sz - 1 > len-1 ? len-1 : lo + sz + sz - 1, lo + sz - 1);
}

template<typename T>
void Show(vector<T>&nums)
{
	for (auto i : nums)
		cout << i << "    ";
	cout << endl;
}

template<typename T>
int partition(vector<T>&nums, int lo, int hi)
{
	int i = lo, j = hi + 1;
	T v = nums[lo];
	while (true)
	{
		while (nums[++i] < v)
			if (i == hi)
				break;
		while (v < nums[--j])
			if (j == lo)
				break;
		if (i >= j)
			break;
		swap(nums[i], nums[j]);
	}
	swap(nums[j], nums[lo]);
	return j;
}

template<typename T>
void QuickSort(vector<T>&nums, int lo, int hi)
{
	if (hi <= lo+10 )
	{
		InsertSort(nums, lo, hi);
		return;
	}
	int j = partition(nums, lo,  hi);
	QuickSort(nums, lo, j-1);
	QuickSort(nums, j + 1, hi);
}

template<typename T>
bool IsSort(vector<T>&nums)
{
	for (int i = 1; i < nums.size(); i++)
	{
		if (nums[i] < nums[i - 1])
			return false;
	}
	return true;
}

template<typename T>
void QuickSort3Way(vector<T>&nums, int lo, int hi)
{
	if (hi <= lo)
		return;
	int lt = lo, i = lo + 1, gt = hi;
	T v = nums[lo];
	while (i <= gt)
	{
		if (nums[i] < v)
			swap(nums[lt++], nums[i++]);
		else if (nums[i] > v)
			swap(nums[i], nums[gt--]);
		else i++;
	}
	QuickSort3Way(nums, lo, lt - 1);
	QuickSort3Way(nums, gt + 1, hi);
}

template<typename T>
bool IsDuiSort(vector<T>&nums)
{
	for (int i = 2; i < nums.size(); i++)
	{
		if (nums[i] < nums[i - 1])
			return false;
	}
	return true;
}


template<typename T>
void DuiSort(vector<T>& nums)
{
	int len = nums.size()-1;
	for (int k = len / 2; k >= 1; k--)
		sink(nums, k, len);
	while (len > 1)
	{
		swap(nums[1], nums[len--]);
		sink(nums, 1, len);
	}
}


template<typename T>
void sink(vector<T>& nums, int k, int len)
{
	while (2 * k <= len)
	{
		int j = 2 * k;
		if (j < len&&nums[j]<nums[j+1])
			j++;
		if (nums[k]>nums[j])
			break;
		swap(nums[k], nums[j]);
		k = j;
	}
}