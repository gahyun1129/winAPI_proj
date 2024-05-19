#include "stdafx.h"

extern GameFramework Framework;

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
	SetBkColor(hDC, RGB(255, 255, 255));
	TextOut(hDC, 200, 500, L"press r button to retry", lstrlen(L"press r button to retry"));

	SelectObject(hDC, oldFont);

	DeleteObject(hFont);
}

void GameOverScene::ProcessKey(UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
	{
		if (wParam == VK_R) {
			Scene* scene = Framework.CurScene;   // ���� ���� tmp�� �ְ� ������
			Framework.CurScene = new LobbyScene;
			Framework.CurScene->Init();
			Framework.SceneIndex = EASY;
			delete scene;
		}
	}
	break;
	}
}
