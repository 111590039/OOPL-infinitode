#include "stdafx.h"
#include "freezing.h"

freezing::freezing() {
	SetType("freezing");
	SetBasePicPath("resources/Base_freezing.bmp");
	SetTowerName("冰凍");
	upgradeIcons = { 0,5,6,7 };
	Barrel = std::make_shared<freezingBarrel>();
	range = 2;
	totalCost = 70;
	freezeing_persentage = 0.2;
	freeze_time = 2.5;
	defrosting_time = 1;
}
void freezing::move(double time, double x, double y, std::vector<std::shared_ptr<enemy>> Enemy) {
	for (std::shared_ptr<enemy> e : Enemy) {
		if (sqrt(pow( x + 0.5 - e->GetX(), 2) + pow( y + 0.5 - e->GetY(), 2)) <= range) {
			bool alreadyInside = false;
			for (size_t i = 0; i < inRange.size();i++) {
				if (e == inRange[i]) {
					alreadyInside = true;
					inTime[i] += time;
					break;
				}
			}
			if (!alreadyInside) {
				inRange.push_back(e);
				inTime.push_back(0.0);
			}
		}
	}
	for (size_t i = 0; i < inRange.size(); i++) {
		if (inTime[i] >= freeze_time) {
			inRange[i]->GetSlow(freezeing_persentage,defrosting_time);
		}
		if (inRange[i]->IsDied() || sqrt(pow(x + 0.5 - inRange[i]->GetX(), 2) + pow(y + 0.5 - inRange[i]->GetY(), 2)) > range) {
			inRange.erase(inRange.begin() + i);
			inTime.erase(inTime.begin() + i);
			continue;
		}
	}
}
double freezing::GetRange() {
	return range;
}
std::vector<int> freezing::GetUpgradeCost() {
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
std::vector<std::string> freezing::GetAttributeName() {
	return { "範圍" ,"冰凍率","冰凍時間","解凍時間","#毒藥持續時間" };
}
std::vector<std::string> freezing::GetAttributeValue() {
	std::vector<std::string> result = {};
	result.push_back(std::to_string(this->range));
	result.push_back(std::to_string(this->freezeing_persentage * 100) + "%");
	result.push_back(std::to_string(this->freeze_time) + "/s");
	result.push_back(std::to_string(this->defrosting_time) + "/s");
	result.push_back("+1.50s");
	return result;
}
std::vector<std::vector<double>> freezing::GetAffected(int type) {
	//type是升級選項 1/2/3/4 回傳{影響第幾項屬性,影響值}
	if (type == 1) {
		return { {0,rangeUpgrade.at(upgradeLevel[0])} };
	}
	else if (type == 2) {
		return { {1,freezePercentUpgrade.at(upgradeLevel[1])} };
	}
	else if (type == 3) {
		return { {2,freezeTimeUpgrade.at(upgradeLevel[2])} };
	}
	else if (type == 4) {
		return { {3,defrostingTimeUpgrade.at(upgradeLevel[3])} };
	}
	return {};
}
void freezing::upgrade1() {
	range += rangeUpgrade.at(upgradeLevel[0]);
	totalCost += upgradeCost[0].at(upgradeLevel[0]);
	upgradeLevel[0] += 1;
}
void freezing::upgrade2() {
	freezeing_persentage += freezePercentUpgrade.at(upgradeLevel[1]);
	totalCost += upgradeCost[1].at(upgradeLevel[1]);
	upgradeLevel[1] += 1;
}
void freezing::upgrade3() {
	freeze_time += freezeTimeUpgrade.at(upgradeLevel[2]);
	totalCost += upgradeCost[2].at(upgradeLevel[2]);
	upgradeLevel[2] += 1;
}
void freezing::upgrade4() {
	defrosting_time += defrostingTimeUpgrade.at(upgradeLevel[3]);
	totalCost += upgradeCost[3].at(upgradeLevel[3]);
	upgradeLevel[3] += 1;
}