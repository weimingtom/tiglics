#include "Objects/Fiber.h"
#include <cstdlib>

//int grobal_int;
using namespace TiGLiCS;
using namespace Object;
std::list<int*> CFiberMemoryManager::Stack_List;

int* CFiberMemoryManager::GetStackMem(){
	//メモリの確保
	int* ret;
	
	if(Stack_List.size()!=0){//スタック用メモリ確保
		//確保済みのメモリがあるなら
		ret=Stack_List.back();
		Stack_List.pop_back();
	}else{	
		ret=(int*)malloc(STACK_SIZE);//無かった場合、作成
	}
	return ret;
}
void CFiberMemoryManager::RetStackMem(int *ptr){
	Stack_List.push_back(ptr);//メモリの返却
	//free(ptr);
}
void CFiberMemoryManager::ClearStackMem(){//メモリ解放。終了時に呼び差無ければいけない
	for(std::list<int*>::iterator it=Stack_List.begin();it!=Stack_List.end();++it){
		if((*it)!=NULL)free(*it);
	}
}
void CFiberMemoryManager::GCStackMem(int max,int rest){
	while(max>0 && (int)Stack_List.size()>rest){//restで指定された個数は残す
		std::list<int*>::iterator it=Stack_List.begin();
		if((*it)!=NULL)free(*it);
		Stack_List.pop_front();
		--max;
	}
}
int CFiberMemoryManager::GetStackMemNum(){
	return (int)Stack_List.size();//確保されていて使用されていないスタック数
}

//----------------------------------------------------------------------------


CFiber::CFiber(){//コンストラクタ
	this->cfbase=new CFiberBase(this);
}
CFiber::~CFiber(){
	delete cfbase;
}
bool CFiber::isFiberEnd(){//終了したかを返す
	return cfbase->_isFiberEnd();
}
int CFiber::GetStackRest(){//スタックの残りを返す
	return cfbase->_GetStackRest_Out();
}
bool CFiber::Run(){//外部からはこれを呼び出す
	return cfbase->_Run();
}
void CFiber::Suspend(){//一時中止
	cfbase->_Suspend();
}

CFiberBase::CFiberBase(CFiber* cf){//コンストラクタ
	isEnd=false;
	isStart=false;
	this->StackMemRest=0;
	this->cfiber=cf;
	this->stack_mem=NULL;
}
CFiberBase::~CFiberBase(){//デストラクタ
	CFiberMemoryManager::RetStackMem(stack_mem);
}
void CFiberBase::_Suspend(){//実行の中断
	int key,tmp;
	
	__asm{//現在のスタックの使用状況を記録
		mov eax,esp;
		mov tmp,eax;
	}
	
	StackMemRest=tmp;

	key=setjmp(this->func_jb);//復帰の場合はここへ戻る。
	if(key==0){//Runからの復帰ではない場合、Runへ戻る
		SwitchStack((int)this->resume_);
	}
}


void CFiberBase::SwitchStack(int return_pc){
	//ここでスタックのスイッチを行う。
	__asm {
		mov		EAX,this;

//	naked functionならばEAXにはthisが入っていると仮定して良いらしい
//	それなら、[EAX+8]がこのクラスで宣言されているの一つ目の変数
//	(register_esp_)だと仮定していい
		push	eax;//thisポインタの保存
		push	return_pc;
		push	EBX;
		push	EBP;
		push	ESI;
		push	EDI;

			push	dword ptr FS:[0];	//	例外処理のために必要

		xchg	ESP,[EAX];

			pop		dword ptr FS:[0];	//	例外処理のために必要

		pop		EDI;
		pop		ESI;
		pop		EBP;
		pop		EBX;
		pop		ECX;//ジャンプアドレス
		jmp		ECX;
	}
}


bool CFiberBase::_Run(){//実行関数。外部からはこれを呼び出す
	int exception_ptr;
	if(isEnd==true)return false;//すでに終了しているならば、falseを返す
	if(isStart==false){
		isStart=true;//初回ならば
		if(setjmp(this->ret_jb)==0){
			//呼び出し側のスタック初期化
			stack_mem=(int*)CFiberMemoryManager::GetStackMem();
			func_sp=(int)stack_mem+STACK_SIZE;
			func_sp-=4;*(int*)func_sp=(int)this;		//thisポインタ、[ebp+4]
			func_sp-=4;*(int*)func_sp=(int)this->start_;//ジャンプ先
			func_sp-=4;*(int*)func_sp=0;//EBX
			func_sp-=4;*(int*)func_sp=0;//EBP
			func_sp-=4;*(int*)func_sp=0;//ESI
			func_sp-=4;*(int*)func_sp=0;//DSI
			__asm{
				mov eax,dword ptr FS:[0]
				mov exception_ptr,eax

			}
			func_sp-=4;*(int*)func_sp=exception_ptr;//例外ポインタの設定
			SwitchStack((int)this->end_);//切り替え処理
			//ここに移ることはない
		}
		return !isEnd;//終了

	}else{//二回目から
		if (isEnd==true) return false;
		//isSuspend = false;//中断していないならば
		SwitchStack((int)this->end_);	//スイッチング
		return false;//ここに移ることはない,が、一応書いておく
	}
}