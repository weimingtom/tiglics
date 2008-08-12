#include "Base/Base.h"

namespace TiGLiCS{
	namespace Manager{
		class CInputManager{//シングルトン
			static CInputManager * Instance;
			Sint32 KeyState[0x100];//キーステート
			CInputManager(){
				//キーステートの初期化
				for(Sint32 i=0;i<=0xFF;++i){
					KeyState[i]=0;
				}
			}
			~CInputManager(){}
		public:
			static CInputManager * GetInstance(){return Instance;}
			static void Release(){delete Instance;}
			
			//Object側から呼び出される関数
			inline Sint32 GetKey(Selene::eVirtualKeyCode KeyCode){
				return ((KeyCode>=0 && KeyCode<=0xFF)?KeyState[KeyCode]:0);
			}
			//キーステート設定用
			inline Sint32 * _GetKeyStateArr(){return KeyState;}

		};
	}
}