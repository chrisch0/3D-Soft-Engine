#pragma once
#include <string>
#include "../math/vec.hpp"

class Image
{
public:
	Image(int width, int height, int channel);
	~Image();
	Image(const Image&);
	Image& operator=(const Image& rhs);

	void LoadTGA(std::string& filename);
	void SaveasTGA(std::string& filename);

	void SetColorRGB(int row, int col, Color color);
	void SetColorBGR(int row, int col, Color color);
	void SetBuffer(unsigned char* buffer);

	unsigned char* GetBuffer() const { return m_buffer; }
	const int GetWidth() const { return m_width; }
	const int GetHeight() const { return m_height; }
	const size_t GetBufferSize() const { return m_bufferSize; }
private:
	int m_width;
	int m_height;
	int m_channels;
	size_t m_bufferSize;
	unsigned char* m_buffer;
};