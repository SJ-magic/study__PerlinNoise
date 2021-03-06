/************************************************************
rand()関数の使用
	description
		rand() 関数は、stdlib.hで定義されている関数で、 0 から RAND_MAX の間の疑似乱数整数を返します。 
		この関数を用いて、0より大きくNより小さい一様乱数（実数）を生成するには
			((double)rand() / ((double)RAND_MAX + 1)) * N
		とすればできます。
		
		
		整数がほしいなら、
			(int)( ((double)rand() / ((double)RAND_MAX + 1)) * N )
			
		整数が必要で、浮動小数を使うことが気になるのなら、
			rand() / (RAND_MAX / N + 1)
		としてください。
		
		どちらもNがRAND_MAXにくらべて十分小さいことを仮定しています。
		
	
	乱数の質
		すぐに思いつく方法として
		rand() % N
		も考えられますが、この方法 (これは 0から N-1までの数を返そうとする)は乱数の質が低いので使わないでください。
		なぜなら乱数発生器の多くで下位のビットは、ランダムにならないからです。
		
	srand() 関数
		srand()関数は、 rand()関数で作られる疑似乱数整数系列の新しい種として、その引数の値を使用します。 
		この関数を使用して作られた疑似乱数系列は、同じ値を引数に使用してsrand()を呼ぶことによって、 再現することが可能です。 
		種の値が与えられない場合には、rand()関数は自動的に 1 を種とします。 
		本当にランダムに乱数を発生したいときは、srand()を使って、擬似乱数発生器にランダムな初期値を与えてください。
		よくある乱数の種は、時刻などです。
		注意：プログラム中で srand()を2回以上呼んで役にたつことは滅多にありません。 本当にランダムな数を得ようと思って、rand()を呼ぶ前に毎回srand() を呼ぶような真似はぜったいにしてはいけません。
************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "PerlinNoise.h"

/************************************************************
************************************************************/

/******************************
******************************/
int main()
{
	/********************
	必ず、乱数でoffsetをつけないと、毎回同じ出力になってしまう.
	
	offsetは小さめにすること。
		N を大きくしすぎると、PerlinNoise.cppにて、double->floatの変換で丸まってしまい、
		全て整数になるなどして、all = 0.5となってしまうケースなどが見られた。
	********************/
	const double N = 100;
	srand((unsigned int)time(NULL));
	double offset = ((double)rand() / ((double)RAND_MAX + 1)) * N;
	printf("%f(max = %d)\n", offset, RAND_MAX);
	
	/********************
	noise()は、引数がintegerの時、必ずzeroを返すので注意.
	********************/
	FILE* fp;
	
	fp = fopen("Log.csv", "w");
	if(fp == NULL)	{ printf("Please close Log file\n"); exit(1); }
	
	for(int i = 0; i < 100; i++){
		fprintf(fp, "%d,%f\n", i, noise1( double(i) * 0.05 + offset ) + 0.5 );
	}
	fclose(fp);
	
	return 0;
}


