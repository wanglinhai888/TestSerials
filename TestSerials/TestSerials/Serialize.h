#include <vector>
#include <map>
#include <set>
#include <list>
#include <string>
#include "inttype.h"
using namespace std;

class CSerialize
{
public:
	CSerialize() {}

	CSerialize(const string& d) :size_(d.size()), offset_(0)
	{
		uint8_t *data = (uint8_t*) d.data();

		cdata_ = data;
	}
	~CSerialize() {}

	const std::string& buffer() const
	{
		return buf;
	}
//---------------------------------------------------------
//≤Â»Î
	template<class T>
	CSerialize& operator <<( T value );

	template<class T>
	void push(T value);

	void push(string value);

	template<class T>
	void push(const std::vector<T> &val);

//---------------------------------------------------------	
	template<class T>
	CSerialize& operator >> ( T &value );

	template<class T>
	void pop(T &val);

	void pop(string &value);

	template<class T>
	void pop(std::vector<T>& val);
//---------------------------------------------------------	
private:
	string buf;
	const uint8_t *cdata_;
	size_t size_;
	size_t offset_;
};


template<class T>
inline CSerialize& CSerialize::operator << ( T value )
{
	push(value);
	return *this;
}

template<class T>
void CSerialize::push(T value)
{
	int size = sizeof( value );
	buf.append(( const char* )&value,sizeof(value));
}

void  CSerialize::push(string value)
{
	 uint16_t size = value.size();
	 push((uint16_t) ( size ));
     buf.append(value.c_str(), value.size());
}

template<class T>
void CSerialize::push(const std::vector<T> &val)
{
	push((int32_t) val.size());

	for ( std::vector<T>::const_iterator citer = val.begin(); citer != val.end(); ++citer )
	{
		push(*citer);
	}
}

//---------------------------------------------------------	
template<class T>
CSerialize& CSerialize::operator >> ( T &value )
{
	pop(value);
	return *this;
}

template<class T>
void CSerialize::pop(T &val)
{
	T *p = (T*) ( cdata_ + offset_ );
	val = *p;
	offset_ += sizeof( val );
}

void CSerialize::pop(string &value)
{
	uint16_t size = 0;
	pop(size);
	value.append((const char*) ( cdata_ + offset_ ), size);
	offset_ += size;
}

template<class T>
void  CSerialize::pop(std::vector<T>& val)
{
	uint32_t size = 0;
	pop(size);
	
	for ( uint32_t i = 0; i < size; ++i )
	{
		std::vector<T>::value_type tmpval;
		pop(tmpval);
		val.push_back(tmpval);
	}
}