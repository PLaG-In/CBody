#pragma once
#include "CBody.h"
class CCompound final : public CBody
{
public:
	CCompound();
	~CCompound();

	virtual double GetVolume() const override final;
	virtual double GetDensity() const override final;
	virtual double GetMass() const override final;
	virtual std::string GetInfo() const override final;

	void AddBody(const std::shared_ptr<CBody> ptr);
private:
	double m_volume;
	double m_density;
	double m_mass;
	std::vector<std::shared_ptr<CBody>> m_bodies;
};
