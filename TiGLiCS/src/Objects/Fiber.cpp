#include "Objects/Fiber.h"
#include <cstdlib>

//int grobal_int;
using namespace TiGLiCS;
using namespace Object;
std::list<int*> CFiberMemoryManager::Stack_List;

int* CFiberMemoryManager::GetStackMem(){
	//�������̊m��
	int* ret;
	
	if(Stack_List.size()!=0){//�X�^�b�N�p�������m��
		//�m�ۍς݂̃�����������Ȃ�
		ret=Stack_List.back();
		Stack_List.pop_back();
	}else{	
		ret=(int*)malloc(STACK_SIZE);//���������ꍇ�A�쐬
	}
	return ret;
}
void CFiberMemoryManager::RetStackMem(int *ptr){
	Stack_List.push_back(ptr);//�������̕ԋp
	//free(ptr);
}
void CFiberMemoryManager::ClearStackMem(){//����������B�I�����ɌĂэ�������΂����Ȃ�
	for(std::list<int*>::iterator it=Stack_List.begin();it!=Stack_List.end();++it){
		if((*it)!=NULL)free(*it);
	}
}
void CFiberMemoryManager::GCStackMem(int max,int rest){
	while(max>0 && (int)Stack_List.size()>rest){//rest�Ŏw�肳�ꂽ���͎c��
		std::list<int*>::iterator it=Stack_List.begin();
		if((*it)!=NULL)free(*it);
		Stack_List.pop_front();
		--max;
	}
}
int CFiberMemoryManager::GetStackMemNum(){
	return (int)Stack_List.size();//�m�ۂ���Ă��Ďg�p����Ă��Ȃ��X�^�b�N��
}

//----------------------------------------------------------------------------


CFiber::CFiber(){//�R���X�g���N�^
	this->cfbase=new CFiberBase(this);
}
CFiber::~CFiber(){
	delete cfbase;
}
bool CFiber::isFiberEnd(){//�I����������Ԃ�
	return cfbase->_isFiberEnd();
}
int CFiber::GetStackRest(){//�X�^�b�N�̎c���Ԃ�
	return cfbase->_GetStackRest_Out();
}
bool CFiber::Run(){//�O������͂�����Ăяo��
	return cfbase->_Run();
}
void CFiber::Suspend(){//�ꎞ���~
	cfbase->_Suspend();
}

CFiberBase::CFiberBase(CFiber* cf){//�R���X�g���N�^
	isEnd=false;
	isStart=false;
	this->StackMemRest=0;
	this->cfiber=cf;
	this->stack_mem=NULL;
}
CFiberBase::~CFiberBase(){//�f�X�g���N�^
	CFiberMemoryManager::RetStackMem(stack_mem);
}
void CFiberBase::_Suspend(){//���s�̒��f
	int key,tmp;
	
	__asm{//���݂̃X�^�b�N�̎g�p�󋵂��L�^
		mov eax,esp;
		mov tmp,eax;
	}
	
	StackMemRest=tmp;

	key=setjmp(this->func_jb);//���A�̏ꍇ�͂����֖߂�B
	if(key==0){//Run����̕��A�ł͂Ȃ��ꍇ�ARun�֖߂�
		SwitchStack((int)this->resume_);
	}
}


void CFiberBase::SwitchStack(int return_pc){
	//�����ŃX�^�b�N�̃X�C�b�`���s���B
	__asm {
		mov		EAX,this;

//	naked function�Ȃ��EAX�ɂ�this�������Ă���Ɖ��肵�ėǂ��炵��
//	����Ȃ�A[EAX+8]�����̃N���X�Ő錾����Ă���̈�ڂ̕ϐ�
//	(register_esp_)���Ɖ��肵�Ă���
		push	eax;//this�|�C���^�̕ۑ�
		push	return_pc;
		push	EBX;
		push	EBP;
		push	ESI;
		push	EDI;

			push	dword ptr FS:[0];	//	��O�����̂��߂ɕK�v

		xchg	ESP,[EAX];

			pop		dword ptr FS:[0];	//	��O�����̂��߂ɕK�v

		pop		EDI;
		pop		ESI;
		pop		EBP;
		pop		EBX;
		pop		ECX;//�W�����v�A�h���X
		jmp		ECX;
	}
}


bool CFiberBase::_Run(){//���s�֐��B�O������͂�����Ăяo��
	int exception_ptr;
	if(isEnd==true)return false;//���łɏI�����Ă���Ȃ�΁Afalse��Ԃ�
	if(isStart==false){
		isStart=true;//����Ȃ��
		if(setjmp(this->ret_jb)==0){
			//�Ăяo�����̃X�^�b�N������
			stack_mem=(int*)CFiberMemoryManager::GetStackMem();
			func_sp=(int)stack_mem+STACK_SIZE;
			func_sp-=4;*(int*)func_sp=(int)this;		//this�|�C���^�A[ebp+4]
			func_sp-=4;*(int*)func_sp=(int)this->start_;//�W�����v��
			func_sp-=4;*(int*)func_sp=0;//EBX
			func_sp-=4;*(int*)func_sp=0;//EBP
			func_sp-=4;*(int*)func_sp=0;//ESI
			func_sp-=4;*(int*)func_sp=0;//DSI
			__asm{
				mov eax,dword ptr FS:[0]
				mov exception_ptr,eax

			}
			func_sp-=4;*(int*)func_sp=exception_ptr;//��O�|�C���^�̐ݒ�
			SwitchStack((int)this->end_);//�؂�ւ�����
			//�����Ɉڂ邱�Ƃ͂Ȃ�
		}
		return !isEnd;//�I��

	}else{//���ڂ���
		if (isEnd==true) return false;
		//isSuspend = false;//���f���Ă��Ȃ��Ȃ��
		SwitchStack((int)this->end_);	//�X�C�b�`���O
		return false;//�����Ɉڂ邱�Ƃ͂Ȃ�,���A�ꉞ�����Ă���
	}
}