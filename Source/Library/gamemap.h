#pragma once

#include "block.h"
#include <string>
#include <vector>
#include <memory>

class gamemap {
public:
	gamemap();
	gamemap(int size);
	void setScale(double scale);
	void newblocktest(block Block) {
		testmap.push_back(Block);
	}
	void newblock(std::shared_ptr<block> block);
	//讓整張地圖顯示
	void drawmap();

private:
	int size = 32;
	std::vector<block> testmap;
	std::vector<std::shared_ptr<block>> map;
	double scale = 1.0;
};