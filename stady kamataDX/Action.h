#pragma once
//Insert header file　ヘッダー　むやみにインクルードしないでね、エラーの原因
#include"DxLib.h"
#include<math.h>
#include<stdio.h>
#include<string.h>
#include"Stage.h"

//プレイヤー移動　ここは更新かけるからいじらないで
class ACTION
{
public:
	void Out() {
		Cal();
		Cha();
	}

private:

	struct
	{
		struct
		{
			int x = 210;
			int y = POS_MAX_Y - 6 * CELL;
			int Yin = POS_MAX_Y - 3 * CELL;
			int X_Sta;
		}Pos;

		struct
		{
			int le_up = 0;
			int ri_up = 0;
			int le_do = 0;
			int ri_do = 0;
		}In;

		struct
		{
			int le_up = 0;
			int ri_up = 0;
			int le_do = 0;
			int ri_do = 0;
		}Out;

	}Player;


	//プレイヤー移動
	const int Movx = CELL / 10;
	int Movy = 0;
	const int Movy_max = CELL * 4;

	int Sta_PosX = 0;


	struct
	{
		bool Xpl = 0;
		bool Xmi = 0;
		bool Jum = 0;
		bool Rev = 0;
	}Fla;

	int cou = 0;
	double T = 0.0;
	const double T_k = 10.0;

	void Cal();
	void Cha();


};

ACTION act;

void ACTION::Cal()
{
	if (Key[KEY_INPUT_D] != 0) {  Fla.Xpl = 1;  }
	else if (Key[KEY_INPUT_A] != 0) {  Fla.Xmi = 1; }

	if (Key[KEY_INPUT_W] == 1)
	{
		Fla.Jum = 1;
		Player.Pos.Yin = Player.Pos.y;
	}


	if (Fla.Xpl == 1)
	{
		if (Sta_PosX == 0 || Sta_PosX == -POS_MAX_X + WIN_MAX_X)
		{
			Player.Pos.x = Player.Pos.x + Movx;
		}
		if (Player.Pos.x == WIN_MAX_X / 2)
		{
			Sta_PosX = Sta_PosX - Movx;
		}
	}

	else if (Fla.Xmi == 1)
	{
		if (Sta_PosX == 0 || Sta_PosX == -POS_MAX_X + WIN_MAX_X)
		{
			Player.Pos.x = Player.Pos.x - Movx;
		}
		if (Player.Pos.x == WIN_MAX_X / 2)
		{
			Sta_PosX = Sta_PosX + Movx;
		}
	}

	Player.Pos.X_Sta = Player.Pos.x + abs(Sta_PosX);

	//ジャンプ処理
	if (Fla.Rev == 0 && Fla.Jum == 1)
	{
		cou = cou + 1;
		T = T_k * ((double)cou / 60.0);

		Movy = (int)(pow(T, 2.0));
		for (int y = 1; y <= Movy; y = y + 1)
		{
			Player.Pos.y = Player.Pos.y - 1;
			Player.Out.le_up = Sta.Blo.Typ_Exp[Player.Pos.X_Sta][Player.Pos.y - 1];
			Player.Out.ri_up = Sta.Blo.Typ_Exp[Player.Pos.X_Sta + CELL - 1][Player.Pos.y - 1];
			if (Movy_max == Player.Pos.Yin - Player.Pos.y || Player.Out.le_up != 0 || Player.Out.ri_up != 0)
			{
				Player.Pos.y = Player.Pos.y + 1;
				Fla.Rev = 1;
				cou = 0;
				break;
			}
		}
	}

	else if ((Fla.Rev == 1 && Fla.Jum == 1) || Player.Out.ri_do == 0 && Player.Out.le_do == 0)
	{
		cou = cou + 1;
		T = T_k * ((double)cou / 60.0);

		Movy = (int)(pow(T, 2.0));
		for (int y = 1; y <= Movy; y = y + 1)
		{

			Player.Pos.y = Player.Pos.y + 1;
			//すり抜け防止
			Player.Out.le_do = Sta.Blo.Typ_Exp[Player.Pos.X_Sta][Player.Pos.y + CELL];
			Player.Out.ri_do = Sta.Blo.Typ_Exp[Player.Pos.X_Sta + CELL - 1][Player.Pos.y + CELL];

			if (Player.Out.le_do != 0 || Player.Out.ri_do != 0)
			{
				Player.Pos.y = Player.Pos.y - 1;
				Player.Pos.Yin = Player.Pos.y;
				Fla.Jum = 0;
				Fla.Rev = 0;
				Movy = 0;
				cou = 0;
				break;
			}
		}
	}

	Player.Out.le_up = Sta.Blo.Typ_Exp[Player.Pos.X_Sta][Player.Pos.y - 1];
	Player.Out.ri_up = Sta.Blo.Typ_Exp[Player.Pos.X_Sta + CELL - 1][Player.Pos.y - 1];
	Player.Out.le_do = Sta.Blo.Typ_Exp[Player.Pos.X_Sta][Player.Pos.y + CELL];
	Player.Out.ri_do = Sta.Blo.Typ_Exp[Player.Pos.X_Sta + CELL - 1][Player.Pos.y + CELL];


	Player.In.le_up = Sta.Blo.Typ_Exp[Player.Pos.X_Sta][Player.Pos.y];
	Player.In.ri_up = Sta.Blo.Typ_Exp[Player.Pos.X_Sta + CELL - 1][Player.Pos.y];
	Player.In.le_do = Sta.Blo.Typ_Exp[Player.Pos.X_Sta][Player.Pos.y + CELL - 1];
	Player.In.ri_do = Sta.Blo.Typ_Exp[Player.Pos.X_Sta + CELL - 1][Player.Pos.y + CELL - 1];

	if (Player.In.ri_up != 0 || Player.In.ri_do != 0)
	{
		if (Sta_PosX == 0 || Sta_PosX == -POS_MAX_X + WIN_MAX_X)
		{
			Player.Pos.x = Player.Pos.x - Movx;
		}
		if (Player.Pos.x == WIN_MAX_X / 2)
		{
			Sta_PosX = Sta_PosX + Movx;
		}
	}

	else if (Player.In.le_up != 0 || Player.In.le_do != 0)
	{
		if (Sta_PosX == 0 || Sta_PosX == -POS_MAX_X + WIN_MAX_X)
		{
			Player.Pos.x = Player.Pos.x + Movx;
		}
		if (Player.Pos.x == WIN_MAX_X / 2)
		{
			Sta_PosX = Sta_PosX - Movx;
		}
	}
}



//プレイヤーの描写処理
void ACTION::Cha() {
	Sta.Out(&Sta_PosX);
	DrawGraph(Player.Pos.x, Player.Pos.y, Pic.Player, TRUE);

	Fla.Xpl = 0;
	Fla.Xmi = 0;
}