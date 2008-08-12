#pragma once 

//----------------------------------------------------------------------------------
// DEFINE
//----------------------------------------------------------------------------------
#define	TIGLICS_VERSION	"Beta 1.00"	//バージョンデータ

#define MAX_TASK_LOG_ROW	(15)	//最大タスクログ行
#define MAX_TASK_LOG_SIZE	(256)	//最大タスクログサイズ


#define STACK_SIZE	(0x4000)//スタックサイズ(状況に応じて増やすべき Releaseの方が大きい?)
#define UNIT_PRIMITIVE_SIZE2D	(0x1000)//2Dオブジェクトサイズ
#define MAX_ACTOR_NUM			(0x2000)//最大アクター数
