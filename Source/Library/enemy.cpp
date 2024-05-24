#include "stdafx.h"
#include "enemy.h"
enemy::enemy(double difficulty, int wave, std::vector<CPoint> enemyPath):enemyPath(enemyPath){
	SetX(1.5);
	SetY(0.5);
}
std::string enemy::GetType() {
	return type;
}
double enemy::Gethealth() {
	return health;
}
double enemy::Getspeed() {
	return speed;
}
double enemy::Getbounty() {
	return bounty;
}
double enemy::Getexp() {
	return exp;
}
double enemy::GetX() {
	return x;
}
double enemy::GetY() {
	return y;
}
int enemy::GetDamage() {
	return damage;
}
bool enemy::GetSlow() {
	return Slow;
}
bool enemy::GetPoisoned() {
	return Poisoned;
}
bool enemy::GetBurning() {
	return Burning;
}
bool enemy::GetDizzy() {
	return Dizzy;
}
void enemy::SetType(std::string type) {
	this->type = type;
}
void enemy::Sethealth(double health) {
	this->health = health;
}
void enemy::Setspeed(double speed) {
	this->speed = speed;
}
void enemy::Setbounty(double bounty) {
	this->bounty = bounty;
}
void enemy::Setexp(double exp) {
	this->exp = exp;
}
void enemy::SetX(double x) {
	this->x = x;
}
void enemy::SetY(double y) {
	this->y = y;
}
void enemy::SetMaxHealth(double health) {
	this->maxHealth = health;
}
void enemy::show(double scale) {
	ShowBitmap(scale);
	HealthBar.ShowBitmap(scale);
}
void enemy::SetPicPath(std::string picPath) {
	this->picPath = picPath;
}
void enemy::SetSlowTime(double time) {
	this->SlowTime = time;
}
void enemy::SetPoisonedTime(double time) {
	this->PoisonedTime = time;
}
void enemy::SetBurningTime(double time) {
	this->BurningTime = time;
}
void enemy::SetDizzyTime(double time) {
	this->DizzyTime = time;
}
void enemy::GetDamage(double damage) {
	health = health - damage;
	if (health / maxHealth >= 0.75) {
		HealthBar.SetFrameIndexOfBitmap(0);
	}
	else if (health / maxHealth >= 0.5) {
		HealthBar.SetFrameIndexOfBitmap(1);
	}
	else if (health / maxHealth >= 0.25) {
		HealthBar.SetFrameIndexOfBitmap(2);
	}
	else {
		HealthBar.SetFrameIndexOfBitmap(3);
	}
}
bool enemy::IsDied() {
	return (health <= 0);
}
void enemy::GetSlow(double slowEffect, double slowTime) {
	this->SlowTime = slowTime;
}
void enemy::GetPoisoned(double poisonedEffect, double poisonedTime) {
	this->PoisonedTime = poisonedTime;
}
void enemy::GetBurning(double burningEffect, double burningTime) {
	this->BurningTime = burningTime;
}
void enemy::GetDizzy(double dizzyTime) {
	this->DizzyTime = dizzyTime;
}
std::string enemy::GetPicPath() {
	return picPath;
}
bool enemy::enemyMove(double time) {
	if (y < enemyPath[targetPos].y + 0.5){
		y += time * speed;
		if (y > enemyPath[targetPos].y + 0.5) {
			y = enemyPath[targetPos].y + 0.5;
			targetPos += 1;
		}
	}
	else if (y > enemyPath[targetPos].y + 0.5) {
		y -= time * speed;
		if (y < enemyPath[targetPos].y + 0.5) {
			y = enemyPath[targetPos].y + 0.5;
			targetPos++;
		}
	}
	else if (x < enemyPath[targetPos].x + 0.5) {
		x += time * speed;
		if (x > enemyPath[targetPos].x + 0.5) {
			x = enemyPath[targetPos].x + 0.5;
			targetPos++;
		}
	}
	else if (x > enemyPath[targetPos].x + 0.5) {
		x -= time * speed;
		if (x < enemyPath[targetPos].x + 0.5) {
			x = enemyPath[targetPos].x + 0.5;
			targetPos++;
		}
	}
	if (targetPos == (int)enemyPath.size()) {
		return true;
	}
	return false;
}
Regular::Regular(double difficulty, int wave, std::vector<CPoint> enemyPath) : enemy(difficulty, wave, enemyPath) {
	Sethealth(4 + pow(wave * 7.0, 1.3));
	SetMaxHealth(Gethealth());
	Setspeed(1.0);
	Setbounty(2.0);
	Setexp(1.0);
	SetPicPath("resources/enemy_Regular.bmp");
}

void enemy::loadPic() {
	LoadBitmapByString({ GetPicPath() }, RGB(255, 255, 255));
	HealthBar.LoadBitmapByString({ "resources/health_bar_100.bmp", 
									"resources/health_bar_75.bmp", 
									"resources/health_bar_50.bmp", 
									"resources/health_bar_25.bmp" }, RGB(255, 255, 255));
}

void enemy::resetShow(int TOP, int LEFT, int TILE_SIZE, double scale, int moveX, int moveY) {
	SetTopLeft(int(LEFT + moveX + GetX() * TILE_SIZE*scale), int(TOP + moveY + GetY()* TILE_SIZE*scale));
	HealthBar.SetTopLeft(int(LEFT + moveX + GetX() * TILE_SIZE*scale - 3 * scale), int(TOP + moveY + GetY()* TILE_SIZE*scale - 7 * scale));
}

Fast::Fast(double difficulty, int wave, std::vector<CPoint> enemyPath) : enemy(difficulty, wave, enemyPath) {
	Sethealth(2.95 + pow(wave * 0.45, 1.695));
	SetMaxHealth(Gethealth());
	Setspeed(1.4 + pow(wave / 1500, 1.25));
	Setbounty(4 + pow(wave, 0.55));
	Setexp(1.0);
	SetPicPath("resources/enemy_Fast.bmp");
}

Strong::Strong(double difficulty, int wave, std::vector<CPoint> enemyPath) : enemy(difficulty, wave, enemyPath) {
	Sethealth(8.2 + pow(wave * 0.69, 1.7));
	SetMaxHealth(Gethealth());
	Setspeed(0.85);
	Setbounty(8 + pow(wave * 2, 0.6));
	Setexp(1.0);
	SetPicPath("resources/enemy_Strong.bmp");
}

DenseRegular::DenseRegular(double difficulty, int wave, std::vector<CPoint> enemyPath) : enemy(difficulty, wave, enemyPath) {
	Sethealth(4.1 + pow(wave * 0.4, 1.67));
	SetMaxHealth(Gethealth());
	Setspeed(1);
	Setbounty(2 + pow(wave * 0.45, 0.6));
	Setexp(1.0);
	SetPicPath("resources/enemy_Regular.bmp");
}

Air::Air(double difficulty, int wave, std::vector<CPoint> enemyPath) : enemy(difficulty, wave, enemyPath) {
	Sethealth(3.4 + pow(wave * 0.5, 1.7));
	SetMaxHealth(Gethealth());
	Setspeed(1);
	Setbounty(4 + pow(wave, 0.6));
	Setexp(1.0);
	SetPicPath("resources/enemy_Air.bmp");
}