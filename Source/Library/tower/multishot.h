#include "tower.h"
#include <stdlib.h>
#include <time.h>

class multishot : public tower {
public:
	multishot();
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
	std::vector<std::vector<int>> upgradeCost = { {58,85,127,194,302,481,782,1299,2202,4239},//-1
		{77,111,162,240,362,554,862,1362,2187,3264},//-1
		{29,41,60,87,126,185,269,401,608,929},
		{53,75,111,168,261,428,716,1211,2127,3198}};//-1
	std::vector<double> rangeUpgrade = { 0.387, 0.395, 0.415, 0.455, 0.477, 0.487, 0.513, 0.537, 0.562, 0.589 };//-2
	std::vector<double> damageUpgrade = { 1.41, 1.71, 1.86, 2.06, 2.04, 2.21, 2.51, 2.64, 2.78, 2.99 };//-2
	std::vector<double> attackSpeedUpgrade = { 0.173, 0.187, 0.192, 0.209, 0.216, 0.211, 0.245, 0.243, 0.229, 0.267 };
	std::vector<double> rotataionSpeedUpgrade = { 11.6, 14.3, 14.3, 15.8, 17.4, 20, 19.6, 22.4, 25.6, 28.4 };//-2
	std::vector<double> projectileSpeedUpgrade = { 0.435, 0.51, 0.57, 0.594, 0.699, 0.672, 0.702, 0.702, 0.715 ,0.721 };//-2
	double coolDown;
	double range;
	double damage;
	double attackSpeed; //攻擊次數/每秒
	double rotataionSpeed; //旋轉速度/每秒 (還沒實作)
	double projectileSpeed;
	double shootingAngle;
	double projectileCount;
};