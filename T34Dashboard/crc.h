#pragma once

#include <cstdint>
#include <string>

class CRC
{
public:
	static uint32_t fromFile(const std::string file_path);
	static uint32_t fromString(const std::string data, uint32_t crc = 0);
	static uint32_t fromBuffer(const unsigned char * buf, uint32_t len, uint32_t crc = 0);
	static uint32_t combineCRC32(uint32_t crc1, uint32_t crc2, uint32_t len2);

private:
	CRC() {};
	~CRC() {};

	static uint32_t gf2MatrixTimes(uint32_t * mat, uint32_t vec);
	static void gf2MatrixSquare(uint32_t * square, uint32_t * mat);
}; /* class CRC */

