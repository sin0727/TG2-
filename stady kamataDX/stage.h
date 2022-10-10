#pragma once

#include"DxLib.h"
#include<math.h>
#include<stdio.h>
#include<string.h>
#include"Picter.h"


class STAGE
{
public:

	struct
	{
		int Typ[STAGE_MAX_X][STAGE_MAX_Y];
		int Typ_Exp[POS_MAX_X][POS_MAX_Y];

	}Blo;

	void Read()
	{
		FILE* fp_stage_1_1;
		fp_stage_1_1 = fopen("./stage/sta.txt", "r");


		FILE* fp_block_exp;
		fp_block_exp = fopen("./stage/sta_exp.txt", "w");

		for (int y = 0; y < STAGE_MAX_Y; y = y + 1)
		{
			for (int x = 0; x < STAGE_MAX_X; x = x + 1)
			{
				(void)fscanf(fp_stage_1_1, "%d", &Blo.Typ[x][y]);


			}
		}

		for (int y = 0; y < STAGE_MAX_Y; y = y + 1)
		{
			for (int x = 0; x < STAGE_MAX_X; x = x + 1)
			{
				int ins = Blo.Typ[x][y];
				fprintf(fp_block_exp, "(%d,%d)\n", x, y);
				for (int ye = 0; ye < CELL; ye = ye + 1)
				{
					for (int xe = 0; xe < CELL; xe = xe + 1)
					{
						Blo.Typ_Exp[x * CELL + xe][y * CELL + ye] = ins;
						fprintf(fp_block_exp, "%d", Blo.Typ_Exp[x * CELL + xe][y * CELL + ye]);
					}
					fprintf(fp_block_exp, "\n");
				}
			}
		}
		fclose(fp_stage_1_1);
		fclose(fp_block_exp);
	}



	void Out(int* PosX)
	{
		int pic = 0;
		for (int x = 0; x < STAGE_MAX_X; x = x + 1)
		{
			for (int y = 0; y < STAGE_MAX_Y; y = y + 1)
			{
				switch (Blo.Typ[x][y])
				{
				case 0:
					pic = Pic.sky;
					break;
				case 1:
					pic = Pic.Block1;
					break;
				case 2:
					pic = Pic.Block2;
					break;
				case 3:
					pic = Pic.Block3;
					break;
				case 4:

					break;
				case 5:
					pic = Pic.Block5;
					break;
				}

				DrawGraph(CELL * x + *PosX, CELL * y, pic, TRUE);
			}

		}

	}

private:
};

STAGE Sta;
