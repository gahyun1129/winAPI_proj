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
	Rectangle(hDC, 100, 100, 300, 300);
}

void LobbyScene::ProcessKey(UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
	{
		switch (wParam) {

		case VK_RETURN:
			Scene* scene = Framework.CurScene;   // ÇöÀç ¾ÀÀ» tmp¿¡ ³Ö°í Áö¿öÁÜ
			// Framework.CurScene = new EasyScene;
			Framework.CurScene->Init();
			Framework.SceneIndex = EASY;
			delete scene;
			break;
		}
	}
	break;
	}
}

