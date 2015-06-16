#pragma once
#include "CSolidBody.h"
class CCylinder final : public CSolidBody
{
public:
	CCylinder(double radius, double height, double density);
	~CCylinder();

	double GetRadius() const;
	double GetHeight() const;
	double GetVolume() const override final;
	std::string GetInfo() const override final;

private:
	double m_radius;
	double m_height;
};