// CG_Progetto2.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//
#define GLM_ENABLE_EXPERIMENTAL 1
#define TICK_TIME 10

#define POINTS_PER_ENEMY 50
#define ENEMY_SPAWN_INTERVAL 3000
#define DELTA_MOVE_PLAYER 2.5
#define DELTA_MOVE_PROJECTILE 2
#define DELTA_MOVE_ENEMY 2

#include <ctime>
#include <cstdlib> 
#include <ctime> 
#include <iostream>
#include <map>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ProgramText.h"
#include "ProgramM.h"
#include "Hermite.h"
#include "Window.h"
#include "Hearth.h"
#include "Background.h"
#include "Projectile.h"
#include "Player.h"
#include "Enemy.h"

using namespace glm;
using namespace std;

ProgramText* textProgram = new ProgramText();
ProgramM* mProgram = new ProgramM();

Background* background;
Player* player;
vector<Hearth*> playerLives;
vector<Projectile*> projectiles;
vector<Enemy*> enemies;
map<int, bool> keys;

vector<vec3> asteroidPolygonal;
vector<vec3> spaceshipPolygonal;

bool isGameOver() {
	return player->isDead();
}

void createEntities(void)
{
	asteroidPolygonal = Hermite::loadPolygonalFromFile("resources/asteroid.txt");
	spaceshipPolygonal = Hermite::loadPolygonalFromFile("resources/spaceship.txt");

	background = new Background(2.0, 2.0);
	background->setX(Window::getWidth() / 2);
	background->setY(Window::getHeight() / 2);
	background->setScaleX(Window::getWidth());
	background->setScaleY(Window::getHeight());

	player = new Player(spaceshipPolygonal);
	player->setX(Window::getWidth() / 6);
	player->setY(Window::getHeight() / 2);

	for (int i = 0; i < Player::getMaxLives(); i++)
	{
		Hearth* h = new Hearth(1, 1, 25);
		h->setX(25 + (i * 35));
		h->setY(Window::getHeight() - 20);
		playerLives.push_back(h);
	}
}

void initAll(void)
{
	textProgram->initFreeType();
	textProgram->initProgram("vertexShaderText.glsl", "fragmentShaderText.glsl");
	textProgram->initUniforms();
	textProgram->initVao();
	mProgram->initProgram("vertexShaderM.glsl", "fragmentShaderM.glsl");
	mProgram->initUniforms();
	background->initAll();
	player->initAll();
	for (Hearth* h : playerLives)
	{
		h->initAll();
	}
}

long lastEnemySpawn = 0;
void tick(int _) {
	long now = glutGet(GLUT_ELAPSED_TIME);
	glutTimerFunc(TICK_TIME, tick, 0);

	if (isGameOver()) {
		glutPostRedisplay();
		return;
	}

	if (now - lastEnemySpawn > ENEMY_SPAWN_INTERVAL) {
		lastEnemySpawn = now;
		Enemy* e = new Enemy(asteroidPolygonal);
		e->setX(Window::getWidth() + 50);
		e->setY(30 + rand() % int(Window::getHeight() - 60));
		e->setDx(-DELTA_MOVE_ENEMY);
		e->initAll();
		enemies.push_back(e);
	}

	for (auto it = enemies.begin(); it != enemies.end(); ) {
		Enemy* e = (*it);
		if (e->isRemoveNext()) {
			it = enemies.erase(it);
			continue;
		}
		e->tick(now);
		if(e->collidesWith(player)) {
			player->decreaseLives();
			e->setRemoveNext();
		}
		++it;
	}
	for (auto it = projectiles.begin(); it != projectiles.end(); ) {
		Projectile* p = (*it);
		if (p->isRemoveNext()) {
			it = projectiles.erase(it);
			continue;
		}
		p->tick(now);
		for (Enemy* e : enemies)
		{
			if (p->collidesWith(e)) {
				player->addPoints(POINTS_PER_ENEMY);
				p->setRemoveNext();
				e->setRemoveNext();
			}
		}
		++it;
	}
	player->tick(now);

	// Movimento del player
	float dx = 0;
	float dy = 0;
	if (keys['w']) {
		dy += DELTA_MOVE_PLAYER;
	}
	if (keys['s']) {
		dy -= DELTA_MOVE_PLAYER;
	}
	if (keys['d']) {
		dx += DELTA_MOVE_PLAYER;
	}
	if (keys['a']) {
		dx -= DELTA_MOVE_PLAYER;
	}
	player->setDx(dx);
	player->setDy(dy);

	glutPostRedisplay();
}

void drawScene(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	long now = glutGet(GLUT_ELAPSED_TIME);

	mat4 projection = ortho(0.0f, Window::getAspectWidth(), 0.0f, Window::getAspectHeight());
	mProgram->switchProgram(projection);
	glUniform2f(mProgram->getResolutionId(), Window::getAspectWidth(), Window::getAspectHeight());
	glUniform1f(mProgram->getTimeId(), now / 1000.0f);

	glUniform1i(mProgram->getIsBackgroundShaderId(), 1);
	background->render(mProgram, now);

	glUniform1i(mProgram->getIsBackgroundShaderId(), 0);
	for (Enemy* e : enemies)
	{
		e->render(mProgram, now);
	}
	for (Projectile* p : projectiles)
	{
		p->render(mProgram, now);
	}
	player->render(mProgram, now);
	for (int i = 0; i < player->getLives(); i++)
	{
		playerLives[i]->render(mProgram, now);
	}
	textProgram->switchProgram(projection);
	if (isGameOver()) {
		string over = "GAME OVER";
		textProgram->renderText(over, Window::getWidth() / 2 - over.length() * 15.0f, Window::getHeight() / 2, 1.0f, vec3(1.0f, 0.0f, 0.0f));
	}
	string str = to_string(player->getPoints()) + " points";
	textProgram->renderText(str, Window::getWidth() - str.length() * 12.0f, Window::getHeight() - 25.0f, 0.5f, vec3(1.0f, 0.5f, 0.0f));
	glutSwapBuffers(); //swap tra il frame buffer front e back durante un’animazione
}

void reshapeScene(int w, int h)
{
	float aspectRatio = Window::getAspectWidth() / Window::getAspectHeight(); // Rapporto larghezza altezza di tutto ciò che è nel mondo
	// Se l'aspect ratio del mondo   diversa da quella della finestra devo mappare in modo diverso per evitare distorsioni del disegno
	if (aspectRatio > w / h)   //Se ridimensioniamo la larghezza della Viewport
	{
		glViewport(0, 0, w, w / aspectRatio);
		Window::setWidth(w);
		Window::setHeight(w / aspectRatio);
	}
	// Se ridimensioniamo la larghezza della viewport oppure se l'aspect ratio tra la finestra del mondo e la finestra sullo schermo sono uguali
	else {  
		glViewport(0, 0, h * aspectRatio, h);
		Window::setWidth(h * aspectRatio);
		Window::setHeight(h);
	}
}
void keyboardHandler(unsigned char key, int x, int y)
{
	keys[key] = true;
	if (!isGameOver() && key == ' ') {
		long now = glutGet(GLUT_ELAPSED_TIME);
		if (now - player->getLastShotTime() < player->getShotCooldown()) {
			return;
		}

		Projectile* e = new Projectile(10, 25);
		e->setX(player->getX() + 100);
		e->setY(player->getY());
		e->setDx(DELTA_MOVE_PROJECTILE);
		e->initAll();
		projectiles.push_back(e);
		player->setLastShotTime(now);
	}
}

void keyboardUpHandler(unsigned char key, int x, int y)
{
	keys[key] = false;
}

int main(int argc, char* argv[])
{
	srand(time(0));
	glutInit(&argc, argv);

	glutInitContextVersion(4, 0);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(Window::getWidth(), Window::getHeight());
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Progetto 1 CG");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glViewport(0.0, 0.0, Window::getWidth(), Window::getHeight());
	glutDisplayFunc(drawScene);
	glutReshapeFunc(reshapeScene);
	glutKeyboardFunc(keyboardHandler);
	glutKeyboardUpFunc(keyboardUpHandler);

	glewExperimental = GL_TRUE;
	glewInit(); // Inizializza l’estensione utilizzata

	createEntities();
	initAll();
	tick(0);
	
	glutMainLoop();
	return 0;
}