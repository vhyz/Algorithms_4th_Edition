#include<memory>
#include<iostream>
template<typename T>
class Vector
{
	template<typename T>
	friend std::ostream& operator<<(std::ostream&os, Vector<T>& vec);
private:
	std::allocator<T>alloc;
	void chk_n_alloc();
	std::pair<T*, T*>alloc_n_copy(const T*b, const T*e);
	void free();
	int partition(int& lo, int& hi);
	void sort(int lo, int hi);
	void swap(T &Valve1, T &Valve2);
	Vector& operator=(const Vector& vec);
	Vector& operator=(std::initializer_list<T> l);
	T& operator[](size_t i);
	void realocate();//获得更多内存并拷贝元素
	T* elements;//相当于begin()
	T* first_free;// 指向数组第一个空间元素的指针
	T* cap;//指向尾后位置指针
public:
	void sort();
	Vector() :
		elements(nullptr), first_free(nullptr), cap(nullptr) {}
	Vector(T*b, T*e) :
		elements(nullptr), first_free(nullptr), cap(nullptr){}
	Vector(int i, T s = T()) :
		elements(nullptr), first_free(nullptr), cap(nullptr)
	{
		auto p = alloc.allocate(i+3);
		elements = p;
		for (int j = 0; j < i;++j)
			alloc.construct(p++, s);
		first_free = p;
		cap = elements + i + 3;
	}
	Vector(std::initializer_list<T> l);
	Vector(const Vector& vec);
	~Vector();
	void push_back(const T& s);
	void push_back(const T&& s);
	size_t size()const { return first_free - elements; }
	size_t capacity()const { return cap - elements; }
	T* begin() const{ return elements; }
	T* end()const { return first_free; }
};
template<typename T>
void Vector<T>::chk_n_alloc()
{
	if (size() == capacity())
		realocate();
}
template<typename T>
inline std::pair<T*, T*> Vector<T>::alloc_n_copy(const T * b, const T * e)
{
	auto data = alloc.allocate(e - b);
	return std::pair<T*, T*>{ data, std::uninitialized_copy(b, e, data) };
}
template<typename T>
void Vector<T>::push_back(const T & s)
{
	chk_n_alloc();
	alloc.construct(first_free++, s);
}

template<typename T>
void Vector<T>::free()
{
	if (elements)
	{
		for (auto i = first_free; i != elements;)
			alloc.destroy(--i);
		alloc.deallocate(elements, cap - elements);
	}
}
template<typename T>
void Vector<T>::realocate()
{
	auto newcap = size() ? 2 * size() : 1;
	auto newdata = alloc.allocate(newcap);
	auto dest = newdata;
	auto elem = elements;
	for (size_t i = 0; i != size(); i++)
		alloc.construct(dest++, std::move(*elem++));
	free();
	elements = newdata;
	first_free = dest;
	cap = elements + newcap;
}
template<typename T>
void Vector<T>::sort()
{
	sort(0, size() - 1);
}
template<typename T>
inline Vector<T>::Vector(std::initializer_list<T> l)
{
	std::pair<T*, T*>data = alloc_n_copy(l.begin(), l.end());
	elements = data.first;
	cap = first_free = data.second;
}
template<typename T>
Vector<T>::Vector(const Vector & vec)
{
	std::pair<T*, T*> data = alloc_n_copy(vec.begin(), vec.end());
	elements = data.first;
	cap = first_free = data.second;
}
template<typename T>
Vector<T>::~Vector()
{
	free();
}
template<typename T>
Vector<T> & Vector<T>::operator=(const Vector & vec)
{
	std::pair<T*, T*> data = alloc_n_copy(vec.begin(), vec.end());
	free();//防止自赋值引起错误
	elements = data.first;
	cap = first_free = data.second;
	return *this;
}
template<typename T>
inline T & Vector<T>::operator[](size_t i)
{
	return elements[i];
}
template<typename T>
inline void Vector<T>::push_back(const T && s)
{
	chk_n_alloc();
	alloc.construct(first_free++, std::move(s));
}
template<typename T>
inline Vector<T> & Vector<T>::operator=(std::initializer_list<T> l)
{
	std::pair<T*,T*> data = alloc_n_copy(l.begin(), l.end());
	free();
	elements = data.first;
	cap = first_free = data.second;
	return *this;
}
template<typename T>
std::ostream & operator<<(std::ostream & os, Vector<T>& vec)
{
	for (size_t i = 0; i < vec.size(); ++i)
		os << vec[i] << " ";
	os << std::endl;
	return os;
}
template<typename T>
int Vector<T>::partition(int & lo, int & hi)
{
	int i = lo, j = hi + 1;
	T v = elements[lo];
	while (true)
	{
		while (elements[++i] < v)
			if (i == hi)
				break;
		while (elements[--j] > v)
			if (j == lo)
				break;
		if (i >= j)
			break;
		swap(elements[i], elements[j]);
	}
	swap(elements[lo], elements[j]);
	return j;
}
template<typename T>
void Vector<T>::swap(T& Valve1, T &Valve2)
{
	T temp = Valve1;
	Valve1 = Valve2;
	Valve2 = temp;
}
template<typename T>
void Vector<T>::sort(int lo, int hi)
{
	if (lo >= hi)
		return;
	int j = partition(lo, hi);
	sort(lo, j - 1);
	sort(j + 1, hi);
}