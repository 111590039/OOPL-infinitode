#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
	map.loadmap();
	map.loadpic();
}

void CGameStateRun::OnMove()							// ���ʹC������
{
	
	//���ե� ��ܨ�V���������j�ɶ�(��)
	if (map.devmode) {
		CDC *pDC = game_framework::CDDraw::GetBackCDC();
		game_framework::CTextDraw::ChangeFontLog(pDC, 21, "�L�n������", RGB(255, 255, 255), 800);
		game_framework::CTextDraw::Print(pDC, 1200, 20, std::to_string((map.GetElapsedTime())));
		game_framework::CDDraw::ReleaseBackCDC();
	}
	if (!map.IsGameover()) {
		map.processMove();
	}
}

void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
{
	for (int i = 0; i < 3; i++) {
		keyboardInput[i] = 0x01;
	}
	gameoverPage.LoadBitmapByString({ "resources/gameover.bmp" });
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_UP) {
		map.addMoveY(-50);
		map.resetshow();
	}
	else if (nChar == VK_DOWN) {
		map.addMoveY(50);
		map.resetshow();
	}
	else if (nChar == VK_RIGHT) {
		map.addMoveX(50);
		map.resetshow();
	}
	else if (nChar == VK_LEFT) {
		map.addMoveX(-50);
		map.resetshow();
	}
	else if (nChar == VK_OEM_PLUS) {
		map.addScale(0.1);
		map.resetshow();
	}
	else if (nChar == VK_OEM_MINUS) {
		map.addScale(-0.1);
		map.resetshow();
	}
	/*
	else if (nChar == 0x50) {
		map.SummonTestEnemy();
	}
	else if (nChar == VK_OEM_4) {
		map.CheatCoin();
	}
	*/
	else {
		for (int i = 2; i > 0; i--) {
			keyboardInput[i] = keyboardInput[i - 1];
		}
		keyboardInput[0] = nChar;
		if (keyboardInput[2] == 0x44 && keyboardInput[1] == 0x45 && keyboardInput[0] == 0x56) {
			//dev
			map.devmode = true;
		}
		else if ((keyboardInput[2] == 0x31 && keyboardInput[1] == 0x30 && keyboardInput[0] == 0x30)\
			|| (keyboardInput[2] == 0x61 && keyboardInput[1] == 0x60 && keyboardInput[0] == 0x60)){
			//100
			map.cheat_100();
		}
		else if ((keyboardInput[2] == 0x30 && keyboardInput[1] == 0x32 && keyboardInput[0] == 0x30)  \
			|| (keyboardInput[2] == 0x60 && keyboardInput[1] == 0x62 && keyboardInput[0] == 0x60)){
			//020
			map.cheat_20();
		}
		else if (keyboardInput[2] == 0x47 && keyboardInput[1] == 0x47 && keyboardInput[0] == 0x53) {
			//ggs
			map.cheat_gameover();
		}
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	if (map.IsGameover()) {
		if (1341 >= point.x && point.x >= 1100 && 748 >= point.y && point.y >= 688) {
			map.resetGamemap();
			map.resetshow();
		}
		else if (1341 >= point.x && point.x >= 1100 && 838 >= point.y && point.y >= 773) {
			//�^���ܭ���
			gamemap temp;
			map = temp;
			GotoGameState(GAME_STATE_INIT);
		}
	}
	else {
		map.clickOnMap(point);
	}
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{

}

void CGameStateRun::OnShow()
{
	if (map.IsGameover()) {
		gameoverPage.ShowBitmap();
		CDC *pDC = game_framework::CDDraw::GetBackCDC();
		game_framework::CTextDraw::ChangeFontLog(pDC, 48, "�L�n������", RGB(255, 255, 255), 1500);
		int T = map.GetTotalTime();
		if (T >= 60) {
			game_framework::CTextDraw::Print(pDC, 770, 374, std::to_string(int(T / 60)) + " �� " + std::to_string(T % 60) + " ��" );
		}
		else {
			game_framework::CTextDraw::Print(pDC, 770, 374, std::to_string(T) + " ��");
		}
		game_framework::CTextDraw::Print(pDC, 770, 464, std::to_string(map.GetWave()));
		game_framework::CDDraw::ReleaseBackCDC();
	}
	else {
		map.drawmap();
		map.showtext();
	}

}
