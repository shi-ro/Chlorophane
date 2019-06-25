#pragma once
#include <SDL.h>
#include <map>
#include <list>
#include <stack>
#include <chrono>
#include <string>

#include "CNE_Time.h"
#include "CNE_Point.h"
#include "CNE_Vector.h"
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

#include "CNE_Enemy_Paper.h"

using namespace std;
using namespace std::chrono;

class Chlorophane
{
	const string LCT_LS = "leftCenterTop-leftSide";
	const string RCT_RS = "rightCenterTop-rightSide";
	const string LCT_LS_L = "leftCenterTop-leftSide-low";
	const string RCT_RS_L = "rightCenterTop-rightSide-low";
	const string LT_RS_L = "leftTop-rightSide-low";
	const string RT_LS_L = "rightTop-leftSide-low";
	const string LS_RS_H = "leftSide-rightSide-high";
	const string RS_LS_H = "rightSide-leftSide-high";
	const string LS_RS_L = "leftSide-rightSide-low";
	const string RS_LS_L = "rightSide-leftSide-low";
	const string LC_RC_H = "leftCenter-rightCenter-high";
	const string RC_LC_H = "rightCenter-leftCenter-high";
	const string LC_RC_L = "leftCenter-rightCenter-low";
	const string RC_LC_L = "rightCenter-leftCenter-low";

	CNE_BulletTranslator* translator;
	stack<CNE_GameObject*> garbageArray;
	list<CNE_GameObject*> backGroundObjects;
	list<CNE_GameObject*> mainObjects;
	list<CNE_GameObject*> effectObjects;
	list<CNE_GameObject*> foregroundObjects;
	bool resetOscillators;

	int currentWave = 0;
	CNE_Time* waveTimer;

	CNE_Time* playerInvisible;
	
	CNE_Oscillation* oscillation1;
	CNE_Oscillation* oscillation2;
	CNE_Oscillation* focusOscillation;
	map<int, bool> keyStates;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* surface;
	CNE_Time* bulletTimer;
	CNE_ResourceManager* manager;
	int updateCount, deltaUpdateCount;
	microseconds lastUpdateStart;
	microseconds lastUpdateEnd;
	microseconds lastTimeSync;
	long lastUpdateDelta;
	bool paused;
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	float loopTimeRatio;
public:
	Chlorophane(SDL_Window*, SDL_Renderer*, SDL_Surface*, const int, const int);
	void loadResources();
	void processKeyboardInput();
	bool keyRegistered(int);
	bool isKeyDown(int);
	bool isVisibleOnScreen(CNE_GameObject*);
	bool isPointOnSceen(float x, float y);
	
	void waveFinished(string);

	CNE_Vector* createTimedPointToPointVector(CNE_Point*, CNE_Point*, long);
	CNE_GameObject* getObjectByAlias(string);

	CNE_GameObject* createObject(int, int, string, string, list<CNE_GameObject*>*);
	CNE_ParabolicEnemy* createParabolicEnemy(string, float, float, float, float, float);
	CNE_VectorBullet* createVectorBullet(int, int, CNE_Vector*, string, string);

	CNE_SlashEffect* createSlashEffect(int, int, string, float, float, float);
	CNE_RippleEffect* createRippleEffect(int, int, float);


	CNE_Enemy_Paper* createEnemyPaper(string, float);
	CNE_Enemy_Folder* createEnemyFolder(string, float);
	CNE_Enemy_Urchin* createEnemyUrchin(string, int, float);
	CNE_Enemy_Boss1* createEnemyBoss1();

	void gameWaves();
	int update(SDL_Event*);
	
	~Chlorophane();
};


