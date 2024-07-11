#pragma once

#define PHI0(t) (2.0f * pow(t, 3) - 3.0f * pow(t, 2) + 1.0f)
#define PHI1(t) (pow(t, 3) - 2.0f * pow(t, 2) + t)
#define PSI0(t) (-2.0f * pow(t, 3) + 3.0f * pow(t, 2))
#define PSI1(t) (pow(t, 3) - pow(t, 2))

#include <glm/fwd.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <string>

using namespace glm;
using namespace std;

class Hermite
{
public:
	static vector<vec3> loadPolygonalFromFile(string file);
	static float dx(int i, float* t, float tens, float bias, float cont, vector<vec3> polygonal);
	static float dy(int i, float* t, float tens, float bias, float cont, vector<vec3> polygonal);
	static float DX(int i, float* t, vector<vec3> derivative, vector<vec3> polygonal);
	static float DY(int i, float* t, vector<vec3> derivative, vector<vec3> polygonal);
};

