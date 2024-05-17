#include "stdafx.h"
#include "sniper.h"

sniper::sniper() {
	SetType("sniper");
	SetBasePicPath("resources/Base_Sniper.bmp");
	SetTowerName("����");
	upgradeIcons = { 0,1,2,4 };
	Barrel = std::make_shared<sniperBarrel>();
	range = 4.5;
	damage = 16;
	attackSpeed = 0.2; //��������/�C��
	rotataionSpeed = 50; //����t��/�C�� (�٨S��@)
	aimTime = 0.6;
	coolDown = 1 / attackSpeed;
	last_target = nullptr;
	totalCost = 100;
	srand(unsigned(time(NULL)));
}
void sniper::move(double time, double x, double y, std::vector<std::shared_ptr<enemy>> Enemy) {
	if (target == last_target && target != nullptr) {
		aimimgtime = max(0, aimimgtime - time);
	}
	else {
		aimimgtime = aimTime;
	}
	if (coolDown == 0 && aimimgtime == 0) {
		if (target != nullptr) {
			bool p = (rand() % 10) == 1;
			std::shared_ptr<sniperbullet> Bullet = std::make_shared<sniperbullet>(p);
			Bullet->SetTarget(GetTarget());
			Bullet->SetXY(x + 0.5, y + 0.5);
			Bullet->SetSpeed(50);
			if (p) {
				Bullet->SetDamage(damage * 2);
			}
			else {
				Bullet->SetDamage(damage);
			}
			newBullet(Bullet);
			coolDown = 1 / attackSpeed;
		}
	}
	else {
		coolDown = max(0, coolDown - time);
	}

	//�l�u����
	for (std::shared_ptr<bullet> b : Bullets) {
		b->move(time);
	}
	//�R���w�Χ����l�u
	for (size_t i = 0; i < Bullets.size(); i++) {
		if (Bullets[i]->IsPathOver()) {
			if (GetTarget() != nullptr) {
				GetTarget()->GetDamage(Bullets[i]->GetDamage());
			}
			Bullets.erase(Bullets.begin() + i);
		}
	}
	last_target = target;
}
double sniper::GetRange() {
	return range;
}
std::vector<int> sniper::GetUpgradeCost() {
	std::vector<int> result;
	for (int i = 0; i < 4; i++) {
		if (upgradeLevel[i] != 10) {
			result.push_back(upgradeCost[i][upgradeLevel[i]]);
		}
		else {
			result.push_back(99999999);
		}
	}
	return result;
}
std::vector<std::string> sniper::GetAttributeName() {
	return { "�d��" ,"�ˮ`","�����t��","����t��","�˷Ǯɶ�","#�������v","#�����ˮ`" };
}
std::vector<std::string> sniper::GetAttributeValue() {
	std::vector<std::string> result = {};
	result.push_back(std::to_string(this->range));
	result.push_back(std::to_string(this->damage));
	result.push_back(std::to_string(this->attackSpeed) + "/s");
	result.push_back(std::to_string(this->rotataionSpeed) + "/s");
	result.push_back(std::to_string(this->aimTime) + "s");
	result.push_back("10.0%");
	result.push_back("x2.00");
	return result;
}
std::vector<std::vector<double>> sniper::GetAffected(int type) {
	//type�O�ɯſﶵ 1/2/3/4 �^��{�v�T�ĴX���ݩ�,�v�T��}
	if (type == 1) {
		return { {0,rangeUpgrade.at(upgradeLevel[0])} };
	}
	else if (type == 2) {
		return { {1,damageUpgrade.at(upgradeLevel[1])} };
	}
	else if (type == 3) {
		return { {2,attackSpeedUpgrade.at(upgradeLevel[2])} };
	}
	else if (type == 4) {
		return { {4,aimTimeUpgrade.at(upgradeLevel[3])} };
	}
	return {};
}
void sniper::upgrade1() {
	range += rangeUpgrade.at(upgradeLevel[0]);
	totalCost += upgradeCost[0].at(upgradeLevel[0]);
	upgradeLevel[0] += 1;
}
void sniper::upgrade2() {
	damage += damageUpgrade.at(upgradeLevel[1]);
	totalCost += upgradeCost[1].at(upgradeLevel[1]);
	upgradeLevel[1] += 1;
}
void sniper::upgrade3() {
	attackSpeed += attackSpeedUpgrade.at(upgradeLevel[2]);
	totalCost += upgradeCost[2].at(upgradeLevel[2]);
	upgradeLevel[2] += 1;
}
void sniper::upgrade4() {
	aimTime += aimTimeUpgrade.at(upgradeLevel[3]);
	totalCost += upgradeCost[3].at(upgradeLevel[3]);
	upgradeLevel[3] += 1;
}