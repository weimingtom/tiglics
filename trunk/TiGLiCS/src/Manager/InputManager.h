#include "Base/Base.h"

namespace TiGLiCS{
	namespace Manager{
		class CInputManager{//�V���O���g��
			static CInputManager * Instance;
			Sint32 KeyState[0x100];//�L�[�X�e�[�g
			CInputManager(){
				//�L�[�X�e�[�g�̏�����
				for(Sint32 i=0;i<=0xFF;++i){
					KeyState[i]=0;
				}
			}
			~CInputManager(){}
		public:
			static CInputManager * GetInstance(){return Instance;}
			static void Release(){delete Instance;}
			
			//Object������Ăяo�����֐�
			inline Sint32 GetKey(Selene::eVirtualKeyCode KeyCode){
				return ((KeyCode>=0 && KeyCode<=0xFF)?KeyState[KeyCode]:0);
			}
			//�L�[�X�e�[�g�ݒ�p
			inline Sint32 * _GetKeyStateArr(){return KeyState;}

		};
	}
}