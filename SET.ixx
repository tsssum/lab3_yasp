module;
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <compare>
#include <regex>
#include <Windows.h>
export module SET;

export const size_t MAX{ 256 };

export template<typename T>
class Set
{
private:
	T* elems;
	size_t size;
	void valid();

public:
	Set();
	Set(const std::string& filename);
	Set(const Set& other);
	~Set();

	Set<T>& operator=(const Set& other);

	void add(const T& elem);
	void del(const T& elem);
	void circle_to_left(T* subset, size_t size);
	bool find(const T& elem) const;
	void Union(const Set& set);
	void Intersection(const Set& set);
	void Difference(const Set& set);
	void print_to_console() const;
	void print_to_file(const std::string& filename)const;

	size_t get_size() { return size; };
	T get_elem(size_t id) { return elems[id]; };
};

template<typename T>
void Set<T>::valid()
{
	T* new_elems = new T[size];

	for (size_t i{}; i < size - 1; i++)
	{
		new_elems[i] = elems[i];
	}

	delete[] elems;
	elems = new_elems;
}

template<typename T>
Set<T>::Set() : size(0)
{
	elems = new T[MAX];
}

template<typename T>
Set<T>::Set(const std::string& filename) :size(0)
{
	elems = new T[MAX];

	std::ifstream file(filename);
	if (!file)
	{
		std::cout << "\n���� �� ������!\n";
	}

	else
	{
		T value;
		if constexpr (std::is_same<T, std::string>::value)
		{
			while (!file.eof())
			{
				std::getline(file, value);
				add(value);
			}
		}
		else while (file >> value)
		{
			add(value);
		}
		file.close();
	}
}

template<typename T>
Set<T>::Set(const Set& other)
{
	elems = new T[MAX];
	for (size_t i = 0; i < size; ++i) 
	{
		elems[i] = other.elems[i];
	}
}

template<typename T>
Set<T>::~Set()
{
	delete[]elems;
}

template<typename T>
Set<T>& Set<T>::operator=(const Set& other)
{
	if (this != &other) 
	{ 

		size = other.size;
		elems = new T[MAX];

		for (size_t i = 0; i < size; ++i) {
			elems[i] = other.elems[i]; 
		}
	}
	return *this;
}

template<typename T>
void Set<T>::add(const T& elem)
{
	if (!find(elem))
	{
		size++;
		valid();
		elems[size - 1] = elem;
	}
}

template<typename T>
void Set<T>::del(const T& elem)
{
	for (size_t i{}; i < size; ++i)
	{
		if (elems[i] == elem)
		{
			if(i!= size-1)
				circle_to_left(elems + i, size - i);
			--size;
		}
	}
}

template<typename T>
void Set<T>::circle_to_left(T* subset, size_t size)
{
	T tmp = subset[0];

	for (size_t i{}; i < size; ++i)
		subset[i] = subset[i + 1];
	subset[size - 1] = tmp;

}

template<typename T>
bool Set<T>::find(const T& elem) const
{
	bool res{};
	for (size_t i{ 0 }; i < size; ++i)
		if (elems[i] == elem)
			res = 1;
	return res;
}

template<typename T>
void Set<T>::Union(const Set& set)
{
	for (size_t i = 0; i < set.size; ++i)
		add(set.elems[i]);

}

template<typename T>
void Set<T>::Intersection(const Set& set)
{
	for (size_t i{}; i < size; ++i)
	{
		if (!set.find(elems[i])) {
			del(elems[i]);
			i--;
		}
	}
}

template<typename T>
void Set<T>::Difference(const Set& set)
{
	for (size_t i{}; i < size; ++i)
	{
		if (set.find(elems[i])) {
			del(elems[i]);
			i--;
		}
	}
}

template<typename T>
void Set<T>::print_to_console() const
{
	std::cout << "{ ";
	for (int i = 0; i < size - 1; ++i)
		std::cout << elems[i] << "; ";
	std::cout << elems[size - 1];
	std::cout << " }\n";
}

template<typename T>
void Set<T>::print_to_file(const std::string& filename) const
{
	std::ofstream file(filename);

	if (!file)
	{
		std::cout << "\n���� �� ������!\n";
	}

	else
	{
		for (size_t i{}; i < size - 1; ++i)
			file << elems[i] << '; ';
		file << elems[size - 1];
	}
}