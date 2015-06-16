#pragma once
#include "CBody.h"
class CSolidBody : public CBody
{
public:
	CSolidBody(double density);
	~CSolidBody();

	virtual double GetDensity() const override final;
	virtual double GetMass() const override final;

private:
	double m_density;
};