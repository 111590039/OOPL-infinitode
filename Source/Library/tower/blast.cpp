#include "stdafx.h"
#include "blast.h"

blast::blast() {
	SetType("blast");
	SetBasePicPath("resources/Base_blast.bmp");
	SetTowerName("爆破");
	upgradeIcons = { 0,1,2,8 };
	Barrel = std::make_shared<blastBarrel>();
	coolDown = 1 / attack_speed;
	range = 1.75;
	damage = 4.4;
	attack_speed = 0.4;
	stun_chance = 10;
	stun_duration = 2;
	totalCost = 120;
}

void blast::move(double time, double x, double y, std::vector<std::shared_ptr<enemy>> Enemy) {
	findTarget(x,y,Enemy);
	coolDown = max(0, coolDown - time);
	if (coolDown == 0 && target != NULL) {
		for (std::shared_ptr<enemy> e : Enemy) {
			if (sqrt(pow(x + 0.5 - e->GetX(), 2) + pow(y + 0.5 - e->GetY(), 2)) <= range) {
				if (e->GetType().compare("Air") && e->GetType().compare("Icy") && e->GetType().compare("Jet")) {
					e->GetDamage(damage);
					if (rand() % 100 < stun_chance) {
						e->GetDizzy(stun_duration);
					}
				}
			}
		}
		coolDown = 1 / attack_speed;
	}
}
double blast::GetRange() {
	return range;
}
std::vector<int> blast::GetUpgradeCost() {
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
std::vector<std::string> blast::GetAttributeName() {
	return { "範圍" ,"傷害","攻擊速度","暈眩機率","#暈眩時間" };
}
std::vector<std::string> blast::GetAttributeValue() {
	std::vector<std::string> result = {};
	result.push_back(std::to_string(this->range));
	result.push_back(std::to_string(this->damage));
	result.push_back(std::to_string(this->attack_speed) + "/s");
	result.push_back(std::to_string(this->stun_chance) + "%");
	result.push_back(std::to_string(this->stun_duration) + "/s");
	return result;
}
std::vector<std::vector<double>> blast::GetAffected(int type) {
	//type是升級選項 1/2/3/4 回傳{影響第幾項屬性,影響值}
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
		return { {3,stunChanceUpgrade.at(upgradeLevel[3])} };
	}
	return {};
}
void blast::upgrade1() {
	range += rangeUpgrade.at(upgradeLevel[0]);
	totalCost += upgradeCost[0].at(upgradeLevel[0]);
	upgradeLevel[0] += 1;
}
void blast::upgrade2() {
	damage += damageUpgrade.at(upgradeLevel[1]);
	totalCost += upgradeCost[1].at(upgradeLevel[1]);
	upgradeLevel[1] += 1;
}
void blast::upgrade3() {
	attack_speed += attackSpeedUpgrade.at(upgradeLevel[2]);
	totalCost += upgradeCost[2].at(upgradeLevel[2]);
	upgradeLevel[2] += 1;
}
void blast::upgrade4() {
	stun_chance += stunChanceUpgrade.at(upgradeLevel[3]);
	totalCost += upgradeCost[3].at(upgradeLevel[3]);
	upgradeLevel[3] += 1;
}
void blast::findTarget(double x, double y, std::vector<std::shared_ptr<enemy>> Enemy) {
	bool findTarget = false;
	for (std::shared_ptr<enemy> e : Enemy) {
		if (sqrt(pow(x + 0.5 - e->GetX(), 2) + pow(y + 0.5 - e->GetY(), 2)) <= GetRange()) {
			if (e->GetType().compare("Air") && e->GetType().compare("Jet") && e->GetType().compare("Icy")) {
				SetTarget(e);
				findTarget = true;
				break;
			}
		}
	}
	if (!findTarget) {
		SetTarget(nullptr);
	}
}