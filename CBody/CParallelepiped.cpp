#include "stdafx.h"
#include "CParallelepiped.h"

using namespace std;

CParallelepiped::CParallelepiped(double width, double height, double depth, double density)
	:CSolidBody(density), 
	m_width(width),
	m_height(height),
	m_depth(depth)
{
}


CParallelepiped::~CParallelepiped()
{
}

double CParallelepiped::GetWidth() const
{
	return m_width;
}

double CParallelepiped::GetHeight() const
{
	return m_height;
}

double CParallelepiped::GetDepth() const
{
	return m_depth;
}

double CParallelepiped::GetVolume() const
{
	return m_width * m_height * m_depth;
}

string CParallelepiped::GetInfo() const
{
	return "Object: Parallelepiped\nMass: " + to_string(GetMass()) +
		"\nVolume: " + to_string(GetVolume()) + "\nDensity: " + to_string(GetDensity()) +
		"\nWidth: " + to_string(GetWidth()) + "\nHeight: " + to_string(GetHeight()) +
		"\nDepth: " + to_string(GetDepth());
}