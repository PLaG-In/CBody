#pragma once
#include "CSolidBody.h"

class CSphere final : public CSolidBody
{
public:
	CSphere(double radius, double density);
	~CSphere();

	double GetRadius() const;
	double GetVolume() const override final;
	std::string GetInfo() const override final;

private:
	double m_radius;
};
