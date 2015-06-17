// TestBody.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../CBody/AllBodies.h"

using namespace std;


const double solidDensity = 9820;

const double sphereRadius = 4.6;
const double sphereVolume = (4 * M_PI / 3 * pow(sphereRadius, 3));
const double sphereMass = solidDensity * sphereVolume;

const double parallelepipedWidth = 14;
const double parallelepipedHeight = 5;
const double parallelepipedDepth = 0.7;
const double parallelepipedVolume = parallelepipedWidth * parallelepipedHeight * parallelepipedDepth;
const double parallelepipedMass = solidDensity * parallelepipedVolume;

const double cylinderRadius = 2.9;
const double cylinderHeight = 8;
const double cylinderVolume = (M_PI * pow(cylinderRadius, 2) * cylinderHeight);
const double cylinderMass = solidDensity * cylinderVolume;

const double coneRadius = 6.5;
const double coneHeight = 11;
const double coneVolume = (M_PI / 3 * pow(coneRadius, 2) * coneHeight);
const double coneMass = solidDensity * coneVolume;

struct SphereFixture
{
	CSphere sphere;

	SphereFixture()
		:sphere(sphereRadius, solidDensity)
	{
	}
};

struct ParallelepipedFixture
{
	CParallelepiped parallelepiped;

	ParallelepipedFixture()
		:parallelepiped(parallelepipedWidth,
		parallelepipedHeight, parallelepipedDepth, solidDensity)
	{
	}
};

struct ConeFixture
{
	CCone cone;

	ConeFixture()
		:cone(coneRadius, coneHeight, solidDensity)
	{
	}
};

struct CylinderFixture
{
	CCylinder cylinder;

	CylinderFixture()
		:cylinder(cylinderRadius, cylinderHeight, solidDensity)
	{
	}
};

struct CompoundFixture
{
	CCompound comp;
	CCone cone;
	CSphere sphere;
	CParallelepiped parallelepiped;

	CompoundFixture()
		:comp(),
		cone(coneRadius, coneHeight, solidDensity),
		sphere(sphereRadius, solidDensity),
		parallelepiped(parallelepipedWidth, parallelepipedHeight, parallelepipedDepth, solidDensity)
	{
	}
};
BOOST_FIXTURE_TEST_SUITE(Sphere, SphereFixture)

BOOST_AUTO_TEST_CASE(SphereHasDensityAndRadius)
{
	BOOST_CHECK_EQUAL(sphere.GetDensity(), solidDensity);
	BOOST_CHECK_EQUAL(sphere.GetRadius(), sphereRadius);
}

BOOST_AUTO_TEST_CASE(SphereHasVolume)
{
	BOOST_CHECK_EQUAL(sphere.GetVolume(), sphereVolume);
}

BOOST_AUTO_TEST_CASE(SphereHasMass)
{
	BOOST_CHECK_EQUAL(sphere.GetMass(), sphereMass);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_FIXTURE_TEST_SUITE(Parallelepiped, ParallelepipedFixture)

BOOST_AUTO_TEST_CASE(ParallelepipedHasDimensionsAndDensity)
{
	BOOST_CHECK_EQUAL(parallelepiped.GetWidth(), parallelepipedWidth);
	BOOST_CHECK_EQUAL(parallelepiped.GetHeight(), parallelepipedHeight);
	BOOST_CHECK_EQUAL(parallelepiped.GetDepth(), parallelepipedDepth);
	BOOST_CHECK_EQUAL(parallelepiped.GetDensity(), solidDensity);
}

BOOST_AUTO_TEST_CASE(ParallelepipedHasVolume)
{
	BOOST_CHECK_EQUAL(parallelepiped.GetVolume(), parallelepipedVolume);
}

BOOST_AUTO_TEST_CASE(ParallelepipedHasMass)
{
	BOOST_CHECK_EQUAL(parallelepiped.GetMass(), parallelepipedMass);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_FIXTURE_TEST_SUITE(Cone, ConeFixture)

BOOST_AUTO_TEST_CASE(ConeHasDensityBaseRadiusAndHeight)
{
	BOOST_CHECK_EQUAL(cone.GetRadius(), coneRadius);
	BOOST_CHECK_EQUAL(cone.GetHeight(), coneHeight);
	BOOST_CHECK_EQUAL(cone.GetDensity(), solidDensity);
}

BOOST_AUTO_TEST_CASE(ConeHasVolume)
{
	BOOST_CHECK_EQUAL(cone.GetVolume(), coneVolume);
}

BOOST_AUTO_TEST_CASE(ConeHasMass)
{
	BOOST_CHECK_EQUAL(cone.GetMass(), coneMass);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_FIXTURE_TEST_SUITE(Cylinder, CylinderFixture)

BOOST_AUTO_TEST_CASE(CylinderHasDensityBaseRadiusAndHeight)
{
	BOOST_CHECK_EQUAL(cylinder.GetRadius(), cylinderRadius);
	BOOST_CHECK_EQUAL(cylinder.GetHeight(), cylinderHeight);
	BOOST_CHECK_EQUAL(cylinder.GetDensity(), solidDensity);
}

BOOST_AUTO_TEST_CASE(CylinderHasVolume)
{
	BOOST_CHECK_EQUAL(cylinder.GetVolume(), cylinderVolume);
}

BOOST_AUTO_TEST_CASE(CylinderHasMass)
{
	BOOST_CHECK_EQUAL(cylinder.GetMass(), cylinderMass);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_FIXTURE_TEST_SUITE(Compound, CompoundFixture)

BOOST_AUTO_TEST_CASE(TestEmptyCompound)
{
	comp.AddBody(make_shared<CCompound>(comp));
	BOOST_CHECK_EQUAL(comp.GetVolume(), 0);
	BOOST_CHECK_EQUAL(comp.GetMass(), 0);
}

BOOST_AUTO_TEST_CASE(AddOneElement)
{
	comp.AddBody(make_shared<CSphere>(sphere));
	BOOST_CHECK_EQUAL(comp.GetVolume(), sphere.GetVolume());
	BOOST_CHECK_EQUAL(comp.GetDensity(), sphere.GetDensity());
	BOOST_CHECK_EQUAL(comp.GetMass(), sphere.GetMass());
}

BOOST_AUTO_TEST_CASE(AddAllElements)
{
	comp.AddBody(make_shared<CSphere>(sphere));
	comp.AddBody(make_shared<CParallelepiped>(parallelepiped));
	comp.AddBody(make_shared<CCone>(cone));
	double mass = sphere.GetMass() + parallelepiped.GetMass() + cone.GetMass();
	double volume = sphere.GetVolume() + parallelepiped.GetVolume() + cone.GetVolume();
	BOOST_CHECK_EQUAL(comp.GetVolume(), volume);
	BOOST_CHECK_EQUAL(comp.GetDensity(), mass / volume);
	BOOST_CHECK_EQUAL(comp.GetMass(), mass);
}

BOOST_AUTO_TEST_SUITE_END()