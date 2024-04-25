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
	Sethealth(23.0);
	SetMaxHealth(Gethealth());
	Setspeed(1.0);
	Setbounty(3.0);
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