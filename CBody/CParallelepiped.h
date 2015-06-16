#pragma once
#include "CSolidBody.h"

class CParallelepiped final :
	public CSolidBody
{
public:
	CParallelepiped(double width, double height, double depth,
		double density);
	~CParallelepiped();

	double GetWidth() const;
	double GetHeight() const;
	double GetDepth() const;
	double GetVolume() const override final;
	std::string GetInfo() const override final;

private:
	double m_width;
	double m_height;
	double m_depth;
};