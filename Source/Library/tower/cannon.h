#include "tower.h"
#include <time.h>

class cannon : public tower {
public:
	cannon();
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
	std::vector<std::vector<int>> upgradeCost = { {42,64,99,157,255,423,717,1243,2202,3721},//-1
		{53,81,128,209,353,615,1104,2043,3892,6199},//-1
		{24,36,54,82,128,210,341,583,1021,1841},
		{39,57,84,127,194,314,522,872,1298,1924} };//-2
	std::vector<double> rangeUpgrade = { 0.227, 0.259, 0.254, 0.273, 0.270, 0.292, 0.290, 0.308, 0.314, 0.304 };//-2
	std::vector<double> damageUpgrade = { 2.73, 3.32, 3.72, 3.83, 4.59, 4.77, 5.43, 4.99, 4.87, 4.98 };//-2
	std::vector<double> attackSpeedUpgrade = { 0.143, 0.144, 0.151, 0.157, 0.166, 0.174, 0.183, 0.176, 0.199, 0.194 };
	std::vector<double> rotataionSpeedUpgrade = { 10.8, 12.4, 13.3, 13.9, 15.5, 16.0, 17.5, 20.6, 19.6, 19.3 };//-1
	std::vector<double> projectileSpeedUpgrade = { 0.323, 0.337, 0.361, 0.396, 0.458, 0.591, 0.517, 0.561, 0.552 ,0.562 };//-1
	double coolDown;
	double range = 1.75;
	double damage = 3.1;
	double attackSpeed = 0.65; //攻擊次數/每秒
	double rotataionSpeed = 60; //旋轉速度/每秒 (還沒實作)
	double projectileSpeed = 2.2;
	double explosion_range = 0.660;
};