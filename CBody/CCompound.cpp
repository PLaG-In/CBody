#include "stdafx.h"
#include "CCompound.h"

using namespace std;

CCompound::CCompound()
	:m_bodies(),
	m_volume(0),
	m_density(0), m_mass(0)
{
}

CCompound::~CCompound()
{
}

double CCompound::GetVolume() const
{
	return m_volume;
}

double CCompound::GetDensity() const
{
	return m_density;
}

double CCompound::GetMass() const
{
	return m_mass;
}

string CCompound::GetInfo() const
{
	string res = "Compound object (" + to_string(m_bodies.size()) + "entities):\n";
	for (const auto &elem : m_bodies)
	{
		res += elem->GetInfo() + "\n";
	}

	return res;
}

void CCompound::AddBody(const std::shared_ptr<CBody> ptr)
{
	if (this == &(*ptr))
	{
		return;
	}

	m_bodies.push_back(ptr);

	m_mass += ptr->GetMass();
	m_volume += ptr->GetVolume();
	m_density = m_mass / m_volume;
}