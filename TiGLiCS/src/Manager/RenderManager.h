#pragma once
#include "Manager/FontManager.h"
#include "Manager/TextureManager.h"
#include "Base/Base.h"
#include <map>
#include <list>
#include <vector>
using namespace Selene;
namespace TiGLiCS{
	namespace Manager{
		/**
			@brief 描画マネージャ
			@author my04337

			描画順序とリソースの管理を行うクラス。<br>
			主に2Dの描画をサポートするが、シーンマネージャを取得することで<br>
			直接3Dの描画を行うことができる。
		*/
		class  CRenderManager{//描画マネージャ。シングルトン
			//-----クラス群--------------------------------
			class CSprite2DManager{
			public:
				Renderer::Object::ISprite2D * pSpr;//スプライト
				Sint32 TextureID;//テクスチャ
				Sint32 Priority;//優先度
				Sint32 DrawNum;//描画数
				Sint32 UnUsedFrame;//未使用フレーム数
				CSprite2DManager(Sint32 TextureID,Sint32 Priority);
				~CSprite2DManager(){SAFE_RELEASE(pSpr);}
			};
			class CFontSprite2DManager{
			public:
				Renderer::Object::IFontSprite2D * pFontSpr;//スプライト
				Sint32 FontID;//テクスチャ
				Sint32 Priority;//優先度
				Sint32 DrawNum;//描画数
				Sint32 UnUsedFrame;//未使用フレーム数
				CFontSprite2DManager(Sint32 FontID,Sint32 Priority);
				~CFontSprite2DManager(){SAFE_RELEASE(pFontSpr);}
			};
			class CPrimitive2DManager{
			public:
				Renderer::Object::IPrimitive2D * pPrimitive;//スプライト
				Sint32 Priority;//優先度
				Sint32 DrawNum;//描画数
				Sint32 UnUsedFrame;//未使用フレーム数
				CPrimitive2DManager(Sint32 Priority);
				~CPrimitive2DManager(){SAFE_RELEASE(pPrimitive);}
			};
			class CLine2DManager{
			public:
				Renderer::Object::ILine2D * pLine;//スプライト
				Sint32 Priority;//優先度
				Sint32 DrawNum;//描画数
				Sint32 UnUsedFrame;//未使用フレーム数
				CLine2DManager(Sint32 Priority);
				~CLine2DManager(){SAFE_RELEASE(pLine);}
			};
			class CPoint2DManager{
			public:
				Renderer::Object::IPoint2D  * pPoint;//スプライト
				Sint32 Priority;//優先度
				Sint32 DrawNum;
				Sint32 UnUsedFrame;//未使用フレーム数
				CPoint2DManager(Sint32 Priority);
				~CPoint2DManager(){SAFE_RELEASE(pPoint);}
			};

			class CSceneManager{
			public:
				Scene::ISceneManager   * pScene;//シーン
				Sint32 Priority;//優先度
				Math::Vector4D ClearColor;//初期化時の色
				CSceneManager(Sint32 Priority){
					this->Priority=Priority;
				}
				~CSceneManager(){SAFE_RELEASE(pScene);}
				void SetSceneManager(Scene::ISceneManager   * pScene){
					this->pScene=pScene;
				}
			};

			typedef std::multimap<Sint32,CSprite2DManager*>tSpriteList2D;
			typedef std::multimap<Sint32,CFontSprite2DManager*>tFontSpriteList2D;
			typedef std::multimap<Sint32,CPrimitive2DManager*>tPrimitiveList2D;
			typedef std::multimap<Sint32,CLine2DManager*>tLineList2D;
			typedef std::multimap<Sint32,CPoint2DManager*>tPointList2D;

			//typedef std::list<CLine3DManager*>tLineList3D;

			tSpriteList2D		SpriteList2D;
			tFontSpriteList2D	FontSpriteList2D;
			tPrimitiveList2D	PrimitiveList2D;
			tLineList2D		LineList2D;
			tPointList2D	PointList2D;
			
			//tLineList3D		LineList3D;


			Sint32 UnitPrimitiveSize2D;//この単位で2Dオブジェクト追加削除を行う。
			Sint32 MaxActorNum;//最大アクター数 相手側で調整してもらう
			CColor DefaultBackColor;
			static CRenderManager * Instance;
			char str_buf[1024];//文字列生成用バッファ。コスト削減のため

			CSprite2DManager * GetCSprite2DManager(Sint32 TexutrID,Sint32 Priority);
			CFontSprite2DManager * GetCFontSprite2DManager(Sint32 FontID,Sint32 DrawNum,Sint32 Priority);
			CPrimitive2DManager * GetCPrimitive2DManager(Sint32 DrawNum,Sint32 Priority);
			CLine2DManager * GetCLine2DManager(Sint32 DrawNum,Sint32 Priority);
			CPoint2DManager * GetCPoint2DManager(Sint32 Priority);

			CRenderManager();//コンストラクタ
			~CRenderManager(){}//デストラクタ
		public:
			static CRenderManager * GetInstance(){return Instance;}
			static void Release();
			///シーンマネージャへのポインタ
			CSceneManager * pSceneManager;
			
			
			

			/**
				@brief シーンマネージャの作成
				@author my04337
				@param isPixelShaderEnable [in] PixelShaderを有効にするか
				@param Priority [in] 描画優先度
				@return シーンマネージャへのポインタ

				シーンマネージャの作成を行う。戻り値はシーンマネージャへのポインタである。
			*/
			Scene::ISceneManager * CreateSceneManager(bool isPixelShaderEnable,Sint32 Priority);

			inline Scene::ISceneManager * GetSceneManager(){return (pSceneManager->pScene);}

			inline void SetBackgroundColor(CColor &col){DefaultBackColor=col;}
			//2D系----------------------------------------------------------
			//スプライト系
			/**
				@brief 2Dスプライト描画
				@author my04337
				@param Pos [in] 座標
				@param TextureID [in] テクスチャID
				@param TexRectID [in] テクスチャ範囲ID
				@param Priority [in] 描画優先度

				2Dスプライトの描画を行う。描画される座標は自動的にテクスチャの中心となる。
			*/
			void DrawSprite(Math::Point2DF &Pos,Sint32 TextureID,Sint32 TexRectID,Sint32 Priority);//スプライト描画、回転なし
			
			/**
				@brief 2Dスプライト描画 回転あり
				@author my04337
				@param Pos [in] 座標
				@param TextureID [in] テクスチャID
				@param TexRectID [in] テクスチャ範囲ID
				@param Priority [in] 描画優先度
				@param Angle [in] 角度

				回転した2Dスプライトの描画を行う。描画される座標は自動的にテクスチャの中心となる。
			*/
			void DrawSprite(Math::Point2DF &Pos,Sint32 TextureID,Sint32 TexRectID,Sint32 Priority,Sint32 Angle);//スプライト描画

			//テキスト系---------------------------------------------------------------------------
			/**
				@brief 2D文字列描画
				@author my04337
				@param DrawPos [in] 描画座標
				@param col [in] 描画色
				@param FontID [in] フォントID
				@param Priority [in] 描画優先度
				@param src [in] 書式文字列
				
				2Dテキストの描画を行う。DrawPosが文字列の右上端となる。改行した場合正しい位置に描画できない。<br>
				src , ... はprintfと同等の書式である。
			*/
			void DrawString(Math::Point2DF &DrawPos,CColor &col,Sint32 FontID,Sint32 Priority,const char * src,...);//文字列描画

			//プリミティブ系-------------------------------------------------------------------------
			
			/**
				@brief 2D塗りつぶし三角形描画
				@author my04337
				@param Pos1 [in] 描画座標1
				@param Pos2 [in] 描画座標2
				@param Pos3 [in] 描画座標3
				@param col [in] 描画色
				@param Priority [in] 描画優先度
				
				塗りつぶした3角形を描画する。頂点は時計回りにソートする必要がある。
			*/
			void FillTriangle(Math::Point2DF &Pos1,Math::Point2DF &Pos2,Math::Point2DF &Pos3,CColor &col,Sint32 Priority);//三角形塗りつぶし
			
			/**
				@brief 2D塗りつぶし四角形描画
				@author my04337
				@param pos [in] 描画範囲
				@param col [in] 描画色
				@param Priority [in] 描画優先度
				
				塗りつぶした長方形を描画する。
			*/
			void FillRect(Math::Rect2DF &pos,CColor &col,Sint32 Priority);//四角形塗りつぶし
			
			/**
				@brief 2D塗りつぶし四角形描画 回転あり
				@author my04337
				@param pos [in] 描画範囲
				@param col [in] 描画色
				@param Priority [in] 描画優先度
				@param Angle [in] 角度
				
				回転した塗りつぶした長方形を描画する。
			*/
			void FillRect(Math::Rect2DF &pos,CColor &col,Sint32 Priority,Sint32 Angle);//四角形角度付き

			/**
				@brief 2D塗りつぶし円形描画
				@author my04337
				@param pos [in] 描画位置
				@param Radius [in] 半径
				@param col [in] 描画色
				@param Priority [in] 描画優先度
				
				塗りつぶした円を描画する。
			*/
			void FillCircle(Math::Point2DF &pos,float Radius,CColor &col,Sint32 Priority);//円塗りつぶし

			/**
				@brief 2D塗りつぶし多角形描画
				@author my04337
				@param posArray [in] 座標配列の先頭アドレス
				@param posNum [in] 頂点数
				@param col [in] 描画色
				@param Priority [in] 描画優先度
				
				複数の三角形が連続した物を描画する。多角形を描画する際は始点と終点をあわせる必要がある。<br>
				頂点は時計回りに並んでいる必要がある。
			*/
			void FillPolygon(Math::Vector2D *posArray,Sint32 posNum,CColor &col,Sint32 Priority);//ポリゴン描画
			
			//ライン系-----------------------------------------------------------------------------------------
			
			/**
				@brief 2D四角形描画
				@author my04337
				@param pos [in] 描画範囲
				@param col [in] 描画色
				@param Priority [in] 描画優先度
				
				長方形を描画する。
			*/
			void DrawRect(Math::Rect2DF &pos,CColor &col,Sint32 Priority);//四角形
			
			/**
				@brief 2D四角形描画 回転あり
				@author my04337
				@param pos [in] 描画範囲
				@param col [in] 描画色
				@param Priority [in] 描画優先度
				@param Angle [in] 角度
				
				回転した長方形を描画する。
			*/
			void DrawRect(Math::Rect2DF &pos,CColor &col,Sint32 Priority,Sint32 Angle);//四角形角度付き
			
			/**
				@brief 2D三角形描画
				@author my04337
				@param Pos1 [in] 描画座標1
				@param Pos2 [in] 描画座標2
				@param Pos3 [in] 描画座標3
				@param col [in] 描画色
				@param Priority [in] 描画優先度
				
				3角形を描画する。頂点は時計回りにソートする必要がある。
			*/
			void DrawTriangle(Math::Point2DF &Pos1,Math::Point2DF &Pos2,Math::Point2DF &Pos3,CColor &col,Sint32 Priority);//三角形描画

			/**
				@brief 2D線描画
				@author my04337
				@param Pos1 [in] 始点座標
				@param Pos2 [in] 終点座標
				@param col [in] 描画色
				@param Priority [in] 描画優先度
				
				直線を描画する。
			*/
			void DrawLine(Math::Point2DF &Pos1,Math::Point2DF &Pos2,CColor &col,Sint32 Priority);//ライン描画

			/**
				@brief 2D多角形描画
				@author my04337
				@param posArray [in] 座標配列の先頭アドレス
				@param posNum [in] 頂点数
				@param col [in] 描画色
				@param Priority [in] 描画優先度
				
				複数の直線が連続した物を描画する。多角形を描画する際は始点と終点をあわせる必要がある。<br>
				頂点は時計回りに並んでいる必要がある。
			*/
			void DrawPolygon(Math::Vector2D *posArray,Sint32 posNum,CColor &col,Sint32 Priority);//ポリゴン描画
			
			/**
				@brief 2D円形描画
				@author my04337
				@param pos [in] 描画位置
				@param Radius [in] 半径
				@param col [in] 描画色
				@param Priority [in] 描画優先度
				
				円を描画する。
			*/
			void DrawCircle(Math::Point2DF &pos,float Radius,CColor &col,Sint32 Priority);//円描画

			//ポイント系-----------------------------------------------------------------------------------------

			/**
				@brief 2D点描画
				@author my04337
				@param Pos [in] 描画位置
				@param col [in] 描画色
				@param Priority [in] 描画優先度
				
				点を描画する。
			*/
			void DrawPoint(Math::Point2DF &Pos,CColor &col,Sint32 Priority);//ポイント描画

			//ダミー---------------------------------------------------------------------------------------------

			void DrawDummy(Sint32 Priority);//ベンチマーク用

			void Begin();//描画開始通知
			void End();//描画終了通知
			void Rendering();//描画終了通知
			void GabageCollection(Sint32 MaxCorllectNum=0);//ガーベージコレクタ
		};
	};
};