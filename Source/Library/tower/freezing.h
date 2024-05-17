#include "tower.h"
#include <time.h>

class freezing: public tower {
public:
	freezing();
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
	std::vector<std::vector<int>> upgradeCost = { {50,77,122,198,330,564,989,1777,3271,5267},//-1
		{79,121,191,310,516,882,1546,2777,4576,6782},//-2
		{54,81,124,196,313,510,866,1514,2714,4658}, //-1
		{51,74,110,170,271,445,754,1317,2368,3256} };//-1
	std::vector<double> rangeUpgrade = { 0.3, 0.31, 0.328, 0.336, 0.360, 0.338, 0.370, 0.364, 0.953, 0.998 };//-2
	std::vector<double> freezePercentUpgrade = { 1.4, 1.44, 1.38, 1.4, 1.44, 1.48, 1.46, 1.44, 1.46, 2.10};//-3
	std::vector<double> freezeTimeUpgrade = { -0.175, -0.205, -0.213, -0.203, -0.210, -0.195, -0.187, -0.171, -0.164, -0.172 };//-2
	std::vector<double> defrostingTimeUpgrade = { 0.175, 0.201, 0.227, 0.235, 0.258, 0.285, 0.303, 0.321, 0.345, 0.368 };//-2
	double range = 2;
	double freezeing_persentage = 20;
	double freeze_time = 2.5;
	double defrosting_time = 1;
	std::vector<enemy> inRange;
	//poison_duration = 1.5
	//tesla chain length

};