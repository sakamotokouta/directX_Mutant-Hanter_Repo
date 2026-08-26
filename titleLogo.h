#pragma once

#include "gameObject.h"

class TitleLogo : public GameObject
{
private:
	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;

	class Sprit2D* m_Sprite1{};
	class Sprit2D* m_Sprite2{};

	D3DXVECTOR3 m_Sprite1Pos{};
	D3DXVECTOR3 m_Sprite1Scale{};
	D3DXVECTOR3 m_Sprite2Pos{};
	D3DXVECTOR3 m_Sprite2Scale{};

	bool m_PulsFlg{};
	bool m_Minus{};

	float m_clear{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};