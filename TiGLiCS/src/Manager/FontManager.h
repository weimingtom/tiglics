//フォント管理構造体。生成に必要な情報の管理
#pragma once
#include "Base/Base.h"
#include <vector>
namespace TiGLiCS{
	namespace Manager{
		/**
			@brief フォント単体マネージャ
			@author my04337
			@note
			フォントファイル管理クラス。フォントスプライトの生成を請け負う
		*/
		class  CFont{
			const char * FileName;//ファイル名
			const char * FileType;//ファイルフォーマット
		public:
			/**
				@brief コンストラクタ
				@author my04337
				@param FileName [in] フォントファイル名
				@param FileType [in] ファイルフォーマット
			*/
			CFont(const char * FileName,const char * FileType){
				this->FileName=FileName;
				this->FileType=FileType;
			}
			~CFont(){}//デストラクタ
			Selene::Renderer::Object::IFontSprite2D *MakeFontSprite2D(Selene::Renderer::IRender *pRender,Sint32 MaxDrawNum){
				return pRender->CreateFontSprite2DFromFile(FileName,FileType,MaxDrawNum);
			}
			Selene::Renderer::Object::IFontSprite3D *MakeFontSprite3D(Selene::Renderer::IRender *pRender,Sint32 MaxDrawNum){
				return pRender->CreateFontSprite3DFromFile(FileName,FileType,MaxDrawNum);
			}
			inline const char * GetFileName(){return FileName;}
			inline const char * GetFileType(){return FileType;}
		};
		//-------------------------------------------------------------------------------------
		
		/**
			@brief フォントマネージャ
			@author my04337
			@note
			フォント全体の管理を請け負う。
		*/
		class CFontManager{//シングルトン
			static CFontManager * Instance;
			std::vector<CFont *> FontList;//フォントリスト
			CFontManager(){}
			~CFontManager(){}
		public:
			static CFontManager * GetInstance(){return Instance;}
			static void Release(){
				//フォントの解放
				for(Sint32 i=0;i<(Sint32)Instance->FontList.size();++i){
					SAFE_DELETE(Instance->FontList[i]);
				}	
			}
			/**
				@brief フォントの追加
				@author my04337
				@param pFont [in] フォントマネージャへのポインタ
				@return フォントID

				フォントの登録を行う。戻り値はフォントIDで、フォントの追加順に<br>
				0 , 1 , 2 , ... といった値となる。
			*/
			Sint32 AddFont(CFont * pFont){FontList.push_back(pFont);return (Sint32)FontList.size();}
			
			inline Sint32 GetCFontNum(void){
				return (Sint32)FontList.size();
			}
			inline CFont* GetCFont(Sint32 idx){
				return (idx>=0 && idx<(Sint32)FontList.size()?FontList[idx]:NULL);
			}
		};
	};
};
