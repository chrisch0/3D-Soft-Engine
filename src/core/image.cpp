#pragma once
#include <cassert>
#include <fstream>
#include <exception>
#include <cstring>
#include <windows.h>
#include "../utils/util.hpp"
#include "image.hpp"

Image::Image(int width, int height, int channel) :
	m_width(width), m_height(height), m_channels(channel)
{
	assert(m_width > 0 && m_height > 0 && 0 < m_channels && m_channels < 5);
	m_bufferSize = m_width * m_height * m_channels;

	try
	{
		m_buffer = new unsigned char[m_bufferSize]();
	}
	catch (const std::bad_alloc& e)
	{
		std::string msg = "Bad allocate!\nImage buffer allocate fail!\n" + std::string(e.what());
		MessageBoxA(NULL, msg.c_str(), "Error", MB_OK);
	}
}

Image::~Image()
{
	delete[](m_buffer);
}

Image::Image(const Image& rhs) :
	m_width(rhs.m_width), m_height(rhs.m_height), m_channels(rhs.m_channels), m_bufferSize(rhs.m_bufferSize)
{
	m_buffer = new unsigned char[m_bufferSize];
	std::memcpy(m_buffer, rhs.m_buffer, m_bufferSize);
}

Image& Image::operator=(const Image& rhs)
{
	m_width = rhs.m_width;
	m_height = rhs.m_height;
	m_channels = rhs.m_channels;
	m_bufferSize = rhs.m_bufferSize;

	unsigned char* new_buffer = new unsigned char[m_bufferSize];
	std::memcpy(new_buffer, rhs.m_buffer, m_bufferSize);
	delete[] m_buffer;
	m_buffer = new_buffer;
	return *this;
}


void Image::LoadTGA(std::string& filename)
{

}

void Image::SaveasTGA(std::string& filename)
{
	std::string filename_with_extension = filename + ".tga";
	unsigned char header[TAG_HEAD_SIZE];
	std::ofstream file(filename_with_extension, std::ios::binary);

	memset(header, 0, TAG_HEAD_SIZE);
	header[2] = m_channels = 1 ? 3 : 2;
	header[12] = m_width & 0xFF;
	header[13] = (m_width >> 8) & 0xFF;
	header[14] = m_height & 0xFF;
	header[15] = (m_height >> 8) & 0xFF;
	header[16] = (m_channels * 8) & 0xFF;

	file.write((char*)header, TAG_HEAD_SIZE);
	file.write((char*)m_buffer, GetBufferSize());

	file.close();
}

void Image::SetColorRGB(int u, int v, Color color)
{
	assert(u < m_width && v < m_height);
	int flipped_row = m_height - v - 1;
	int index = flipped_row * m_width * m_channels + u * m_channels;
	m_buffer[index] = color.x;
	m_buffer[index + 1] = color.y;
	m_buffer[index + 2] = color.z;
}

void Image::SetColorBGR(int u, int v, Color color)
{
	assert(u < m_width && v < m_height);
	int flipped_row = m_height - v - 1;
	int index = flipped_row * m_width * m_channels + u * m_channels;
	m_buffer[index] = color.z;
	m_buffer[index + 1] = color.y;
	m_buffer[index + 2] = color.x;
}

void Image::SetBuffer(unsigned char* buffer)
{
	m_buffer = buffer;
}