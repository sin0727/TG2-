//Preprocessor definiton　マクロ
#define WIN_MAX_X 1920
#define WIN_MAX_Y 1080
#define WIN_POS_X 0
#define WIN_POS_Y 0
#define POS_MAX_X 1920
#define POS_MAX_Y 1080
#define CELL 30
#define STAGE_MAX_X 1920 / 30
#define STAGE_MAX_Y 1080 / 30
#define _CRT_SECURE_NO_WARNINGS

//シーン列挙
enum MEN
{
	MEN_00_ACTION,
	
};

int Sce = MEN::MEN_00_ACTION;
//Insert header file　ヘッダー　むやみにインクルードしないでね、エラーの原因
#include"DxLib.h"
#include<math.h>
#include"Key.h"
#include"picter.h"
#include"stage.h"
#include"Action.h"


//Main Function　　　　　//ここはむやみに触らないでね　標準使用
int WINAPI WinMain(
	//ここはむやみに触らないでね　標準使用
	_In_ HINSTANCE himstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{
	//ここはむやみに触らないでね　標準使用
	ChangeWindowMode(TRUE);
	DxLib_Init();

	//ここはむやみに触らないでね　標準使用
	//window init
	SetWindowInitPosition(WIN_POS_X, WIN_POS_Y);
	SetWindowText("sanple");
	SetGraphMode(WIN_MAX_X, WIN_MAX_Y, 32);
	SetBackgroundColor(255, 255, 255);
	SetDrawScreen(DX_SCREEN_BACK);





	//Read //更新処理　順番きをつけてね
	Col.Read();
	Fon.Read();
	Pic.Read();
	Sta.Read();


	//描画処理
	while (ScreenFlip() == 0 &&
		ClearDrawScreen() == 0 &&
		ProcessMessage() == 0 &&
		GetKey() == 0 &&
		Key[KEY_INPUT_ESCAPE] == 0)
	{
		//ゲームシーン切り替え 追加したら追加を忘れずに
		switch (Sce)
		{
		case MEN::MEN_00_ACTION:
			act.Out();
			break;
		}
	}

	/*WaitKey();*/

	DxLib_End();
	return 0;				// ソフトの終了 
}