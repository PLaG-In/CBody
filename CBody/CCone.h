#pragma once
#include "CSolidBody.h"

class CCone final : public CSolidBody
{
public:
	CCone(double radius, double height, double density);
	~CCone();

	double GetRadius() const;
	double GetHeight() const;
	double GetVolume() const override final;
	std::string GetInfo() const override final;

private:
	double m_radius;
	double m_height;
};