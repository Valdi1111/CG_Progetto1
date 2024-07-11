#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "ProgramM.h"

using namespace glm;
using namespace std;

class Entity
{
protected:
	bool removeNext = false;
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float shiftX = 0.0f;
	float shiftY = 0.0f;
	float shiftZ = 0.0f;
	float scaleX = 1.0f;
	float scaleY = 1.0f;
	float scaleZ = 1.0f;
	float angle = 0.0f;
	unsigned int vao;
	unsigned int vboFigures;
	unsigned int vboColors;
	vector<vec3> vertices;
	vector<vec4> colors;
	vector<vec3> cpVertices;
	vector<vec4> cpColors;

	void initVao(void);
	virtual void draw(void) = 0;
	void createHermiteShape(vector<vec3> controlPoints, vec3 center, vec4 color1, vec4 color2);

public:
	Entity() {}

	bool isRemoveNext() const { return this->removeNext; }
	void setRemoveNext() { this->removeNext = true; }

	float getX() const { return this->x; }
	float getY() const { return this->y; }
	float getZ() const { return this->z; }

	void setX(float x) { this->x = x;  }
	void setY(float y) { this->y = y;  }
	void setZ(float z) { this->z = z;  }

	void addX(float x) { this->x += x; }
	void addY(float y) { this->y += y; }
	void addZ(float z) { this->z += z; }

	float getScaleX() const { return this->scaleX; }
	float getScaleY() const { return this->scaleY; }
	float getScaleZ() const { return this->scaleZ; }

	void setScaleX(float scaleX) { this->scaleX = scaleX; }
	void setScaleY(float scaleY) { this->scaleY = scaleY; }
	void setScaleZ(float scaleZ) { this->scaleZ = scaleZ; }

	float getShiftX() const { return this->shiftX; }
	float getShiftY() const { return this->shiftY; }
	float getShiftZ() const { return this->shiftZ; }

	void setShiftX(float shiftX) { this->shiftX = shiftX; }
	void setShiftY(float shiftY) { this->shiftY = shiftY; }
	void setShiftZ(float shiftZ) { this->shiftZ = shiftZ; }

	float getAngle() const { return this->angle; }
	void setAngle(float angle) { this->angle = angle; }

	virtual void initAll(void) = 0;
	void render(ProgramM* mProgram, long time);
	virtual void tick(int time) = 0;
};

