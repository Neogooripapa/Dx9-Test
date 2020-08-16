#pragma once

class MainGame
{
private:
	float elapsedTime = 0.f;
public:
	MainGame();
	~MainGame();

public:
	float GetElapsedTime();
	bool init();
	void update();
	void render();
};

extern MainGame g_MainGame;