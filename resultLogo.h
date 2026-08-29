#pragma once

#include "gameObject.h"

class ResultLogo : public GameObject
{
private:
	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;

	class Sprit2D* m_Sprit1;
	class Sprit2D* m_Sprit2;
	class Sprit2D* m_Sprit3;
	class Sprit2D* m_Sprit4;
	class Sprit2D* m_Sprit5;
	class Sprit2D* m_Sprit6;
	class Sprit2D* m_Sprit7;

	float m_Celar{};

	bool m_PulsFlg{};
	bool m_Minus{};

	int m_Level1Reward{};
	int m_Level2Reward{};
	int m_Level3Reward{};

	D3DXVECTOR3 m_Pos1;
	D3DXVECTOR3 m_Scale1;
	D3DXVECTOR3 m_Rot1;

	D3DXVECTOR3 m_Pos2;
	D3DXVECTOR3 m_Scale2;
	D3DXVECTOR3 m_Rot2;

	D3DXVECTOR3 m_Pos3;
	D3DXVECTOR3 m_Scale3;
	D3DXVECTOR3 m_Rot3;

	D3DXVECTOR3 m_Pos4;
	D3DXVECTOR3 m_Scale4;
	D3DXVECTOR3 m_Rot4;

	D3DXVECTOR3 m_Pos5;
	D3DXVECTOR3 m_Scale5;

	D3DXVECTOR3 m_Pos6;
	D3DXVECTOR3 m_Scale6;

	D3DXVECTOR3 m_Pos7;
	D3DXVECTOR3 m_Scale7;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};
