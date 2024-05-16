#pragma once


enum SCENELIST { LOBBY, EASY, NORMAL, HARD, HERO, END };
class GameFramework
{
public:

	clock_t	prevFrameTime;
	clock_t	curFrameTime;

	SCENELIST SceneIndex;
	Scene* CurScene;

public:

	GameFramework();
	~GameFramework();

	void Reset();
	void Clear();

	void Create(HWND hWnd);
	void OnDraw(HDC hDc);
	void OnUpdate(const float frameTime = 0.17f);
	void KeyBoard(UINT iMessage, WPARAM wParam, LPARAM lParam);

	float GetTick();

private:
	HWND m_hWnd;
};

