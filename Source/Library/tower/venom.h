#include "tower.h"
#include <stdlib.h>
#include <time.h>

class venom : public tower {
public:
	venom();
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
protected:
	void findTarget(double x, double y, std::vector<std::shared_ptr<enemy>> Enemy) override;
private:
	std::vector<std::vector<int>> upgradeCost = { {84,127,196,309,498,820,1380,2371,4321,7654},//-2
		{134,185,261,376,553,830,1270,1982,3061,4259},//-2
		{49,65,89,122,170,247,352,514,754,1146},
		{78,114,168,261,409,651,1097,1900,3303,4837}};//-1
	std::vector<double> rangeUpgrade = { 0.273, 0.315, 0.317, 0.346, 0.349, 0.357, 0.397, 0.449, 0.497, 0.554 };//-3
	std::vector<double> poisonDamageUpgrade = { 1.87, 1.89, 2.11, 2.06, 2.07, 2.15, 2.59, 2.61, 3.14, 3.11 };//-3
	std::vector<double> attackSpeedUpgrade = { 0.136, 0.156, 0.168, 0.173, 0.182, 0.198, 0.191, 0.212, 0.211, 0.215 };//-1
	std::vector<double> rotataionSpeedUpgrade = { 16.2, 18.4, 20.2, 22.1, 23.1, 26.4, 29.3, 30, 31.2, 32.4 };//-2
	std::vector<double> projectileSpeedUpgrade = { 0.402, 0.441, 0.522, 0.576, 0.567, 0.576, 0.699, 0.696, 0.69 ,0.71 };//-2
	double coolDown;
	double range;
	double poisonDamage;
	double attackSpeed; //攻擊次數/每秒
	double rotataionSpeed; //旋轉速度/每秒 (還沒實作)
	double projectileSpeed;
	double poisonDuration;

};