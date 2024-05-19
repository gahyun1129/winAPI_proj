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
		80,                   // 높이
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
			Scene* scene = Framework.CurScene;   // 현재 씬을 tmp에 넣고 지워줌
			Framework.CurScene = new LobbyScene;
			Framework.CurScene->Init();
			Framework.SceneIndex = EASY;
			delete scene;
		}
	}
	break;
	}
}
