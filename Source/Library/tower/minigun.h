#include "tower.h"
#include <stdlib.h>
#include <time.h>

class minigun : public tower {
public:
	minigun();
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
	std::vector<std::vector<int>> upgradeCost = { {101,143,206,303,455,697,1088,1730,2803,4256},//-1
		{154,216,305,434,621,895,1298,1896,2654,3687},//-2
		{94,126,171,241,343,465,666,921,1293,1816},
		{71,98,138,203,302,449,697,1108,1783,2495}};//-1
	std::vector<double> rangeUpgrade = { 0.398, 0.459, 0.414, 0.454, 0.440, 0.515, 0.543, 0.507, 0.532, 0.587 };//-2
	std::vector<double> damageUpgrade = { 3.01, 3.59, 4.01, 4.08, 4.44, 4.91, 5.54, 5.98, 6.23, 6.84 };//-3
	std::vector<double> attackSpeedUpgrade = { 0.498, 0.578, 0.68, 0.676, 0.722, 0.836, 0.741, 0.885, 0.988, 1.105 };//-1
	std::vector<double> rotationSpeedUpgrade = { 14, 17.4, 19.3, 20.8, 21.0, 23.8, 26.6, 25.6, 26.8, 26.1 };//-2
	std::shared_ptr<enemy> last_target;
	double coolDown;

	double range;
	double damage;
	double attackSpeed; //攻擊次數/每秒
	double rotationSpeed; //旋轉速度/每秒 (還沒實作)
	double maxAttackSpeed;
	double attacktime;
	double speedUpTime;
};