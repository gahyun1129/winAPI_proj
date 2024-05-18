#include "stdafx.h"

GameOverScene::~GameOverScene()
{
}

void GameOverScene::Init()
{
}

void GameOverScene::Update(const float frameTime)
{
}

void GameOverScene::Draw(HDC hDC)
{
	HFONT hFont, oldFont;
	hFont = CreateFont(
		80,                   // ����
		0,                    // �ʺ�
		0,                    // ���� ����
		0,                    // �⺻ ���� ����
		FW_BOLD,              // ����
		FALSE,                // �����
		FALSE,                // ����
		FALSE,                // ��Ҽ�
		DEFAULT_CHARSET,      // ���� ����
		OUT_DEFAULT_PRECIS,   // ��� ���е�
		CLIP_DEFAULT_PRECIS,  // Ŭ���� ���е�
		DEFAULT_QUALITY,      // ��� ǰ��
		DEFAULT_PITCH | FF_SWISS,  // �۲ð� ��ġ
		TEXT("Arial"));       // �۲� �̸�

	oldFont = (HFONT)SelectObject(hDC, hFont);

	TCHAR scoreTxt[100];
	wsprintf(scoreTxt, L"GameOver...");
	SetBkColor(hDC, RGB(255, 255, 255));
	TextOut(hDC, 380, 400, scoreTxt, lstrlen(scoreTxt));

	SelectObject(hDC, oldFont);

	DeleteObject(hFont);
}

void GameOverScene::ProcessKey(UINT iMessage, WPARAM wParam, LPARAM lParam)
{
}
