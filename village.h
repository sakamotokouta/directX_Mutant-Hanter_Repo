#pragma once
#include "scene.h"

class Village : public Scene
{
private:
	class Audio* m_BGM{};
	class Fade* m_Fade{};
	class VillagePlayerAction* m_VPlayer{};
	class Player* m_Player{};
	class VillageUi* m_VUi{};
	class VillageObjCollition* villageCillition{};
	static bool m_VLoadFinish;
	bool m_QuestFlg{};
	static bool m_QuestFlg1;
	static bool m_TutorialFlg;

	//村シーンの時にオンにするフラグ
	static bool m_VillageFlg;

public:

	static void Load();
	static void Unload();
	static bool GetLoadFinish(void) { return m_VLoadFinish; }

	void Init() override;
	void Update()override;
	void Uninit()override;
	void Draw()override;

	static bool GetNextGameFlg(void) { return m_QuestFlg1; }
	static bool GetTutorialFlg(void) { return m_TutorialFlg; }
	static void SetTutorialFlg(bool flg) { m_TutorialFlg = flg; }

	static bool GetVillageFlg(void) { return m_VillageFlg; }
	static void SetVillageFlg(bool flg) { m_VillageFlg = flg; }

};