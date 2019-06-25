#include "Chlorophane.h"

#include <SDL.h>

#include <list>
#include <stack>
#include <math.h>
#include <chrono>
#include <string>
#include <iostream>
#include <Windows.h>

#include "CNE_Time.h"
#include "CNE_Math.h"
#include "CNE_Point.h"
#include "CNE_GameObject.h"
#include "CNE_Enemy_Boss1.h"
#include "CNE_Oscillation.h"
#include "CNE_SlashEffect.h"
#include "CNE_Enemy_Urchin.h"
#include "CNE_Enemy_Folder.h"
#include "CNE_RippleEffect.h"
#include "CNE_VectorBullet.h"
#include "CNE_BulletEmittor.h"
#include "CNE_ParabolicEnemy.h"
#include "CNE_ResourceManager.h"
#include "CNE_TranslatedBullet.h"
#include "CNE_BulletTranslator.h"

using namespace std;
using namespace std::chrono;

Chlorophane::Chlorophane(SDL_Window* w, SDL_Renderer* r, SDL_Surface* s, const int SW, const int SH) {
	window = w;
	renderer = r;
	surface = s;
	SCREEN_WIDTH = SW;
	SCREEN_HEIGHT = SH;
	resetOscillators = false;
	oscillation1 = new CNE_Oscillation(-16, 16, 0, 5, true);
	oscillation2 = new CNE_Oscillation(-16, 16, 0, 5, false);
	manager = new CNE_ResourceManager(w, r);
	bulletTimer = new CNE_Time();
	translator = new CNE_BulletTranslator();
	bulletTimer->start();
	loadResources();
	waveTimer = new CNE_Time();
	playerInvisible = new CNE_Time();
	waveTimer->start();
	
	createObject(240, 400, "player", "d_player_f1", &mainObjects); 
	createObject(320, 240, "sidebar1", "d_bar1", &foregroundObjects);
	createObject(320, 240, "sidebar1", "d_bg1", &backGroundObjects);
	createObject(0, 0, "focusPointer", "d_focus", &mainObjects);
	createObject(0, 0, "focusPointer2", "d_focus", &effectObjects);

	// fly in from top center and dissapear left
	//createParabolicEnemy("e_enemy1", 0, 300, 100, 200, -0.5);

	// fly in from right top center and leave left top center
	//createParabolicEnemy("e_enemy1", 240, 200, 1, 256, -0.05);

	// fly in from right and leave left ( pointing up closing in on player )
	//createParabolicEnemy("e_enemy1", 240, 200, 985, 500, -0.5);
}

void Chlorophane::loadResources() {
	manager->loadSurface("empty", "C:\\Users\\usagi\\Desktop\\c_dev_lib\\assets\\empty.png");
	manager->loadSurface("d_player_f1", "C:\\Users\\usagi\\Desktop\\c_dev_lib\\assets\\player.png");
	manager->loadSurface("d_bullet1", "C:\\Users\\usagi\\Desktop\\c_dev_lib\\assets\\bullet.png");
	manager->loadSurface("d_bullet2", "C:\\Users\\usagi\\Desktop\\c_dev_lib\\assets\\side_bullet.png");
	manager->loadSurface("d_bullet3", "C:\\Users\\usagi\\Desktop\\c_dev_lib\\assets\\bullet2.png");
	manager->loadSurface("d_bullet4", "C:\\Users\\usagi\\Desktop\\c_dev_lib\\assets\\side_bullet2.png");
	manager->loadSurface("d_bar1", "C:\\Users\\usagi\\Desktop\\c_dev_lib\\assets\\sidebar.png"); 
	manager->loadSurface("e_bullet1", "C:\\Users\\usagi\\Desktop\\c_dev_lib\\assets\\e_bullet1.png");
	manager->loadSurface("e_bullet2", "C:\\Users\\usagi\\Desktop\\c_dev_lib\\assets\\e_bullet2.png");
	manager->loadSurface("e_bullet3", "C:\\Users\\usagi\\Desktop\\c_dev_lib\\assets\\e_bullet3.png");
	manager->loadSurface("e_enemy1", "C:\\Users\\usagi\\Desktop\\c_dev_lib\\assets\\enemy.png"); 
	manager->loadSurface("e_paper1", "C:\\Users\\usagi\\Desktop\\c_dev_lib\\assets\\paper1.png");
	manager->loadSurface("e_paper2", "C:\\Users\\usagi\\Desktop\\c_dev_lib\\assets\\paper2.png");
	manager->loadSurface("e_paper3", "C:\\Users\\usagi\\Desktop\\c_dev_lib\\assets\\paper3.png");
	manager->loadSurface("d_bg1", "C:\\Users\\usagi\\Desktop\\c_dev_lib\\assets\\background.png"); 
	manager->loadSurface("d_focus", "C:\\Users\\usagi\\Desktop\\c_dev_lib\\assets\\focusPoint.png");
	manager->loadSurface("d_ping", "C:\\Users\\usagi\\Desktop\\c_dev_lib\\assets\\ping.png");
	manager->loadSurface("e_boss1", "C:\\Users\\usagi\\Desktop\\c_dev_lib\\assets\\boss1.png");
}

int Chlorophane::update(SDL_Event* ptr_event) {

	//if (playerInvisible->getTime().count() > 5000000) {
	//	return 1; // tell testing caller to restar chlorophane ( and the game subsequently ) 
	//}

	if (updateCount % 100 == 0 && deltaUpdateCount != 0) {
		microseconds ms = duration_cast<microseconds>(system_clock::now().time_since_epoch());
		long delta = ms.count() - lastTimeSync.count();
		loopTimeRatio = delta / deltaUpdateCount;
		deltaUpdateCount = 0;
		lastTimeSync = duration_cast<microseconds>(system_clock::now().time_since_epoch());
	}
	lastUpdateDelta = lastUpdateEnd.count() - lastUpdateStart.count();
	lastUpdateStart = duration_cast<microseconds>(system_clock::now().time_since_epoch());
	SDL_Event event = *ptr_event;
	if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
		int key;
		key = (int)event.key.keysym.sym;
		if (!keyRegistered(key)) {
			keyStates.insert(make_pair(key, false));
		}
		if (event.type == SDL_KEYDOWN && !keyStates[key]) {
			keyStates[key] = true;
		}
		if (event.type == SDL_KEYUP && keyStates[key]) {
			keyStates[key] = false;
		}
	}

	processKeyboardInput();

	gameWaves();

	while (translator->hasNextBullet()) {
		CNE_TranslatedBullet* ptr_tb = translator->getNextBullet();
		createVectorBullet(ptr_tb->x, ptr_tb->y, ptr_tb->vector, "bullet", ptr_tb->id);
		delete ptr_tb;
	}

	list<CNE_GameObject*>::iterator it;
	for (it = backGroundObjects.begin(); it != backGroundObjects.end(); it++) {
		CNE_GameObject* ptr_cur = *it;
		if ((ptr_cur->destoryOffScreen && !isVisibleOnScreen(ptr_cur)) || ptr_cur->garbage) {
			garbageArray.push(ptr_cur);
		} else {
			ptr_cur->draw(lastUpdateDelta);
			ptr_cur->update(lastUpdateDelta);
		}
	}
	while (!garbageArray.empty()) {
		CNE_GameObject* ptr_rem = garbageArray.top();
		garbageArray.pop();
		backGroundObjects.remove(ptr_rem);
		delete ptr_rem;
	}

	for (it = mainObjects.begin(); it != mainObjects.end(); it++) {
		CNE_GameObject* ptr_cur = *it;
		if ((ptr_cur->destoryOffScreen && !isVisibleOnScreen(ptr_cur)) || ptr_cur->garbage) {
			garbageArray.push(ptr_cur);
		}
		else {
			ptr_cur->draw(lastUpdateDelta);
			ptr_cur->update(lastUpdateDelta);

			if (ptr_cur->resourceId == "player" || ptr_cur->resourceId == "playerBullet" ) {
				list<CNE_GameObject*>::iterator it2;
				for (it2 = mainObjects.begin(); it2 != mainObjects.end(); it2++) {
					CNE_GameObject* o = *it2;
					if (o->id == ptr_cur->id || (o->resourceId != "enemyBullet" && o->resourceId != "enemy") || sqrt(pow(o->x - ptr_cur->x, 2) + pow(o->y - ptr_cur->y, 2)) > 100) {
						continue;
					}
					CNE_Math* math = new CNE_Math();
					bool collides = math->rectOverlap(ptr_cur->x, ptr_cur->y, ptr_cur->w, ptr_cur->h, o->x, o->y, o->w, o->h);
					if (collides) {
						if (ptr_cur->resourceId == "player" && o->resourceId == "enemyBullet" &&  ptr_cur->visible) {
							createRippleEffect(ptr_cur->x+10, ptr_cur->y, 0.5);
							createRippleEffect(ptr_cur->x, ptr_cur->y+10, 0.5);
							createRippleEffect(ptr_cur->x-10, ptr_cur->y, 0.5);
							createRippleEffect(ptr_cur->x, ptr_cur->y-10, 0.5); 
							getObjectByAlias("player")->visible = false;
							getObjectByAlias("focusPointer2")->visible = false;
							ptr_cur->visible = false;
							playerInvisible->start();
						}
						else if (ptr_cur->resourceId == "playerBullet" && o->resourceId == "enemy") {
							ptr_cur->garbage = true;
							o->health -= 10;
							createSlashEffect(o->x, o->y, "e_bullet1", -20, 20, 1);
							createSlashEffect(o->x, o->y, "e_bullet1", -40, 40, 2);
							createSlashEffect(o->x, o->y, "e_bullet1", -60, 60, 3);
							if (o->health < 0) {
								o->garbage = true;
								createRippleEffect(o->x, o->y, 1);
							}
						}
					}
					delete math;
				}
			}
		}
	}
	while (!garbageArray.empty()) {
		CNE_GameObject* ptr_rem = garbageArray.top();
		//cout << "deleting: #@" << ptr_rem << "\n";
		garbageArray.pop();
		mainObjects.remove(ptr_rem);
		delete ptr_rem;
	}

	for (it = effectObjects.begin(); it != effectObjects.end(); it++) {
		CNE_GameObject* ptr_cur = *it;
		if ((ptr_cur->destoryOffScreen && !isVisibleOnScreen(ptr_cur)) || ptr_cur->garbage) {
			garbageArray.push(ptr_cur);
		}
		else {
			ptr_cur->draw(lastUpdateDelta);
			ptr_cur->update(lastUpdateDelta);
		}
	}
	while (!garbageArray.empty()) {
		CNE_GameObject* ptr_rem = garbageArray.top();
		//cout << "deleting: #@" << ptr_rem << "\n";
		garbageArray.pop();
		effectObjects.remove(ptr_rem);
		delete ptr_rem;
	}

	for (it = foregroundObjects.begin(); it != foregroundObjects.end(); it++) {
		CNE_GameObject* ptr_cur = *it;
		if ((ptr_cur->destoryOffScreen && !isVisibleOnScreen(ptr_cur)) || ptr_cur->garbage) {
			garbageArray.push(ptr_cur);
		}
		else {
			ptr_cur->draw(lastUpdateDelta);
			ptr_cur->update(lastUpdateDelta);
		}
	}
	while (!garbageArray.empty()) {
		CNE_GameObject* ptr_rem = garbageArray.top();
		garbageArray.pop();
		foregroundObjects.remove(ptr_rem);
		delete ptr_rem;
	}
	lastUpdateEnd = duration_cast<microseconds>(system_clock::now().time_since_epoch());
	updateCount++;
	deltaUpdateCount++;
	const float updateTime = 10;
	long ms = (lastUpdateEnd.count() - lastUpdateStart.count()) / 1000.0;
	float sleepTime = 10 - ms;
	sleepTime = sleepTime < 0 ? 0 : sleepTime;
	Sleep(sleepTime);
	return 0;
}

bool Chlorophane::isKeyDown(int key) {
	if (keyRegistered(key)) {
		return keyStates[key];
	}
	return false;
}

bool Chlorophane::keyRegistered(int key) {
	map<int, bool>::iterator it;
	for (it = keyStates.begin(); it != keyStates.end(); it++) {
		if (it->first == key) {
			return true;
		}
	}
	return false;
}
 
bool Chlorophane::isVisibleOnScreen(CNE_GameObject* ptr_obj) {
	bool diag1 = isPointOnSceen(ptr_obj->x, ptr_obj->y) || isPointOnSceen(ptr_obj->x+ptr_obj->w, ptr_obj->y+ptr_obj->h);
	bool diag2 = isPointOnSceen(ptr_obj->x + ptr_obj->w, ptr_obj->y) || isPointOnSceen(ptr_obj->x, ptr_obj->y + ptr_obj->h);
	return diag1 || diag2;
}

bool Chlorophane::isPointOnSceen(float x, float y) {
	return x >= 0 && y >= 0 && x < SCREEN_HEIGHT && y < SCREEN_HEIGHT;
}

void Chlorophane::processKeyboardInput() {
	CNE_GameObject* focusPointer = getObjectByAlias("focusPointer");
	CNE_GameObject* focusPointer2 = getObjectByAlias("focusPointer2");
	CNE_GameObject* player = getObjectByAlias("player");
	focusPointer->resourceId = "player";
	float speed = 4;
	bool focused = false;
	if (player != NULL && player->visible) {
		if (isKeyDown(SDLK_LSHIFT)) {
			focused = true;
			focusPointer->opacity = 255;
			focusPointer2->opacity = 255;
			player->opacity = 100;
			speed = 1.3;
		} else {
			focused = false;
			focusPointer->opacity = 90;
			focusPointer2->opacity = 90;
			player->opacity = 255;
		}
		if (isKeyDown(SDLK_UP)) {
			player->y -= speed;
		}
		if (isKeyDown(SDLK_RIGHT)) {
			player->x += speed;
		}
		if (isKeyDown(SDLK_LEFT)) {
			player->x -= speed;
		}
		if (isKeyDown(SDLK_DOWN)) {
			player->y += speed;
		}
		if (isKeyDown(SDLK_z)) {
			if (bulletTimer->getTime().count() < 50000) {
				// bullet is not fired 
			} else {
				bulletTimer->stop();
				// fire the bullet 
				if (focused) {
					if (resetOscillators) {
						oscillation1->current = 0;
						oscillation2->current = 0;
						resetOscillators = false;
					}
					oscillation1->update();
					oscillation2->update();
					CNE_Point* p1 = new CNE_Point(0, 0);
					CNE_Point* p2 = new CNE_Point(0, 1000);
					CNE_Vector* ptr_vec = createTimedPointToPointVector(p1, p2, 50000);
					CNE_Vector* ptr_vec2 = createTimedPointToPointVector(p1, p2, 50000);
					CNE_Vector* ptr_vec3 = createTimedPointToPointVector(p1, p2, 50000);
					createVectorBullet(player->x, player->y, ptr_vec, "p_bullet", "d_bullet3")->resourceId = "playerBullet";
					createVectorBullet(player->x + oscillation1->current, player->y, ptr_vec2, "p_bullet", "d_bullet2")->resourceId = "playerBullet";
					createVectorBullet(player->x + oscillation2->current, player->y, ptr_vec3, "p_bullet", "d_bullet4")->resourceId = "playerBullet";
					delete p1;
					delete p2;
				} else {
					CNE_Point* p1 = new CNE_Point(0, 0);
					CNE_Point* p2 = new CNE_Point(0, 1000);
					CNE_Point* p3 = new CNE_Point(500, 1000);
					CNE_Point* p4 = new CNE_Point(-500, 1000);
					CNE_Vector* ptr_vec = createTimedPointToPointVector(p1, p2, 50000);
					CNE_Vector* ptr_vec2 = createTimedPointToPointVector(p1, p3, 50000);
					CNE_Vector* ptr_vec3 = createTimedPointToPointVector(p1, p4, 50000);
					createVectorBullet(player->x, player->y, ptr_vec, "p_bullet", "d_bullet1")->resourceId = "playerBullet";
					createVectorBullet(player->x, player->y, ptr_vec2, "p_bullet", "d_bullet2")->resourceId = "playerBullet";
					createVectorBullet(player->x, player->y, ptr_vec3, "p_bullet", "d_bullet2")->resourceId = "playerBullet";
					delete p1;
					delete p2;
					delete p3;
					delete p4;
					resetOscillators = true;
				}
				bulletTimer->reset();
				bulletTimer->start();
			}
		}

		focusPointer->x = player->x;
		focusPointer->y = player->y;
		focusPointer2->x = player->x;
		focusPointer2->y = player->y;
	}
	focusPointer->w = 6;
	focusPointer->h = 6;
	focusPointer2->w = 6;
	focusPointer2->h = 6;
}

void Chlorophane::gameWaves() {
	if (currentWave == 0 && waveTimer->getTime().count() > 3000000) {
		waveFinished("pause wave finished.");
		createEnemyPaper(LCT_LS, 0.5)->health = 10;
		createEnemyPaper(RCT_RS, 0.5)->health = 10;
		return;
	}
	if (currentWave == 1 && waveTimer->getTime().count() > 4000000) {
		waveFinished("first attack wave finished.");
		createEnemyFolder(LCT_LS, 0.5);
		createEnemyPaper(LCT_LS, 0.6)->health = 30;
		createEnemyFolder(RCT_RS, 0.5);
		createEnemyPaper(RCT_RS, 0.6)->health = 30;
		createEnemyPaper(LCT_LS_L, 0.5)->health = 30;
		createEnemyPaper(LCT_LS_L, 0.6)->health = 30;
		createEnemyPaper(RCT_RS_L, 0.5)->health = 30;
		createEnemyPaper(RCT_RS_L, 0.6)->health = 30;
		return;
	}
	if (currentWave == 2 && waveTimer->getTime().count() > 4000000) {
		waveFinished("second attack wave finished.");
		for (int i = 0; i < 6; i++) {
			createEnemyPaper(LT_RS_L, 0.6+0.1*i)->health = 40;
			createEnemyPaper(RT_LS_L, 0.6+0.1*i)->health = 40;
		}
		createEnemyUrchin(LT_RS_L, 5, 1.3);
		createEnemyUrchin(RT_LS_L, 5, 1.3);
		return;
	}
	if (currentWave == 3 && waveTimer->getTime().count() > 5000000) {
		waveFinished("third attack wave finished.");
		for (int i = 0; i < 10; i++) {
			if (i % 2 == 0) {
				createEnemyPaper(LCT_LS_L, 0.2 + 0.05*i)->health = 50;
			}
			else {
				createEnemyUrchin(LCT_LS_L, 7, 0.2 + 0.05*i);
			}
		}
		return;
	}
	if (currentWave == 4 && waveTimer->getTime().count() > 3000000) {
		waveFinished("continuation of fouth attack wave ...");
		for (int i = 0; i < 10; i++) {
			if (i % 2 == 1) {
				createEnemyPaper(RCT_RS_L, 0.2 + 0.05*i)->health = 50;
			}
			else {
				createEnemyUrchin(RCT_RS_L, 7, 0.2 + 0.05*i);
			}
		}
		return;
	}
	if (currentWave == 5 && waveTimer->getTime().count() > 3000000) {
		waveFinished("fifth wave finished.");
		createEnemyBoss1();
		return;
	}
	if (currentWave == 6 && waveTimer->getTime().count() > 25000000) {
		waveFinished("boss wave finished.");
		for (int i = 0; i < 5; i++) {
			createEnemyUrchin(LT_RS_L, 5, 0.2 + 0.05*i);
			createEnemyUrchin(RT_LS_L, 5, 0.2 + 0.05*i);
		}
		return;
	}
	if (currentWave == 7 && waveTimer->getTime().count() > 4000000) {
		waveFinished("seventh wave finished.");
		createEnemyFolder(LCT_LS, 0.2);
		createEnemyFolder(RCT_RS, 0.2);
		createEnemyFolder(LCT_LS, 0.4);
		createEnemyFolder(RCT_RS, 0.4);
		for (int i = 0; i < 7; i++) {
			createEnemyPaper(LT_RS_L, 0.1 + 0.05*i);
			createEnemyPaper(RT_LS_L, 0.1 + 0.05*i);
		}
		return;
	}
	if (currentWave == 8 && waveTimer->getTime().count() > 5000000) {
		waveFinished("eighth wave finished.");
		createEnemyUrchin(RS_LS_L, 10, 2);
		createEnemyUrchin(RS_LS_L, 10, 2.1);
		createEnemyUrchin(RS_LS_L, 10, 2.2);
		createEnemyFolder(RC_LC_H, 0.05);
		createEnemyFolder(LC_RC_H, 0.05);
		for (int i = 0; i < 10; i++) {
			if (i % 2 == 0) {
				createEnemyUrchin(LT_RS_L, 5, 0.1 + 0.05*i);
			} else {
				createEnemyPaper(LT_RS_L, 0.1 + 0.05*i);
			}
		}
		return;
	}
}

void Chlorophane::waveFinished(string message) {
	cout << "[ " << currentWave << " ] " << message << "\n";
	currentWave++;
	waveTimer->stop();
	waveTimer->reset();
	waveTimer->start();
	return;
}

CNE_Vector* Chlorophane::createTimedPointToPointVector(CNE_Point* p1, CNE_Point* p2, long ms) {
	float distance = p1->distanceTo(p2);
	float updatesForMovement = ms / 1000;
	float dx = p1->x - p2->x;
	float dy = p1->y - p2->y;
	return new CNE_Vector(dx / updatesForMovement, dy / updatesForMovement);
}

CNE_GameObject* Chlorophane::getObjectByAlias(string alias) {
	list<CNE_GameObject*>::iterator it;
	for (it = backGroundObjects.begin(); it != backGroundObjects.end(); it++) {
		CNE_GameObject* ptr_cur = *it;
		if (ptr_cur->alias == alias) {
			return ptr_cur;
		}
	}
	for (it = mainObjects.begin(); it != mainObjects.end(); it++) {
		CNE_GameObject* ptr_cur = *it;
		if (ptr_cur->alias == alias) {
			return ptr_cur;
		}
	}
	for (it = effectObjects.begin(); it != effectObjects.end(); it++) {
		CNE_GameObject* ptr_cur = *it;
		if (ptr_cur->alias == alias) {
			return ptr_cur;
		}
	}
	for (it = foregroundObjects.begin(); it != foregroundObjects.end(); it++) {
		CNE_GameObject* ptr_cur = *it;
		if (ptr_cur->alias == alias) {
			return ptr_cur;
		}
	}
	return NULL;
}

CNE_ParabolicEnemy* Chlorophane::createParabolicEnemy(string id, float parX, float parY, float parScal, float parStartX, float parDelta) {
	CNE_ParabolicEnemy* ptr_pe = new CNE_ParabolicEnemy(0, 0, id, parX, parY, parScal, parStartX, parDelta, manager);
	mainObjects.push_front(ptr_pe);
	return ptr_pe;
}

CNE_VectorBullet* Chlorophane::createVectorBullet(int x, int y, CNE_Vector* vec, string alias, string id) {
	CNE_VectorBullet* ptr_vb = new CNE_VectorBullet(x, y, vec, alias, id, manager);
	ptr_vb->destoryOffScreen = true;
	mainObjects.push_front(ptr_vb);
	return ptr_vb;
}

CNE_SlashEffect* Chlorophane::createSlashEffect(int x, int y, string id, float min, float max, float delta) {
	CNE_SlashEffect* ptr_se = new CNE_SlashEffect(x, y, id, min, max, delta, manager);
	effectObjects.push_front(ptr_se);
	return ptr_se;
}

CNE_RippleEffect* Chlorophane::createRippleEffect(int x, int y, float speed) {
	CNE_RippleEffect* ptr_re = new CNE_RippleEffect(x, y, speed, manager);
	effectObjects.push_front(ptr_re);
	return ptr_re;
}

CNE_GameObject* Chlorophane::createObject(int x, int y, string alias, string id, list<CNE_GameObject*>* toAdd) {
	CNE_GameObject* ptr_obj = new CNE_GameObject(x, y, alias, id, manager);
	toAdd->push_front(ptr_obj);
	return ptr_obj;
}

CNE_Enemy_Paper* Chlorophane::createEnemyPaper(string pattern, float speed) {
	CNE_Enemy_Paper* ptr_e_p = new CNE_Enemy_Paper(translator, getObjectByAlias("player"), pattern, speed, manager);
	mainObjects.push_front(ptr_e_p);
	return ptr_e_p;
}

CNE_Enemy_Folder* Chlorophane::createEnemyFolder(string pattern, float speed) {
	CNE_Enemy_Folder* ptr_e_f = new CNE_Enemy_Folder(translator, pattern, speed, manager);
	mainObjects.push_front(ptr_e_f);
	return ptr_e_f;
}

CNE_Enemy_Urchin* Chlorophane::createEnemyUrchin(string pattern, int count, float speed) {
	CNE_Enemy_Urchin* ptr_e_u = new CNE_Enemy_Urchin(translator, pattern, count, speed, manager);
	mainObjects.push_front(ptr_e_u);
	return ptr_e_u;
}

CNE_Enemy_Boss1* Chlorophane::createEnemyBoss1() {
	CNE_Enemy_Boss1* ptr_boss = new CNE_Enemy_Boss1(translator, manager);
	mainObjects.push_front(ptr_boss);
	return ptr_boss;
}
 
Chlorophane::~Chlorophane() {
	delete translator;
	delete waveTimer;
	delete playerInvisible;
	delete bulletTimer;
	delete oscillation1;
	delete oscillation2;
	delete focusOscillation;
}