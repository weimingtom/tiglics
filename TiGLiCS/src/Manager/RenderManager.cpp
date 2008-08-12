#include "Manager/RenderManager.h"
#include "Engine/Engine.h"

using namespace Selene;
using namespace TiGLiCS;
using namespace TiGLiCS::Manager;

CRenderManager * CRenderManager::Instance = new CRenderManager();

CRenderManager::CSprite2DManager::CSprite2DManager(Sint32 TextureID,Sint32 Priority){
	this->TextureID=TextureID;
	this->Priority=Priority;
	this->pSpr=CEngine::GetInstance()->GetIRender()->CreateSprite2D(
		CRenderManager::GetInstance()->UnitPrimitiveSize2D*6,
		CTextureManager::GetInstance()->GetCTexture(TextureID)->GetITexture());
	this->DrawNum=0;this->UnUsedFrame=0;
}
CRenderManager::CFontSprite2DManager::CFontSprite2DManager(Sint32 FontID,Sint32 Priority){
	CRenderManager * pRenderMgr=CRenderManager::GetInstance();
	this->FontID=FontID;
	this->Priority=Priority;
	CFont * pFont=Manager::CFontManager::GetInstance()->GetCFont(FontID);
	this->pFontSpr=CEngine::GetInstance()->GetIRender()->CreateFontSprite2DFromFile(
		pFont->GetFileName() , pFont->GetFileType() , pRenderMgr->UnitPrimitiveSize2D);
	this->DrawNum=0;this->UnUsedFrame=0;
}
CRenderManager::CPrimitive2DManager::CPrimitive2DManager(Sint32 Priority){
	this->Priority=Priority;
	this->pPrimitive=CEngine::GetInstance()->GetIRender()->CreatePrimitive2D(
		CRenderManager::GetInstance()->UnitPrimitiveSize2D*3);
	this->DrawNum=0;this->UnUsedFrame=0;
}
CRenderManager::CLine2DManager::CLine2DManager(Sint32 Priority){
	this->Priority=Priority;
	this->pLine=CEngine::GetInstance()->GetIRender()->CreateLine2D(CRenderManager::GetInstance()->UnitPrimitiveSize2D*2);
	this->DrawNum=0;this->UnUsedFrame=0;
}
CRenderManager::CPoint2DManager::CPoint2DManager(Sint32 Priority){
	this->Priority=Priority;
	this->pPoint=CEngine::GetInstance()->GetIRender()->CreatePoint2D(CRenderManager::GetInstance()->UnitPrimitiveSize2D);
	this->DrawNum=0;this->UnUsedFrame=0;
}
//-----------------------------------------------------------

Scene::ISceneManager * CRenderManager::CreateSceneManager(bool isPixelShaderEnable,Sint32 Priority){
	pSceneManager=new CSceneManager(Priority);
	pSceneManager->SetSceneManager(CEngine::GetInstance()->GetIRender()->CreateSceneManager( MAX_ACTOR_NUM, isPixelShaderEnable ));
	
	return pSceneManager->pScene ;
}
void CRenderManager::Begin(){
	//スプライトについて
	for(tSpriteList2D::iterator it=SpriteList2D.begin();it!=SpriteList2D.end();++it){
		it->second->pSpr->Begin();
		it->second->DrawNum=0;
	}
	//ポイントについてについて
	for(tPointList2D::iterator it=PointList2D.begin();it!=PointList2D.end();++it){
		it->second->pPoint->Begin();
		it->second->DrawNum=0;
	}
	//ラインについてについて
	for(tLineList2D::iterator it=LineList2D.begin();it!=LineList2D.end();++it){
		it->second->pLine->Begin();
		it->second->DrawNum=0;
	}
	//プリミティブについてについて
	for(tPrimitiveList2D::iterator it=PrimitiveList2D.begin();it!=PrimitiveList2D.end();++it){
		it->second->pPrimitive->Begin();
		it->second->DrawNum=0;
	}
	//フォントについて
	for(tFontSpriteList2D::iterator it=FontSpriteList2D.begin();it!=FontSpriteList2D.end();++it){
		it->second->pFontSpr->Begin();
		it->second->DrawNum=0; 
	}
	//シーンについて	
	if(pSceneManager!=NULL){		
		CFrameManager * pFrameManager=Manager::CPageManager::GetInstance()->GetNowPage()->GetCFrameManager();
		pSceneManager->pScene->Reset();	
		if(pFrameManager!=NULL){
			pFrameManager->OnSceneManagerReset();
		}
		pSceneManager->pScene->Begin(false);	
	}
}
void CRenderManager::End(){
#ifdef TIGLICS_DEBUG
	Manager::CPageManager * pPageManager=Manager::CPageManager::GetInstance();
#endif
	//スプライトについて
	for(tSpriteList2D::iterator it=SpriteList2D.begin();it!=SpriteList2D.end();++it){
		it->second->pSpr->End();
		if(it->second->DrawNum!=0){
			it->second->UnUsedFrame=0;
		}else{
			++it->second->UnUsedFrame;
		}

	}
	//ポイントについて
	for(tPointList2D::iterator it=PointList2D.begin();it!=PointList2D.end();++it){
		it->second->pPoint->End();
		if(it->second->DrawNum!=0){
			it->second->UnUsedFrame=0;
		}else{
			++it->second->UnUsedFrame;
		}
	}
	//ラインについて
	for(tLineList2D::iterator it=LineList2D.begin();it!=LineList2D.end();++it){
		it->second->pLine->End();
		if(it->second->DrawNum!=0){
			it->second->UnUsedFrame=0;
		}else{
			++it->second->UnUsedFrame;
		}
	}
	//プリミティブについて
	for(tPrimitiveList2D::iterator it=PrimitiveList2D.begin();it!=PrimitiveList2D.end();++it){
		it->second->pPrimitive->End();
		if(it->second->DrawNum!=0){
			it->second->UnUsedFrame=0;
		}else{
			++it->second->UnUsedFrame;
		}
	}
	//フォントについて
	for(tFontSpriteList2D::iterator it=FontSpriteList2D.begin();it!=FontSpriteList2D.end();++it){
		it->second->pFontSpr->End();
		if(it->second->DrawNum!=0){
			it->second->UnUsedFrame=0;
		}else{
			++it->second->UnUsedFrame;
		}
	}
	
	//シーンについて
	if(pSceneManager!=NULL){
		pSceneManager->pScene->End();
#ifdef TIGLICS_DEBUG
		pPageManager->GetNowPage()->Log2Print(6,"RequestActor:%d",pSceneManager->pScene->GetResult_RenderingRequestActorCount());
#endif

	}

#ifdef TIGLICS_DEBUG
	pPageManager->GetNowPage()->Log2Print(4,"Sprite2D    :%d",SpriteList2D.size());
	pPageManager->GetNowPage()->Log2Print(3,"FontSprite2D:%d",FontSpriteList2D.size());
	pPageManager->GetNowPage()->Log2Print(2,"Primitive2D :%d",PrimitiveList2D.size());
	pPageManager->GetNowPage()->Log2Print(1,"Line2D      :%d",LineList2D.size());
	pPageManager->GetNowPage()->Log2Print(0,"Point2D     :%d",PointList2D.size());
#endif
}

void CRenderManager::Rendering(){
	//描画を行う。
	//描画を行う。
	//描画順番は、
	//sprite->point->line->primitive->FontSprite->PostEffect
	//とする。	
	Sint32 endFlag=0;
	tSpriteList2D::iterator itSprite2D=SpriteList2D.begin();
	tFontSpriteList2D::iterator itFontSprite2D=FontSpriteList2D.begin();
	tPrimitiveList2D::iterator itPrimitive2D=PrimitiveList2D.begin();
	tLineList2D::iterator itLine2D=LineList2D.begin();
	tPointList2D::iterator itPoint2D=PointList2D.begin();

	bool isSceneRender=false;
	do{
		Sint32 nowPriority=LONG_MAX;//優先度最大値
		eRequestDrawType nextDraw=drDummy;
		//まずは、もっとも優先度が高いものを探す
		//スプライト
		if(itSprite2D!=SpriteList2D.end()){
			if(nowPriority>itSprite2D->second->Priority ){
				nowPriority=itSprite2D->second->Priority ;
				nextDraw=drSprite2D;
			}
		}	
		//ライン
		if(itPoint2D!=PointList2D.end()){
			if(nowPriority>itPoint2D->second->Priority ){
				nowPriority=itPoint2D->second->Priority ;
				nextDraw=drPoint2D;
			}
		}		
		//ライン
		if(itLine2D!=LineList2D.end()){
			if(nowPriority>itLine2D->second ->Priority ){
				nowPriority=itLine2D->second ->Priority ;
				nextDraw=drLine2D;
			}
		}		
		//プリミティブ
		if(itPrimitive2D!=PrimitiveList2D.end()){
			if(nowPriority>itPrimitive2D->second ->Priority ){
				nowPriority=itPrimitive2D->second ->Priority ;
				nextDraw=drPrimitive2D;
			}
		}			
		//フォント
		if(itFontSprite2D!=FontSpriteList2D.end()){
			if(nowPriority>itFontSprite2D->second ->Priority ){
				nowPriority=itFontSprite2D->second ->Priority ;
				nextDraw=drFontSprite2D;
			}
		}		
		//シーン
		
		if(pSceneManager!=NULL && !isSceneRender && nowPriority>pSceneManager->Priority ){
			nowPriority=pSceneManager->Priority;
			nextDraw=drScene;
			isSceneRender=true;
		}
		//求まったので、描画する
		switch(nextDraw){
			case drSprite2D:itSprite2D->second ->pSpr->Rendering();++itSprite2D;break;
			case drPoint2D:itPoint2D->second ->pPoint->Rendering();++itPoint2D;break;
			case drLine2D:itLine2D->second ->pLine->Rendering();++itLine2D;break;
			case drPrimitive2D:itPrimitive2D->second ->pPrimitive->Rendering();++itPrimitive2D;break;
			case drFontSprite2D:itFontSprite2D->second ->pFontSpr->Rendering();++itFontSprite2D;break;
			case drScene:
#ifdef TIGLICS_DEBUG
				pSceneManager->pScene->Rendering(true);
#else
				pSceneManager->pScene->Rendering(false);
#endif
				break;
			default:endFlag=1;
		}
	}while(endFlag!=1);

}

CRenderManager::CRenderManager(){
	//コンストラクタ。
	this->UnitPrimitiveSize2D=UNIT_PRIMITIVE_SIZE2D;
	this->MaxActorNum=MAX_ACTOR_NUM;
	this->pSceneManager=NULL;//最初はNULLで
}
void CRenderManager::Release(){
	
	//シーンマネージャについて
	SAFE_DELETE(Instance->pSceneManager);
	//スプライトの削除
	for(tSpriteList2D::iterator it=Instance->SpriteList2D.begin();it!=Instance->SpriteList2D.end();){
		SAFE_RELEASE(it->second ->pSpr);
		delete (it++)->second ;
	}	
	//ポイントについて
	for(tPointList2D::iterator it=Instance->PointList2D.begin();it!=Instance->PointList2D.end();){
		SAFE_RELEASE(it->second ->pPoint);
		delete (it++)->second ;
	}
	//ラインについて
	for(tLineList2D::iterator it=Instance->LineList2D.begin();it!=Instance->LineList2D.end();){
		SAFE_RELEASE(it->second ->pLine);
		delete (it++)->second ;
	}
	//プリミティブについて
	for(tPrimitiveList2D::iterator it=Instance->PrimitiveList2D.begin();it!=Instance->PrimitiveList2D.end();){
		SAFE_RELEASE(it->second ->pPrimitive);
		delete (it++)->second ;
	}
	//フォントについて
	for(tFontSpriteList2D::iterator it=Instance->FontSpriteList2D.begin();it!=Instance->FontSpriteList2D.end();){
		SAFE_RELEASE(it->second->pFontSpr);
		delete (it++)->second ;
	}
	
	
	delete Instance;
}
CRenderManager::CSprite2DManager * CRenderManager::GetCSprite2DManager(Sint32 TextureID ,Sint32 Priority){
	//スプライトを返す
	CTextureManager * pTextureManager = CTextureManager::GetInstance();
	if(TextureID>=(Sint32)pTextureManager->GetCTextureNum())return NULL;//テクスチャIDが不正
	for(tSpriteList2D::iterator it=SpriteList2D.begin();it!=SpriteList2D.end();++it){
		if(it->second->Priority==Priority && it->second->TextureID==TextureID && it->second->DrawNum<UnitPrimitiveSize2D){
			//条件に合うのがあったら
			it->second->DrawNum+=1;
			return it->second;
		}
	}
	//いいのがなかった場合
	CSprite2DManager * pSpr2DMgr=new CSprite2DManager(TextureID,Priority);
	SpriteList2D.insert(std::pair<Sint32,CSprite2DManager*>(Priority,pSpr2DMgr));
	pSpr2DMgr->pSpr->Begin();//新しく作ったから開始されていないため
	pSpr2DMgr->DrawNum+=1;
	Manager::CPageManager::GetInstance()->GetNowPage()->LogPrint("MKSprite2D    :%+03d,%02d,%p",Priority,TextureID,pSpr2DMgr);
	return pSpr2DMgr;
}
CRenderManager::CLine2DManager * CRenderManager::GetCLine2DManager(Sint32 VertexNum,Sint32 Priority){
	//ラインを返す
	for(tLineList2D::iterator it=LineList2D.begin();it!=LineList2D.end();++it){
		if(it->second->Priority==Priority && it->second->DrawNum+VertexNum<=UnitPrimitiveSize2D){
			//条件に合うのがあったら
			it->second->DrawNum+=VertexNum;
			return it->second;
		}
	}
	//いいのがなかった場合
	CLine2DManager * pLine2DMgr=new CLine2DManager(Priority);
	LineList2D.insert(std::pair<Sint32,CLine2DManager*>(Priority,pLine2DMgr));
	pLine2DMgr->pLine->Begin();//新しく作ったから開始されていないため
	pLine2DMgr->DrawNum+=VertexNum;
	Manager::CPageManager::GetInstance()->GetNowPage()->LogPrint("MKLine2D      :%+03d,   %p",Priority,pLine2DMgr);
	return pLine2DMgr;
}
CRenderManager::CPoint2DManager * CRenderManager::GetCPoint2DManager(Sint32 Priority){
	//ポイントを返す
	for(tPointList2D::iterator it=PointList2D.begin();it!=PointList2D.end();++it){
		if(it->second->Priority==Priority && it->second->DrawNum<UnitPrimitiveSize2D){
			//条件に合うのがあったら
			it->second->DrawNum+=1;
			return it->second;
		}
	}
	//いいのがなかった場合
	CPoint2DManager * pPoint2DMgr=new CPoint2DManager(Priority);
	PointList2D.insert(std::pair<Sint32,CPoint2DManager*>(Priority,pPoint2DMgr));
	pPoint2DMgr->pPoint->Begin();//新しく作ったから開始されていないため
	pPoint2DMgr->DrawNum+=1;
	Manager::CPageManager::GetInstance()->GetNowPage()->LogPrint("MKPoint2D     :%+03d,   %p",Priority,pPoint2DMgr);
	return pPoint2DMgr;
}
CRenderManager::CPrimitive2DManager * CRenderManager::GetCPrimitive2DManager(Sint32 VertexNum,Sint32 Priority){
	//プリミティブを返す
	for(tPrimitiveList2D::iterator it=PrimitiveList2D.begin();it!=PrimitiveList2D.end();++it){
		if(it->second->Priority==Priority && it->second->DrawNum+VertexNum<=UnitPrimitiveSize2D){
			//条件に合うのがあったら
			it->second->DrawNum+=VertexNum;
			return it->second;
		}
	}
	//いいのがなかった場合
	CPrimitive2DManager * pPrimitive2DMgr=new CPrimitive2DManager(Priority);
	PrimitiveList2D.insert(std::pair<Sint32,CPrimitive2DManager*>(Priority,pPrimitive2DMgr));
	pPrimitive2DMgr->pPrimitive->Begin();//新しく作ったから開始されていないため
	pPrimitive2DMgr->DrawNum+=VertexNum;
	Manager::CPageManager::GetInstance()->GetNowPage()->LogPrint("MKPrimitive2D :%+03d,   %p",Priority,pPrimitive2DMgr);
	return pPrimitive2DMgr;
}
CRenderManager::CFontSprite2DManager * CRenderManager::GetCFontSprite2DManager(Sint32 FontID,Sint32 StrLen,Sint32 Priority){
	//フォントを返す
	CFontManager * pFontManager=CFontManager::GetInstance();
	if(FontID>=(Sint32)pFontManager->GetCFontNum())return NULL;//テクスチャIDが不正
	for(tFontSpriteList2D::iterator it=FontSpriteList2D.begin();it!=FontSpriteList2D.end();++it){
		if(it->second->Priority==Priority && it->second->FontID==FontID && it->second->DrawNum+StrLen<=UnitPrimitiveSize2D){
			//条件に合うのがあったら
			it->second->DrawNum+=StrLen;
			return it->second;
		}
	}
	//いいのがなかった場合
	CFontSprite2DManager * pFontSpr2DMgr=new CFontSprite2DManager(FontID,Priority);
	FontSpriteList2D.insert(std::pair<Sint32,CFontSprite2DManager*>(Priority,pFontSpr2DMgr));
	pFontSpr2DMgr->pFontSpr->Begin();//新しく作ったから開始されていないため
	pFontSpr2DMgr->DrawNum+=StrLen;
	Manager::CPageManager::GetInstance()->GetNowPage()->LogPrint("MKFontSprite2D:%+03d,%02d,%p",Priority,FontID,pFontSpr2DMgr);
	return pFontSpr2DMgr;
}
void CRenderManager::GabageCollection(Sint32 MaxCollectNum){
	
	//ガーベージコレクタ
	//オブジェクト数が減ったときにスプライト数を減らす処理。
	//MaxGarbageNumは最大処理数。これを少なくすることで1フレームでの処理を減らせる。
	Sint32 _MaxCollectNum=MaxCollectNum;//各オブジェクトについてMaxCollectNum回処理させるので
	Manager::CPageManager * pPageManager=Manager::CPageManager::GetInstance();
	//誰も使ってないスプライトについて、削除する。
	for(tSpriteList2D::iterator it=SpriteList2D.begin();it!=SpriteList2D.end();){
		if(it->second->UnUsedFrame>300){
			pPageManager->GetNowPage()->LogPrint("GCSprite2D    :%+03d,%02d,%p",it->second->Priority,it->second->TextureID,it->second );
			CSprite2DManager * pSpr2DMgr=it->second ;//バックアップ用
			SpriteList2D.erase(it++);
			SAFE_RELEASE(pSpr2DMgr->pSpr);
			if((--_MaxCollectNum)==0)break;//あえて==0(0の時ほぼ無限回繰り返し)
		}else{
			++it;
		}		
	}
	_MaxCollectNum=MaxCollectNum;
	//誰も使ってないポイントについて、削除する。
	for(tPointList2D::iterator it=PointList2D.begin();it!=PointList2D.end();){
		if(it->second->UnUsedFrame>300){
			pPageManager->GetNowPage()->LogPrint("GCPoint2D     :%+03d,   %p",it->second->Priority,it->second );
			CPoint2DManager * pPoint2DMgr=it->second;//バックアップ用
			PointList2D.erase(it++);
			SAFE_RELEASE(pPoint2DMgr->pPoint);
			if((--_MaxCollectNum)==0)break;//あえて==0(0の時ほぼ無限回繰り返し)
		}else{
			++it;
		}		
	}
	_MaxCollectNum=MaxCollectNum;
	//誰も使ってないラインについて、削除する。
	for(tLineList2D::iterator it=LineList2D.begin();it!=LineList2D.end();){
		if(it->second->UnUsedFrame>300){
			pPageManager->GetNowPage()->LogPrint("GCLine2D      :%+03d,   %p",it->second->Priority,it->second );
			CLine2DManager * pLine2DMgr=it->second;//バックアップ用
			LineList2D.erase(it++);
			SAFE_RELEASE(pLine2DMgr->pLine);
			if((--_MaxCollectNum)==0)break;//あえて==0(0の時ほぼ無限回繰り返し)
		}else{
			++it;
		}		
	}
	_MaxCollectNum=MaxCollectNum;
	//誰も使ってないプリミティブについて、削除する。
	for(tPrimitiveList2D::iterator it=PrimitiveList2D.begin();it!=PrimitiveList2D.end();){
		if(it->second->UnUsedFrame>300){
			pPageManager->GetNowPage()->LogPrint("GCPrimitive2D :%+03d,   %p",it->second->Priority,it->second );
			CPrimitive2DManager * pPrimitive2DMgr=it->second;//バックアップ用
			PrimitiveList2D.erase(it++);
			SAFE_RELEASE(pPrimitive2DMgr->pPrimitive);
			if((--_MaxCollectNum)==0)break;//あえて==0(0の時ほぼ無限回繰り返し)
		}else{
			++it;
		}		
	}
	_MaxCollectNum=MaxCollectNum;
	//誰も使ってないフォントスプライトについて、削除する。
	for(tFontSpriteList2D::iterator it=FontSpriteList2D.begin();it!=FontSpriteList2D.end();){
		if(it->second->UnUsedFrame>600){//フォントは、生成の手間が大きいので
			pPageManager->GetNowPage()->LogPrint("GCFontSprite2D:%+03d,%02d,%p" ,it->second->Priority,it->second->FontID,it->second );
			CFontSprite2DManager * pFontSpr2DMgr=it->second;//バックアップ用
			FontSpriteList2D.erase(it++);
			SAFE_RELEASE(pFontSpr2DMgr->pFontSpr);
			if((--_MaxCollectNum)==0)break;//あえて==0(0の時ほぼ無限回繰り返し)
		}else{
			++it;
		}		
	}
}
