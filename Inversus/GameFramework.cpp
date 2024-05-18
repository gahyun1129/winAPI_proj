#include "stdafx.h"

GameFramework::GameFramework()
{
}

GameFramework::~GameFramework()
{
}

void GameFramework::Reset()
{
}

void GameFramework::Clear()
{
	delete(CurScene);
	delete(mainCamera);
}

void GameFramework::Create(HWND hWnd)
{
	m_hWnd = hWnd;

	CurScene = new LobbyScene;
	SceneIndex = LOBBY;
	mainCamera = new Camera;

	CurScene->Init();
}

void GameFramework::OnDraw(HDC hDC)
{
	CurScene->Draw(hDC);
}

void GameFramework::OnUpdate(const float frameTime)
{
	CurScene->Update(frameTime);
	mainCamera->ShakeCam(frameTime);
}

void GameFramework::KeyBoard(UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
	{
		if (wParam == VK_ESCAPE) {
			SendMessage(m_hWnd, WM_DESTROY, 0, 0);	// 종료
			return;
		}
		else if (wParam == VK_Q) {
			SendMessage(m_hWnd, WM_DESTROY, 0, 0);	// 종료
			return;
		}
		else if (wParam == VK_P) {
			if (CurScene->status == RUN) {
				CurScene->status = PAUSE;
			}
			else if (CurScene->status == PAUSE) {
				CurScene->status = RUN;
			}
		}
		
	}
	}
	CurScene->ProcessKey(iMessage, wParam, lParam);	//현재 씬의 프로세스키
}

float GameFramework::GetTick()
{
	return (float)(curFrameTime - prevFrameTime) / 1000;
}
