#include <iostream>
#include <initializer_list>
#include <exception>
#include <vector>

template<typename T>
class MyVector
{
public:
	MyVector()
	{
		_capacity = 0;
		_size = 0;
		_vector = nullptr;
	};

	explicit MyVector(int size)
	{
		if (size > 0)
		{
			_capacity = size;
			_size = 0;
			_vector = new T[size];
		}
		else
		{
			_capacity = 0;
			_size = 0;
			_vector = nullptr;
		}
	};

	MyVector(std::initializer_list<T> list) : MyVector(list.size())//инициализация вектора списком
	{
		int count = 0;
		for (const T &element : list)
		{
			_vector[count++] = element;
		}
		_size = _capacity;
	};

	MyVector(T *arr, const int size) : MyVector(size)//инициализация вектора массивом
	{
		_size = size;
		_capacity = size;
		for (int i = 0; i < _size; ++i)
		{
			_vector[i] = arr[i];
		}
	};

	MyVector(const MyVector &other)//конструктор копирования
	{
		_capacity = other._capacity;
		_size = other._size;
		if (other._vector != nullptr)
		{
			_vector = new T[_size];
			for (int i = 0; i < _size; ++i)
			{
				_vector[i] = other._vector[i];
			}
		}
		else
		{
			_vector = nullptr;
		}
	}
	MyVector(MyVector &&other) noexcept//конструктор перемещения
	{
		_capacity = other._capacity;
		_size = other._size;
		_vector = other._vector;
		other._vector = nullptr;
		other._size = 0;
		other._capacity = 0;
	}
	~MyVector()
	{
		if (_vector != nullptr)
		{
			delete[] _vector;
		}
	};

	MyVector &operator=(const MyVector &other)//оператора присваивания копированием
	{
		if (this != &other)
		{
			if (_vector != nullptr)
			{
				delete[] _vector;
			}
			_capacity = other._capacity;
			_size = other._size;
			if (_size > 0)
			{
				_vector = new T[_size];
				for (int i = 0; i < _size; ++i)
				{
					_vector[i] = other._vector[i];
				}
			}
		}
		return *this;
	}
	MyVector &operator=(MyVector &&other) noexcept//оператор присваивания перемещением
	{
		if (this != &other)
		{
			if (_vector != nullptr)
			{
				delete[] _vector;
			}
			_capacity = other._capacity;
			_size = other._size;
			_vector = other._vector;
			other._vector = nullptr;
			other._capacity = 0;
			other._size = 0;
		}
		return *this;
	}

	T &operator[](int index)//без проверки индекса
	{
		return _vector[index];
	};

	T at(int index)//с проверкой индекса
	{
		if (index >= 0 && index < _size)
		{
			return _vector[index];
		}
		else
		{
			throw(std::out_of_range("Попытка получить доступ к элементу с недопустимым индексом"));
		}
	};

	void clear()
	{
		if (_vector != nullptr)
		{
			delete[] _vector;
		}
		_capacity = 0;
		_size = 0;
		_vector = nullptr;
	}

	T *begin()
	{
		return _vector;
	};

	T *end()
	{
		return _vector + _size;
	};

	int getSize()
	{
		return _size;
	};

	int getCapacity()
	{
		return _capacity;
	};

	void pushFront(T value)
	{
		if (_vector == nullptr)
		{
			*this = MyVector(1);
		}
		if (_capacity > _size)
		{
			for (int i = _size; i > 0; --i)
			{
				_vector[i] = _vector[i - 1];
			}
			_vector[0] = value;
			_size++;
		}
		else
		{
			T *newVector = new T[_capacity * 2];
			for (int i = _size; i > 0; --i)
			{
				newVector[i] = _vector[i - 1];
			}
			newVector[0] = value;
			_size++;
			_capacity *= 2;
			delete[] _vector;
			_vector = newVector;
		}
	};

	void pushBack(T value)
	{
		if (_vector == nullptr)
		{
			*this = MyVector(1);
		}
		if (_capacity > _size)
		{
			_vector[_size] = value;
			_size++;
		}
		else
		{
			T *newVector = new T[_capacity * 2];
			for (int i = 0; i < _size; ++i)
			{
				newVector[i] = _vector[i];
			}
			newVector[_size] = value;
			_size++;
			_capacity *= 2;
			delete[] _vector;
			_vector = newVector;
		}
	};

	void pushElement(T value, int index)//вставка элемента по индексу со сдвигом вправо остальных элементов
	{
		if ((index > _size) || (index < 0))
		{
			throw(std::out_of_range("Попытка добавить элемент с недопустимым индексом"));
		}
		if (_vector == nullptr)
		{
			*this = MyVector(1);
		}		
		if (_capacity > _size)
		{
			for (int i = _size; i > index; --i)
			{
				_vector[i] = _vector[i - 1];
			}
			_vector[index] = value;
			_size++;
		}
		else
		{
			T *newVector = new T[_capacity * 2];
			for (int i = _size; i > 0; --i)
			{
				if (i == index)
				{
					newVector[index] = value;
					continue;
				}
				newVector[i] = _vector[i - 1];
			}
			_size++;
			_capacity *= 2;
			delete[] _vector;
			_vector = newVector;
		}
	};

	void popFront()
	{
		if (_size == 0)
		{
			throw(std::out_of_range("Попытка удалить несуществующий элемент"));
		}
		if (_size - 1 <= 0)
		{
			_size = 0;
			return;
		}
		else if (_capacity < (_size - 1) * 3)
		{
			for (int i = 0; i < _size - 1; ++i)
			{
				_vector[i] = _vector[i + 1];
			}
			_size--;
		}
		else
		{
			T *newVector = new T[_size - 1];
			for (int i = 0; i < _size - 1; ++i)
			{
				newVector[i] = _vector[i + 1];
			}
			_size--;
			_capacity = _size;
			delete[] _vector;
			_vector = newVector;
		}
	};

	void popBack()
	{
		if (_size == 0)
		{
			throw(std::out_of_range("Попытка удалить несуществующий элемент"));
		}
		if ((_size - 1) <= 0)
		{
			_size = 0;
			return;
		}
		else if (_capacity < (_size - 1) * 3)
		{
			_size--;
		}
		else
		{
			T *newVector = new T[_size - 1];
			for (int i = 0; i < _size - 1; ++i)
			{
				newVector[i] = _vector[i];
			}
			_size--;
			_capacity = _size;
			delete[] _vector;
			_vector = newVector;
		}
	};

	void popElement(int index)
	{
		if ((index >= _size) || (index < 0))
		{
			throw(std::out_of_range("Попытка удалить элемент с недопустимым индексом"));
		}
		if ((_size - 1) <= 0)
		{
			_size = 0;
			return;
		}
		else if (_capacity < (_size - 1) * 3)
		{
			for (int i = index; i < _size - 1; ++i)
			{
				_vector[i] = _vector[i + 1];
			}
			_size--;
		}
		else
		{
			T *newVector = new T[_size - 1];
			for (int i = 0; i < _size - 1; ++i)
			{
				if (i < index)
				{
					newVector[i] = _vector[i];
				}
				else if (i >= index)
				{
					newVector[i] = _vector[i + 1];
				}
			}
			_size--;
			_capacity = _size;
			delete[] _vector;
			_vector = newVector;
		}
	};

private:
	int _capacity;
	int _size;
	T *_vector;
};


template<typename T>
void printVector(MyVector<T> v)
{
	for (const auto &el : v)
	{
		std::cout << el << " ";
	}
	std::cout << std::endl;
}

int main()
{
	setlocale(LC_ALL, "RU");

	{
		std::cout << "Тест вектора с конструктором по умолчанию и выброса исключений\n";
		MyVector<int> v;
		std::cout << "v.getSize() = " << v.getSize() << std::endl;
		std::cout << "v.getCapacity() = " << v.getCapacity() << std::endl;
		
		try
		{
			std::cout << "\nv.at(0)" << std::endl;
			std::cout << v.at(0) << std::endl;
		}
		catch (const std::out_of_range &ex)
		{
			std::cout << ex.what() << std::endl;
		}

		try
		{
			std::cout << "\nv.popFront()" << std::endl;
			v.popFront();
		}
		catch (const std::out_of_range &ex)
		{
			std::cout << ex.what() << std::endl;
		}

		try
		{
			std::cout << "\nv.popBack()" << std::endl;
			v.popBack();
		}
		catch (const std::out_of_range &ex)
		{
			std::cout << ex.what() << std::endl;
		}

		try
		{
			std::cout << "\nv.pushElement(value = 5,index = 5)" << std::endl;
			v.pushElement(5,5);
		}
		catch (const std::out_of_range &ex)
		{
			std::cout << ex.what() << std::endl;
		}

		try
		{
			std::cout << "\nv.popElement(index = 5)" << std::endl;
			v.popElement(5);
		}
		catch (const std::out_of_range &ex)
		{
			std::cout << ex.what() << std::endl;
		}
	}


	std::cout << "--------------------------------------------------------------------------------\n\n";


	{
		std::cout << "Тест вектора с конструктором MyVector(size =  5) и всех методов push\n";
		MyVector<int> v(5);
		std::cout << "v.getSize() = " << v.getSize() << std::endl;
		std::cout << "v.getCapacity() = " << v.getCapacity() << std::endl;

		std::cout << "\nv.pushBack(3)" << std::endl;
		v.pushBack(3);
		std::cout << "v.getSize() = " << v.getSize() << std::endl;
		std::cout << "v.getCapacity() = " << v.getCapacity() << std::endl;
		std::cout << "vector: ";
		printVector(v);

		std::cout << "\nv.pushFront(1)" << std::endl;
		v.pushFront(1);
		std::cout << "v.getSize() = " << v.getSize() << std::endl;
		std::cout << "v.getCapacity() = " << v.getCapacity() << std::endl;
		std::cout << "vector: ";
		printVector(v);

		std::cout << "\nv.pushElement(value = 2, index = 1)" << std::endl;
		v.pushElement(2,1);
		std::cout << "v.getSize() = " << v.getSize() << std::endl;
		std::cout << "v.getCapacity() = " << v.getCapacity() << std::endl;
		std::cout << "vector: ";
		printVector(v);

		std::cout << "\nv.pushBack(7) - 5 раз, для увеличения capacity вектора" << std::endl;
		for (int i = 0; i < 5; ++i)
		{
			v.pushBack(7);
		}
		std::cout << "v.getSize() = " << v.getSize() << std::endl;
		std::cout << "v.getCapacity() = " << v.getCapacity() << std::endl;
		std::cout << "vector: ";
		printVector(v);
	}

	std::cout << "--------------------------------------------------------------------------------\n\n";

	{
		std::cout << "Тест вектора с конструктором со списком инициализации и всех методов pop\n";
		MyVector<int> v{1,2,3,4,5,6,7,8,9,10};
		std::cout << "v.getSize() = " << v.getSize() << std::endl;
		std::cout << "v.getCapacity() = " << v.getCapacity() << std::endl;
		std::cout << "vector: ";
		printVector(v);

		std::cout << "\nv.popFront()" << std::endl;
		v.popFront();
		std::cout << "v.getSize() = " << v.getSize() << std::endl;
		std::cout << "v.getCapacity() = " << v.getCapacity() << std::endl;
		std::cout << "vector: ";
		printVector(v);

		std::cout << "\nv.popBack()" << std::endl;
		v.popBack();
		std::cout << "v.getSize() = " << v.getSize() << std::endl;
		std::cout << "v.getCapacity() = " << v.getCapacity() << std::endl;
		std::cout << "vector: ";
		printVector(v);

		std::cout << "\nv.popElement(index = 1)" << std::endl;
		v.popElement(1);
		std::cout << "v.getSize() = " << v.getSize() << std::endl;
		std::cout << "v.getCapacity() = " << v.getCapacity() << std::endl;
		std::cout << "vector: ";
		printVector(v);

		std::cout << "\nv.popBack() - 4 раза, для уменьшения capacity" << std::endl;
		for (int i = 0; i < 4; ++i)
		{
			v.popBack();
		}		
		std::cout << "v.getSize() = " << v.getSize() << std::endl;
		std::cout << "v.getCapacity() = " << v.getCapacity() << std::endl;
		std::cout << "vector: ";
		printVector(v);
	}

	std::cout << "--------------------------------------------------------------------------------\n\n";

	{
		int arr[10] = { 11,12,13,14,15,16,17,18,19,20 };
		std::cout << "Тест вектора с конструктором на основе массива, operator[], at(), begin, end, clear\n";
		MyVector<int> v(arr, 10);
		std::cout << "v.getSize() = " << v.getSize() << std::endl;
		std::cout << "v.getCapacity() = " << v.getCapacity() << std::endl;
		std::cout << "vector: ";
		printVector(v);

		std::cout << "\nv.operator[index = 2] = " << v[2] << std::endl;
		std::cout << "v.at(3) = " << v.at(3) << std::endl;
		std::cout << "*v.begin() = " << *v.begin() << std::endl;
		std::cout << "*(v.end()-1) = " << *(v.end()-1) << std::endl;

		std::cout << "\nv.[0] = 99 присваивание" << std::endl;
		v[0] = 99;
		std::cout << "vector: ";
		printVector(v);

		std::cout << "\nv.clear()" << std::endl;
		v.clear();
		std::cout << "v.getSize() = " << v.getSize() << std::endl;
		std::cout << "v.getCapacity() = " << v.getCapacity() << std::endl;
	}

	std::cout << "--------------------------------------------------------------------------------\n\n";
	{
		std::cout << "Тест конструкторов копирования/перемещения и операторов присваивания копированием/перемещением\n";
		MyVector<int> v1{ 1,2,3,4,5,6,7,8,9,10 };
		MyVector<int> v2{ 11,12,13,14,15,16,17,18,19,20 };
		MyVector<int> v3;
		
		std::cout << "vector1: ";
		printVector(v1);
		std::cout << "vector2: ";
		printVector(v2);
		std::cout << "vector3: ";
		printVector(v3);
		

		std::cout << "\nПрисваивание перемещением v3 = v1 и создание v4 из v2 перемещением" << std::endl;
		v3 = std::move(v1);
		MyVector<int> v4(std::move(v2));
		std::cout << "vector1: ";
		printVector(v1);
		std::cout << "vector2: ";
		printVector(v2);
		std::cout << "vector3: ";
		printVector(v3);
		std::cout << "vector4: ";
		printVector(v4);

		std::cout << "\nПрисваивание копированием v1 = v3 и создание копированием v5 из v4" << std::endl;
		v1 = v3;
		MyVector<int> v5(v4);
		std::cout << "vector1: ";
		printVector(v1);
		std::cout << "vector2: ";
		printVector(v2);
		std::cout << "vector3: ";
		printVector(v3);
		std::cout << "vector4: ";
		printVector(v4);
		std::cout << "vector5: ";
		printVector(v5);
	}

	
}

