#pragma once
#include<iostream>
/*
sort
String
array
Vector
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

	class string
	{
	private:
		char* m_buffer;
		size_t m_size;
	public:
		string(const char* string);//constructor
		~string();
		string(const string& other); //copyconstructor

		char& operator[](unsigned const int index);

		friend std::ostream& operator<<(std::ostream& stream, const string& str);
	};
	std::ostream& operator<<(std::ostream& stream, const string& str); //<<运算符重载

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


	char& string::operator[](unsigned const int index)
	{
		return m_buffer[index];
	}

	std::ostream& operator<<(std::ostream& stream, const string& str)
	{
		stream << str.m_buffer;
		return stream;
	}


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

	template<typename T>
	class list
	{
	public:
		list();
		~list();

		T& operator[](int index);
		//插入
		void prepend(const T& buffer);
		void append(const T& buffer);
		void insert(int index, const T& buffer);
		void remove(int index);
		void clear();
		size_t size() const;

	private:
		class Node
		{
		public:
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
	inline void list<T>::prepend(const T& buffer)
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
		free(del_ptr);
		--m_size;
	}

	template<typename T>
	inline size_t list<T>::size() const
	{
		return m_size;
	}

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
		int& operator()(unsigned const int& row, unsigned const int& col) const;
		//深拷贝
		Matrix(const Matrix& other) = delete;

		//矩阵加法
		Matrix* operator+(const Matrix& other);
		//矩阵减法
		Matrix* operator-(const Matrix& other);
		//矩阵乘法
		Matrix* operator*(const Matrix& other);
		//转置
		Matrix* Transform();
		//打印矩阵
		void Print();
	};

	Matrix::Matrix(const size_t& row, const size_t& col)
		:m_row(row), m_col(col)
	{
		m_matrix = new int[m_row * m_col];
	}

	Matrix::~Matrix()
	{
		delete[] m_matrix;
	}

	int& Matrix::operator()(unsigned const int& row, unsigned const int& col) const
	{
#ifdef P_DEBUG
		if (row >= m_row || col >= m_col)
			throw std::invalid_argument("索引超出数组大小");
#endif
		return m_matrix[m_col * row + col];
	}

	Matrix* Matrix::operator+(const Matrix& other)
	{
#ifdef P_DEBUG
		if (m_row != other.m_row || m_col != other.m_col)
			throw std::invalid_argument("矩阵维度不匹配，无法相加");
#endif
		Matrix* m = new Matrix(m_row, m_col);
		for (int i = 0; i < m_row; ++i)
		{
			for (int j = 0; j < m_col; ++j)
			{
				(*m)(i, j) = (*this)(i, j) + other(i, j);
			}
		}
		return m;
	}

	Matrix* Matrix::operator-(const Matrix& other)
	{
#ifdef P_DEBUG
		if (m_row != other.m_row || m_col != other.m_col)
			throw std::invalid_argument("矩阵维度不匹配，无法相减");
#endif
		Matrix* m = new Matrix(m_row, m_col);
		for (int i = 0; i < m_row; ++i)
		{
			for (int j = 0; j < m_col; ++j)
			{
				(*m)(i, j) = (*this)(i, j) - other(i, j);
			}
		}
		return m;
	}

	Matrix* Matrix::operator*(const Matrix& other)
	{
#ifdef P_DEBUG
		if (m_col != other.m_row)
			throw std::invalid_argument("矩阵无法相乘");
#endif
		Matrix* m = new Matrix(m_row, other.m_col);
		for (int i = 0; i < m_row; ++i)//row
		{
			for (int j = 0; j < other.m_col; ++j)//col
			{
				(*m)(i, j) = 0;
				for (int x = 0; x < m_col; ++x)
				{
					(*m)(i, j) += (*this)(i, x) * other(x, j);
				}
			}
		}
		return m;
	}

	Matrix* Matrix::Transform()
	{
		Matrix* m = new Matrix(m_col, m_row);
		for (int i = 0; i < m_col; ++i)
		{
			for (int j = 0; j < m_col; ++j)
			{
				(*m)(j, i) = (*this)(i, j);
			}
		}
		return m;
	}

}