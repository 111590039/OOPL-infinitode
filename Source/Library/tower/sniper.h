#include "tower.h"
#include <stdlib.h>
#include <time.h>

class sniper : public tower {
public:
	sniper();
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
	std::vector<std::vector<int>> upgradeCost = { {60,89,136,212,338,550,915,1554,2695,3947},//-1
		{107,152,220,321,484,781,1282,2098,3004,4236},//-2
		{76,102,135,189,270,383,577,886,1348,2077},
		{92,138,212,330,527,870,1487,2582,4735,7777}};//-2
	std::vector<double> rangeUpgrade = { 0.774, 0.796, 0.823, 0.824, 0.846, 0.868, 0.900, 0.922, 0.953, 0.998 };//-2
	std::vector<double> damageUpgrade = { 13.8, 19.0, 22.9, 23.1, 24.2, 31.4, 33.8, 35.7, 48.2, 49.8 };//-3
	std::vector<double> attackSpeedUpgrade = { 0.05, 0.059, 0.06, 0.068, 0.068, 0.073, 0.075, 0.078, 0.076, 0.074 };//-1
	std::vector<double> aimTimeUpgrade = { -0.042, -0.047, -0.047, -0.048, -0.047, -0.042, -0.04, -0.04, -0.038, -0.038 };//-3
	std::shared_ptr<enemy> last_target;
	double coolDown;
	double aimimgtime;
	double range = 4.5;
	double damage = 16;
	double attackSpeed = 0.2; //攻擊次數/每秒
	double rotataionSpeed = 50; //旋轉速度/每秒 (還沒實作)
	double aimTime = 0.6;
	//crit_hit_chace
	//critical_damage
};