#include "stdafx.h"

extern GameFramework Framework;

EasyScene::~EasyScene()
{
}

void EasyScene::Init()
{
	for (int i = 0; i < boardSizeX; ++i) {
		for (int j = 0; j < boardSizeY; ++j) {
			board[i][j].size.left = i * rectSize;
			board[i][j].size.top = j * rectSize;
			board[i][j].size.right = (i + 1) * rectSize;
			board[i][j].size.bottom = (j + 1) * rectSize;
		}
	}

	for (int i = 4; i < 9; ++i) {
		for (int j = 2; j < 7; ++j) {
			board[i][j].color = WHITE;
		}
	}
	board[4][2].color = BLACK;
	board[8][2].color = BLACK;
	board[4][6].color = BLACK;
	board[8][6].color = BLACK;

	player.size = { 5, 5, rectSize-5, rectSize-5 };
	player.pos = { 6 * rectSize, 4 * rectSize };
	player.rectSize = player.size.right - player.size.left;
	CreateEnemy();
}

void EasyScene::ProcessKey(UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
	{
		if (wParam == VK_W) {
			player.pos.y -= 10;
			if (CheckBoardPlayer()) {
				player.pos.y += 10;
			}
		}
		else if (wParam == VK_A) {
			player.pos.x -= 10;
			if (CheckBoardPlayer()) {
				player.pos.x += 10;
			}
		}
		else if (wParam == VK_S) {
			player.pos.y += 10;
			if (CheckBoardPlayer()) {
				player.pos.y -= 10;
			}
		}
		else if (wParam == VK_D) {
			player.pos.x += 10;
			if (CheckBoardPlayer()) {
				player.pos.x -= 10;
			}
		}
		else if (wParam == VK_UP) {
			if (player.bulletNum > 0) {
				player.bulletNum -= 1;
				FireBullet(UP);
			}
		}
		else if (wParam == VK_DOWN) {
			if (player.bulletNum > 0) {
				player.bulletNum -= 1;
				FireBullet(DOWN);
			}
		}
		else if (wParam == VK_LEFT) {
			if (player.bulletNum > 0) {
				player.bulletNum -= 1;
				FireBullet(LEFT);
			}
		}
		else if (wParam == VK_RIGHT) {
			if (player.bulletNum > 0) {
				player.bulletNum -= 1;
				FireBullet(RIGHT);
			}
		}
	}
	break;
	}
}

void EasyScene::DrawBoard(HDC hDC)
{
	HBRUSH hBrush, oldBrush;
	HPEN hPen, oldPen;

	for (int i = 0; i < boardSizeX; ++i) {
		for (int j = 0; j < boardSizeY; ++j) {

			if (board[i][j].color == BLACK) {
				hBrush = CreateSolidBrush(RGB(0, 0, 0));
				hPen = CreatePen(PS_SOLID, 0, RGB(200, 200, 200));
			}
			else {
				hBrush = CreateSolidBrush(RGB(255, 255, 255));
				hPen = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
			}
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
			oldPen = (HPEN)SelectObject(hDC, hPen);

			Rectangle(hDC, boardPos.x + board[i][j].size.left, boardPos.y + board[i][j].size.top, boardPos.x + board[i][j].size.right, boardPos.y + board[i][j].size.bottom);
			
			SelectObject(hDC, oldBrush);
			DeleteObject(hBrush);
			DeleteObject(oldBrush);

			SelectObject(hDC, oldPen);
			DeleteObject(hPen);
			DeleteObject(oldPen);
		}
	}
}

void EasyScene::DrawPlayer(HDC hDC)
{
	HBRUSH hBrush, oldBrush;

	hBrush = CreateSolidBrush(RGB(255, 0, 0));
	oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	RoundRect(hDC, boardPos.x + player.pos.x + player.size.left,
		boardPos.y + player.pos.y + player.size.top,
		boardPos.x + player.pos.x + player.size.right,
		boardPos.y + player.pos.y + player.size.bottom,
		20,
		20);
	SelectObject(hDC, oldBrush);
	DeleteObject(hBrush);
	DeleteObject(oldBrush);
}

void EasyScene::DrawBullets(HDC hDC)
{
	HBRUSH hBrush, oldBrush;
	for (int i = 0; i < bullets.size(); ++i) {
		for ( int j = 0; j < 4; ++j)
		{
			hBrush = CreateSolidBrush(RGB(50 + j * 40, 50 + j * 40, 50 + j * 40));
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
			switch (bullets[i].dir) {
			case UP:
				Rectangle(hDC, bullets[i].pos.x, bullets[i].pos.y + j * 10, bullets[i].pos.x + 10, bullets[i].pos.y + 20 + j * 10);
				break;
			case DOWN:
				Rectangle(hDC, bullets[i].pos.x, bullets[i].pos.y - j * 10, bullets[i].pos.x + 10, bullets[i].pos.y + 20 - j * 10);
				break;
			case LEFT:
				Rectangle(hDC, bullets[i].pos.x + j * 10, bullets[i].pos.y, bullets[i].pos.x + 20 + j * 10, bullets[i].pos.y + 10);
				break;
			case RIGHT:
				Rectangle(hDC, bullets[i].pos.x - j * 10, bullets[i].pos.y, bullets[i].pos.x + 20 - j * 10, bullets[i].pos.y + 10);
				break;
			}
			// Rectangle(hDC, bullets[i].pos.x, bullets[i].pos.y + j * 10, bullets[i].pos.x + 10, bullets[i].pos.y + 10 + j * 10);
			SelectObject(hDC, oldBrush);
			DeleteObject(hBrush);
			DeleteObject(oldBrush);
		}
	}
}

void EasyScene::DrawEnemys(HDC hDC)
{
	HBRUSH hBrush, oldBrush;

	POINT neighbor[9] = {
		{-1, -1}, {-1, 0}, {-1, 1},
		{ 0, -1}, {0, 0}, {0, 1},
		{1, -1}, {1, 0}, {1, 1}
	};

	for (int i = 0; i < enemys.size(); ++i) {

		POINT p = { enemys[i].pos.x / rectSize, enemys[i].pos.y / rectSize };
		hBrush = CreateHatchBrush(HS_BDIAGONAL, RGB(80, 100, 255));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

		for (int j = 0; j < 9; ++j) {
			if (p.x + neighbor[j].x >= 0 && p.y + neighbor[j].y >= 0 && p.x + neighbor[j].x < boardSizeX && p.y + neighbor[j].y < boardSizeY) {
				if (board[p.x + neighbor[j].x][p.y + neighbor[j].y].color == BLACK) {
					SetBkColor(hDC, RGB(0, 0, 0));
				}
				else {
					SetBkColor(hDC, RGB(255, 255, 255));
				}
				Rectangle(hDC, (p.x + neighbor[j].x) * rectSize + boardPos.x, (p.y + neighbor[j].y) * rectSize + boardPos.y, ((p.x + neighbor[j].x) + 1) * rectSize + boardPos.x, ((p.y + neighbor[j].y) + 1) * rectSize + boardPos.y);
			}
		}

		hBrush = CreateSolidBrush(RGB(80, 100, 255));
		SelectObject(hDC, hBrush);
		Rectangle(hDC, enemys[i].pos.x + boardPos.x + enemys[i].size.left,
			enemys[i].pos.y + boardPos.y + enemys[i].size.top,
			enemys[i].pos.x + boardPos.x + enemys[i].size.right,
			enemys[i].pos.y + boardPos.y + enemys[i].size.bottom);
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
		DeleteObject(oldBrush);

	}
}

void EasyScene::CreateEnemy()
{
	Enemy e;
	e.size = { 5, 5, rectSize - 5, rectSize - 5 };
	e.rectSize = e.size.right - e.size.left;
	e.pos = { (rand() % boardSizeX) * rectSize, (rand() % boardSizeY) * rectSize };
	enemys.push_back(e);
}

void EasyScene::FireBullet(DIREC dir)
{
	Bullet b;
	b.pos = { player.pos.x + boardPos.x + player.rectSize / 2,player.pos.y + boardPos.y + player.rectSize / 2 };
	b.dir = dir;
	if (dir == UP || dir == DOWN) {
		b.size = { 0, 0, 10, 20 };
	}
	else {
		b.size = { 0, 0, 20, 10 };
	}
	bullets.push_back(b);
}

void EasyScene::CheckBoardBullet()
{
	for (int i = 0; i < bullets.size(); ++i) {
		switch (bullets[i].dir) {
		case UP:
			bullets[i].pos.y -= 20;
			if (bullets[i].pos.y < boardPos.y) {
				bullets.erase(bullets.begin() + i);
				return;
			}
			break;
		case DOWN:
			bullets[i].pos.y += 20;
			if (bullets[i].pos.y > (boardPos.y + 8 * rectSize)) {
				bullets.erase(bullets.begin() + i);
				return;
			}
			break;
		case LEFT:
			bullets[i].pos.x -= 20;
			if (bullets[i].pos.x < boardPos.x) {
				bullets.erase(bullets.begin() + i);
				return;
			}
			break;
		case RIGHT:
			bullets[i].pos.x += 20;
			if (bullets[i].pos.x > (boardPos.x + 12 * rectSize)) {
				bullets.erase(bullets.begin() + i);
				return;
			}
			break;
		}
		if (board[(bullets[i].pos.x - boardPos.x) / rectSize][(bullets[i].pos.y - boardPos.y) / rectSize].color == BLACK) {
			board[(bullets[i].pos.x - boardPos.x) / rectSize][(bullets[i].pos.y - boardPos.y) / rectSize].color = WHITE;
		}
		if (board[(bullets[i].pos.x - boardPos.x + bullets[i].size.right) / rectSize][(bullets[i].pos.y - boardPos.y + bullets[i].size.bottom) / rectSize].color == BLACK) {
			board[(bullets[i].pos.x - boardPos.x + bullets[i].size.right) / rectSize][(bullets[i].pos.y - boardPos.y + bullets[i].size.bottom) / rectSize].color = WHITE;
		}
		if (board[(bullets[i].pos.x - boardPos.x + bullets[i].size.right) / rectSize][(bullets[i].pos.y - boardPos.y) / rectSize].color == BLACK) {
			board[(bullets[i].pos.x - boardPos.x + bullets[i].size.right) / rectSize][(bullets[i].pos.y - boardPos.y) / rectSize].color = WHITE;
		}
		if (board[(bullets[i].pos.x - boardPos.x) / rectSize][(bullets[i].pos.y - boardPos.y + bullets[i].size.bottom) / rectSize].color == BLACK) {
			board[(bullets[i].pos.x - boardPos.x) / rectSize][(bullets[i].pos.y - boardPos.y + bullets[i].size.bottom) / rectSize].color = WHITE;
		}
	}
}

bool EasyScene::CheckBoardPlayer()
{
	if (board[player.pos.x / rectSize][player.pos.y / rectSize].color == BLACK) {
		return true;
	}
	if (board[(player.pos.x + player.size.right) / rectSize][(player.pos.y + player.size.bottom) / rectSize].color == BLACK) {
		return true;
	}
	if (board[(player.pos.x + player.size.right) / rectSize][(player.pos.y) / rectSize].color == BLACK) {
		return true;
	}
	if (board[(player.pos.x) / rectSize][(player.pos.y + player.size.bottom) / rectSize].color == BLACK) {
		return true;
	}
	if (player.pos.x < 0 || player.pos.x > 11 * rectSize || player.pos.y < 0 || player.pos.y > 7 * rectSize) {
		return true;
	}
	return false;
}

void EasyScene::CheckBoardEnemy()
{
	for (int i = 0; i < enemys.size(); ++i) {

		if (player.pos.x < enemys[i].pos.x) {
			enemys[i].pos.x -= 5;
		}
		else if (player.pos.x > enemys[i].pos.x) {
			enemys[i].pos.x += 5;
		}
		if (player.pos.y > enemys[i].pos.y) {
			enemys[i].pos.y += 5;
		}
		else if (player.pos.y < enemys[i].pos.y) {
			enemys[i].pos.y -= 5;
		}

		if (board[(enemys[i].pos.x) / rectSize][(enemys[i].pos.y) / rectSize].color == WHITE) {
			board[(enemys[i].pos.x) / rectSize][(enemys[i].pos.y) / rectSize].color = BLACK;
		}
		if (board[(enemys[i].pos.x + enemys[i].size.right) / rectSize][(enemys[i].pos.y + enemys[i].size.bottom) / rectSize].color == WHITE) {
			board[(enemys[i].pos.x + enemys[i].size.right) / rectSize][(enemys[i].pos.y + enemys[i].size.bottom) / rectSize].color = BLACK;
		}
		if (board[(enemys[i].pos.x + enemys[i].size.right) / rectSize][(enemys[i].pos.y) / rectSize].color == WHITE) {
			board[(enemys[i].pos.x + enemys[i].size.right) / rectSize][(enemys[i].pos.y) / rectSize].color = BLACK;
		}
		if (board[(enemys[i].pos.x) / rectSize][(enemys[i].pos.y + enemys[i].size.bottom) / rectSize].color == WHITE) {
			board[(enemys[i].pos.x) / rectSize][(enemys[i].pos.y + enemys[i].size.bottom) / rectSize].color = BLACK;
		}
	}
}

void EasyScene::CheckBulletEnemy()
{
	for (int i = 0; i < bullets.size(); ++i) {
		RECT bulletR = { bullets[i].pos.x, bullets[i].pos.y, bullets[i].pos.x + bullets[i].size.right, bullets[i].pos.y + bullets[i].size.bottom };
		for (int j = 0; j < enemys.size(); ++j) {
			RECT enemyR = { enemys[j].pos.x + boardPos.x + enemys[j].size.left,
				enemys[j].pos.y + boardPos.y + enemys[j].size.top,
				enemys[j].pos.x + boardPos.x + enemys[j].size.right,
				enemys[j].pos.y + boardPos.y + enemys[j].size.bottom };
			RECT tmp;
			if (IntersectRect(&tmp, &bulletR, &enemyR)) {
				bullets.erase(bullets.begin() + i);
				enemys.erase(enemys.begin() + j);
				break;
			}
		}
	}
}

void EasyScene::Update(const float frameTime)
{
	if (status == PAUSE) {
		return;
	}

	player.radian -= 5.f;

	CheckBoardBullet();

	CheckBoardEnemy();

	CheckBulletEnemy();

}

void EasyScene::Draw(HDC hDC)
{
	HBRUSH hBrush, oldBrush;
	hBrush = CreateSolidBrush(RGB(50, 50, 50));
	oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	Rectangle(hDC, 0, 150, 1100, 900);
	SelectObject(hDC, oldBrush);
	DeleteObject(hBrush);
	DeleteObject(oldBrush);


	DrawBoard(hDC);
	
	DrawEnemys(hDC);
	
	DrawBullets(hDC);
	DrawPlayer(hDC);
	player.DrawBullet(hDC, boardPos);

}

