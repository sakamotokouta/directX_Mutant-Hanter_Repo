#pragma once
#include "game.h"

class Title :public Scene
{
private:
	class Fade* m_Fade{};
	static bool m_Flg;
	class Audio* m_BGM{};

public:
	void Init() override;
	void Update() override;
	void Draw() override;

	static bool GetStartFlg(void) { return m_Flg; }
	static void SetStartFlg(bool flg) { m_Flg = flg; }

};