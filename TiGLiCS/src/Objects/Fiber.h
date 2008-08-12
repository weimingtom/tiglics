//����t�@�C�o�N���X 
//�쐬��:tomoteru
//�쐬��:20080325
//�p�r�F�Q�[�����ŏ������ꎞ���f�������Ƃ��ȂǁB
#pragma once
#include "Base/Base.h"
#include "Base/Configure.h"
#include <cstdio>
#include <list>
#include <cstdlib>
#include <setjmp.h>

namespace TiGLiCS{
	namespace Object{
		class  CFiberMemoryManager{//�X�^�b�N�p�������Ǘ�
			static std::list<int*> Stack_List;//�m�ۂ����X�^�b�N�p���������X�g
		public:
			static int* GetStackMem();//�X�^�b�N�p�������m��
			static void RetStackMem(int* ptr);//�X�^�b�N�p�������ԋp
			static void ClearStackMem();//�X�^�b�N�p�������S�ԋp
			static void GCStackMem(int max,int rest=1000);//������
			static int GetStackMemNum();//�m�ۃ������̐�
		};

		/**
			@brief �t�@�C�o�[�N���X
			@author my04337

			�t�@�C�o�[���������邽�߂̃N���X�BIObject���p�����Ă���B<br>
			���̃N���X���p�����邱�ƂŁA����̃t�@�C�o�N���X���쐬�\�ł���B<br>
			�Ȃ��ACFiber::Process�͓Ǝ��̃X�^�b�N�̈�(�q�[�v)�œ��삷��B<br>
			�Ȃ��A�p���̍ۂɂ�private�ɂČp�����邱�ƂŊO������s�p�ӂ�Process��Suspend��<br>
			�Ă΂�邱�Ƃ�h�����Ƃ��ł���B
		*/
		class  CFiber:IFiber{//�t�@�C�o�N���X�B���N���X�Ƃ���
			CFiberBase * cfbase;//���ۂɃX�C�b�`���O�Ȃǂ��s���N���X
		public:
			CFiber();
			virtual ~CFiber();
			/**
				@brief ���f�\�֐�
				@author my04337
				
				���f�\�Ȋ֐��ł���B���̊֐�����Suspend()���Ăяo���ƁA<br>
				�����ϐ��Ȃǂ�ۑ�������ԂŒ��f���邱�Ƃ��ł���B<br>
				�ĊJ��Suspend()���Ăяo���ꂽ���ォ����s�����B<br>
				���[�U�[�͂��̊֐����I�[�o�[���C�g���Ďg�p����B<br>
				�܂��A�֐����I����ɌĂяo���ƌĂяo�������s����B				
			*/
			virtual void Process()=0;//���ۂ̏����B
			/**
				@brief Process�̒��f
				@author my04337

				Process���ŌĂяo�����Ƃ�Process�̎��s�𒆒f���邱�Ƃ��ł���B<br>
				�������AProcess�O�ŌĂяo���ƃ��������j�󂳂�邽�߂ɁA�Ăяo������<br>
				Process�݂̂ɂ���K�v������B
			*/
			void Suspend();//���f�BProcess���ŌĂяo��
			/**
				@���s�֐�
				@author my04337
				@retval true �֐������f����Ă���ꍇ
				@retval false �֐����I���������A���łɏI�����Ă���ꍇ

				�O������Process�֐����Ăяo���ꍇ�A���̊֐����Ăяo���悤�ɂ���B<br>
				���s���I���������ǂ����͖߂�l����m�F���邱�Ƃ��ł���B
			*/
			bool Run();//�g�p�҂��Ăяo��
			/**
				@brief �c��X�^�b�N�T�C�Y�m�F
				@author my04337
				@return �c��X�^�b�N�T�C�Y

				Process�֐��̎c��X�^�b�N�T�C�Y���擾����B�������A���̒l��<br>
				Suspend()���Ă΂ꂽ�ۂɍX�V����邽�߁A�ڈ��Ƃ��čl����ׂ��ł���B
			*/
			int GetStackRest();//�X�^�b�N�̎c���Ԃ�	
			/**
				@brief �t�@�C�o�I���m�F
				@author my04337
				@retval true Process()�̎��s���I����Ă���ꍇ
				@retval false Process()�����f����Ă���ꍇ

				�t�@�C�o�̎��s���I�����������擾����B
			*/
			bool isFiberEnd();//�t�@�C�o���I���������ǂ���
		};

		class  CFiberBase{//�X�^�b�N�Ǘ��A�؂�ւ�
			int func_sp;//�Ăяo������Sp [this+4]
			int * stack_mem;//���z�X�^�b�N[this+8]
			jmp_buf ret_jb;//�߂葤
			jmp_buf func_jb;//�֐���
			bool isEnd;//�I���������ǂ���
			bool isStart;//�J�n���ꂽ���ǂ���
			int	StackMemRest;//�c��X�^�b�N�T�C�Y(���f���X�V)
			CFiber* cfiber;//�t�@�C�o�ւ̃A�h���X
			void SwitchStack();//�X�^�b�N�؂�ւ�
			void SwitchStack(int return_pc);//�X�^�b�N�؂�ւ�
			static void start_() {//�Ăяo���p�W�����v��
				int fib;
				__asm{//ebp+4�ɂ́A�Ăяo������this�������Ă���̂�
					mov eax,[ebp+4];
					mov fib,eax;
				}
				((CFiberBase*)fib)->cfiber->Process();//�������s
				((CFiberBase*)fib)->isEnd = true; // �t�@�C�o�̎��s���I������
				((CFiberBase*)fib)->SwitchStack(0);//�����߂邱�Ƃ͂Ȃ��̂�
				//	�����������s����邱�Ƃ͖���
			}
			static void end_(){//�I���p�̃W�����v��
				int fib;
				__asm{
					mov eax,[ebp+4];
					mov fib,eax;
				}
				longjmp(((CFiberBase*)fib)->ret_jb,1);//���C���֖߂�
				
			}
			static void resume_(){
				int fib;//���A�p�̃W�����v��
				__asm{
					mov eax,[ebp+4];
					mov fib,eax;
				}
				longjmp(((CFiberBase*)fib)->func_jb,1);//�Ăяo����֐��֖߂�
				
			}

		public:
			CFiberBase(CFiber* cf);//�R���X�g���N�^
			~CFiberBase();//�f�X�g���N�^
			void _Suspend();//���f�BProcess���ŌĂяo��
			bool _Run();//�g�p�҂��Ăяo��
			int _GetStackRest(){//�����p�B�c��X�^�b�N�T�C�Y�𒲂ׂ�
				int now_sp;
				__asm mov now_sp,esp;
				return now_sp-(int)stack_mem;
			}
			int _GetStackRest_Out(){//�O���p�B�c��X�^�b�N�T�C�Y��Ԃ�	
				return StackMemRest-(int)stack_mem;
			}
			inline bool _isFiberEnd(){return isEnd;}//�t�@�C�o���I���������ǂ���

		};
	};
};