#pragma once
#include "scene.h"

class Tutorial : public Scene
{
private:
	class Fade* m_Fade{};

	static bool m_TLoadFinish;

	static bool m_TutorialFlg;

public:

	static void Load();
	static void Unload();

	void Init() override;
	void Update()override;
	void Uninit()override;
	void Draw()override;

	static bool GetLoardFinish(void) { return m_TLoadFinish; }
	static bool GetTutorialFlg(void) { return m_TutorialFlg; }
	static void SetTutorialFlg(bool flg) { m_TutorialFlg = flg; }

};