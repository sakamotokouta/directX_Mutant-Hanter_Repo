#pragma once

#include "gameObject.h"
#include "model.h"

class CollisionBox : public GameObject
{
private:
	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;

	static Model* m_Model;
	D3DXMATRIX m_Pearent{};
	D3DXMATRIX m_BoneMatrix{};
	bool m_HitFlg{};
	bool m_DrawFlg{};
	bool m_BoneEnable{};

public:
	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool SetOBB(GameObject* obb1, GameObject* obb2, float offset);
	float LenSegOnSeparateAxis(D3DXVECTOR3* Sep, D3DXVECTOR3* e1, D3DXVECTOR3* e2, D3DXVECTOR3* e3);

	void SetPearent(D3DXMATRIX pearent) { m_Pearent = pearent; }
	void SetBoneMatrix(D3DXMATRIX pearent) { m_BoneMatrix = pearent; }
	void SetBoneEnable(bool enable) { m_BoneEnable = enable; }
	void SetDrawFlg(bool draw) { m_DrawFlg = draw; }
};