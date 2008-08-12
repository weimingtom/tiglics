#pragma once

#include "Base/Base.h"
#include <vector>
namespace TiGLiCS{
	namespace Manager{
		/**
			@brief テクスチャ
			@author my04337
			@note
			テクスチャ管理を行う。テクスチャと、描画時に使用する領域のリストを持つ。
		*/
		class  CTexture{
			Selene::Renderer::ITexture *Texture;//テクスチャ
			std::vector<Selene::Math::Rect2DF> TextureArea;//テクスチャ領域
		public:
			/**
				@brief コンストラクタ
				@author my04337
				@param pEngine [in] タスクへのポインタ
				@param FileName [in] テクスチャファイル名
				
				テクスチャマネージャの作成を行う。
			*/
			CTexture(const char * FileName);
			~CTexture(){SAFE_RELEASE(Texture);}//デストラクタ
			/**
				@brief テクスチャ取得
				@author my04337
				@return テクスチャへのポインタ

				テクスチャへのポインタを取得する
			*/
			inline Selene::Renderer::ITexture *GetITexture(){return Texture;}
			
			/**
				@brief テクスチャ領域追加
				@author my04337
				@param TexArea テクスチャ領域
				@return テクスチャ領域ID

				
				テクスチャ領域の登録を行う。戻り値はテクスチャ領域IDで、テクスチャ領域の追加順に<br>
				0 , 1 , 2 , ... といった値となる。
			*/
			inline Sint32 AddTextureArea(Selene::Math::Rect2DF TexArea){TextureArea.push_back(TexArea);return TextureArea.size();}

			inline Selene::Math::Rect2DF GetTextureArea(Sint32 idx){return (idx >=0 &&idx<(Sint32)TextureArea.size()?TextureArea[idx]:Selene::Math::Rect2DF(0,0,0,0));}
			inline Sint32 GetTextureAreaNum(){return TextureArea.size();}
		};

		//-----------------------------------------------------------------------------------
		/**
			@brief テクスチャマネージャ
			@author my04337
			@note
			テクスチャ全体の管理を請け負う。
		*/
		class CTextureManager{
			static CTextureManager * Instance;
			std::vector<CTexture *> TextureList;//テクスチャリスト

			CTextureManager(){}
			~CTextureManager(){}
		public:
			static CTextureManager * GetInstance(){return Instance;}
			static void Release(){
				//テクスチャーの解放
				for(Sint32 i=0;i<(Sint32)Instance->TextureList.size();++i){
					SAFE_DELETE(Instance->TextureList[i]);
				}	
			}
			/**
				@brief テクスチャの追加
				@author my04337
				@param pTex [in] テクスチャマネージャへのポインタ
				@return テクスチャID

				テクスチャの登録を行う。登録の際にはあらかじめテクスチャマネージャの<br>
				各種設定を行う必要がある。戻り値はテクスチャIDで、テクスチャの追加順に<br>
				0 , 1 , 2 , ... といった値となる。
			*/
			Sint32 AddTexture(CTexture * pTex){
				TextureList.push_back(pTex);
				return (Sint32)TextureList.size();
			}
			
			/**
				@brief テクスチャの取得
				@author my04337
				@param idx [in] テクスチャID
				@retval 成功時 テクスチャマネージャへのポインタ
				@retval 失敗時 NULL
				
				テクスチャの取得を行う。存在しないテクスチャIDを指定するとNULLが返される。				
			*/
			inline CTexture* GetCTexture(Sint32 idx){
				return (idx>=0 &&idx<(Sint32)TextureList.size()?TextureList[idx]:NULL);
			}
			inline Sint32 GetCTextureNum(void){
				return (Sint32)TextureList.size();
			}
		};
	};
};
