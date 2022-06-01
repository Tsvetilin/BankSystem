#pragma once
#define DEFAULT_CAPACITY 10
#define RESIZE_FACTOR 2

template <typename T>
class List {
	T* data;
	size_t capacity;
	size_t count;

	void copyFrom(const List& other);
	void free();

public:
	List();
	List(size_t);
	List(const List& other);
	List& operator= (const List& other);
	~List();

	List(List&& other);
	List& operator= (List&& other);

	void clear();
	bool contains(const T& element) const;

	template<typename K>
	int getIndexByPredicate(bool predicate(const T&, const K&), const K& value) const;

	void add(const T& element);
	void remove(const T& element);
	void removeAt(size_t index);
	T& at(size_t ind) const;

	size_t getCount()const {
		return count;
	}

	T& operator[](size_t index)const {
		return at(index);
	}

};

template <typename T>
void List<T>::clear() {
	count = 0;
}

template <typename T>
void List<T>::copyFrom(const List& other) {
	count = other.count;
	capacity = other.capacity;
	data = new T[capacity];
	for (size_t i = 0; i < count; i++)
	{
		data[i] = other.data[i];
	}
}

template <typename T>
void List<T>::free() {
	delete[] data;
}

template <typename T>
List<T>::List() {
	count = 0;
	capacity = DEFAULT_CAPACITY;
	data = new T[capacity];
}

template <typename T>
List<T>::List(size_t capacity) {
	count = 0;
	this->capacity = capacity;
	data = new T[this->capacity];
}

template <typename T>
List<T>::List(const List& other) {
	copyFrom(other);
}

template <typename T>
List<T>& List<T>::operator= (const List<T>& other) {
	if (this != &other) {
		copyFrom(other);
		free();
	}

	return *this;
}

template <typename T>
List<T>::~List() {
	free();
}

template <typename T>
T& List<T>::at(size_t ind) const {
	if (ind >= count) {
		throw std::invalid_argument("Index out of range exception.");
	}

	return data[ind];
}

template <typename T>
void List<T>::add(const T& element) {
	if (capacity == count) {
		capacity *= RESIZE_FACTOR;
		T* newArr = new T[capacity];
		for (size_t i = 0; i < count; i++)
		{
			newArr[i] = data[i];
		}
		delete[] data;
		data = newArr;
	}

	data[count++] = element;
}


template <typename T>
void List<T>::remove(const T& element) {
	for (size_t i = 0; i < count; i++)
	{
		if (data[i] == element) {
			removeAt(i);
			return;
		}
	}
}

template <typename T>
void List<T>::removeAt(size_t index) {
	if (index >= count) {
		return;
	}

	--count;

	if (count * RESIZE_FACTOR * RESIZE_FACTOR <= capacity) {
		capacity /= RESIZE_FACTOR;
		T* newData = new T[capacity];

		for (size_t i = 0; i < index; i++)
		{
			newData[i] = data[i];
		}

		for (size_t i = index; i < count; i++)
		{
			newData[i] = data[i + 1];
		}

		delete[] data;
		data = newData;
		return;
	}

	for (size_t i = index; i < count; i++)
	{
		data[index] = data[index + 1];
	}
}

template <typename T>
bool List<T>::contains(const T& element)const {
	for (size_t i = 0; i < count; i++)
	{
		if (data[i] == element) {
			return true;
		}
	}

	return false;
}

template <typename T>
template<typename K>
int List<T>::getIndexByPredicate(bool predicate(const T&, const K&), const K& value) const {
	for (size_t i = 0; i < count; i++)
	{
		if (predicate(data[i], value)) {
			return i;
		}
	}

	return -1;
}

template <typename T>
List<T>::List(List&& other) {
	data = other.data;
	count = other.count;
	capacity = other.capacity;
	other.data = nullptr;
}

template <typename T>
List<T>& List<T>::operator= (List&& other) {
	delete[] data;
	data = other.data;
	count = other.count;
	capacity = other.capacity;
	other.data = nullptr;

	return *this;
}