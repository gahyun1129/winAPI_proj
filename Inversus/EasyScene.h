#pragma once

class EasyScene : public Scene
{

public:
	BoardRect board[12][8];

	int boardSizeX = 12;
	int boardSizeY = 8;
	
	int rectSize = 80;

	POINT boardPos = { 60, 190 };
	
	Player player;
	vector<Bullet> bullets;

	vector<Enemy> enemys;

public:
	virtual ~EasyScene() override;
	virtual void Init() override;
	virtual void Update(const float frameTime) override;
	virtual void Draw(HDC hDC) override;
	virtual void ProcessKey(UINT iMessage, WPARAM wParam, LPARAM lParam) override;

public:
	void DrawBoard(HDC hDC);
	void DrawPlayer(HDC hDC);
	void DrawBullets(HDC hDC);
	void DrawEnemys(HDC hDC);
	void CreateEnemy();
	void FireBullet(DIREC dir);
	void CheckBoardBullet();
	bool CheckBoardPlayer();
	void CheckBoardEnemy();
	void CheckBulletEnemy();
};

