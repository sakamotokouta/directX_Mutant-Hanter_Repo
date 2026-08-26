#pragma once

#include "gameObject.h"
#define SUTAMINAMAX 360.0f
#define HPREDMAX 538.0f
#define SPRITEINDEX 7

class Ui01 : public GameObject
{
private:
	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;

	ID3D11Buffer* m_VertexBuffer = nullptr;
	ID3D11ShaderResourceView* m_Texture = nullptr;

	int m_Count{};

	bool m_ClearFlg{};
	int  m_ClearCo{};


	class Sprit2D* m_Sprit[SPRITEINDEX]{};

	class Sprit2D* m_Sprit1;
	class Sprit2D* m_Sprit3;
	class Sprit2D* m_Sprit4;
	class Sprit2D* m_Sprit5;
	class Sprit2D* m_Sprit6;
	class Sprit2D* m_Sprit7;
	class Sprit2D* m_Sprit8;
	class Sprit2D* m_Sprit9;
	class Sprit2D* m_Sprit10;
	class Sprit2D* m_Sprit11;
	class Sprit2D* m_Sprit12;
	class Sprit2D* m_Sprit13;
	class Sprit2D* m_Sprit14;
	class Sprit2D* m_Sprit15;
	class Sprit2D* m_Sprit16;
	class Sprit2D* m_Sprit17;
	class Sprit2D* m_Sprit18;
	class Sprit2D* m_Sprit19;

	class ItemDataLoad* m_ItemData{};
	class WeaponDataLoad* m_WeaponData{};

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_scale;

	D3DXVECTOR3 m_Pos1;
	D3DXVECTOR3 m_Scale1;
	D3DXVECTOR3 m_Rot1;


	D3DXVECTOR3 m_Pos3;
	D3DXVECTOR3 m_Scale3;
	D3DXVECTOR3 m_Rot3;

	D3DXVECTOR3 m_Pos4;
	D3DXVECTOR3 m_Scale4;
	D3DXVECTOR3 m_Rot4;

	D3DXVECTOR3 m_Pos5;
	D3DXVECTOR3 m_Scale5;
	D3DXVECTOR3 m_Rot5;

	D3DXVECTOR3 m_Pos6;
	D3DXVECTOR3 m_Scale6;
	D3DXVECTOR3 m_Rot6;

	D3DXVECTOR3 m_Pos7;
	D3DXVECTOR3 m_Scale7;
	D3DXVECTOR3 m_Rot7;

	D3DXVECTOR3 m_Pos8;
	D3DXVECTOR3 m_Scale8;
	D3DXVECTOR3 m_Rot8;

	D3DXVECTOR3 m_Pos9;
	D3DXVECTOR3 m_Scale9;
	D3DXVECTOR3 m_Rot9;

	D3DXVECTOR3 m_Pos10;
	D3DXVECTOR3 m_Scale10;
	D3DXVECTOR3 m_Rot10;

	D3DXVECTOR3 m_Pos11;
	D3DXVECTOR3 m_Scale11;
	D3DXVECTOR3 m_Rot11;

	D3DXVECTOR3 m_Pos12;
	D3DXVECTOR3 m_Scale12;
	D3DXVECTOR3 m_Rot12;

	D3DXVECTOR3 m_Pos13;
	D3DXVECTOR3 m_Scale13;
	D3DXVECTOR3 m_Rot13;

	D3DXVECTOR3 m_Pos14;
	D3DXVECTOR3 m_Scale14;
	D3DXVECTOR3 m_Rot14;

	D3DXVECTOR3 m_Pos15;
	D3DXVECTOR3 m_Scale15;

	D3DXVECTOR3 m_Pos16;
	D3DXVECTOR3 m_Scale16;

	D3DXVECTOR3 m_Pos17;
	D3DXVECTOR3 m_Scale17;

	D3DXVECTOR3 m_Pos18;
	D3DXVECTOR3 m_Scale18;



	D3DXMATRIX m_Rot;

	int count = 0;

	int m_DamegeCo{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void AddCount(int Count) { m_Count += Count; }
	
	void SetSutaminahiku(float scale) { m_Scale5.x -= scale; }
	void SetSutaminaplus(float scale) { m_Scale5.x += scale; }
	void SetSutamina(float scale) { m_Scale5.x = scale; }
	float GetSutaminaScale(void) { return m_Scale5.x; }

	void SetHPRedhiku(float scale) { m_Scale6.x -= scale; }
	void SetHPRedplsu(float scale) { m_Scale6.x += scale; }
	void SetHPRedScale(float scale) { m_Scale6.x = scale; }
	float GetHPRed(void) { return m_Scale6.x; }

	void SetHPGreenhiku(float scale) { m_Scale7.x -= scale; }
	void SetHPGreenplus(float scale) { m_Scale7.x += scale; }
	void SetHPGreenScale(float scale) { m_Scale7.x = scale; }
	float GetHPGreenScale(void) { return m_Scale7.x; }
	float GetSpescalAttackScale(void) { return m_Scale18.x; }
	void SetSpescalAttackScalePulsu(float x) { m_Scale18.x += x; }
	void SetSpescalAttackScaleMin(float x) { m_Scale18.x -= x; }
	void SetSpescalAttackScale(float x) { m_Scale18.x = x; }

};