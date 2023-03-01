#pragma once

//Engine Includes
#include "..\DragonFly Engine\ViewObject.h"
#include "..\DragonFly Engine\Music.h"


class GameOver : public df::ViewObject
{
private:
	int time_to_live;
	df::Music* stop_music;
	void step();

public:
	GameOver();
	~GameOver();
	int eventHandler(const df::Event* p_e);
	int draw();
};

