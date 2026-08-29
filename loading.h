#pragma once
#include "game.h"

class Loading :public Scene
{
private:
	class Fade* m_Fade{};

public:
	void Init() override;
	void Update() override;
};