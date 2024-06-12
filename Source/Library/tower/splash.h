#include "tower.h"
#include <stdlib.h>
#include <time.h>

class splash : public tower {
public:
	splash();
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
	std::vector<std::vector<int>> upgradeCost = { {51,79,125,203,338,578,1015,1827,2371,4239},//-1
		{71,101,145,211,311,464,701,1073,1664,2613},
		{33,43,57,80,110,160,229,335,519,801},
		{53,75,111,168,261,428,716,1211,2127,3198}};//??
	std::vector<double> rangeUpgrade = { 0.241, 0.268, 0.248, 0.272, 0.274, 0.279, 0.305, 0.311, 0.324, 0.336 };//-2
	std::vector<double> damageUpgrade = { 2.32, 3.25, 3.56, 4.08, 4.62, 4.98, 4.76, 5.13, 5.54, 5.86 };//-1
	std::vector<double> attackSpeedUpgrade = { 0.173, 0.187, 0.192, 0.209, 0.216, 0.211, 0.245, 0.243, 0.229, 0.267 };
	std::vector<double> projectileSpeedUpgrade = { 0.535, 0.61, 0.67, 0.694, 0.799, 0.772, 0.802, 0.802, 0.815 ,0.821 };//*3
	double coolDown;
	double range;
	double damage;
	double attackSpeed; //§ðÀ»¦¸¼Æ/¨C¬í
	double accuracy;
	double projectileSpeed;
	double projectileCount;
	std::shared_ptr<enemy> last_target = nullptr;
	double angle;
	int counter;
};