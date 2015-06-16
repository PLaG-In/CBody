#include "stdafx.h"
#include "CCylinder.h"

using namespace std;

CCylinder::CCylinder(double radius, double height, double density)
	:CSolidBody(density), m_radius(radius), m_height(height)
{
}

CCylinder::~CCylinder()
{
}

double CCylinder::GetRadius() const
{
	return m_radius;
}

double CCylinder::GetHeight() const
{
	return m_height;
}

double CCylinder::GetVolume() const
{
	return (M_PI * pow(m_radius, 2) * m_height);
}

string CCylinder::GetInfo() const
{
	return "Object: Cylinder\nMass: " + to_string(GetMass()) +
		"\nVolume: " + to_string(GetVolume()) + "\nDensity: " + to_string(GetDensity()) +
		"\nRadius: " + to_string(GetRadius()) + "\nHeight: " + to_string(GetHeight());
}