#include <iostream>
#include <string>
using namespace std;

template <typename T> class Buffer
{
private:
	const int MAXSIZE = 5;	

	/*maksymalny rozmiar bufora*/

	int size;

	/*aktualny rozmiar bufora*/

	struct container
	{
		container * prev;
		container * next;

		T cont;
	};

	/*lista która przetrzymuje dowolne typy danych*/

	class iterator
	{		
	private:

		friend class Buffer<T>;
		container * wsk;

	public:

		T operator*() const
		{
			return wsk -> cont;
		}

		iterator& operator ++(int)
		{
			iterator temporary = *this;
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

	/* iterator z przeciążonymi operatorami do łatwiejszego poruszania się po buforze*/

	iterator first;

	/*iterator wskazujący na pierwszy element w liście*/

	iterator last;

	/*iterator wskazujący na ostatni element w liście*/
	string error_log;
	bool error;
public:

	Buffer();
	Buffer(const Buffer<T>&);
	~Buffer();
	int push(T);

	/* funckja która dodaje pojedynczy element do bufora/ zwraca 1 jeśli nastąpiło nadpisanie jakiegos elementu w buforze i 0 jeśli nie nastąpiło nasdpisanie*/

	T pop();

	/* usuwa pojedynczy element z bufora*/

	const T peak();

	/* zwraca pojedynczy element bufora bez jego usuwania */

	int clear();

	/* funckja która resetuje bufor do jego stanu początkowego */

	const int count();

	/*funckja wypisuje aktualny rozmiar bufora */

	string get_error()
	{
		string temporary;
		error = false;
		temporary = error_log;
		error_log.clear();
		return temporary;
	}

	/*funkcja zwraca błędy utraty danych*/ 

	template <class U> friend ostream& operator << (ostream& out, const Buffer<U> &);
	template <class U> friend istream& operator >> (istream& in, Buffer<U> &);
	template <class U> friend Buffer<U>& operator += (Buffer<U>&, const Buffer<U>&);

	/* przeciążony operator += sumuje dwa bufory */

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

		iterator temporary;
		temporary = last;
		temporary++;

		return temporary;
	}
};


template <typename T> Buffer<T> :: Buffer()
{
	size = 0;
	first.wsk = NULL;
	last.wsk = NULL;
	error = false;
	error_log.clear();
}

template <typename T> Buffer<T> :: Buffer(const Buffer<T>& right)
{
	size = 0;
	first.wsk = NULL;
	last.wsk = NULL;
	error = false;
	error_log.clear();

	*this += right;
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

	if(last != NULL)
	{
		temporary -> next = current;
	}
	else
	{
		first.wsk = current;
	}

	last.wsk = current;

	if(size == MAXSIZE)
	{
		if(error == false)
		{
			error = true;
			error_log += "Uwaga utrata danych\n";
		}

		pop();
		size++;

		return 1;
	}
	else
	{
		size++;

		return 0;
	}
}

template <typename T> T Buffer<T> :: pop()
{
	T t;

	if(size != 0 && first != NULL)
	{
		container * temporary = first.wsk;

		t = *first;

		first++;

		if(first.wsk)
		{
			first.wsk -> prev = NULL;
		}

		delete temporary;
		size--;

		if(size == 0)
		{
			first.wsk = NULL;
			last.wsk = NULL;
		}
		return t;
	}

	return t;
}

template <typename T> const T Buffer<T> :: peak()
{
	T t;

	if(first != NULL)
	{
		t =*first;

		return t;
	}

	return t;
}

template <typename T> const int Buffer<T> :: count()
{
	return size;
}

template <typename T> int Buffer<T> :: clear()
{
	size = 0;
	container * temporary = first.wsk;

	while(first != NULL)
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
	error_log.clear();
	error = false;
}

template <class U> ostream& operator << (ostream & out, Buffer<U> const& buff)
{
	if(buff.size == 0)
	{
		out<<endl;
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
	U temporary;
	int n;

	in>>n;

	for(int i = 1; i <= n; i++)
	{
		in>>temporary;
		if(buff.push(temporary));
	}

	return in;
}

template <class U> Buffer<U>& operator += (Buffer<U>& left, const Buffer<U>& right)
{
	
	if(right.size != 0)
	{
		typename Buffer<U> :: iterator it;
		typename Buffer<U> :: iterator end;

		it = right.first;
		
		U temporary;

		end = right.last;
		end++;

		while(it != end)
		{
			temporary = *it;
			left.push(temporary);
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

	if(left.size != right.size) 
	{
		return false;
	}
	else if(left.size == 0)
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
