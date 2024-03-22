#include "stdafx.h"
#include "gamemap.h"
#define TOP 0
#define LEFT 0
#define TILE_SIZE 65

gamemap::gamemap() {

}
gamemap::gamemap(int size) {

}
void gamemap::addScale(double delta) {
	scale = max(scale + delta, 0.1);
}
void gamemap::addMoveX(int delta) {
	moveX = max(moveX + delta, -100);
}
void gamemap::addMoveY(int delta) {
	moveY  = max(moveY + delta, -100);
}
double gamemap::GetScale() {
	return scale;
}
//讓整張地圖顯示
void gamemap::drawmap() {
	for (std::shared_ptr<block> b : map) {
		b->ShowBitmap(scale);
	}
}
void gamemap::loadpic() {
	for (std::shared_ptr<block> b : map) {
		b->LoadBitmapByString({ b->GetPicPath() },RGB(255,255,255));
		b->SetTopLeft(LEFT + b->GetX()*TILE_SIZE, TOP + b->GetY()*TILE_SIZE);
	}
}
void gamemap::resetshow() {
	for (std::shared_ptr<block> b : map) {
		b->SetTopLeft(int(LEFT + moveX + b->GetX()*TILE_SIZE*scale), int(TOP + moveY + b->GetY()*TILE_SIZE*scale));
	}
}
void gamemap::newblock(std::shared_ptr<block> block) {
	map.push_back(block);
}
void gamemap::TESTMAP1() {
	newblock(std::make_shared<portal>(1,0,0.7));
	newblock(std::make_shared<road>(1, 1));
	newblock(std::make_shared<road>(1, 2));
	newblock(std::make_shared<road>(1, 3));
	newblock(std::make_shared<road>(1, 4));
	newblock(std::make_shared<road>(1, 5));
	newblock(std::make_shared<road>(1, 5));
	newblock(std::make_shared<road>(2, 5));
	newblock(std::make_shared<road>(3, 5));
	newblock(std::make_shared<road>(4, 5));
	newblock(std::make_shared<road>(5, 5));
	newblock(std::make_shared<base>(6, 5));
}
