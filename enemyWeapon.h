#pragma once
#pragma once

#include "gameObject.h"

class EnemyWeapon : public GameObject
{
private:
	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;

	D3DXMATRIX m_Parent{};
	D3DXMATRIX m_CollitionMatrix{};

	D3DXVECTOR3 m_CollitionPos{};
	D3DXVECTOR3 m_BonePos{};

	class Audio* m_AttackSE{};
	class Model* m_Model{};
	class Scene* m_Scene{};
	class CollisionBox* m_CollisionBox{};


	bool m_EnemyDamege{};
	bool m_EnemyDamege2{};

	bool m_collitionflg1{};
	bool m_collitionflg2{};

	bool flg{};


public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetWeaponPos(D3DXVECTOR3 pos) { m_Position = pos; }
	bool GetEnemyDamege(void) { return m_EnemyDamege; }
};