#pragma once

#include "gameObject.h"
#include <string>
#include "animationModel.h"


enum RECEPTION_STATE
{
	RECEPTION_STATE_IDLE,
	RECEPTION_STATE_MOVE
};

class RECEPTIONDESK : public GameObject
{
private:
	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;
	ID3D11ShaderResourceView* m_DisolveTexture = nullptr;

	class AnimationModel* m_Model{};
	class Fade* m_Fade{};

	std::string m_AnimationName;

	std::string m_NextAnimationName;

	float m_BlendRate{};

	float m_Time;

	float m_Threshold{};

	bool m_QuestFlg{};


	RECEPTION_STATE m_ReceptionState = RECEPTION_STATE_IDLE;

	D3DXMATRIX m_WorldMatrix{};
	D3DXVECTOR3 m_BonePos{};
	D3DXVECTOR3 m_BoneScale{};


public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool GetQuestFlg(void) { return m_QuestFlg; }
	void SetQuestFlg(bool flg) { m_QuestFlg = flg; }

};

