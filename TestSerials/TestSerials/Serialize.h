#include <vector>
#include <map>
#include <set>
#include <list>
#include <string>
#include "inttype.h"
using namespace std;

//


class CSerial
{
public:
	CSerial() {}

	CSerial(const string& d) :size_(d.size()), offset_(0)
	{
		uint8_t *data = (uint8_t*) d.data();

		cdata_ = data;
	}
	~CSerial() {}

	const std::string& buffer() const
	{
		return buf;
	}
//---------------------------------------------------------
//≤Â»Î
	template<class T>
	CSerial& operator <<( T value );

	template<class T>
	void push(T value);

	void push(string value);

//---------------------------------------------------------	
	template<class T>
	CSerial& operator >> ( T &value );

	template<class T>
	void pop(T &val);

	void pop(string &value);
//---------------------------------------------------------	
private:
	string buf;
	const uint8_t *cdata_;
	size_t size_;
	size_t offset_;
};


template<class T>
inline CSerial& CSerial::operator << ( T value )
{
	push(value);
	return *this;
}

template<class T>
void CSerial::push(T value)
{
	int size = sizeof( value );
	buf.append(( const char* )&value,sizeof(value));
}

void  CSerial::push(string value)
{
	 uint16_t size = value.size();
	 push((uint16_t) ( size ));
     buf.append(value.c_str(), value.size());
}


//---------------------------------------------------------	
template<class T>
CSerial& CSerial::operator >> ( T &value )
{
	pop(value);
	return *this;
}

template<class T>
void CSerial::pop(T &val)
{
	T *p = (T*) ( cdata_ + offset_ );
	val = *p;
	offset_ += sizeof( val );
}

void CSerial::pop(string &value)
{
	uint16_t size = 0;
	pop(size);
	value.append((const char*) ( cdata_ + offset_ ), size);
	offset_ += size;
}