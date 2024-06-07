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
// �o��class���C�����C���}�Y�e������
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g) : CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(0, "Start Initialize...");	// �@�}�l��loading�i�׬�0%
	//
	// �}�l���J���
	//
	//Sleep(100);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
	//
	background.LoadBitmapByString({ "resources/selectlevel.bmp" });
	std::vector<std::string> picPath;
	for (int i = 1; i < 18; i++) {
		picPath.push_back("resources/preview" + to_string(i) + ".bmp");
	}
	previewLevelPic.LoadBitmapByString(picPath);
	previewLevelPic.SetTopLeft(423,134);
	selected_level = 1;
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{	
	if (195 >= point.x && point.x >= 105 && 438 >= point.y && point.y >= 315) {
		//�V���b�Y
		if (selected_level == 1) {
			selected_level = 17;
		}
		else {
			selected_level--;
		}
	}
	else if (1305 >= point.x && point.x >= 1215 && 438 >= point.y && point.y >= 315) {
		//�V�k�b�Y
		if (selected_level == 17) {
			selected_level = 1;
		}
		else {
			selected_level++;
		}
	}
	previewLevelPic.SetFrameIndexOfBitmap(selected_level - 1);
	if (1311 >= point.x && point.x >= 1098 && 780 >= point.y && point.y >= 712) {
		ofstream ofs("Source/Game/Settings.map");
		ofs << selected_level;
		ofs.close();
		GotoGameState(GAME_STATE_RUN);		// ������GAME_STATE_RUN
	}
}

void CGameStateInit::OnShow()
{
	if (previewLevelPic.IsBitmapLoaded()) {
		background.ShowBitmap();
		previewLevelPic.ShowBitmap();

		CDC *pDC = game_framework::CDDraw::GetBackCDC();
		game_framework::CTextDraw::ChangeFontLog(pDC, 48, "�L�n������", RGB(128, 128, 128), 1500);

		game_framework::CTextDraw::Print(pDC, 600, 734,"���d:" + to_string(selected_level));
		game_framework::CDDraw::ReleaseBackCDC();
	}
}
