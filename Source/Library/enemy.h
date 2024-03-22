#pragma once

#include <string>
#include <vector>
#include "stdafx.h"
#include "gameutil.h"

class enemy : public game_framework::CMovingBitmap {
public:
	
protected:
	
private:
	std::string type;
	float count, health, speed, bounty, exp, probability;
};



/*int prob = 10 - (int)(value / 28); 
if (prob < 1) prob = 1; 
if (value > 300) prob = 0; 
return prob;*/