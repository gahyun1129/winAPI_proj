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
	Rectangle(hDC, 100, 200, 300, 300);
}

void LobbyScene::ProcessKey(UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
	{
		if (wParam == VK_1) {
			Scene* scene = Framework.CurScene;   // ÇöÀç ¾ÀÀ» tmp¿¡ ³Ö°í Áö¿öÁÜ
			Framework.CurScene = new EasyScene;
			Framework.CurScene->Init();
			Framework.SceneIndex = EASY;
			delete scene;
		}
		else if (wParam == VK_2) {
			Scene* scene = Framework.CurScene;   // ÇöÀç ¾ÀÀ» tmp¿¡ ³Ö°í Áö¿öÁÜ
			Framework.CurScene = new NormalScene;
			Framework.CurScene->Init();
			Framework.SceneIndex = NORMAL;
			delete scene;
		}
		else if (wParam == VK_3) {
			Scene* scene = Framework.CurScene;   // ÇöÀç ¾ÀÀ» tmp¿¡ ³Ö°í Áö¿öÁÜ
			Framework.CurScene = new HardScene;
			Framework.CurScene->Init();
			Framework.SceneIndex = EASY;
			delete scene;
		}
	}
	break;
	}
}

