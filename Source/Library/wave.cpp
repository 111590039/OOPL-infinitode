#include "stdafx.h"
#include "wave.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamecore.h"
#include <string>
#include <stdlib.h>
#include <math.h>
#include <time.h>

Wave::Wave() {

}
int Wave::GetWave() {
	return wave;
}
double Wave::GetdelayTime() {
	return delayTime;
}
int Wave::GetRemainingCount() {
	return RemainingCount;
}
double Wave::GetCd15() {
	return cd15;
}
std::string Wave::GetEnemyType() {
	return enemytype;
}
bool Wave::GetStart() {
	return Start;
}
void Wave::SetWave(int wave) {
	this->wave = wave;
}
void Wave::AccDelayTime(double time) {
	this->delayTime += time;
}
void Wave::SetDelayTime(double time) {
	this->delayTime = time;
}
void Wave::SetRemainingCount(int count) {
	this->RemainingCount = count;
	this->MaxRemainingCount = count;
}
void Wave::SetCd15(double time) {
	this->cd15 = time;
}
void Wave::ReduceCd(double time) {
	this->cd15 -= time;
}
void Wave::nextLevel() {
	this->wave += 1;
}
void Wave::enemyType(int wave) {
	int RegularProb = 0, FastProb = 0, StrongProb = 0, DenseRegularProb = 0, AirProb = 0, JetProb = 0, Lightprob = 0, IcyProb = 0, ToxicProb = 0;

	RegularProb = 10 - (int)(wave / 28);
	if (RegularProb < 1) RegularProb = 1;
	if (wave > 300) RegularProb = 0;

	if (wave < 7) {
		FastProb = 0;
	}
	else {
		FastProb = 1; //+ (int)(difficulty / 10)
		if (FastProb > 5) FastProb = 5;
	}

	if (wave < 15) { 
		StrongProb = 0;
	}
	else {
		StrongProb = 1 + (int)(wave / 15);
		if (StrongProb > 4) StrongProb = 4;
	}

	if (wave < 20) { 
		DenseRegularProb = 0;
	}
	else {
		DenseRegularProb = 1 + (int)(wave / 50);
		if (DenseRegularProb > 5) DenseRegularProb = 5;
	}

	if (wave < 10) { 
		AirProb = 0;
	}
	else {
		AirProb = 1 + (int)(wave / 20);
		if (AirProb > 4) AirProb = 4;
	}

	if (wave < 75){ 
		JetProb = 0;
	}
	else {
		int JetProb = 1 + (int)(wave / 70);
		if (JetProb > 5) JetProb = 5;
	}

	if (wave < 40) { 
		Lightprob = 0;
	}
	else { 
		int Lightprob = 1 + (int)(wave / 35);
		if (Lightprob > 5) Lightprob = 5;
	}

	if (wave < 40) { 
		IcyProb = 0; 
	}
	else { 
		int IcyProb = 1 + (int)(wave / 80);
		if (IcyProb > 4) IcyProb = 4;
	}

	if (wave < 120) { 
		ToxicProb = 0; 
	}
	else { 
		int ToxicProb = 1 + (int)((wave - 120) / 20);
		if (ToxicProb > 5) ToxicProb = 5;
		if (ToxicProb >= 5) {
			ToxicProb -= (int)((wave - 240) / 40);
			if (ToxicProb < 0) ToxicProb = 0;
		}
	}

	int TotalProb = RegularProb + FastProb + StrongProb + DenseRegularProb + AirProb + JetProb + Lightprob + IcyProb + ToxicProb;
	srand(unsigned int(time(NULL)));
	int x = rand() % (TotalProb + 1);

	if (x < RegularProb) {
		enemytype = "Regular";
	}
	else if (x < RegularProb + FastProb) {
		enemytype = "Fast";
	}
	else if (x < RegularProb + FastProb + StrongProb) {
		enemytype = "Strong";
	}
	else if (x < RegularProb + FastProb + StrongProb + DenseRegularProb) {
		enemytype = "DenseRegular";
	}
	else if (x < RegularProb + FastProb + StrongProb + DenseRegularProb + AirProb) {
		enemytype = "Air";
	}
	else if (x < RegularProb + FastProb + StrongProb + DenseRegularProb + AirProb + JetProb) {
		enemytype = "Jet";
	}
	else if (x < RegularProb + FastProb + StrongProb + DenseRegularProb + AirProb + JetProb + Lightprob) {
		enemytype = "Light";
	}
	else if (x < RegularProb + FastProb + StrongProb + DenseRegularProb + AirProb + JetProb + Lightprob + IcyProb) {
		enemytype = "Icy";
	}
	else if (x < RegularProb + FastProb + StrongProb + DenseRegularProb + AirProb + JetProb + Lightprob + IcyProb + ToxicProb) {
		enemytype = "Toxic";
	}
	else {
		enemytype = "Regular";
	}

	if (wave % 20 == 0) {
		enemytype = "Boss";
	}

	if (wave % 100 == 0) {
		enemytype = "SuperBoss";
	}
}
int Wave::enemyCount(std::string eType, int wave) {
	if (eType == "Regular") {
		return 12 + int(floor(pow(wave, 0.65)));
	}
	else if (eType == "Fast") {
		return 10 + int(floor(pow(wave * 0.8, 0.65)));
	}
	else if (eType == "Strong") {
		this->MaxRemainingCount = 12 + int(floor(pow(wave, 0.65)));
		return 5 + int(floor(pow(wave * 0.4, 0.65)));
	}
	else if (eType == "DenseRegular") {
		return 16 + int(floor(pow(wave * 1.2, 0.65)));
	}
	else if (eType == "Air") {
		return 6 + int(floor(pow(wave / 12, 0.65)));
	}
	else if (eType == "Jet") {
		return 6 + int(floor(pow(wave / 10, 0.7)));
	}
	else if (eType == "Light") {
		return 10 + int(floor(pow(wave, 0.6)));
	}
	else if (eType == "Icy") {
		return 24 + int(floor(pow(wave * 1.5, 0.7)));
	}
	else if (eType == "Toxic") {
		return 7 + int(floor(pow(wave * 0.55, 0.62)));
	}
	else if (eType == "SuperBoss") {
		return 1;
	}
	else if (eType == "Boss") {
		return 2 + int(floor(pow(wave / 12, 0.6))) + 1 + 3 + int(floor(pow(wave / 8, 0.6)));
	}
	else {
		return 12 + int(floor(pow(wave, 0.65)));
	}
}
void Wave::showStartText() {
	CDC *pDC = game_framework::CDDraw::GetBackCDC();
	game_framework::CTextDraw::ChangeFontLog(pDC, 21, "微軟正黑體", RGB(255, 255, 255), 800);
	game_framework::CTextDraw::Print(pDC, 1225, 820, "Start");
	game_framework::CDDraw::ReleaseBackCDC();
}
void Wave::showWaveText() {
	CDC *pDC = game_framework::CDDraw::GetBackCDC();
	game_framework::CTextDraw::ChangeFontLog(pDC, 21, "微軟正黑體", RGB(255, 255, 255), 800);
	game_framework::CTextDraw::Print(pDC, 1200, 820, "Wave: " + std::to_string(wave));
	game_framework::CDDraw::ReleaseBackCDC();
}
void Wave::loadClockPic() {
	std::string clockPicPath = "resources/BlueClock.bmp";
	std::string clockPicPath2 = "resources/GrayClock.bmp";
	clock.LoadBitmapByString({ clockPicPath, clockPicPath2 }, RGB(255, 255, 255));
	clock.SetTopLeft(1300, 800);
}
void Wave::showClock() {
	clock.ShowBitmap(0.25);
}
void Wave::showCD() {
	CDC *pDC = game_framework::CDDraw::GetBackCDC();
	game_framework::CTextDraw::ChangeFontLog(pDC, 21, "微軟正黑體", RGB(255, 255, 255), 800);
	game_framework::CTextDraw::Print(pDC, 1330, 830, std::to_string(cd15));
	game_framework::CDDraw::ReleaseBackCDC();
}
bool Wave::IsClockClicked(CPoint point) {
	if (1337 >= point.x && point.x >= 1300 && 846 >= point.y && point.y >= 800) {
		if (Start == true) {
			clockClicked = true;
		}
		Start = true;
		clock.SetFrameIndexOfBitmap(1);
	}
	return false;
}

void Wave::Restart() {
	wave = 0;
	delayTime = 0.0; //敵人間隔
	RemainingCount = 0; //敵人剩餘數量
	MaxRemainingCount = 0; //敵人最大數量
	cd15 = 0;
	Start = false;
	clock.SetFrameIndexOfBitmap(0);
}

void Wave::SkipWave() {
	if (clockClicked) {
		cd15 = 0;
		clockClicked = false;
	}
	clock.SetFrameIndexOfBitmap(0);
}