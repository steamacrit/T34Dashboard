#pragma once


#include "pch.h"

class UID
{
private:
    void * pimpl;


public:
	// create empty fuid
    UID(void);

	// create a fuid from vector of bytes
    UID(const std::vector<uint8_t> & bytes);

	// create a fuid from array of bytes
    UID(const uint8_t * bytes, size_t size);

	// create a fuid from string
    UID(const std::string & s);

	// copy constructor
    UID(const UID & other);

	// destructor
	~UID();

	// overload assignment operator
    UID &operator=(const UID & other);

	// overload equality and inequality operator
	bool operator==(const UID & other) const;
	bool operator!=(const UID & other) const;

	int32_t ToCString(char * pCString, size_t size);
	std::string ToString();
	std::string ToStringW();

private:

    inline void Initialize();

	// make the << operator a friend so it can access m_data->m_vBytes
	friend std::ostream & operator<<(std::ostream & s, const UID & fuid);

}; /* class UID */



