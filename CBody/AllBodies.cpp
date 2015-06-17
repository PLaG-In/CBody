#include "stdafx.h"
#include "AllBodies.h"

using namespace std;

typedef function<shared_ptr<CBody>(istringstream &paramsStrm)> Handler;
typedef map<string, Handler> StringToHadlerMap;
StringToHadlerMap handlers;

shared_ptr<CBody> HandleSphere(istringstream &paramsStrm)
{
	double radius, density;
	if (paramsStrm >> radius &&  paramsStrm >> density)
	{
		CSphere sphere(radius, density);
		return make_shared<CSphere>(sphere);
	}
	return nullptr;
}


shared_ptr<CBody> HandleCone(istringstream &paramsStrm)
{
	double radius, height, density;
	if (paramsStrm >> radius &&  paramsStrm >> height && paramsStrm >> density)
	{
		CCone cone(radius, height, density);
		return make_shared<CCone>(cone);
	}
	return nullptr;
}

shared_ptr<CBody> HandleCylinder(istringstream &paramsStrm)
{
	double radius, height, density;
	if (paramsStrm >> radius &&  paramsStrm >> height && paramsStrm >> density)
	{
		CCylinder cylinder(radius, height, density);
		return make_shared<CCylinder>(cylinder);
	}
	return nullptr;
}

shared_ptr<CBody> HandleParallelepiped(istringstream &paramsStrm)
{
	double width, height, depth, density;
	if (paramsStrm >> width &&  paramsStrm >> height && paramsStrm >> depth && paramsStrm >> density)
	{
		CParallelepiped parallelepiped(width, height, depth, density);
		return make_shared<CParallelepiped>(parallelepiped);
	}
	return nullptr;

}

shared_ptr<CBody> HandleCompound(istringstream &paramsStrm)
{
	CCompound compound;
	string shapeType;
	bool compoundWasCreated = false;
	while (paramsStrm >> shapeType)
	{
		auto it = handlers.find(shapeType);
		if (it != handlers.cend())
		{
			shared_ptr<CBody> res = it->second(paramsStrm);
			if (res != nullptr)
			{
				compound.AddBody(res);
				compoundWasCreated = true;
			}
		}
	}
	if (compoundWasCreated)
	{
		return make_shared<CCompound>(compound);
	}
	return nullptr;
}

void HandleUserInput(vector<shared_ptr<CBody>> &bodies, const StringToHadlerMap &handlers)
{
	string shapeType;
	cout << "Input object: ";
	while (cin >> shapeType)
	{
		auto it = handlers.find(shapeType);
		string params;
		getline(cin, params);
		istringstream strm(params);

		if (it != handlers.cend())
		{
			shared_ptr<CBody> res = it->second(strm);
			if (res != nullptr)
			{
				bodies.push_back(res);
				cout << "Handling " << shapeType << endl;
			}
			else
			{
				cout << "Invalid parametrs for creating " << shapeType << endl;
			}
		}
		else
		{
			cout << "Unknown shape type: " << shapeType << endl;
		}
		cout << "Input object: ";
	}
}

void ProccessAndOutputInfo(const vector<shared_ptr<CBody>> &bodies)
{
	if (bodies.size() == 0)
	{
		return;
	}

	double waterDensity = 1000;
	auto maxMass = bodies[0];
	auto elemWithMinWeightInWater = bodies[0];
	double minWeightInWater = (bodies[0]->GetDensity() - waterDensity) * bodies[0]->GetVolume();

	for (const auto &elem : bodies)
	{
		if (maxMass->GetMass() < elem->GetMass())
		{
			maxMass = elem;
		}
		double curWeightInWater = (elem->GetDensity() - waterDensity) * elem->GetVolume();
		if (minWeightInWater > curWeightInWater)
		{
			elemWithMinWeightInWater = elem;
			minWeightInWater = curWeightInWater;
		}
	}

	cout << "Max mass body: " << endl;
	cout << maxMass->GetInfo() << endl;

	cout << "Min weight in water: " << endl;
	cout << elemWithMinWeightInWater->GetInfo() << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	vector<shared_ptr<CBody>> bodies;

	handlers["cone"] = HandleCone;
	handlers["cylinder"] = HandleCylinder;
	handlers["parallelepiped"] = HandleParallelepiped;
	handlers["sphere"] = HandleSphere;
	handlers["compound"] = HandleCompound;

	HandleUserInput(bodies, handlers);
	ProccessAndOutputInfo(bodies);

	return 0;
}