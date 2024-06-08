#include "tower.h"
#include <stdlib.h>
#include <time.h>

class air : public tower {
public:
	air();
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
	std::vector<std::vector<int>> upgradeCost = { {42,65,103,167,278,474,829,1486,2729,5164},//-1
		{67,100,153,240,386,636,1073,1852,3269,5241},//-1
		{41,59,90,142,221,367,603,1041,1788,3173},
		{47,71,111,181,297,511,894,1612,2961,4987}};//-1
	std::vector<double> rangeUpgrade = { 0.405, 0.441, 0.468, 0.486, 0.509, 0.495, 0.477, 0.549, 0.501, 0.506 };//-2
	std::vector<double> damageUpgrade = { 5.1, 6.64, 6.86, 7.48, 7.87, 9.43, 10.1, 10.6, 11.5, 12.3 };//-2
	std::vector<double> attackSpeedUpgrade = { 0.416, 0.496, 0.58, 0.652, 0.616, 0.724, 0.788, 0.752, 0.82, 0.85 };//-1
	std::vector<double> rotataionSpeedUpgrade = { 7.8, 9.6, 11.7, 11.4, 13, 14.5, 16.2, 18.2, 20.4, 21.3 };//-2
	std::vector<double> projectileSpeedUpgrade = { 0.416, 0.486, 0.541, 0.547, 0.65, 0.688, 0.726, 0.72, 0.77 ,0.82 };//-2
	double coolDown;
	double range;
	double damage;
	double attackSpeed; //攻擊次數/每秒
	double rotataionSpeed; //旋轉速度/每秒 (還沒實作)
	double projectileSpeed;
	double burningChance;

};