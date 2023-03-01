#pragma once

#include "..\DragonFly Engine\ViewObject.h"
#include "..\DragonFly Engine\Music.h"


class GameStart : public df::ViewObject
{

private:
	df::Music* start_music;
	void start();

public:
	GameStart();
	int eventHandler(const df::Event* p_e);
	int draw();
	void playMusic();
};

