#pragma once
#include<iostream>
#include<cstring>
/*
sort
string
vector
array
binarysearchtree
graph
Matrix
*/
namespace sort
{
	template<typename Ty>
	void InsertSort(Ty& array)//插入排序
	{
		int sel = 0;
		int temp = 0;
		for (int cur = 1; cur < array.size(); ++cur)
		{
			if (array[cur - 1] > array[cur])
			{
				temp = array[cur];				//缓存
				sel = cur - 1;
				while (sel > -1 && array[sel] > temp)
				{
					array[sel + 1] = array[sel];
					--sel;
				}
				array[sel + 1] = temp;
			}
		}
	}

	template<typename Ty>
	void BubbleSort(Ty& array) //冒泡排序
	{
		unsigned int cur = 0;
		int temp = 0;
		for (int i = 1; (cur + i) < array.size(); ++i)
		{
			for (; (cur + 1) < array.size(); ++cur)
			{
				if (array[cur] > array[cur + 1])
				{
					temp = array[cur];
					array[cur] = array[cur + 1];
					array[cur + 1] = temp;
				}
			}
			cur = 0;
		}
	}

	template<typename Ty>
	void ShellSort(Ty& array)
	{
		unsigned int cur = 0;
		int sel = 0;
		int temp = 0;
		for (size_t gap = array.size() / 2; gap > 0; gap /= 2)
		{
			cur = 0;
			for (; (cur + gap) < array.size(); cur += gap)//插入排序
			{
				if (array[cur] > array[cur + gap])
				{
					temp = array[cur + gap];
					array[cur + gap] = array[cur];
					sel = cur - gap;
					while (sel > -1 && temp < array[sel])
					{
						array[sel + gap] = array[sel];
						sel -= gap;
					}
					array[sel + gap] = temp;
				}
			}
		}
	}
};

namespace eh {
	//——————————————————
	//      字符串
	//——————————————————
	class string
	{
	private:
		char* m_buffer;
		size_t m_size;
		string(const int& size);
	public:
		string(const char* string);//constructor
		~string();
		string(const string& other); //copyconstructor
		string& operator=(const string& other);
		string(string&& other) noexcept; //move
		string& operator=(string&& other);

		char& operator[](unsigned const int index);
		const char& operator[](unsigned const int index) const;
		string operator+(const string& other);

		friend std::ostream& operator<<(std::ostream& stream, const string& str);
	};
	std::ostream& operator<<(std::ostream& stream, const string& str); //<<运算符重载

	string::string(const int& size)
	{
		m_size = size;
		m_buffer = new char[m_size + 1];
		memset(m_buffer, '0', m_size);
		m_buffer[m_size] = '\0';
	}

	string::string(const char* string)
	{
		m_size = strlen(string);
		m_buffer = new char[m_size + 1];//终止符
		memcpy(m_buffer, string, m_size);
		m_buffer[m_size] = '\0';
	}

	string::~string()
	{
		delete[] m_buffer;
	}

	string::string(const string& other)
		:m_size(other.m_size)
	{
		m_buffer = new char[m_size + 1];
		memcpy(m_buffer, other.m_buffer, m_size + 1);
	}

	string& string::operator=(const string& other)
	{
		if (this == &other)
			return *this;
		char* newstring = new char[other.m_size + 1];
		memcpy(newstring, other.m_buffer, m_size + 1);
		delete[] m_buffer;
		m_size = other.m_size;
		m_buffer = newstring;
	}

	string::string(string&& other) noexcept
		:m_size(other.m_size), m_buffer(other.m_buffer)
	{
		other.m_buffer = nullptr;//置空
	}

	string& string::operator=(string&& other)
	{
		if (this == &other)
			return *this;
		delete[] m_buffer;
		m_buffer = other.m_buffer;
		m_size = other.m_size;
		other.m_buffer = nullptr;
		other.m_size = 0;
	}

	char& string::operator[](unsigned const int index)
	{
		return m_buffer[index];
	}
	const char& string::operator[](unsigned const int index) const
	{
		return m_buffer[index];
	}

	string string::operator+(const string& other)
	{
		string result(m_size + other.m_size);
		memcpy(result.m_buffer, m_buffer, m_size);//第一段复制
		memcpy(result.m_buffer + m_size, other.m_buffer, other.m_size);//第二段复制
		return result;
	}

	std::ostream& operator<<(std::ostream& stream, const string& str)
	{
		stream << str.m_buffer;
		return stream;
	}
	//——————————————————
	//    动态数组
	//——————————————————

	template<typename T, typename compare = std::less<T>>
	class vector
	{
	private:
		T* m_data;
		size_t m_capacity;
		size_t m_size;
	public:
		vector();
		vector(size_t capacity);
		~vector();
		vector(const vector& other);
		vector& operator=(const vector& other);
		vector(vector&& other);
		vector& operator=(vector&& other);

		void push_back(const T& buffer);
		void reserve(size_t size);
		void remove(size_t index);
		void insert(size_t index, const T& buffer);

		size_t size() { return m_size; }
		size_t capacity() { return m_capacity; }

		//void sort(compare com = compare())
	};

	template<typename T, typename compare>
	inline vector<T, compare>::vector()
		:m_data(nullptr), m_capacity(0), m_size(0)
	{}

	template<typename T, typename compare>
	inline vector<T, compare>::vector(size_t capacity)
		: m_capacity(capacity), m_size(0)
	{
		reserve(capacity);
	}

	template<typename T, typename compare>
	inline vector<T, compare>::~vector()
	{
		delete[] m_data;
	}

	template<typename T, typename compare>
	inline vector<T, compare>::vector(const vector& other)
		:m_capacity(other.m_capacity), m_size(other.m_size)
	{
		m_data = new T[m_capacity];
		for (int i = 0; i < m_size; ++i)
		{
			m_data[i] = other.m_data[i];
		}
	}

	template<typename T, typename compare>
	inline vector<T, compare>& vector<T, compare>::operator=(const vector& other)
	{
		if (this == &other)
			return *this;
		delete[] m_data;
		m_capacity = other.m_capacity;
		m_size = other.m_size;
		m_data = new T[m_capacity];
		for (int i = 0; i < m_size; ++i)
		{
			m_data[i] = other.m_data[i];
		}
		return *this;
	}

	template<typename T, typename compare>
	inline vector<T, compare>::vector(vector&& other)
		:m_capacity(other.m_capacity), m_size(other.m_size)
	{
		m_data = other.m_data;
		other.m_data = nullptr;
		other.m_capacity = 0;
		other.m_size = 0;
	}

	template<typename T, typename compare>
	inline vector<T, compare>& vector<T, compare>::operator=(vector&& other)
	{
		if (this == &other)
			return *this;
		delete[] m_data;
		m_data = other.m_data;
		m_capacity = other.m_capacity;
		m_size = other.m_size;
		other.m_data = nullptr;
		other.m_capacity = 0;
		other.m_size = 0;
		return *this;
	}

	template<typename T, typename compare>
	inline void vector<T, compare>::push_back(const T& buffer)
	{
		if (m_size == m_capacity)
		{
			reserve(m_capacity + 1);
			m_data[m_size] = buffer;
			++m_size;
		}
		else
		{
			m_data[m_size] = buffer;
			++m_size;
		}
	}

	template<typename T, typename compare>
	inline void vector<T, compare>::reserve(size_t size)
	{
		if (!m_data)
		{
			m_data = new T[size];
		}
		else
		{
			T* new_data = new T[size];
			for (int i = 0; i < m_size; ++i)
			{
				new_data[i] = m_data[i];
			}
			delete[] m_data;
			m_data = new_data;
		}
		m_capacity = size;
	}

	template<typename T, typename compare>
	inline void vector<T, compare>::remove(size_t index)
	{
		for (int i = index; i < m_size - 1; ++i)
		{
			m_data[i] = m_data[i + 1];
		}
		m_data[m_size - 1].~T();
		--m_size;
	}

	template<typename T, typename compare>
	inline void vector<T, compare>::insert(size_t index, const T& buffer)
	{
		if (m_capacity == m_size)
		{
			reserve(m_capacity + 1);
			for (int i = m_size; i > index; --i)
			{
				m_data[i] = m_data[i - 1];
			}
			m_data[index] = buffer;
			++m_size;
		}
		else
		{
			for (int i = m_size; i > index; --i)
			{
				m_data[i] = m_data[i - 1];
			}
			m_data[index] = buffer;
			++m_size;
		}
	}

	//——————————————————
	//    静态数组
	//——————————————————
	template<typename Type, size_t m_size>
	class array
	{
	private:
		Type* head_ptr;
	public:
		array();
		~array();
		array(const array& other) = delete;  //copyconstructor

		size_t size() const;
		Type& operator[](unsigned const int& index);

		//排序(希尔排序)
		void sort();
	};

	template<typename Type, size_t m_size>
	array<Type, m_size>::array()
	{
		head_ptr = new Type[m_size];
	}

	template<typename Type, size_t m_size>
	array<Type, m_size>::~array() { delete[] head_ptr; }

	template<typename Type, size_t m_size>
	size_t array<Type, m_size>::size() const
	{
		return m_size;
	}

	template<typename Type, size_t m_size>
	Type& array<Type, m_size>::operator[](unsigned const int& index)
	{
		return head_ptr[index];
	}

	template<typename Type, size_t m_size>
	void array<Type, m_size>::sort()
	{
		unsigned int cur = 0;
		int sel = 0;
		int temp = 0;
		for (size_t gap = m_size / 2; gap > 0; gap /= 2)
		{
			cur = 0;
			for (; (cur + gap) < m_size; cur += gap)//插入排序
			{
				if (head_ptr[cur] > head_ptr[cur + gap])
				{
					temp = head_ptr[cur + gap];
					head_ptr[cur + gap] = head_ptr[cur];
					sel = cur - gap;
					while (sel > -1 && temp < head_ptr[sel])
					{
						head_ptr[sel + gap] = head_ptr[sel];
						sel -= gap;
					}
					head_ptr[sel + gap] = temp;
				}
			}
		}
	}
	//——————————————————
	//      单链表
	//——————————————————
	template<typename T>
	class list
	{
	public:
		list();
		~list();

		list(const list& other);
		list& operator=(const list& other);
		list(list&& other);
		list* operator=(list&& other);

		T& operator[](int index);

		//插入
		void prepend(const T& buffer);
		void append(const T& buffer);
		void insert(int index, const T& buffer);
		void remove(int index);
		void clear();
		size_t size() const;

	private:
		struct Node
		{
			Node(const T& buffer)
				:m_buffer(buffer), next(nullptr)
			{}
			~Node()
			{}
			T m_buffer;
			Node* next;
		};
		size_t m_size;
		Node* head_ptr;
		Node* tail_ptr;
	};

	template<typename T>
	list<T>::list()
		:head_ptr(nullptr), tail_ptr(nullptr), m_size(0)
	{
		head_ptr = new Node(0);
		tail_ptr = head_ptr;
	}

	template<typename T>
	list<T>::~list()
	{
		Node* del_ptr = head_ptr;
		while (head_ptr != nullptr)
		{
			head_ptr = head_ptr->next;
			free(del_ptr);
			del_ptr = head_ptr;
		}
	}

	template<typename T>
	T& list<T>::operator[](int index)
	{
#ifdef P_DEBUG
		if (index >= m_size)
			throw std::invalid_argument("索引超出list大小");
#endif
		Node* ptr = head_ptr;
		for (int i = -1; i < index; ++i)
		{
			ptr = ptr->next;
		}
		return ptr->m_buffer;
	}

	template<typename T>
	void list<T>::prepend(const T& buffer)
	{
		Node* new_ptr = new Node(buffer);
		new_ptr->next = head_ptr;
		head_ptr = new_ptr;
		++m_size;
	}

	template<typename T>
	void list<T>::append(const T& buffer)
	{
		Node* new_ptr = new Node(buffer);
		tail_ptr->next = new_ptr;
		tail_ptr = new_ptr;
		++m_size;
	}

	template<typename T>
	void list<T>::insert(int index, const T& buffer)
	{
#ifdef P_DEBUG
		if (index >= m_size)
			throw std::invalid_argument("索引超出list大小");
#endif
		Node* ptr = head_ptr;
		for (int i = 0; i < index; ++i)
		{
			ptr = ptr->next;
		}
		Node* new_ptr = new Node(buffer);
		new_ptr->next = ptr->next;
		ptr->next = new_ptr;
		++m_size;
	}

	template<typename T>
	void list<T>::remove(int index)
	{
#ifdef P_DEBUG
		if (index >= m_size)
			throw std::invalid_argument("索引超出list大小");
#endif
		Node* last_ptr = head_ptr;
		for (int i = 0; i < index; ++i)
		{
			last_ptr = last_ptr->next;
		}
		Node* del_ptr = last_ptr->next;
		last_ptr->next = del_ptr->next;
		delete del_ptr;
		--m_size;
	}

	template<typename T>
	size_t list<T>::size() const
	{
		return m_size;
	}
	//——————————————————
	//      二叉树
	//——————————————————
	template<typename T, typename Compare = std::less<T>>
	class BinarySearchTree
	{
	private:
		struct Node
		{
			Node(const T& m_buffer)
				:lchild(nullptr), rchild(nullptr)
			{
				data = m_buffer;
			}
			T data;
			Node* lchild;
			Node* rchild;
		};

		Node* root;
		Compare less;

		Node* add(Node* node, const T& buffer)//用于递归
		{
			if (node == nullptr)
				return new Node(buffer);
			if (less(buffer, node->data)) //向左
				node->lchild = add(node->lchild, buffer);
			else                          //向右
				node->rchild = add(node->rchild, buffer);
			return node
		}
		Node* remove(Node* node, const T& buffer)
		{
			if (node == nullptr)//未找到
				return nullptr;
			if (less(buffer, node->data))
				node->lchild = remove(node->lchild, buffer);
			else if (less(node->data, buffer))
				node->rchild = remove(node->rchild, buffer);
			else
			{
				//找到了
				if (node->rchild == nullptr)//无右子树
				{
					Node* l = node->lchild;
					delete node;
					return l;
				}
				else if (node->lchild == nullptr)//无左子树
				{
					Node* r = node->rchild;
					delete node;
					return r;
				}
				else//双子树
				{
					Node* min = searchMin(node->rchild);
					node->data = min->data;
					//递归删除最小右子树节点
					node->rchild = remove(node->rchild, min->data);
				}
			}
			return node
		}
		void clear(Node* node)//递归删除
		{
			if (!node)
				return;
			clear(node->lchild);
			clear(node->rchild);
			delete node;
			root = nullptr;
		}
	public:
		BinarySearchTree(Compare compare = Compare());
		~BinarySearchTree();

		//BinarySearchTree(const BinarySearchTree& other);
		//BinarySearchTree& operator=(const BinarySearchTree& other);
		BinarySearchTree(BinarySearchTree&& other);
		BinarySearchTree& operator=(BinarySearchTree&& other);

		void add(const T& buffer) { add(root, buffer); }
		Node* remove(const T& buffer) { remove(root, buffer); }
		Node* searchMin(Node* node)
		{
			while (node->lchild)
				node = node->lchild;
			return node;
		}
		Node* searchMax(Node* node)
		{
			while (node->rchild)
				node = node->rchild;
			return node;
		}
		Node* DFS(Node* node, const T& target)
		{
			if (node->data == target)
				return node;
			if (node->lchild)
				return DFS(node->lchild, target);
			else if (node->rchild)
				return DFS(node->rchild, target);
			else
				return nullptr;
		}
		Node* BFS(Node* node, const T& target)
		{

		}
		void clear() { clear(root); }
	};

	template<typename T, typename Compare>
	inline BinarySearchTree<T, Compare>::BinarySearchTree(Compare compare)
		: less(compare), root(nullptr)
	{}

	template<typename T, typename Compare>
	inline BinarySearchTree<T, Compare>::~BinarySearchTree()
	{
		clear();
	}

	template<typename T, typename Compare>
	inline BinarySearchTree<T, Compare>::BinarySearchTree(BinarySearchTree&& other)
	{
		root = other->root;
		other->root = nullptr;
	}
	template<typename T, typename Compare>
	inline BinarySearchTree<T, Compare>& BinarySearchTree<T, Compare>::operator=(BinarySearchTree&& other)
	{
		if (this == &other)
			return *this;
		root = other->root;
		other->root = nullptr;
		return *this;
	}

	//——————————————————
	//       图
	//——————————————————
	class graph
	{
	private:
	public:
	};


	//——————————————————
	//      矩阵
	//——————————————————
	class Matrix

	{
	private:
		size_t m_row;
		size_t m_col;
		int* m_matrix;
	public:
		Matrix(const size_t& row, const size_t& col);
		~Matrix();
		//重载（）运算符
		int& operator()(size_t row, size_t col);
		const int& operator()(size_t row, size_t col) const;
		//深拷贝
		Matrix(const Matrix& other); //deep copy
		Matrix& operator=(const Matrix& other);
		Matrix(Matrix&& other); //move
		Matrix& operator=(Matrix&& other);

		//矩阵加法
		Matrix operator+(const Matrix& other) const;
		//矩阵减法
		Matrix operator-(const Matrix& other) const;
		//矩阵乘法
		Matrix operator*(const Matrix& other) const;
		//转置
		Matrix Transform();
		//打印矩阵
		void Print();
		size_t getRow() { return m_row; }
		size_t getCol() { return m_col; }
	};

	Matrix::Matrix(const size_t& row, const size_t& col)
		:m_row(row), m_col(col)
	{
		m_matrix = new int[m_row * m_col];
		memset(m_matrix, 0, row * col * sizeof(int)); //初始化内存
	}

	Matrix::~Matrix()
	{
		delete[] m_matrix;
	}

	int& Matrix::operator()(size_t row, size_t col)
	{
#ifdef P_DEBUG
		if (row >= m_row || col >= m_col)
			throw std::invalid_argument("索引超出数组大小");
#endif
		return m_matrix[m_col * row + col];
	}

	const int& Matrix::operator()(size_t row, size_t col) const
	{
#ifdef P_DEBUG
		if (row >= m_row || col >= m_col)
			throw std::invalid_argument("索引超出数组大小");
#endif
		return m_matrix[m_col * row + col];
	}

	Matrix::Matrix(const Matrix& other)
		:m_row(other.m_row), m_col(other.m_col)
	{
		m_matrix = new int[m_row * m_col];
		memcpy(m_matrix, other.m_matrix, m_row * m_col * sizeof(int));
	}

	Matrix& Matrix::operator=(const Matrix& other)
	{
		if (this == &other) //自赋值
			return *this;

		int* newMatrix = new int[other.m_row * other.m_col];
		memcpy(m_matrix, other.m_matrix, other.m_row * other.m_col * sizeof(int));
		delete[] m_matrix;

		m_matrix = newMatrix;
		m_row = other.m_row;
		m_col = other.m_col;
		return *this;
	}

	Matrix::Matrix(Matrix&& other)
		:m_row(other.m_row), m_col(other.m_col)
	{
		m_matrix = other.m_matrix;
		other.m_matrix = nullptr;
	}

	Matrix& Matrix::operator=(Matrix&& other)
	{
		if (this == &other) //自赋值
			return *this;

		delete[] m_matrix;
		m_matrix = other.m_matrix;
		other.m_matrix = nullptr;
		m_row = other.m_row;
		m_col = other.m_col;
		other.m_row = 0;
		other.m_col = 0;
		return *this;
	}

	Matrix Matrix::operator+(const Matrix& other) const
	{
#ifdef P_DEBUG
		if (m_row != other.m_row || m_col != other.m_col)
			throw std::invalid_argument("矩阵维度不匹配，无法相加");
#endif
		Matrix m(m_row, m_col);
		for (int i = 0; i < m_row; ++i)
		{
			for (int j = 0; j < m_col; ++j)
			{
				m(i, j) = (*this)(i, j) + other(i, j);
			}
		}
		return m;
	}

	Matrix Matrix::operator-(const Matrix& other) const
	{
#ifdef P_DEBUG
		if (m_row != other.m_row || m_col != other.m_col)
			throw std::invalid_argument("矩阵维度不匹配，无法相减");
#endif
		Matrix m(m_row, m_col);
		for (int i = 0; i < m_row; ++i)
		{
			for (int j = 0; j < m_col; ++j)
			{
				m(i, j) = (*this)(i, j) - other(i, j);
			}
		}
		return m;
	}

	Matrix Matrix::operator*(const Matrix& other) const
	{
#ifdef P_DEBUG
		if (m_col != other.m_row)
			throw std::invalid_argument("矩阵无法相乘");
#endif
		Matrix m(m_row, other.m_col);
		for (int i = 0; i < m_row; ++i)//row
		{
			for (int j = 0; j < other.m_col; ++j)//col
			{
				m(i, j) = 0;
				for (int x = 0; x < m_col; ++x)
				{
					m(i, j) += (*this)(i, x) * other(x, j);
				}
			}
		}
		return m;
	}

	Matrix Matrix::Transform()
	{
		Matrix m(m_col, m_row);
		for (int i = 0; i < m_row; ++i)//行
		{
			for (int j = 0; j < m_col; ++j)//列
			{
				m(j, i) = (*this)(i, j);
			}
		}
		return m;
	}

	void Matrix::Print()
	{
		for (int i = 0; i < m_row; ++i)//行
		{
			for (int j = 0; j < m_col; ++j)//列
			{
				std::cout << (*this)(i, j);
			}
			std::cout << '\n';
		}
	}
}