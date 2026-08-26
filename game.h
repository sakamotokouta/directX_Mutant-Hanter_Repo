#pragma once
#include "scene.h"

class Game : public Scene
{
private:
	class Audio* m_BGM{};
	class Audio* m_BGM1{};

	class Fade* m_Fade{};
	static bool m_LoadFinish;

	static bool m_GameFlg;
public:
	
	static void Load();
	static void Unload();
	static bool GetLoadFinish(void) { return m_LoadFinish; }

	void Init() override;
	void Update()override;
	void Uninit()override;
	void Draw()override;

	static bool GetGameFlg(void){ return m_GameFlg; }
	static void SetGameFlg(bool flg) { m_GameFlg = flg; }
};