#include "pch.h"
#include "fuid.h"

#ifdef _WIN32
	#include <rpc.h>
#elif defined MAC_BUILD
	#include <CoreFoundation/CFUUID.h>
#elif defined LINUX_BUILD
	#include <uuid/uuid.h>
#endif

#include <sstream>
#include <iomanip>
#include <ctime>

#define PIMPL(x) static_cast<UIDData *>(x)
struct UIDData 
{
	// buffer for the data
	std::vector<uint8_t> m_vBytes;
};

// converts a single hex char to a number (0 - 15)
uint8_t HexDigitToChar(int8_t ch) {
	if (ch > 47 && ch < 58)
		return ch - 48;

	if (ch > 96 && ch < 103)
		return ch - 87;

	if (ch > 64 && ch < 71)
		return ch - 55;

	return 0;
}

// converts the two hexadecimal characters to an unsigned char (a byte)
uint8_t HexPairToChar(int8_t a, int8_t b) {
	return HexDigitToChar(a) * 16 + HexDigitToChar(b);
}

void UID::Initialize() {
    pimpl = new UIDData;
}

// create a fuid
UID::UID() {
    Initialize();

	for (int i = 0; i < 16; i++) PIMPL(pimpl)->m_vBytes.push_back(0);

#ifdef _WIN32

	UUID uuid;
	RPC_STATUS status = UuidCreate(&uuid);
	if (status != RPC_S_OK)
		return;

	uint8_t * p_byte = reinterpret_cast<uint8_t *>(&uuid.Data1);
	PIMPL(pimpl)->m_vBytes[0] = p_byte[3];
	PIMPL(pimpl)->m_vBytes[1] = p_byte[2];
	PIMPL(pimpl)->m_vBytes[2] = p_byte[1];
	PIMPL(pimpl)->m_vBytes[3] = p_byte[0];

	p_byte = reinterpret_cast<uint8_t *>(&uuid.Data2);
	PIMPL(pimpl)->m_vBytes[4] = p_byte[1];
	PIMPL(pimpl)->m_vBytes[5] = p_byte[0];


	p_byte = reinterpret_cast<uint8_t *>(&uuid.Data3);
	PIMPL(pimpl)->m_vBytes[6] = p_byte[1];
	PIMPL(pimpl)->m_vBytes[7] = p_byte[0];

	p_byte = reinterpret_cast<uint8_t *>(&uuid.Data4);
	PIMPL(pimpl)->m_vBytes[8] = p_byte[0];
	PIMPL(pimpl)->m_vBytes[9] = p_byte[1];
	PIMPL(pimpl)->m_vBytes[10] = p_byte[2];
	PIMPL(pimpl)->m_vBytes[11] = p_byte[3];
	PIMPL(pimpl)->m_vBytes[12] = p_byte[4];
	PIMPL(pimpl)->m_vBytes[13] = p_byte[5];
	PIMPL(pimpl)->m_vBytes[14] = p_byte[6];
	PIMPL(pimpl)->m_vBytes[15] = p_byte[7];

	return;

#elif defined MAC_BUILD

	auto newId = CFUUIDCreate(NULL);
	auto bytes = CFUUIDGetUUIDBytes(newId);
	CFRelease(newId);

	PIMPL(pimpl)->m_vBytes[0] = bytes.byte0;
	PIMPL(pimpl)->m_vBytes[1] = bytes.byte1;
	PIMPL(pimpl)->m_vBytes[2] = bytes.byte2;
	PIMPL(pimpl)->m_vBytes[3] = bytes.byte3;
	PIMPL(pimpl)->m_vBytes[4] = bytes.byte4;
	PIMPL(pimpl)->m_vBytes[5] = bytes.byte5;
	PIMPL(pimpl)->m_vBytes[6] = bytes.byte6;
	PIMPL(pimpl)->m_vBytes[7] = bytes.byte7;
	PIMPL(pimpl)->m_vBytes[8] = bytes.byte8;
	PIMPL(pimpl)->m_vBytes[9] = bytes.byte9;
	PIMPL(pimpl)->m_vBytes[10] = bytes.byte10;
	PIMPL(pimpl)->m_vBytes[11] = bytes.byte11;
	PIMPL(pimpl)->m_vBytes[12] = bytes.byte12;
	PIMPL(pimpl)->m_vBytes[13] = bytes.byte13;
	PIMPL(pimpl)->m_vBytes[14] = bytes.byte14;
	PIMPL(pimpl)->m_vBytes[15] = bytes.byte15;

#elif defined LINUX_BUILD

	uuid_t bytes;
	uuid_generate(bytes);

	PIMPL(pimpl)->m_vBytes[0] = bytes[0];
	PIMPL(pimpl)->m_vBytes[1] = bytes[1];
	PIMPL(pimpl)->m_vBytes[2] = bytes[2];
	PIMPL(pimpl)->m_vBytes[3] = bytes[3];
	PIMPL(pimpl)->m_vBytes[4] = bytes[4];
	PIMPL(pimpl)->m_vBytes[5] = bytes[5];
	PIMPL(pimpl)->m_vBytes[6] = bytes[6];
	PIMPL(pimpl)->m_vBytes[7] = bytes[7];
	PIMPL(pimpl)->m_vBytes[8] = bytes[8];
	PIMPL(pimpl)->m_vBytes[9] = bytes[9];
	PIMPL(pimpl)->m_vBytes[10] = bytes[10];
	PIMPL(pimpl)->m_vBytes[11] = bytes[11];
	PIMPL(pimpl)->m_vBytes[12] = bytes[12];
	PIMPL(pimpl)->m_vBytes[13] = bytes[13];
	PIMPL(pimpl)->m_vBytes[14] = bytes[14];
	PIMPL(pimpl)->m_vBytes[15] = bytes[15];

#endif

}

// create a fuid from vector of bytes
UID::UID(const std::vector<uint8_t> & bytes) {
    Initialize();
	PIMPL(pimpl)->m_vBytes = bytes;
}

// create a fuid from array of bytes
UID::UID(const uint8_t * bytes, size_t size) {
    Initialize();
	PIMPL(pimpl)->m_vBytes.assign(bytes, bytes + size);
}

// create a fuid from string
UID::UID(const std::string & s) {
    Initialize();
	PIMPL(pimpl)->m_vBytes.clear();

	int8_t charOne, charTwo;
	bool lookingForFirstChar = true;

	for (const uint8_t & ch : s)
	{
		if (ch == '-')
			continue;

		if (lookingForFirstChar)
		{
			charOne = ch;
			lookingForFirstChar = false;
		}
		else
		{
			charTwo = ch;
			auto byte = HexPairToChar(charOne, charTwo);
			PIMPL(pimpl)->m_vBytes.push_back(byte);
			lookingForFirstChar = true;
		}
	}
}

// copy constructor
UID::UID(const UID & other) {
	PIMPL(pimpl)->m_vBytes = PIMPL(other.pimpl)->m_vBytes;
}

// destructor
UID::~UID() 
{
    if (pimpl)
        delete PIMPL(pimpl);
}

// overload assignment operator
UID & UID::operator=(const UID & other) {
	PIMPL(pimpl)->m_vBytes = PIMPL(other.pimpl)->m_vBytes;
	return *this;
}

// overload equality and inequality operator
bool UID::operator==(const UID & other) const {
	return PIMPL(pimpl)->m_vBytes == PIMPL(other.pimpl)->m_vBytes;
}
bool UID::operator!=(const UID & other) const {
	return !((*this) == other);
}


// overload << so that it's easy to convert to a string
std::ostream & operator<<(std::ostream & s, const UID & fuid) {
	for (size_t i = 0; i < PIMPL(fuid.pimpl)->m_vBytes.size(); i++) {
		if (i == 4) s << "-";
		if (i == 6) s << "-";
		if (i == 8) s << "-";
		if (i == 10) s << "-";
		s << std::hex << std::uppercase << std::setfill('0') << std::setw(2) << (int32_t)PIMPL(fuid.pimpl)->m_vBytes[i];
	}

	return s;
}

int32_t UID::ToCString(char * pCString, size_t size) {
	if (pCString == nullptr || size == 0)
		return static_cast<int32_t>(ToString().length());

	std::string uid = ToString();
	size_t length = uid.length();
	::strncpy_s(pCString, size, uid.c_str(), length);
	return static_cast<int32_t>((size > length ? length : size));
}

std::string UID::ToString() {
	std::string s;
	std::stringstream ss;

	ss << *this;
	ss >> s;

	return s;
}

std::string UID::ToStringW() {
	std::string s;
	std::stringstream ss;

	for (size_t i = 0; i < PIMPL(pimpl)->m_vBytes.size(); i++) {
		if (i == 4)  ss << "-";
        if (i == 6)  ss << "-";
        if (i == 8)  ss << "-";
        if (i == 10) ss << "-";
		ss << std::hex << std::setfill('0') << std::setw(2) << (int32_t)PIMPL(pimpl)->m_vBytes[i];
	}

	ss >> s;
	return s;
}

