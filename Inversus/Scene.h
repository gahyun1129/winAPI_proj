#pragma once

enum STATUS { RUN, PAUSE, GAMEOVER };
class Scene
{
public:
	STATUS status;
	int startX, startY;

public:
	virtual ~Scene();
	virtual void Init() = 0;
	virtual void Update(const float frameTime) = 0;
	virtual void Draw(HDC hDC) = 0;
	virtual void ProcessKey(UINT iMessage, WPARAM wParam, LPARAM lParam) = 0;
};

