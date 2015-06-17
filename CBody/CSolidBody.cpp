#include "stdafx.h"
#include "CSolidBody.h"


CSolidBody::CSolidBody(double density)
	:m_density(density)
{
}

CSolidBody::~CSolidBody()
{
}

double CSolidBody::GetDensity() const
{
	return m_density;
}

double CSolidBody::GetMass() const
{
	return m_density * GetVolume();
}