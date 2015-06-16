#pragma once
class CBody
{
public:
	CBody();
	virtual ~CBody();

	virtual double GetVolume() const = 0;
	virtual double GetDensity() const = 0;
	virtual double GetMass() const = 0;
	virtual std::string GetInfo() const = 0;
};
