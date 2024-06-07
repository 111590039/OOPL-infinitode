#include "tower.h"
#include <stdlib.h>
#include <time.h>

class blast: public tower {
public:
	blast();
	void move(double time, double x, double y, std::vector<std::shared_ptr<enemy>> Enemy) override;
	double GetRange() override;
	std::vector<int> GetUpgradeCost() override;
	std::vector<std::string> GetAttributeName() override;
	std::vector<std::string> GetAttributeValue() override;
	std::vector<std::vector<double>> GetAffected(int type) override;
	void upgrade1() override;
	void upgrade2() override;
	void upgrade3() override;
	void upgrade4() override;
private:
	std::vector<std::vector<int>> upgradeCost = { {91,138,216,347,571,964,1669,2961,4765,6952,9463},//-3
		{137,205,312,484,765,1232,2021,3254,4692,6847},//-3
		{79,109,155,229,337,506,801,1304,2070,3048}, //-1
		{104,150,225,349,549,908,1467,2473,4467,6752} };//-2
	std::vector<double> rangeUpgrade = { 0.245, 0.248, 0.252, 0.264, 0.254, 0.263, 0.268, 0.271, 0.267, 0.270 };//-3
	std::vector<double> damageUpgrade = { 3.43, 3.94, 4.59, 5.08, 4.94, 6.14, 7.15, 7.84, 7.63, 8.12};//-4
	std::vector<double> attackSpeedUpgrade = { 0.056, 0.07, 0.076, 0.075, 0.083, 0.089, 0.087, 0.1, 0.109, 0.112 };//-2
	std::vector<double> stunChanceUpgrade = { 1.15, 1.25, 1.36, 1.5, 1.56, 1.8, 1.81, 1.87, 1.92, 2.0 };//-3
	double coolDown;
	double range = 2;
	double damage;
	double attack_speed;
	double stun_chance;
	double stun_duration;

};