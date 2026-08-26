#pragma once
#pragma once

#include "gameObject.h"
#include "weaponDataBase.h"

#define WEAPON00 "asset\\model\\sword003.obj"
#define WEAPON01 "asset\\model\\sowrd0001.obj"
#define WEAPON02 "asset\\model\\sowrd0002.obj"
#define WEAPON03 "asset\\model\\sword_03_var2.0.obj"


class Weapon : public GameObject
{
private:
	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;

	D3DXMATRIX m_Parent{};
	D3DXMATRIX m_CollitionMatrix{};

	D3DXVECTOR3 m_CollitionPos{};
	D3DXVECTOR3 m_BonePos{};
	D3DXVECTOR3 m_TopVertex{};
	D3DXVECTOR3 m_BottomVertex{};



	class Model* m_Model{};
	class Scene* m_Scene{};
	class CollisionBox* m_Collision{};
	class Trail* m_Trail{};
	class SwordTopVertex* m_SwordTopVertex{};
	class Player* m_Player{};

	bool m_EnemyDamege{};
	bool m_EnemyDamege2{};

	bool m_collitionflg1{};
	bool m_collitionflg2{};

	bool m_TrailFlg{};

	bool m_EffectFlg{};

	int m_AttackCo{};

	class WeaponDataLoad* m_WeaponData{};

	WeaponDataBase* m_Weapondata[100];

	static int m_WeaponCount;

	bool m_WeaponChangeFlg{};

	const char* m_WeaponName;


public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetWeaponPos(D3DXVECTOR3 pos) { m_Position = pos; }
	bool GetEnemyDamege(void) { return m_EnemyDamege; }
	D3DXVECTOR3 GetBottomVertexPostion() { return m_BottomVertex; }
	void SetWeapon(int co);
	WeaponDataBase* GetWeaponData(void) { return m_Weapondata[m_WeaponCount]; }


};




//剣の頂点クラス
class SwordTopVertex :public GameObject
{
private:
	static ID3D11Buffer* m_VertexBuffer;
	D3DXMATRIX m_Parent{};
	D3DXVECTOR3 m_TopVertex{};

	class Scene* m_Scene{};

	class WeaponDataLoad* m_WeaponData{};

public:
	D3DXVECTOR3 GetTopVertexPostion() { return m_TopVertex; }



	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();
};
