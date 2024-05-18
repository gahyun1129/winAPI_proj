#pragma once
class NormalScene : public Scene
{

public:
	BoardRect board[20][14];

	int boardSizeX = 20;
	int boardSizeY = 14;

	int rectSize = 45;

	POINT boardPos = { 90, 190 };

	Player player;
	vector<Bullet> bullets;

	vector<Enemy> enemys;

	vector<Effect> effects;

	vector<Bullet> readyBullets;

	int score = 0;

	float enemyCoolTime = 5.f;
	int spawnNum = 4;

	bool isHeroMode = false;

public:
	virtual ~NormalScene() override;
	virtual void Init() override;
	virtual void Update(const float frameTime) override;
	virtual void Draw(HDC hDC) override;
	virtual void ProcessKey(UINT iMessage, WPARAM wParam, LPARAM lParam) override;

public:
	void DrawBoard(HDC hDC);
	void DrawPlayer(HDC hDC);
	void DrawBullets(HDC hDC);
	void DrawEnemys(HDC hDC);
	void DrawTexts(HDC hDC);
	void DrawComboBox(HDC hDC);
	void DrawEnemyCoolTimeBox(HDC hDC);
	void DrawEffect(HDC hDC);
	void DrawReadyBullets(HDC hDC);
	void CreateEnemy();
	void FireBullet(DIREC dir);
	void CheckBoardBullet();
	bool CheckBoardPlayer();
	void CheckBoardEnemy();
	void CheckBulletEnemy();
	void CheckPlayerEnemy();
	void CheckPlayerReadyBullets();
	void EnemySpawn(float time);
};

