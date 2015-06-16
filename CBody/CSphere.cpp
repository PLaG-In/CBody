#include "stdafx.h"
#include "CSphere.h"

using namespace std;

CSphere::CSphere(double radius, double density)
	: CSolidBody(density), m_radius(radius)
{
}

CSphere::~CSphere(void)
{
}

double CSphere::GetRadius() const
{
	return m_radius;
}

double CSphere::GetVolume() const
{
	return (4 * M_PI / 3 * pow(m_radius, 3));
}

string CSphere::GetInfo() const
{
	return "Object: Sphere\nMass: " + to_string(GetMass()) +
		"\nVolume: " + to_string(GetVolume()) + "\nDensity: " + to_string(GetDensity()) +
		"\nRadius : " + to_string(GetRadius());
}