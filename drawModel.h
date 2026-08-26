#pragma once

#include "component.h"
#include "model.h"

// 3Dモデル描画コンポーネント
class DrawModel : public Component
{
private:
	Model* m_Model = nullptr;
	bool m_DrawFlg{};
public:
	void Init(const char* model);
	void Uninit();
	void Update();
	void Draw();

	bool GetDrawFlg(void) { return m_DrawFlg; }
};
