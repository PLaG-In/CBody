#include "stdafx.h"
#include "CCone.h"

using namespace std;

CCone::CCone(double radius, double height, double density)
	:CSolidBody(density),
	m_radius(radius),
	m_height(height)
{
}

CCone::~CCone()
{
}

double CCone::GetRadius() const
{
	return m_radius;
}

double CCone::GetHeight() const
{
	return m_height;
}

double CCone::GetVolume() const
{
	return (M_PI / 3 * pow(m_radius, 2) * m_height);
}

string CCone::GetInfo() const
{
	return "Object: Cone\nMass: " + to_string(GetMass()) +
		"\nVolume: " + to_string(GetVolume()) + "\nDensity: " + to_string(GetDensity()) +
		"\nRadius: " + to_string(GetRadius()) + "\nHeight: " + to_string(GetHeight());
}