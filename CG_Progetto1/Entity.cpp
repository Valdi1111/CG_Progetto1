#include "Entity.h"
#include <glm/fwd.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Hermite.h"

#define P_VAL 100

using namespace glm;
using namespace std;

void Entity::initVao(void)
{
	// Genero un VAO
	glGenVertexArrays(1, &this->vao);
	// Ne faccio il bind (lo collego, lo attivo)
	glBindVertexArray(this->vao);

	// Al suo interno genero un VBO
	glGenBuffers(1, &this->vboFigures);
	// Ne faccio il bind (lo collego, lo attivo, assegnandogli il tipo GL_ARRAY_BUFFER)
	glBindBuffer(GL_ARRAY_BUFFER, this->vboFigures);
	// Carico i dati vertices sulla GPU
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(vec3), this->vertices.data(), GL_STATIC_DRAW);
	// Configurazione dell'attributo posizione: informo il vertex shader su: 
	// dove trova le informazioni sulle posizioni e come le deve leggere dal buffer caricato sulla GPU
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);

	//All’interno del VAO genero un VBO per i colori
	glGenBuffers(1, &this->vboColors);
	//Ne faccio il bind (lo collego, lo attivo, assegnandogli il tipo GL_ARRAY_BUFFER)
	glBindBuffer(GL_ARRAY_BUFFER, this->vboColors);
	//Carico i dati vertices sulla GPU
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(vec4), this->colors.data(), GL_STATIC_DRAW);
	// Configurazione dell'attributo Colore: informo il vertex shader su: 
	// dove trova le informazioni sulle posizioni e come le deve leggere dal buffer caricato sulla GPU
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// Scollego il VAO
	glBindVertexArray(0);
}

void Entity::render(ProgramM* mProgram, long time)
{
	mat4 model(1.0);
	model = translate(model, vec3(this->getX() + this->getShiftX(), this->getY() + this->getShiftY(), this->getZ() + this->getShiftZ()));
	model = scale(model, vec3(this->getScaleX(), this->getScaleY(), this->getScaleZ()));
	model = rotate(model, radians(this->getAngle()), vec3(0.0f, 0.0f, 1.0f));
	mat4 view(1.0);

	glUniformMatrix4fv(mProgram->getModelId(), 1, GL_FALSE, value_ptr(model));
	glUniformMatrix4fv(mProgram->getViewId(), 1, GL_FALSE, value_ptr(view));

	glBindVertexArray(this->vao); // Rende attivo il VAO
	this->draw();
}


void Entity::createHermiteShape(vector<vec3> polygonal, vec3 center, vec4 color1, vec4 color2)
{
	float* t = new float[polygonal.size()];
	for (int i = 0; i < polygonal.size(); i++)
	{
		t[i] = (float)i / (float)(polygonal.size() - 1);
	}

	float p_t = 0, p_b = 0, p_c = 0;
	float passotg = 1.0f / (float)(P_VAL - 1);

	int is = 0;

	this->vertices.push_back(center);
	this->colors.push_back(color2);

	vector<vec3> derivative;
	for (int i = 0; i < polygonal.size(); i++)
	{
		derivative.push_back(vec3(0.0f, 0.0f, 0.0f));
	}

	for (float tg = 0.0f; tg <= 1.0f; tg += passotg)
	{
		if (tg > t[is + 1]) {
			is++;
		}
		float ampiezza = (t[is + 1] - t[is]);
		float tgmapp = (tg - t[is]) / ampiezza;

		float x = polygonal[is].x * PHI0(tgmapp) + Hermite::DX(is, t, derivative, polygonal) * PHI1(tgmapp) * ampiezza + polygonal[is + 1].x * PSI0(tgmapp) + Hermite::DX(is + 1, t, derivative, polygonal) * PSI1(tgmapp) * ampiezza;
		float y = polygonal[is].y * PHI0(tgmapp) + Hermite::DY(is, t, derivative, polygonal) * PHI1(tgmapp) * ampiezza + polygonal[is + 1].y * PSI0(tgmapp) + Hermite::DY(is + 1, t, derivative, polygonal) * PSI1(tgmapp) * ampiezza;

		this->vertices.push_back(vec3(x, y, 0.0f));
		this->colors.push_back(color1);
	}
	this->vertices.push_back(polygonal[polygonal.size() - 1]);
	this->colors.push_back(color1);
}
