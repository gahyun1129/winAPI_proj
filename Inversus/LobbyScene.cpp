#include "stdafx.h"

extern GameFramework Framework;

LobbyScene::~LobbyScene()
{
}

void LobbyScene::Init()
{
}

void LobbyScene::Update(const float frameTime)
{
}

void LobbyScene::Draw(HDC hDC)
{
	HBRUSH hBrush, oldBrush;
	hBrush = CreateSolidBrush(RGB(100, 100, 100));
	oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	Rectangle(hDC, 200, 175, 900, 375);
	HFONT hFont, oldFont;
	hFont = CreateFont(
		100,                   // 높이
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

	TCHAR modeTxt[100];
	SetBkColor(hDC, RGB(100, 100, 100));
	wsprintf(modeTxt, L"INVERSUS");
	TextOut(hDC, 330, 235, modeTxt, lstrlen(modeTxt));

	DeleteObject(hFont);
	hFont = CreateFont(
		50,                   // 높이
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

	SelectObject(hDC, hFont);

	DeleteObject(hBrush);
	hBrush = CreateSolidBrush(RGB(100, 120, 150));
	SelectObject(hDC, hBrush);
	Rectangle(hDC, 300, 450, 800, 550);
	SetBkColor(hDC, RGB(100, 120, 150));
	TextOut(hDC, 450, 475, L"Easy Mode", lstrlen(L"Easy Mode"));

	DeleteObject(hBrush);
	hBrush = CreateSolidBrush(RGB(150, 150, 110));
	SelectObject(hDC, hBrush);
	Rectangle(hDC, 300, 575, 800, 675);
	SetBkColor(hDC, RGB(150, 150, 110));
	TextOut(hDC, 425, 600, L"Normal Mode", lstrlen(L"Normal Mode"));

	DeleteObject(hBrush);
	hBrush = CreateSolidBrush(RGB(150, 100, 100));
	SelectObject(hDC, hBrush);
	Rectangle(hDC, 300, 700, 800, 800);
	SetBkColor(hDC, RGB(150, 100, 100));
	TextOut(hDC, 450, 725, L"Hard Mode", lstrlen(L"Hard Mode"));

	SelectObject(hDC, oldFont);

	SelectObject(hDC, oldBrush);
	DeleteObject(hBrush);
	DeleteObject(hFont);

	if (isScorePrint) {
		hBrush = CreateSolidBrush(RGB(150, 150, 150));
		SelectObject(hDC, hBrush);
		Rectangle(hDC, 100, 100, 1000, 800);

		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);

		hFont = CreateFont(
			100,                   // 높이
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

		SelectObject(hDC, hFont);

		SetBkColor(hDC, RGB(150, 150, 150));
		TextOut(hDC, 230, 150, L"SCORE BOARD", lstrlen(L"SCORE BOARD"));

		SelectObject(hDC, oldFont);
		DeleteObject(hFont);

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

		SelectObject(hDC, hFont);
		SetBkColor(hDC, RGB(150, 150, 150));
		TCHAR scoreTxt[100];
		for (int i = 0; i < scores.size(); ++i) {
			if (i == 5) {
				break;
			}
			wsprintf(scoreTxt, L"%d. %d", i+1, scores[i]);
			TextOut(hDC, 460, 300 + i * 100, scoreTxt, lstrlen(scoreTxt));
		}
	}
}

void LobbyScene::ProcessKey(UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
	{
		if (wParam == VK_1) {
			Scene* scene = Framework.CurScene;   // 현재 씬을 tmp에 넣고 지워줌
			Framework.CurScene = new EasyScene;
			Framework.CurScene->Init();
			Framework.SceneIndex = EASY;
			delete scene;
		}
		else if (wParam == VK_2) {
			Scene* scene = Framework.CurScene;   // 현재 씬을 tmp에 넣고 지워줌
			Framework.CurScene = new NormalScene;
			Framework.CurScene->Init();
			Framework.SceneIndex = NORMAL;
			delete scene;
		}
		else if (wParam == VK_3) {
			Scene* scene = Framework.CurScene;   // 현재 씬을 tmp에 넣고 지워줌
			Framework.CurScene = new HardScene;
			Framework.CurScene->Init();
			Framework.SceneIndex = EASY;
			delete scene;
		}
		else if (wParam == VK_4) {
			Scene* scene = Framework.CurScene;   // 현재 씬을 tmp에 넣고 지워줌
			Framework.CurScene = new HeroScene;
			Framework.CurScene->Init();
			Framework.SceneIndex = HERO;
			delete scene;
		}
		else if (wParam == VK_J) {
			isScorePrint = !isScorePrint;
			if (isScorePrint) {
				ReadFile();
			}
			else {
				scores.clear();
			}
		}
	}
	case WM_LBUTTONDOWN: {
		int mx = LOWORD(lParam); //--- 마우스 좌표값: (mx, my)
		int my = HIWORD(lParam);

		if (300 <= mx && mx <= 800) {
			if (450 <= my && my <= 550) {
				Scene* scene = Framework.CurScene;   // 현재 씬을 tmp에 넣고 지워줌
				Framework.CurScene = new EasyScene;
				Framework.CurScene->Init();
				Framework.SceneIndex = EASY;
				delete scene;
			}
			else if (575 <= my && my <= 675) {
				Scene* scene = Framework.CurScene;   // 현재 씬을 tmp에 넣고 지워줌
				Framework.CurScene = new NormalScene;
				Framework.CurScene->Init();
				Framework.SceneIndex = NORMAL;
				delete scene;
			}
			else if (700 <= my && my <= 800) {
				Scene* scene = Framework.CurScene;   // 현재 씬을 tmp에 넣고 지워줌
				Framework.CurScene = new HardScene;
				Framework.CurScene->Init();
				Framework.SceneIndex = EASY;
				delete scene;
			}
		}
	}
	break;
	}
}

void LobbyScene::ReadFile()
{
	ifstream iFile("scores.txt");

	if (!iFile) {
		return;
	}
	
	int score;
	while (iFile >> score) {
		scores.push_back(score);
	}

	iFile.close();

	sort(scores.begin(), scores.end(), greater<int>());
}

