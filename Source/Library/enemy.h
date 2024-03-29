#pragma once

#include <string>
#include <vector>
#include "stdafx.h"
#include "gameutil.h"

class enemy : public game_framework::CMovingBitmap {
public:
	enemy(std::string type, double health, double speed, double bounty, double exp);
	std::string GetType();
	double Gethealth();
	double Getspeed();
	double Getbounty();
	double Getexp();

	std::string GetPicPath();
	void show(double scale);
	virtual void loadPic() = 0;       //Ū���Ϥ�
	//virtual void show(double scale); //�QOnShow�ե� �������

protected:
	void SetType(std::string type);
	void SetXY(int x, int y);
	void SetPicPath(std::string picPath);

private:
	int x, y;
	std::string type;
	std::string picPath;
	double health, speed, bounty, exp;
};

class Regular : public enemy {
public:
	Regular(std::string type, double health, double speed, double bounty, double exp);
	void loadPic() override;       //Ū���Ϥ�
};


/* Regular
int prob = 10 - (int)(value / 28); 
if (prob < 1) prob = 1; 
if (value > 300) prob = 0; 
return prob;
*/

/* Fast
if (value < 7) { 
	return 0; 
}
else {
	int prob = 1 + (int)(difficulty / 10); 
	if (prob > 5) prob = 5; 
	return prob; 
*/

/* Strong
if (value < 15) {
	return 0;
}
else {
	int prob = 1 + (int)(value / 15);
	if (prob > 4) prob = 4;
	return prob;
}
*/

/* DenseRegular
	if (value < 20) {
	return 0;
	} else {
	int prob = 1 + (int)(value / 50);
	if (prob > 5) prob = 5;
	return prob;
	}
*/

/* Air
	if (value < 10) {
	return 0;
	} else {
	int prob = 1 + (int)(value / 20);
	if (prob > 4) prob = 4;
	return prob;
	}
*/


/*int prob = 10 - (int)(value / 28);
if (prob < 1) prob = 1;
if (value > 300) prob = 0;
return prob;*/

