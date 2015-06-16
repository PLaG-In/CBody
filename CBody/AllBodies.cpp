#include "stdafx.h"
#include "CBody.h"
#include "CCompound.h"
#include "CCone.h"
#include "CCylinder.h"
#include "CParallelepiped.h"
#include "CSphere.h"

using namespace std;

typedef function<shared_ptr<CBody>(istringstream &paramsStream)> Handler;
typedef map<string, Handler> StringToHadlerMap;
StringToHadlerMap handlers;

shared_ptr<CBody> HandleCone(istringstream &paramsStream)
{
	string radius, height, density;
	paramsStream >> radius >> height >> density;
	CCone c(atof(radius.c_str()), atof(height.c_str()), atof(density.c_str()));

	return make_shared<CCone>(c);
}

shared_ptr<CBody> HandleCylinder(istringstream &paramsStream)
{
	string radius, height, density;
	paramsStream >> radius >> height >> density;
	CCylinder c(atof(radius.c_str()), atof(height.c_str()), atof(density.c_str()));

	return make_shared<CCylinder>(c);
}

shared_ptr<CBody> HandleParallelepiped(istringstream &paramsStream)
{
	string width, height, depth, density;
	paramsStream >> width >> height >> depth >> density;
	CParallelepiped p(atof(width.c_str()), atof(height.c_str()),
		atof(depth.c_str()), atof(density.c_str()));

	return make_shared<CParallelepiped>(p);

}

shared_ptr<CBody> HandleSphere(istringstream &paramsStream)
{
	string radius, density;
	paramsStream >> radius >> density;
	CSphere s(atof(radius.c_str()), atof(density.c_str()));

	return make_shared<CSphere>(s);
}

shared_ptr<CBody> HandleCompound(istringstream &paramsStream)
{
	CCompound comp;
	string shape;
	while (paramsStream >> shape)
	{
		auto it = handlers.find(shape);
		if (it != handlers.cend())
		{
			comp.AddBody(it->second(paramsStream));
		}
	}
	return make_shared<CCompound>(comp);
}

void HandleUserInput(vector<shared_ptr<CBody>> &resVector,
	const StringToHadlerMap &handlers)
{
	cout << "Input object: ";
	string shape;
	while (cin >> shape)
	{
		auto it = handlers.find(shape);
		string params;
		getline(cin, params);
		istringstream ss(params);

		if (it != handlers.cend())
		{
			resVector.push_back(it->second(ss));
			cout << "Object added" << endl;
		}
		else
		{
			cout << "Unknown shape type: " << shape << endl;
		}
		cout << "Input object: ";
	}
}

void ProccessAndOutputInfo(const vector<shared_ptr<CBody>> &resVector)
{
	if (resVector.size() == 0)
	{
		return;
	}

	double waterDensity = 1000;
	auto maxMass = resVector[0];
	auto minArchPointer = resVector[0];
	double minArch = (resVector[0]->GetDensity() - waterDensity) * resVector[0]->GetVolume();

	for (const auto &elem : resVector)
	{
		if (maxMass->GetMass() < elem->GetMass())
		{
			maxMass = elem;
		}

		if (minArch > (elem->GetDensity() - waterDensity) * elem->GetVolume())
		{
			minArchPointer = elem;
			minArch = (elem->GetDensity() - waterDensity) * elem->GetVolume();
		}
	}

	cout << endl << "Max mass object info: " << endl;
	cout << maxMass->GetInfo() << endl << endl;

	cout << "Min weight in water: " << endl;
	cout << minArchPointer->GetInfo() << endl << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	vector<shared_ptr<CBody>> objects;

	handlers["cone"] = HandleCone;
	handlers["cylinder"] = HandleCylinder;
	handlers["parallelepiped"] = HandleParallelepiped;
	handlers["sphere"] = HandleSphere;
	handlers["compound"] = HandleCompound;

	HandleUserInput(objects, handlers);
	ProccessAndOutputInfo(objects);

	return 0;
}