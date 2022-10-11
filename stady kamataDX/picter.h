#pragma once
//Insert header file　ヘッダー　むやみにインクルードしないでね、エラーの原因
#include"DxLib.h"

class
{
public:
	int sky;
	int Block1;
	int Block2;
	int Block3;
	int Block5;
	int Player;

	//画像読み込み
	void Read()
	{
		sky = LoadGraph("./stage/sky.png");
		Block1 = LoadGraph("./stage/block0.png");
		Block2 = LoadGraph("./stage/block1.png");
		Block3 = LoadGraph("./stage/block2.png");
		Block5 = LoadGraph("./stage/block4.png");
		Player = LoadGraph("./stage/mario.png");

	}


private:
}Pic;