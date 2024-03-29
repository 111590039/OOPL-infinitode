#include "stdafx.h"
#include "barrel.h"


barrel::barrel() {

}
barrel::barrel(std::string type):type(type) {

}
void barrel::loadPic() {
	LoadBitmapByString( barrelPicPaths, RGB(255, 255, 255));
}
void barrel::show(int scale) {
	ShowBitmap(scale);
}
void barrel::resetShow(int TOP, int LEFT, int TILE_SIZE, double scale, int moveX, int moveY, int x, int y) {
	SetTopLeft(int(LEFT + moveX + x * TILE_SIZE*scale), int(TOP + moveY + y * TILE_SIZE*scale));
}
