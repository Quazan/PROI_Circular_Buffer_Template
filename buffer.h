#include <iostream>
#include <string>
using namespace std;

template <typename T> class Buffer
{
private:
	 const int MAXSIZE = 4;	
	int siz;

	struct container
	{
		container * prev;
		container * next;

		T cont;
	};

	class iterator
	{		
	private:

		friend class Buffer<T>;
		container * wsk;

	public:

		T operator*() const
		{
			T tmp;
			tmp = wsk -> cont;
			return tmp;
		}

		iterator& operator ++(int)
		{
			iterator tmp = *this;
			wsk = wsk -> next;
			return *this;
		}

		iterator& operator ++()
		{
			wsk = wsk -> next;
			return *this;
		}

		iterator& operator = (const class Buffer<T>::iterator& right)
		{
			wsk = right.wsk;
			return *this;
		}

		bool operator == (const class Buffer<T>:: iterator& right) const
		{
			if(wsk == right.wsk)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		bool operator != (const class Buffer<T>:: iterator& right) const
		{
			if(wsk != right.wsk)
			{
				return true;
			}

			return false;
		}

		bool operator != (std::nullptr_t) const
		{
			if(wsk != NULL)
			{
				return true;
			}

			return false;
		}

		bool operator == (std::nullptr_t) const
		{
			if(wsk == NULL)
			{
				return true;
			}
			else
			{
				return false;
			}
		}


	};

	iterator first;
	iterator last;

public:

	Buffer();
	Buffer(const Buffer<T>&);
	~Buffer();
	int push(T);
	T pop();
	const T peak();
	int clear();
	const int count();

	template <class U> friend ostream& operator << (ostream& out, const Buffer<U> &);
	template <class U> friend istream& operator >> (istream& in, Buffer<U> &);
	template <class U> friend Buffer<U>& operator += (Buffer<U>&, const Buffer<U>&);
	template <class U> friend Buffer<U>& operator += (Buffer<U>&, const U&);
	template <class U> friend bool operator == ( const Buffer<U>&, const Buffer<U>&);
	template <class U> friend bool operator != ( const Buffer<U>&, const Buffer<U>&);

	iterator begin()
	{
		return first;
	}

	iterator end()
	{
		if(last.wsk == NULL) return last;

		iterator tmp;
		tmp = last;
		tmp++;

		return tmp;
	}
};


template <typename T> Buffer<T> :: Buffer()
{
	siz = 0;
	first.wsk = NULL;
	last.wsk = NULL;
}

template <typename T> Buffer<T> :: Buffer(const Buffer<T>& right)
{
	siz = 0;
	first.wsk = NULL;
	last.wsk = NULL;

	*this += right;

	siz = right.siz;
}

template <typename T> Buffer<T> :: ~Buffer()
{
	clear();
}

template <typename T> int Buffer<T> :: push(T t)
{
	container * current = new container;
	container * temporary = last.wsk;
	current -> next = NULL;
	current -> prev = temporary;
	current -> cont = t;

	if(last.wsk != NULL)
	{
		temporary -> next = current;
	}
	else
	{
		first.wsk = current;
	}

	last.wsk = current;

	if(siz == MAXSIZE)
	{
		pop();
		siz++;
		return 1;
	}
	else
	{
		siz++;
		return 0;
	}
}

template <typename T> T Buffer<T> :: pop()
{
	if(first.wsk != NULL)
	{
		T t;
		container * temporary = first.wsk;
		t = first.wsk -> cont;

		++first;

		if(first.wsk)
		{
			first.wsk -> prev = NULL;
		}

		delete temporary;
		siz--;
		return t;
	}
}

template <typename T> const T Buffer<T> :: peak()
{
	if(first.wsk != NULL)
	{
		return first.wsk -> cont;
	}
}

template <typename T> const int Buffer<T> :: count()
{
	return siz;
}

template <typename T> int Buffer<T> :: clear()
{
	siz = 0;
	container * temporary = first.wsk;

	while(first.wsk != NULL)
	{
		temporary = first.wsk;

		first++;

		if(first.wsk)
		{
		first.wsk -> prev = NULL;
		}

		delete temporary;
	}

	last.wsk = NULL;
}

template <class U> ostream& operator << (ostream & out, Buffer<U> const& buff)
{
	if(buff.siz == 0)
	{
		out<<" ";
	}
	else
	{
		typename Buffer<U> :: iterator it;

		it = buff.first;

		while(it != NULL)
		{
			out<<*it<<" ";
			it++;
		}
	}

	return out;
}

template <class U> istream& operator >> (istream& in, Buffer<U>& buff)
{
	U tmp;
	int n;
	in>>n;
	for(int i = 1; i <= n; i++)
	{
		in>>tmp;
		buff.push(tmp);
	}
	return in;
}

template <class U> Buffer<U>& operator += (Buffer<U>& left, const Buffer<U>& right)
{
	
	if(right.siz != 0)
	{
		typename Buffer<U> :: iterator it;
		typename Buffer<U> :: iterator end;

		it = right.first;
		U tmp;
		end = right.last;
		end++;

		while(it != end)
		{
			tmp = *it;
			left.push(tmp);
			it++;
		}
	}
}

template <class U> Buffer<U>& operator += (Buffer<U>& left, const U& right)
{
	left.push(right);
}

template <class U> bool operator ==( const Buffer<U>& left, const Buffer<U>& right)
{
	typename Buffer<U> :: iterator l;
	l = left.first;
	typename Buffer<U> :: iterator r;
	r = right.first;

	U a;
	U b;

	if(left.siz != right.siz) 
	{
		return false;
	}
	else if(left.siz == 0)
	{
		return true;
	}

	while(l != NULL && r != NULL)
	{
		a = *l;
		b = *r;

		if(a != b)
		{
			return false;
		}

		r++;
		l++;
	}

	return true;
}

template <class U> bool operator !=( const Buffer<U>& left, const Buffer<U>& right)
{
	return !(left==right);
}
