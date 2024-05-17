#include "stdafx.h"
#include "cannon.h"

cannon::cannon() {
	SetType("cannon");
	SetBasePicPath("resources/Base_cannon.bmp");
	SetTowerName("�j��");
	upgradeIcons = { 0,1,2,3 };
	Barrel = std::make_shared<cannonBarrel>();
	range = 1.75;
	damage = 3.1;
	attackSpeed = 0.650; //��������/�C��
	rotataionSpeed = 60; //����t��/�C�� (�٨S��@)
	coolDown = 1 / attackSpeed;
	totalCost = 60;
}
void cannon::move(double time, double x, double y,std::vector<std::shared_ptr<enemy>> Enemy) {
	if (coolDown == 0) {
		if (target != nullptr) {
			std::shared_ptr<cannonbullet> Bullet = std::make_shared<cannonbullet>();
			Bullet->SetTarget(GetTarget());
			Bullet->SetXY(x + 0.5, y + 0.5);
			Bullet->SetSpeed(projectileSpeed);
			Bullet->SetDamage(damage);
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
			for (std::shared_ptr<enemy> e : Enemy) {
				if (sqrt(pow(Bullets[i]->GetX() - e->GetX(), 2) + pow(Bullets[i]->GetY() - e->GetY(), 2)) <= explosion_range) {
					e->GetDamage(Bullets[i]->GetDamage());
				}
			}
			Bullets.erase(Bullets.begin() + i);
		}
	}
}
double cannon::GetRange() {
	return range;
}
std::vector<int> cannon::GetUpgradeCost() {
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
std::vector<std::string> cannon::GetAttributeName() {
	return { "�d��" ,"�ˮ`","�����t��","����t��","�u�Y�t��","#�z���d��" };
}
std::vector<std::string> cannon::GetAttributeValue() {
	std::vector<std::string> result = {};
	result.push_back(std::to_string(this->range));
	result.push_back(std::to_string(this->damage));
	result.push_back(std::to_string(this->attackSpeed) + "/s");
	result.push_back(std::to_string(this->rotataionSpeed) + "/s");
	result.push_back(std::to_string(this->projectileSpeed) + "/s");
	result.push_back(std::to_string(this->explosion_range));
	return result;
}
std::vector<std::vector<double>> cannon::GetAffected(int type) {
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
		return { {3,rotataionSpeedUpgrade.at(upgradeLevel[3])} , {4,projectileSpeedUpgrade.at(upgradeLevel[3])} };
	}
	return {};
}
void cannon::upgrade1() {
	range += rangeUpgrade.at(upgradeLevel[0]);
	totalCost += upgradeCost[0].at(upgradeLevel[0]);
	upgradeLevel[0] += 1;
}
void cannon::upgrade2() {
	damage += damageUpgrade.at(upgradeLevel[1]);
	totalCost += upgradeCost[1].at(upgradeLevel[1]);
	upgradeLevel[1] += 1;
}
void cannon::upgrade3() {
	attackSpeed += attackSpeedUpgrade.at(upgradeLevel[2]);
	totalCost += upgradeCost[2].at(upgradeLevel[2]);
	upgradeLevel[2] += 1;
}
void cannon::upgrade4() {
	rotataionSpeed += rotataionSpeedUpgrade.at(upgradeLevel[3]);
	projectileSpeed += projectileSpeedUpgrade.at(upgradeLevel[3]);
	totalCost += upgradeCost[3].at(upgradeLevel[3]);
	upgradeLevel[3] += 1;
}