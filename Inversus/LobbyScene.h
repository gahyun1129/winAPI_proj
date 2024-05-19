#pragma once
class LobbyScene : public Scene
{
public: 
	vector<int> scores;
	bool isScorePrint = false;
	virtual ~LobbyScene() override;
	virtual void Init() override;
	virtual void Update(const float frameTime) override;
	virtual void Draw(HDC hDC) override;
	virtual void ProcessKey(UINT iMessage, WPARAM wParam, LPARAM lParam) override;
	
	void ReadFile();
};

