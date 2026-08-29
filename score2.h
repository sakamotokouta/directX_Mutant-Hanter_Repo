#pragma once

#include "gameObject.h"

class Score2 : public GameObject
{
private:
	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;

	ID3D11Buffer* m_VertexBuffer = nullptr;
	ID3D11ShaderResourceView* m_Texture = nullptr;

	D3DXVECTOR3 m_Pos;
	D3DXVECTOR3 m_Scale;

	int m_Count{};

	bool m_DrawFlg{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void AddCount(int Count) { m_Count += Count; }
	void SetCount(int count) { m_Count = count; }

	void SetPosAndScale(float x, float y, float width, float height) {
		m_Pos.x = x;
		m_Pos.y = y;
		m_Scale.x = width;
		m_Scale.y = height;
	}

	D3DXVECTOR3 GetScaleXandY(void) { return m_Scale; }
	D3DXVECTOR3 GetPos(void) { return m_Pos; }
	bool GetDrawFlg(void) { return m_DrawFlg; }

	void SetDrawFlg(bool flg) { m_DrawFlg = flg; }
};