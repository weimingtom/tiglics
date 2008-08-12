//SE管理用構造体
#pragma once

#include "Base/Base.h"
#include <list>
#include <vector>
namespace TiGLiCS{
	namespace Manager{
		/**
			@brief サウンド単体マネージャ
			@author my04337
			
			SEの管理を行う。同時発音が可能である。
		*/
		class  CSound{
			Selene::Sound::ISound * pSound;
			Sint32 LayerCount;//最大レイヤ数
			Sint32 NowLayer;//現在のレイヤ番号
		public:
			/**
				@brief コンストラクタ
				@author my04337
				@param pEngine [in] タスクへのポインタ
				@param FileName [in] サウンドファイル名
				@param LayerCount [in] 最大同時再生数
				
				コンストラクタ。 LayerCountを1にすると同時発音を行わない。
			*/
			CSound(const char * FileName,Sint32 LayerCount);//コンストラクタ
			~CSound(){//デストラクタ
				SAFE_RELEASE(pSound);
			}
			/**
				@brief 再生
				@author my04337
				@param isLoop [in] ループするかどうか
				@return レイヤ番号

				SEの再生を行う。戻り値のレイヤ番号は停止や一時停止などに使う。
			*/
			Sint32 Play(bool isLoop=false){//再生
				++NowLayer;
				if(NowLayer>=LayerCount)NowLayer=0;
				pSound->Stop(NowLayer);
				pSound->Play(NowLayer,isLoop);
				return NowLayer;
			}

			/**
				@brief 再生 詳細パラメータ指定
				@author my04337
				@param fVolume [in] ボリューム(0.0f - 100.0f)
				@param fPan [in] パン(-100.0f - 100.0f)
				@param isLoop [in] ループするかどうか
				@return レイヤ番号

				SEの再生を行う。戻り値のレイヤ番号は停止や一時停止などに使う。
			*/
			Sint32 Play(float fVolume,float fPan,bool isLoop=false){
				++NowLayer;
				if(NowLayer>=LayerCount)NowLayer=0;
				pSound->Stop(NowLayer);
				SetVolume(NowLayer,fVolume);
				SetPan(NowLayer,fPan);
				pSound->Play(NowLayer,isLoop);
				return NowLayer;
			}
			/**
				@brief 停止
				@author my04337
				@param Layer [in] レイヤ番号
				
				SEの停止を行う.
			*/
			void Stop(Sint32 Layer){
				pSound->Stop(Layer);
			}
			/**
				@brief 一時停止
				@author my04337
				@param Layer [in] レイヤ番号
				
				SEの一時停止を行う.
			*/
			void Pause(Sint32 Layer){
				pSound->Pause(Layer);
			}
			/**
				@brief 音量調整
				@author my04337
				@param Layer [in] レイヤ番号
				@param fVolume [in] ボリューム(0.0f - 100.0f)
				
				ボリュームの調整を行う
			*/
			void SetVolume(Sint32 Layer,float fVolume){
				pSound->SetVolume(Layer,fVolume);
			}
			/**
				@brief 位相調整
				@author my04337
				@param Layer [in] レイヤ番号
				@param fPan [in] パン(-100.0f - 100.0f)
				
				パンの調整を行う
			*/
			void SetPan(Sint32 Layer,float fPan){
				pSound->SetPan(Layer,fPan);
			}
			/**
				@brief 再生状態取得
				@author my04337
				@param Layer [in] レイヤ番号
				@return 再生中か

				指定レイヤーが再生中かを取得する
			*/
			Bool isPlay(Sint32 Layer){return pSound->IsPlay(Layer);}
		};
		//-----------------------------------------------------------------------------------
		/**
			@brief サウンドマネージャ
			@author my04337

			SE全体マネージャ。登録削除を担当。
		*/
		class CSoundManager{//シングルトン
			std::vector<Manager::CSound *> SoundList;//SEリスト
			static CSoundManager * Instance;
			CSoundManager(){}
			~CSoundManager(){}
		public:
			static CSoundManager * GetInstance(){return Instance;}
			static void Release(){
				for(Sint32 i=0;i<(Sint32)Instance->SoundList.size();++i){
					SAFE_DELETE(Instance->SoundList[i]);
				}
				delete Instance;
			}
			//サウンド管理
			inline Sint32 GetCSoundNum(void){
				return (Sint32)SoundList.size();
			}

			/**
				@brief サウンド追加
				@author my04337
				@param pSound [in] サウンドマネージャのアドレス
				@return サウンドID

				
				サウンドの登録を行う。戻り値はサウンドIDで、サウンドの追加順に<br>
				0 , 1 , 2 , ... といった値となる。
			*/
			Sint32 AddSound(const char * FileName,Sint32 LayerCount){
				SoundList.push_back(new CSound(FileName,LayerCount));
				return (Sint32)SoundList.size();
			}

			/**
				@brief サウンドマネージャ取得
				@author my04337
				@param idx [in] サウンドID
				@retval 成功時 サウンドマネージャのアドレス
				@retval 失敗時 NULL

				サウンドを取得する。無効なサウンドIDの場合、NULLが返される。
			*/
			inline Manager::CSound* GetCSound(Sint32 idx){
				return (idx>=0 && idx<(Sint32)SoundList.size()?SoundList[idx]:NULL);
			}			
		};

	};
};