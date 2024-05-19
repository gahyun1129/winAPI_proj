#include "stdafx.h"

extern GameFramework Framework;

HardScene::~HardScene()
{
}

void HardScene::Init()
{
	for (int i = 0; i < boardSizeX; ++i) {
		for (int j = 0; j < boardSizeY; ++j) {
			board[i][j].size.left = i * rectSize;
			board[i][j].size.top = j * rectSize;
			board[i][j].size.right = (i + 1) * rectSize;
			board[i][j].size.bottom = (j + 1) * rectSize;
		}
	}

	for (int i = 8; i < 13; ++i) {
		for (int j = 5; j < 10; ++j) {
			board[i][j].color = WHITE;
		}
	}
	board[8][5].color = BLACK;
	board[8][9].color = BLACK;
	board[12][5].color = BLACK;
	board[12][9].color = BLACK;

	player.size = { 5, 5, rectSize - 5, rectSize - 5 };
	player.pos = { 10 * rectSize, 7 * rectSize };
	player.rectSize = player.size.right - player.size.left;

	for (int i = 0; i < 6; ++i) {
		player.bullets[i].degree = 10;
	}
	
	int r = rand() % 6 + 5;
	for (int i = 0; i < r; ++i) {
		board[rand() % boardSizeX][rand() % boardSizeY].color = OBSTACLE;
	}


}

void HardScene::ProcessKey(UINT iMessage, WPARAM wParam, LPARAM lParam)
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
			if (player.bulletNum > 0 && !player.isDead) {
				FireBullet(UP);
				player.bulletNum -= 1;
			}
		}
		else if (wParam == VK_DOWN) {
			if (player.bulletNum > 0 && !player.isDead) {
				FireBullet(DOWN);
				player.bulletNum -= 1;
			}
		}
		else if (wParam == VK_LEFT) {
			if (player.bulletNum > 0 && !player.isDead) {
				FireBullet(LEFT);
				player.bulletNum -= 1;
			}
		}
		else if (wParam == VK_RIGHT) {
			if (player.bulletNum > 0 && !player.isDead) {
				FireBullet(RIGHT);
				player.bulletNum -= 1;
			}
		}
		else if (wParam == VK_K) {
			player.isHero = !player.isHero;
			isHeroMode = !isHeroMode;
			player.heroCoolTime = 1.f;
		}
	}
	break;
	}
}

void HardScene::DrawBoard(HDC hDC)
{
	HBRUSH hBrush, oldBrush;
	HPEN hPen, oldPen;

	for (int i = 0; i < boardSizeX; ++i) {
		for (int j = 0; j < boardSizeY; ++j) {

			if (board[i][j].color == BLACK) {
				hBrush = CreateSolidBrush(RGB(0, 0, 0));
				hPen = CreatePen(PS_SOLID, 0, RGB(200, 200, 200));
			}
			else if (board[i][j].color == WHITE) {
				hBrush = CreateSolidBrush(RGB(255, 255, 255));
				hPen = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
			}
			else {
				hBrush = CreateSolidBrush(RGB(100, 100, 100));
				hPen = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
			}
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
			oldPen = (HPEN)SelectObject(hDC, hPen);

			Rectangle(hDC, boardPos.x + board[i][j].size.left, boardPos.y + board[i][j].size.top, boardPos.x + board[i][j].size.right, boardPos.y + board[i][j].size.bottom);

			SelectObject(hDC, oldBrush);
			DeleteObject(hBrush);

			SelectObject(hDC, oldPen);
			DeleteObject(hPen);
		}
	}
}

void HardScene::DrawPlayer(HDC hDC)
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
}

void HardScene::DrawBullets(HDC hDC)
{
	HBRUSH hBrush, oldBrush;
	for (int i = 0; i < bullets.size(); ++i) {
		for (int j = 0; j < 4; ++j)
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

		}
	}
}

void HardScene::DrawEnemys(HDC hDC)
{
	HBRUSH hBrush, oldBrush;

	POINT neighbor[9] = {
		{-1, -1}, {-1, 0}, {-1, 1},
		{ 0, -1}, {0, 0}, {0, 1},
		{1, -1}, {1, 0}, {1, 1}
	};

	for (int i = 0; i < enemys.size(); ++i) {

		POINT p = { enemys[i].pos.x / rectSize, enemys[i].pos.y / rectSize };
		if (enemys[i].type == PASS) {
			hBrush = CreateHatchBrush(HS_BDIAGONAL, RGB(80, 100, 255));
		}
		else {
			hBrush = CreateHatchBrush(HS_BDIAGONAL, RGB(200, 200, 155));
		}
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

		for (int j = 0; j < 9; ++j) {
			if (p.x + neighbor[j].x >= 0 && p.y + neighbor[j].y >= 0 && p.x + neighbor[j].x < boardSizeX && p.y + neighbor[j].y < boardSizeY) {
				if (board[p.x + neighbor[j].x][p.y + neighbor[j].y].color == BLACK) {
					SetBkColor(hDC, RGB(0, 0, 0));
					Rectangle(hDC, (p.x + neighbor[j].x) * rectSize + boardPos.x, (p.y + neighbor[j].y) * rectSize + boardPos.y, ((p.x + neighbor[j].x) + 1) * rectSize + boardPos.x, ((p.y + neighbor[j].y) + 1) * rectSize + boardPos.y);
				}
				else if (board[p.x + neighbor[j].x][p.y + neighbor[j].y].color == WHITE) {
					SetBkColor(hDC, RGB(255, 255, 255));
					Rectangle(hDC, (p.x + neighbor[j].x) * rectSize + boardPos.x, (p.y + neighbor[j].y) * rectSize + boardPos.y, ((p.x + neighbor[j].x) + 1) * rectSize + boardPos.x, ((p.y + neighbor[j].y) + 1) * rectSize + boardPos.y);
				}
			}
		}
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
	}

	for (int i = 0; i < enemys.size(); ++i) {
		if (enemys[i].type == PASS) {
			hBrush = CreateSolidBrush(RGB(80, 100, 255));
		}
		else {
			hBrush = CreateSolidBrush(RGB(200, 200, 155));
		}
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		SelectObject(hDC, hBrush);
		Rectangle(hDC, enemys[i].pos.x + boardPos.x + enemys[i].size.left,
			enemys[i].pos.y + boardPos.y + enemys[i].size.top,
			enemys[i].pos.x + boardPos.x + enemys[i].size.right,
			enemys[i].pos.y + boardPos.y + enemys[i].size.bottom);
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
	}
}

void HardScene::DrawTexts(HDC hDC)
{
	HFONT hFont, oldFont;
	hFont = CreateFont(
		36,                   // 높이
		0,                    // 너비
		0,                    // 기울기 각도
		0,                    // 기본 방향 각도
		FW_BOLD,              // 굵기
		FALSE,                // 기울임
		FALSE,                // 밑줄
		FALSE,                // 취소선
		DEFAULT_CHARSET,      // 문자 집합
		OUT_DEFAULT_PRECIS,   // 출력 정밀도
		CLIP_DEFAULT_PRECIS,  // 클리핑 정밀도
		DEFAULT_QUALITY,      // 출력 품질
		DEFAULT_PITCH | FF_SWISS,  // 글꼴과 피치
		TEXT("Arial"));       // 글꼴 이름

	oldFont = (HFONT)SelectObject(hDC, hFont);

	TCHAR scoreTxt[100];
	wsprintf(scoreTxt, L"SCORE: %d", score);
	SetBkColor(hDC, RGB(255, 255, 255));
	TextOut(hDC, 70, 90, scoreTxt, lstrlen(scoreTxt));

	TCHAR modeTxt[100];
	wsprintf(modeTxt, L"HARD MODE");
	SetBkColor(hDC, RGB(120, 180, 210));
	TextOut(hDC, 70, 40, modeTxt, lstrlen(modeTxt));

	TCHAR HealthTxt[100];
	wsprintf(HealthTxt, L"HEALTH: %d", player.health);
	SetBkColor(hDC, RGB(255, 255, 255));
	TextOut(hDC, 850, 40, HealthTxt, lstrlen(HealthTxt));

	TCHAR enemyTxt[100];
	wsprintf(enemyTxt, L">> NEXT ENEMY <<");
	SetBkColor(hDC, RGB(255, 255, 255));
	TextOut(hDC, 430, 40, enemyTxt, lstrlen(enemyTxt));

	SelectObject(hDC, oldFont);

	DeleteObject(hFont);
}

void HardScene::DrawComboBox(HDC hDC)
{
	TCHAR comboTxt[100];
	wsprintf(comboTxt, L"%d COMBO!!", player.comboStack);
	SetBkColor(hDC, RGB(240, 180, 90));
	TextOut(hDC, 770, 105, comboTxt, lstrlen(comboTxt));
	Rectangle(hDC, 850, 100, 850 + 180, 130);

	HBRUSH hBrush, oldBrush;
	hBrush = CreateSolidBrush(RGB(240, 180, 90));
	oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	Rectangle(hDC, 850, 100, 850 + (int)(player.comboCoolTime * 60), 130);
	SelectObject(hDC, oldBrush);
	DeleteObject(hBrush);
}

void HardScene::DrawEnemyCoolTimeBox(HDC hDC)
{
	Rectangle(hDC, 450, 80, 450 + 250, 110);
	HBRUSH hBrush, oldBrush;
	hBrush = CreateSolidBrush(RGB(240, 120, 150));
	oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	Rectangle(hDC, 450, 80, 450 + (int)(enemyCoolTime * 50), 110);
	SelectObject(hDC, oldBrush);
	DeleteObject(hBrush);
}

void HardScene::DrawEffect(HDC hDC)
{
	HBRUSH hBrush, oldBrush;
	for (int i = 0; i < effects.size(); ++i) {
		hBrush = CreateSolidBrush(RGB(effects[i].r, effects[i].g, effects[i].b));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Ellipse(hDC, effects[i].size.left + effects[i].pos.x,
			effects[i].size.top + effects[i].pos.y,
			effects[i].size.right + effects[i].pos.x,
			effects[i].size.bottom + effects[i].pos.y);
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
	}
}

void HardScene::DrawReadyBullets(HDC hDC)
{
	HBRUSH hBrush, oldBrush;
	for (int i = 0; i < readyBullets.size(); ++i) {
		POINT bulletPos = { readyBullets[i].center.x + cos(readyBullets[i].pos.x + readyBullets[i].radian) * readyBullets[i].degree, readyBullets[i].center.y + sin(readyBullets[i].pos.y + readyBullets[i].radian) * readyBullets[i].degree };
		hBrush = CreateSolidBrush(RGB(readyBullets[i].r, readyBullets[i].g, readyBullets[i].b));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Ellipse(hDC, bulletPos.x, bulletPos.y, bulletPos.x + readyBullets[i].degree, bulletPos.y + readyBullets[i].degree);
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
	}
}

void HardScene::CreateEnemy()
{
	Enemy e;
	e.size = { 5, 5, rectSize - 5, rectSize - 5 };
	e.rectSize = e.size.right - e.size.left;
	e.pos = { (rand() % boardSizeX) * rectSize, (rand() % boardSizeY) * rectSize };
	enemys.push_back(e);
}

void HardScene::FireBullet(DIREC dir)
{
	Bullet b;
	if (player.bullets[player.bulletNum - 1].type == SPECIAL || player.comboStack == 1) {
		if (dir == UP || dir == DOWN) {
			b.size = { 0, 0, 10, 20 };
			b.pos = { player.pos.x + boardPos.x + player.rectSize / 2 - 10, player.pos.y + boardPos.y + player.rectSize / 2 };
		}
		else {
			b.size = { 0, 0, 20, 10 };
			b.pos = { player.pos.x + boardPos.x + player.rectSize / 2, player.pos.y + boardPos.y + player.rectSize / 2 - 10 };
		}
		b.dir = dir;
		bullets.push_back(b);
		if (dir == UP || dir == DOWN) {
			b.size = { 0, 0, 10, 20 };
			b.pos = { player.pos.x + boardPos.x + player.rectSize / 2 + 10 ,player.pos.y + boardPos.y + player.rectSize / 2 };
		}
		else {
			b.size = { 0, 0, 20, 10 };
			b.pos = { player.pos.x + boardPos.x + player.rectSize / 2,player.pos.y + boardPos.y + player.rectSize / 2 + 10 };
		}
		b.dir = dir;
		bullets.push_back(b);
	}
	else {
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
}

void HardScene::CheckBoardBullet()
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
			if (bullets[i].pos.y > (boardPos.y + boardSizeY * rectSize)) {
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
			if (bullets[i].pos.x > (boardPos.x + boardSizeX * rectSize)) {
				bullets.erase(bullets.begin() + i);
				return;
			}
			break;
		}
		if (board[(bullets[i].pos.x - boardPos.x) / rectSize][(bullets[i].pos.y - boardPos.y) / rectSize].color == OBSTACLE) {
			bullets.erase(bullets.begin() + i);
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

bool HardScene::CheckBoardPlayer()
{
	if (board[player.pos.x / rectSize][player.pos.y / rectSize].color == BLACK 
		|| board[player.pos.x / rectSize][player.pos.y / rectSize].color == OBSTACLE) {
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
	if (player.pos.x < 0 || player.pos.x >(boardSizeX - 1) * rectSize || player.pos.y < 0 || player.pos.y >(boardSizeY - 1) * rectSize) {
		return true;
	}
	return false;
}

void HardScene::CheckBoardEnemy()
{
	for (int i = 0; i < enemys.size(); ++i) {

		if (enemys[i].type == PASS) {
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

void HardScene::CheckBoardNonPassEnemy(float time)
{
	for (int i = 0; i < enemys.size(); ++i) {
		if (enemys[i].type == NONPASS) {
			if (enemys[i].dir == UP) {
				enemys[i].pos.y -= 5;
				if (enemys[i].pos.y < 0) {
					enemys[i].pos.y += 5;
					enemys[i].dir = (DIREC)(rand() % 4);
				}
				else if (board[enemys[i].pos.x / rectSize][enemys[i].pos.y / rectSize].color == OBSTACLE) {
					enemys[i].pos.y += 5;
					enemys[i].dir = (DIREC)(rand() % 4);
				}
			}
			else if (enemys[i].dir == DOWN) {
				enemys[i].pos.y += 5;
				if (enemys[i].pos.y + enemys[i].rectSize > boardSizeY * rectSize) {
					enemys[i].pos.y -= 5;
					enemys[i].dir = (DIREC)(rand() % 4);
				}
				else if (board[enemys[i].pos.x / rectSize][(enemys[i].pos.y + rectSize) / rectSize].color == OBSTACLE) {
					enemys[i].pos.y += 5;
					enemys[i].dir = (DIREC)(rand() % 4);
				}
			}
			else if (enemys[i].dir == LEFT) {
				enemys[i].pos.x -= 5;
				if (enemys[i].pos.x < 0) {
					enemys[i].pos.x += 5;
					enemys[i].dir = (DIREC)(rand() % 4);
				}
				else if (board[enemys[i].pos.x / rectSize][enemys[i].pos.y / rectSize].color == OBSTACLE) {
					enemys[i].pos.x += 5;
					enemys[i].dir = (DIREC)(rand() % 4);
				}
			}
			else if (enemys[i].dir == RIGHT) {
				enemys[i].pos.x += 5;
				if (enemys[i].pos.x + enemys[i].rectSize > boardSizeX * rectSize) {
					enemys[i].pos.x -= 5;
					enemys[i].dir = (DIREC)(rand() % 4);
				}
				else if (board[(enemys[i].pos.x + rectSize) / rectSize][(enemys[i].pos.y) / rectSize].color == OBSTACLE) {
					enemys[i].pos.x += 5;
					enemys[i].dir = (DIREC)(rand() % 4);
				}
			}
			enemys[i].coolTime -= time;
			if (enemys[i].coolTime < 0) {
				enemys[i].coolTime = 2.f;
				enemys[i].dir = (DIREC)(rand() % 4);
			}
		}
	}
}

void HardScene::CheckBulletEnemy()
{
	for (int i = 0; i < bullets.size(); ++i) {
		RECT bulletR = { bullets[i].pos.x - 50, bullets[i].pos.y - 50, bullets[i].pos.x + bullets[i].size.right + 50, bullets[i].pos.y + bullets[i].size.bottom + 50 };
		for (int j = 0; j < enemys.size(); ++j) {
			RECT enemyR = { enemys[j].pos.x + boardPos.x + enemys[j].size.left,
				enemys[j].pos.y + boardPos.y + enemys[j].size.top,
				enemys[j].pos.x + boardPos.x + enemys[j].size.right,
				enemys[j].pos.y + boardPos.y + enemys[j].size.bottom };
			RECT tmp;
			if (IntersectRect(&tmp, &bulletR, &enemyR)) {
				player.comboStack += 1;
				score += (100 * player.comboStack);
				player.comboCoolTime = 3.f;

				// effect
				int num = rand() % 3 + 3;
				for (int n = 0; n < num; ++n) {
					Effect e;
					e.size = { -5, -5, 5, 5 };
					e.pos = { enemys[j].pos.x + boardPos.x + (rand() % 3 + 1) * 20, enemys[j].pos.y + boardPos.y + (rand() % 3 + 1) * 20 };
					e.coolTime = (float)((rand() % 2) + 1);
					e.r = 80;
					e.g = 100;
					e.b = 255;
					effects.push_back(e);
				}

				num = rand() % 4;
				for (int n = 0; n < num; ++n) {
					Bullet b;
					b.r = 200, b.g = 200, b.b = 200;
					b.center = { ((enemys[j].pos.x / rectSize) * rectSize) + boardPos.x + enemys[j].rectSize / 2, ((enemys[j].pos.y / rectSize) * rectSize) + boardPos.y + enemys[j].rectSize / 2 };
					b.size = { 0, 0, 10, 10 };
					b.pos = { (long)(((n + 1) * (360.0 / num)) / 180.0 * PI), (long)(((n + 1) * (360.0 / num)) / 180.0 * PI) };
					b.num = num;
					b.degree = 10;
					readyBullets.push_back(b);
				}
				Framework.mainCamera->isShake = true;
				bullets.erase(bullets.begin() + i);
				enemys.erase(enemys.begin() + j);
				break;
			}
		}
	}
}

void HardScene::CheckPlayerEnemy()
{
	RECT playerR = { player.pos.x + boardPos.x + player.size.left,
				player.pos.y + boardPos.y + player.size.top,
				player.pos.x + boardPos.x + player.size.right,
				player.pos.y + boardPos.y + player.size.bottom };
	for (int j = 0; j < enemys.size(); ++j) {
		RECT enemyR = { enemys[j].pos.x + boardPos.x + enemys[j].size.left,
				enemys[j].pos.y + boardPos.y + enemys[j].size.top,
				enemys[j].pos.x + boardPos.x + enemys[j].size.right,
				enemys[j].pos.y + boardPos.y + enemys[j].size.bottom };
		RECT tmp;
		if (IntersectRect(&tmp, &playerR, &enemyR)) {
			// effect
			int num = rand() % 3 + 3;
			for (int n = 0; n < num; ++n) {
				Effect e;
				e.size = { -5, -5, 5, 5 };
				e.pos = { enemys[j].pos.x + boardPos.x + (rand() % 3 + 1) * 20, enemys[j].pos.y + boardPos.y + (rand() % 3 + 1) * 20 };
				e.coolTime = (float)((rand() % 2) + 1);
				e.r = 80;
				e.g = 100;
				e.b = 255;
				effects.push_back(e);
			}
			num = rand() % 3 + 3;
			for (int n = 0; n < num; ++n) {
				Effect e;
				e.size = { -5, -5, 5, 5 };
				e.pos = { player.pos.x + boardPos.x + (rand() % 3 + 1) * 20, player.pos.y + boardPos.y + (rand() % 3 + 1) * 20 };
				e.coolTime = float((rand() % 2) + 1);
				e.r = 255;
				e.g = 0;
				e.b = 0;
				effects.push_back(e);
			}
			player.isDead = true;
			// status = PAUSE;
			enemys.clear();
			player.health -= 1;
			if (player.health == 0) {
				Framework.WriteScore(score);
				Scene* scene = Framework.CurScene;   // 현재 씬을 tmp에 넣고 지워줌
				Framework.CurScene = new GameOverScene;
				Framework.CurScene->Init();
				Framework.SceneIndex = END;
				delete scene;
			}
			break;
		}
	}
}

void HardScene::CheckPlayerReadyBullets()
{
	RECT playerR = { player.pos.x + boardPos.x + player.size.left,
				player.pos.y + boardPos.y + player.size.top,
				player.pos.x + boardPos.x + player.size.right,
				player.pos.y + boardPos.y + player.size.bottom };
	for (int i = 0; i < readyBullets.size(); ++i) {
		RECT bulletR = { readyBullets[i].center.x - rectSize / 2, readyBullets[i].center.y - rectSize / 2, readyBullets[i].center.x + rectSize / 2, readyBullets[i].center.y + rectSize / 2 };
		RECT tmp;
		if (IntersectRect(&tmp, &playerR, &bulletR)) {
			readyBullets.erase(readyBullets.begin() + i);
			if (player.bulletNum < 6) {
				player.bullets[player.bulletNum - 1].type = SPECIAL;
				player.bullets[player.bulletNum - 1].r = 150, player.bullets[player.bulletNum - 1].g = 150, player.bullets[player.bulletNum - 1].b = 150;
				player.bulletNum += 1;
			}
			break;
		}
	}
}

void HardScene::EnemySpawn(float time)
{
	enemyCoolTime -= time;
	if (enemyCoolTime < 0) {
		enemyCoolTime = 5.f - (5 - spawnNum);
		spawnNum -= 1;
		if (spawnNum < 2) {
			spawnNum = 2;
		}
		int n = rand() % 2 + 1;
		for (int i = 0; i < n; ++i) {
			CreateEnemy();
		}
	}
}

void HardScene::Update(const float frameTime)
{
	if (status == PAUSE) {
		return;
	}


	player.radian -= frameTime;

	CheckBoardBullet();

	CheckBoardEnemy();
	CheckBoardNonPassEnemy(frameTime);

	CheckBulletEnemy();

	CheckPlayerReadyBullets();


	if (player.isDead) {
		player.ReviveCoolTime(frameTime);
		if (!player.isDead) {
			player.pos = { 10 * rectSize, 7 * rectSize };
			board[10][7].color = WHITE;
			player.bulletNum = 6;
			enemyCoolTime = 5.f;
			player.isHero = true;
		}
	}
	else {
		EnemySpawn(frameTime);
		if (!player.isHero) {
			CheckPlayerEnemy();
		}
		if (player.isHero && isHeroMode == false) {
			player.HEROCoolTime(frameTime);
		}
		score += 1;
		if (player.comboStack > 0) {
			player.ComboCoolTime(frameTime);
		}

		if (player.bulletNum == 0) {
			player.BulletCoolTime(frameTime);
		}
	}

	for (int i = 0; i < effects.size(); ++i) {
		if (effects[i].EffectCoolTime(frameTime)) {
			effects.erase(effects.begin() + i);
			break;
		}
	}

	for (int i = 0; i < readyBullets.size(); ++i) {
		readyBullets[i].UpdateRadian(frameTime);
	}
}

void HardScene::Draw(HDC hDC)
{
	HBRUSH hBrush, oldBrush;
	hBrush = CreateSolidBrush(RGB(50, 50, 50));
	oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	Rectangle(hDC, 0, 150, 1100, 900);
	SelectObject(hDC, oldBrush);
	DeleteObject(hBrush);


	DrawBoard(hDC);

	DrawEnemys(hDC);

	DrawBullets(hDC);

	if (!player.isDead) {
		DrawPlayer(hDC);
		player.DrawBullet(hDC, boardPos);
	}
	DrawTexts(hDC);
	if (player.comboStack > 0) {
		DrawComboBox(hDC);
	}
	DrawEnemyCoolTimeBox(hDC);

	DrawEffect(hDC);
	DrawReadyBullets(hDC);
}

