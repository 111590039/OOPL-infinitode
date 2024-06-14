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
double enemy::GetDamage() {
	return damage;
}
double enemy::GetMaxSpeed() {
	return MaxSpeed;
}
bool enemy::GetSlow() {
	return Slow;
}
bool enemy::GetPoisoned() {
	return Poisoned;
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
void enemy::SetDamage(double damage) {
	this->damage = damage;
}
void enemy::SetMaxSpeed(double MaxSpeed) {
	this->MaxSpeed = MaxSpeed;
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
	this->Slow = true;
	this->SlowTime = slowTime;
	Setspeed(GetMaxSpeed() * (1 - slowEffect));
}
void enemy::GetPoisoned(double poisonedEffect, double poisonedTime) {
	this->Poisoned = true;
	this->PoisonedEffect = poisonedEffect;
	this->PoisonedTime = poisonedTime;
}
void enemy::GetBurning() {
	this->Burning = true;
}
void enemy::GetDizzy(double dizzyTime) {
	this->Dizzy = true;
	this->DizzyTime = dizzyTime;
	Setspeed(0);
}
void enemy::Effect(double time) {
	if (Slow) {
		SlowTime = SlowTime - time;
		if (SlowTime <= 0) {
			Slow = false;
			Setspeed(GetMaxSpeed());
		}
	}
	if (Poisoned) {
		GetDamage(PoisonedEffect * time);
		//health = health - PoisonedEffect * time;
		PoisonedTime = PoisonedTime - time;
		if (PoisonedTime <= 0) {
			Poisoned = false;
		}
	}
	if (Burning) {
		GetDamage(0.2 * maxHealth * time); 
		//health = health - (0.2 * maxHealth * time);
	}
	if (Dizzy) {
		DizzyTime = DizzyTime - time;
		if (DizzyTime <= 0) {
			Dizzy = false;
			Setspeed(GetMaxSpeed());
		}
	}
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
	SetType("Regular");
	Sethealth(4.1 + pow(wave * 0.4, 1.67));
	SetMaxHealth(Gethealth());
	Setspeed(1.0);
	SetMaxSpeed(Getspeed());
	Setbounty(2 + pow(wave * 0.45, 0.6));
	Setexp(0.75);
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
	SetType("Fast");
	Sethealth(2.95 + pow(wave * 0.45, 1.695));
	SetMaxHealth(Gethealth());
	Setspeed(1.4 + pow(wave / 1500, 1.25));
	SetMaxSpeed(Getspeed());
	Setbounty(4 + pow(wave, 0.55));
	Setexp(1.0);
	SetPicPath("resources/enemy_Fast.bmp");
}

Strong::Strong(double difficulty, int wave, std::vector<CPoint> enemyPath) : enemy(difficulty, wave, enemyPath) {
	SetType("Strong");
	Sethealth(8.2 + pow(wave * 0.69, 1.7));
	SetMaxHealth(Gethealth());
	Setspeed(0.85);
	SetMaxSpeed(Getspeed());
	Setbounty(8 + pow(wave * 2, 0.6));
	Setexp(1.0);
	SetDamage(2.0);
	SetPicPath("resources/enemy_Strong.bmp");
}

DenseRegular::DenseRegular(double difficulty, int wave, std::vector<CPoint> enemyPath) : enemy(difficulty, wave, enemyPath) {
	SetType("Regular");
	Sethealth(4.1 + pow(wave * 0.4, 1.67));
	SetMaxHealth(Gethealth());
	Setspeed(1);
	SetMaxSpeed(Getspeed());
	Setbounty(2 + pow(wave * 0.45, 0.6));
	Setexp(1.0);
	SetPicPath("resources/enemy_Regular.bmp");
}

Air::Air(double difficulty, int wave, std::vector<CPoint> enemyPath) : enemy(difficulty, wave, enemyPath) {
	SetType("Air");
	Sethealth(3.4 + pow(wave * 0.5, 1.7));
	SetMaxHealth(Gethealth());
	Setspeed(1);
	SetMaxSpeed(Getspeed());
	Setbounty(4 + pow(wave, 0.6));
	Setexp(1.0);
	SetPicPath("resources/enemy_Air.bmp");
}

Jet::Jet(double difficulty, int wave, std::vector<CPoint> enemyPath) : enemy(difficulty, wave, enemyPath) {
	SetType("Jet");
	Sethealth(1.7 + pow(wave * 0.21, 1.71));
	SetMaxHealth(Gethealth());
	Setspeed(1.25);
	SetMaxSpeed(Getspeed());
	Setbounty(4 + pow(wave, 0.6));
	Setexp(1.0);
	SetPicPath("resources/enemy_Jet.bmp");
}

BossArmored::BossArmored(double difficulty, int wave, std::vector<CPoint> enemyPath) : enemy(difficulty, wave, enemyPath) {
	SetType("Armored");
	Sethealth(2.0 + pow(wave * 0.35, 1.68));
	SetMaxHealth(Gethealth());
	Setspeed(1);
	SetMaxSpeed(Getspeed());
	Setbounty(4 + pow(wave, 0.6));
	Setexp(1.0);
	SetPicPath("resources/enemy_Armored.bmp");
}

BossFast::BossFast(double difficulty, int wave, std::vector<CPoint> enemyPath) : enemy(difficulty, wave, enemyPath) {
	SetType("Fast");
	Sethealth(2.45 + pow(wave * 0.4, 1.695));
	SetMaxHealth(Gethealth());
	Setspeed(1.5);
	SetMaxSpeed(Getspeed());
	Setbounty(4 + pow(wave, 0.6));
	Setexp(1);
	SetPicPath("resources/enemy_Fast.bmp");
}

BossFighter::BossFighter(double difficulty, int wave, std::vector<CPoint> enemyPath) : enemy(difficulty, wave, enemyPath) {
	SetType("Fighter");
	Sethealth(10 + pow(wave * 1.2, 1.75));
	SetMaxHealth(Gethealth());
	Setspeed(0.95);
	SetMaxSpeed(Getspeed());
	Setbounty(24 + pow(wave * 5, 0.6));
	Setexp(1);
	SetPicPath("resources/enemy_Fighter.bmp");
}

Boss::Boss(double difficulty, int wave, std::vector<CPoint> enemyPath) : enemy(difficulty, wave, enemyPath) {
	SetType("Boss");
	Sethealth(28 + pow(wave * 1.92 *0.75, 1.83));
	SetMaxHealth(Gethealth());
	Setspeed(0.7);
	SetMaxSpeed(Getspeed());
	Setbounty(100 + pow(wave * 70, 0.75));
	Setexp(1);
	SetDamage(25.0);
	SetPicPath("resources/enemy_Boss.bmp");
}

Light::Light(double difficulty, int wave, std::vector<CPoint> enemyPath) : enemy(difficulty, wave, enemyPath) {
	SetType("Light");
	Sethealth(4.1 + pow(wave * 0.50, 1.68));
	SetMaxHealth(Gethealth());
	Setspeed(1.05);
	SetMaxSpeed(Getspeed());
	Setbounty(4 + pow(wave * 0.95, 0.55));
	Setexp(1);
	SetPicPath("resources/enemy_Light.bmp");
}

Icy::Icy(double difficulty, int wave, std::vector<CPoint> enemyPath) : enemy(difficulty, wave, enemyPath) {
	SetType("Icy");
	Sethealth(5.4 + pow(wave * 0.59, 1.51));
	SetMaxHealth(Gethealth());
	Setspeed(0.9);
	SetMaxSpeed(Getspeed());
	Setbounty(1.5 + pow(wave * 0.26, 0.6));
	Setexp(1);
	SetPicPath("resources/enemy_Icy.bmp");
}

Toxic::Toxic(double difficulty, int wave, std::vector<CPoint> enemyPath) : enemy(difficulty, wave, enemyPath) {
	SetType("Toxic");
	Sethealth(4.1 + pow(wave * 0.49, 1.67));
	SetMaxHealth(Gethealth());
	Setspeed(1.0);
	SetMaxSpeed(Getspeed());
	Setbounty(3.5 + pow(wave * 0.94, 0.55));
	Setexp(1);
	SetPicPath("resources/enemy_Toxic.bmp");
}