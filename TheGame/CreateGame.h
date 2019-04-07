#pragma once
class CreateGame
{
public:
	static Scene scene;
	static Camera cam;
	static bool keystate[256];
	static float speed;
	static Player *player;
	static Menu *menu;
	static Background *background;
	static Background *whichLevel;
	static bool light1state;
	static bool light2state;
	static bool light3state;
	static Level level;
	static Crystal **block;
	static Panel **panel;
	static Panel *exit;
	static Background *goodbyeScreen;

	void Create();
	static void OnRender();
	static void OnReshape(int, int);
	static void OnKeyPress(unsigned char, int, int);
	static void OnKeyDown(unsigned char, int, int);
	static void OnKeyUp(unsigned char, int, int);
	static void OnTimer(int);
	CreateGame();
	~CreateGame();
};

