#include "main.h"
#include "manager.h"
#include "scene.h"
#include "villageObjCollition.h"
#include "collitionBox.h"
#include "player.h"
#include "idoObj.h"
#include "questBordObj.h"
#include "weaponStoreObj.h"
#include "generalStoreObj.h"
#include "houseObj.h"
#include "windmillObj.h"

void VillageObjCollition::ObjCollition(void)
{
	Scene* scene = Manager::GetScene();
	CollisionBox* collition = scene->GetGameObject<CollisionBox>();
	Player* player = scene->GetGameObject<Player>();
	IdoObj* ido = scene->GetGameObject<IdoObj>();
	QuestBordObj* questbord = scene->GetGameObject<QuestBordObj>();
	WeaponStoreObj* weaponstore = scene->GetGameObject<WeaponStoreObj>();
	GeneralStoreObj* generalstore = scene->GetGameObject<GeneralStoreObj>();
	HouseObj* house = scene->GetGameObject<HouseObj>();
	WindMillObj* windmill = scene->GetGameObject<WindMillObj>();

	//井戸の当たり判定
	if (collition->SetOBB(player, ido, 3.0f))
	{
		player->SetPosition(player->GetOldPosition());
	}

	//クエストボートの当たり判定
	if (collition->SetOBB(player, questbord, 1.0f))
	{
		player->SetPosition(player->GetOldPosition());
	}

	//武器屋の当たり判定
	if (collition->SetOBB(player, weaponstore, 3.0f))
	{
		player->SetPosition(player->GetOldPosition());
	}

	//雑貨屋の当たり判定
	if (collition->SetOBB(player, generalstore, 3.0f))
	{
		player->SetPosition(player->GetOldPosition());
	}

	//家の当たり判定
	if (collition->SetOBB(player, house, 3.0f))
	{
		player->SetPosition(player->GetOldPosition());
	}

	//風車の当たり判定
	if (collition->SetOBB(player, windmill, 1.0f))
	{
		player->SetPosition(player->GetOldPosition());
	}

}