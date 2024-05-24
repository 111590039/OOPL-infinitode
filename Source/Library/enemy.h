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
	int GetDamage();
	bool GetSlow();
	bool GetPoisoned();
	bool GetBurning();
	bool GetDizzy();

	std::string GetPicPath();
	void show(double scale);
	void loadPic();       //Åª¨ú¹Ï¤ù
	void resetShow(int TOP, int LEFT, int TILE_SIZE, double scale, int moveX, int moveY);
	int targetPos = 1;
	bool enemyMove(double time);
	void GetDamage(double damage);
	bool IsDied();
	bool IsSurvive = true;
	virtual void GetSlow(double slowEffect, double slowTime);
	virtual void GetPoisoned(double poisonedEffect, double poisonedTime);
	virtual void GetBurning(double burningEffect, double burningTime);
	virtual void GetDizzy(double dizzyTime);

protected:
	void Sethealth(double health);
	void Setspeed(double speed);
	void Setbounty(double bounty);
	void Setexp(double exp);
	void SetX(double x);
	void SetY(double y);
	void SetMaxHealth(double health);
	void SetType(std::string type);
	void SetPicPath(std::string picPath);
	void SetSlowTime(double time);
	void SetPoisonedTime(double time);
	void SetBurningTime(double time);
	void SetDizzyTime(double time);

private:
	double x, y;
	std::string type;
	std::string picPath;
	int damage = 1;
	double difficulty = 1, health, speed, bounty, exp, maxHealth;
	std::vector<CPoint> enemyPath;
	game_framework::CMovingBitmap HealthBar;
	bool Slow = false;
	bool Poisoned = false;
	bool Burning = false;
	bool Dizzy = false;
	double slowEffect;
	double PoisonedEffect;
	double BurningEffect;
	double SlowTime = 0.0;
	double PoisonedTime = 0.0;
	double BurningTime = 0.0;
	double DizzyTime = 0.0;
};

class Regular : public enemy {
public:
	Regular(double difficulty, int wave, std::vector<CPoint> enemyPath);
};

class Fast : public enemy {
public:
	Fast(double difficulty, int wave, std::vector<CPoint> enemyPath);
};

class Strong : public enemy {
public:
	Strong(double difficulty, int wave, std::vector<CPoint> enemyPath);
};

class DenseRegular : public enemy {
public:
	DenseRegular(double difficulty, int wave, std::vector<CPoint> enemyPath);
};

class Air : public enemy {
public:
	Air(double difficulty, int wave, std::vector<CPoint> enemyPath);
};