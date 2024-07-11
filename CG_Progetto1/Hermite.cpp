#include "Hermite.h"
#include <fstream>
#include <iostream>
#include <sstream>

vector<vec3> Hermite::loadPolygonalFromFile(string filename)
{
	vector<vec3> polygonal;
	ifstream inputFile(filename);

	if (!inputFile.is_open()) {
		cerr << "Errore nell'apertura del file " << filename << endl;
		return polygonal;
	}

	string line;
	while (getline(inputFile, line)) {
		stringstream ss(line);
		float x, y, z;
		ss >> x >> y >> z;
		polygonal.push_back(vec3(x, y, z));
	}

	inputFile.close();
	return polygonal;
}

float Hermite::dx(int i, float* t, float tens, float bias, float cont, vector<vec3> polygonal)
{
	if (i == 0)
		return 0.5 * (1.0 - tens) * (1.0 - bias) * (1.0 - cont) * (polygonal[i + 1].x - polygonal[i].x) / (t[i + 1] - t[i]);
	if (i == polygonal.size() - 1)
		return 0.5 * (1.0 - tens) * (1.0 - bias) * (1.0 - cont) * (polygonal[i].x - polygonal[i - 1].x) / (t[i] - t[i - 1]);

	if (i % 2 == 0)
		return 0.5 * (1.0 - tens) * (1.0 + bias) * (1.0 + cont) * (polygonal.at(i).x - polygonal.at(i - 1.0).x) / (t[i] - t[i - 1]) + 0.5 * (1.0 - tens) * (1.0 - bias) * (1.0 - cont) * (polygonal.at(i + 1).x - polygonal.at(i).x) / (t[i + 1] - t[i]);
	else
		return 0.5 * (1.0 - tens) * (1.0 + bias) * (1.0 - cont) * (polygonal.at(i).x - polygonal.at(i - 1.0).x) / (t[i] - t[i - 1]) + 0.5 * (1.0 - tens) * (1.0 - bias) * (1.0 + cont) * (polygonal.at(i + 1).x - polygonal.at(i).x) / (t[i + 1] - t[i]);
}

float Hermite::dy(int i, float* t, float tens, float bias, float cont, vector<vec3> polygonal)
{
	if (i == 0)
		return 0.5 * (1.0 - tens) * (1.0 - bias) * (1.0 - cont) * (polygonal.at(i + 1).y - polygonal.at(i).y) / (t[i + 1] - t[i]);
	if (i == polygonal.size() - 1)
		return 0.5 * (1.0 - tens) * (1.0 - bias) * (1.0 - cont) * (polygonal.at(i).y - polygonal.at(i - 1.0).y) / (t[i] - t[i - 1]);

	if (i % 2 == 0)
		return 0.5 * (1.0 - tens) * (1.0 + bias) * (1.0 + cont) * (polygonal.at(i).y - polygonal.at(i - 1.0).y) / (t[i] - t[i - 1]) + 0.5 * (1.0 - tens) * (1.0 - bias) * (1.0 - cont) * (polygonal.at(i + 1).y - polygonal.at(i).y) / (t[i + 1] - t[i]);
	else
		return 0.5 * (1.0 - tens) * (1.0 + bias) * (1.0 - cont) * (polygonal.at(i).y - polygonal.at(i - 1.0).y) / (t[i] - t[i - 1]) + 0.5 * (1.0 - tens) * (1.0 - bias) * (1.0 + cont) * (polygonal.at(i + 1).y - polygonal.at(i).y) / (t[i + 1] - t[i]);
}

float Hermite::DX(int i, float* t, vector<vec3> derivative, vector<vec3> polygonal)
{
	if (derivative.at(i).x == 0)
		return dx(i, t, 0.0f, 0.0f, 0.0f, polygonal);
	if (derivative.at(i).x != 0)
		return derivative.at(i).x;
}

float Hermite::DY(int i, float* t, vector<vec3> derivative, vector<vec3> polygonal)
{
	if (derivative.at(i).y == 0)
		return dy(i, t, 0.0f, 0.0f, 0.0f, polygonal);
	if (derivative.at(i).y != 0)
		return derivative.at(i).y;
}