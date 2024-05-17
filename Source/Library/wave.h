#pragma once

#include "stdafx.h"
#include "gameutil.h"
#include <vector>

class Wave{
public:
	Wave();
	int GetWave();
	double GetdelayTime();
	int GetRemainingCount();
	double GetCd15();

	std::string enemyType(int wave);
	int enemyCount(std::string eType, int wave);
	void showStartText();
	void showWaveText();
	void showClock();
	void showCD();
	bool IsClockClicked(CPoint point);
	void loadClockPic();
	void NextWave();
	void AccDelayTime(double time);
	void SetDelayTime(double time);
	void SetRemainingCount(int count);
	void SetCd15(double time);
	void ReduceCd(double time);
	void nextLevel();

	bool Start = false;

private:
	game_framework::CMovingBitmap clock;
	int wave = 0;
	double delayTime = 0.0; //�ĤH���j
	int RemainingCount = 0; //�ĤH�Ѿl�ƶq
	int MaxRemainingCount = 0; //�ĤH�̤j�ƶq
	double cd15 = 0;
};
