#pragma once

#include <string>
#include <vector>
#include "stdafx.h"
#include "gameutil.h"

class enemy : public game_framework::CMovingBitmap {
public:
	enemy(double difficulty, int wave, std::vector<CPoint> enemyPath);
	std::string GetType();
	double Gethealth();
	double Getspeed();
	double Getbounty();
	double Getexp();
	double GetX();
	double GetY();

	std::string GetPicPath();
	void show(double scale);
	virtual void loadPic() = 0;       //讀取圖片
	void resetShow(int TOP, int LEFT, int TILE_SIZE, double scale, int moveX, int moveY);
	int targetPos = 1;
	bool enemyMove(double time);

protected:
	void Sethealth(double health);
	void Setspeed(double speed);
	void Setbounty(double bounty);
	void Setexp(double exp);
	void SetX(double x);
	void SetY(double y);
	void SetType(std::string type);
	void SetPicPath(std::string picPath);

private:
	int wave = 1;
	double x, y;
	std::string type;
	std::string picPath;
	double difficulty = 1, health, speed, bounty, exp;
	std::vector<CPoint> enemyPath;
};

class Regular : public enemy {
public:
	Regular(double difficulty, int wave, std::vector<CPoint> enemyPath);
	void loadPic() override;       //讀取圖片
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

