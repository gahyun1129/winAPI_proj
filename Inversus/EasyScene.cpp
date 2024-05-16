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

			DeleteObject(hBrush);
			DeleteObject(oldBrush);

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
	DeleteObject(hBrush);
	DeleteObject(oldBrush);
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
	return false;
}

void EasyScene::Update(const float frameTime)
{
	if (status == PAUSE) {
		return;
	}
}

void EasyScene::Draw(HDC hDC)
{
	HBRUSH hBrush, oldBrush;
	hBrush = CreateSolidBrush(RGB(50, 50, 50));
	oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	Rectangle(hDC, 0, 150, 1100, 900);
	DeleteObject(hBrush);
	DeleteObject(oldBrush);

	DrawBoard(hDC);

	DrawPlayer(hDC);
}

