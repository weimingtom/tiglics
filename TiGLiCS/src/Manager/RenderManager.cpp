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
	//�X�v���C�g�ɂ���
	for(tSpriteList2D::iterator it=SpriteList2D.begin();it!=SpriteList2D.end();++it){
		it->second->pSpr->Begin();
		it->second->DrawNum=0;
	}
	//�|�C���g�ɂ��Ăɂ���
	for(tPointList2D::iterator it=PointList2D.begin();it!=PointList2D.end();++it){
		it->second->pPoint->Begin();
		it->second->DrawNum=0;
	}
	//���C���ɂ��Ăɂ���
	for(tLineList2D::iterator it=LineList2D.begin();it!=LineList2D.end();++it){
		it->second->pLine->Begin();
		it->second->DrawNum=0;
	}
	//�v���~�e�B�u�ɂ��Ăɂ���
	for(tPrimitiveList2D::iterator it=PrimitiveList2D.begin();it!=PrimitiveList2D.end();++it){
		it->second->pPrimitive->Begin();
		it->second->DrawNum=0;
	}
	//�t�H���g�ɂ���
	for(tFontSpriteList2D::iterator it=FontSpriteList2D.begin();it!=FontSpriteList2D.end();++it){
		it->second->pFontSpr->Begin();
		it->second->DrawNum=0; 
	}
	//�V�[���ɂ���	
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
	//�X�v���C�g�ɂ���
	for(tSpriteList2D::iterator it=SpriteList2D.begin();it!=SpriteList2D.end();++it){
		it->second->pSpr->End();
		if(it->second->DrawNum!=0){
			it->second->UnUsedFrame=0;
		}else{
			++it->second->UnUsedFrame;
		}

	}
	//�|�C���g�ɂ���
	for(tPointList2D::iterator it=PointList2D.begin();it!=PointList2D.end();++it){
		it->second->pPoint->End();
		if(it->second->DrawNum!=0){
			it->second->UnUsedFrame=0;
		}else{
			++it->second->UnUsedFrame;
		}
	}
	//���C���ɂ���
	for(tLineList2D::iterator it=LineList2D.begin();it!=LineList2D.end();++it){
		it->second->pLine->End();
		if(it->second->DrawNum!=0){
			it->second->UnUsedFrame=0;
		}else{
			++it->second->UnUsedFrame;
		}
	}
	//�v���~�e�B�u�ɂ���
	for(tPrimitiveList2D::iterator it=PrimitiveList2D.begin();it!=PrimitiveList2D.end();++it){
		it->second->pPrimitive->End();
		if(it->second->DrawNum!=0){
			it->second->UnUsedFrame=0;
		}else{
			++it->second->UnUsedFrame;
		}
	}
	//�t�H���g�ɂ���
	for(tFontSpriteList2D::iterator it=FontSpriteList2D.begin();it!=FontSpriteList2D.end();++it){
		it->second->pFontSpr->End();
		if(it->second->DrawNum!=0){
			it->second->UnUsedFrame=0;
		}else{
			++it->second->UnUsedFrame;
		}
	}
	
	//�V�[���ɂ���
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
	//�`����s���B
	//�`����s���B
	//�`�揇�Ԃ́A
	//sprite->point->line->primitive->FontSprite->PostEffect
	//�Ƃ���B	
	Sint32 endFlag=0;
	tSpriteList2D::iterator itSprite2D=SpriteList2D.begin();
	tFontSpriteList2D::iterator itFontSprite2D=FontSpriteList2D.begin();
	tPrimitiveList2D::iterator itPrimitive2D=PrimitiveList2D.begin();
	tLineList2D::iterator itLine2D=LineList2D.begin();
	tPointList2D::iterator itPoint2D=PointList2D.begin();

	bool isSceneRender=false;
	do{
		Sint32 nowPriority=LONG_MAX;//�D��x�ő�l
		eRequestDrawType nextDraw=drDummy;
		//�܂��́A�����Ƃ��D��x���������̂�T��
		//�X�v���C�g
		if(itSprite2D!=SpriteList2D.end()){
			if(nowPriority>itSprite2D->second->Priority ){
				nowPriority=itSprite2D->second->Priority ;
				nextDraw=drSprite2D;
			}
		}	
		//���C��
		if(itPoint2D!=PointList2D.end()){
			if(nowPriority>itPoint2D->second->Priority ){
				nowPriority=itPoint2D->second->Priority ;
				nextDraw=drPoint2D;
			}
		}		
		//���C��
		if(itLine2D!=LineList2D.end()){
			if(nowPriority>itLine2D->second ->Priority ){
				nowPriority=itLine2D->second ->Priority ;
				nextDraw=drLine2D;
			}
		}		
		//�v���~�e�B�u
		if(itPrimitive2D!=PrimitiveList2D.end()){
			if(nowPriority>itPrimitive2D->second ->Priority ){
				nowPriority=itPrimitive2D->second ->Priority ;
				nextDraw=drPrimitive2D;
			}
		}			
		//�t�H���g
		if(itFontSprite2D!=FontSpriteList2D.end()){
			if(nowPriority>itFontSprite2D->second ->Priority ){
				nowPriority=itFontSprite2D->second ->Priority ;
				nextDraw=drFontSprite2D;
			}
		}		
		//�V�[��
		
		if(pSceneManager!=NULL && !isSceneRender && nowPriority>pSceneManager->Priority ){
			nowPriority=pSceneManager->Priority;
			nextDraw=drScene;
			isSceneRender=true;
		}
		//���܂����̂ŁA�`�悷��
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
	//�R���X�g���N�^�B
	this->UnitPrimitiveSize2D=UNIT_PRIMITIVE_SIZE2D;
	this->MaxActorNum=MAX_ACTOR_NUM;
	this->pSceneManager=NULL;//�ŏ���NULL��
}
void CRenderManager::Release(){
	
	//�V�[���}�l�[�W���ɂ���
	SAFE_DELETE(Instance->pSceneManager);
	//�X�v���C�g�̍폜
	for(tSpriteList2D::iterator it=Instance->SpriteList2D.begin();it!=Instance->SpriteList2D.end();){
		SAFE_RELEASE(it->second ->pSpr);
		delete (it++)->second ;
	}	
	//�|�C���g�ɂ���
	for(tPointList2D::iterator it=Instance->PointList2D.begin();it!=Instance->PointList2D.end();){
		SAFE_RELEASE(it->second ->pPoint);
		delete (it++)->second ;
	}
	//���C���ɂ���
	for(tLineList2D::iterator it=Instance->LineList2D.begin();it!=Instance->LineList2D.end();){
		SAFE_RELEASE(it->second ->pLine);
		delete (it++)->second ;
	}
	//�v���~�e�B�u�ɂ���
	for(tPrimitiveList2D::iterator it=Instance->PrimitiveList2D.begin();it!=Instance->PrimitiveList2D.end();){
		SAFE_RELEASE(it->second ->pPrimitive);
		delete (it++)->second ;
	}
	//�t�H���g�ɂ���
	for(tFontSpriteList2D::iterator it=Instance->FontSpriteList2D.begin();it!=Instance->FontSpriteList2D.end();){
		SAFE_RELEASE(it->second->pFontSpr);
		delete (it++)->second ;
	}
	
	
	delete Instance;
}
CRenderManager::CSprite2DManager * CRenderManager::GetCSprite2DManager(Sint32 TextureID ,Sint32 Priority){
	//�X�v���C�g��Ԃ�
	CTextureManager * pTextureManager = CTextureManager::GetInstance();
	if(TextureID>=(Sint32)pTextureManager->GetCTextureNum())return NULL;//�e�N�X�`��ID���s��
	for(tSpriteList2D::iterator it=SpriteList2D.begin();it!=SpriteList2D.end();++it){
		if(it->second->Priority==Priority && it->second->TextureID==TextureID && it->second->DrawNum<UnitPrimitiveSize2D){
			//�����ɍ����̂���������
			it->second->DrawNum+=1;
			return it->second;
		}
	}
	//�����̂��Ȃ������ꍇ
	CSprite2DManager * pSpr2DMgr=new CSprite2DManager(TextureID,Priority);
	SpriteList2D.insert(std::pair<Sint32,CSprite2DManager*>(Priority,pSpr2DMgr));
	pSpr2DMgr->pSpr->Begin();//�V�������������J�n����Ă��Ȃ�����
	pSpr2DMgr->DrawNum+=1;
	Manager::CPageManager::GetInstance()->GetNowPage()->LogPrint("MKSprite2D    :%+03d,%02d,%p",Priority,TextureID,pSpr2DMgr);
	return pSpr2DMgr;
}
CRenderManager::CLine2DManager * CRenderManager::GetCLine2DManager(Sint32 VertexNum,Sint32 Priority){
	//���C����Ԃ�
	for(tLineList2D::iterator it=LineList2D.begin();it!=LineList2D.end();++it){
		if(it->second->Priority==Priority && it->second->DrawNum+VertexNum<=UnitPrimitiveSize2D){
			//�����ɍ����̂���������
			it->second->DrawNum+=VertexNum;
			return it->second;
		}
	}
	//�����̂��Ȃ������ꍇ
	CLine2DManager * pLine2DMgr=new CLine2DManager(Priority);
	LineList2D.insert(std::pair<Sint32,CLine2DManager*>(Priority,pLine2DMgr));
	pLine2DMgr->pLine->Begin();//�V�������������J�n����Ă��Ȃ�����
	pLine2DMgr->DrawNum+=VertexNum;
	Manager::CPageManager::GetInstance()->GetNowPage()->LogPrint("MKLine2D      :%+03d,   %p",Priority,pLine2DMgr);
	return pLine2DMgr;
}
CRenderManager::CPoint2DManager * CRenderManager::GetCPoint2DManager(Sint32 Priority){
	//�|�C���g��Ԃ�
	for(tPointList2D::iterator it=PointList2D.begin();it!=PointList2D.end();++it){
		if(it->second->Priority==Priority && it->second->DrawNum<UnitPrimitiveSize2D){
			//�����ɍ����̂���������
			it->second->DrawNum+=1;
			return it->second;
		}
	}
	//�����̂��Ȃ������ꍇ
	CPoint2DManager * pPoint2DMgr=new CPoint2DManager(Priority);
	PointList2D.insert(std::pair<Sint32,CPoint2DManager*>(Priority,pPoint2DMgr));
	pPoint2DMgr->pPoint->Begin();//�V�������������J�n����Ă��Ȃ�����
	pPoint2DMgr->DrawNum+=1;
	Manager::CPageManager::GetInstance()->GetNowPage()->LogPrint("MKPoint2D     :%+03d,   %p",Priority,pPoint2DMgr);
	return pPoint2DMgr;
}
CRenderManager::CPrimitive2DManager * CRenderManager::GetCPrimitive2DManager(Sint32 VertexNum,Sint32 Priority){
	//�v���~�e�B�u��Ԃ�
	for(tPrimitiveList2D::iterator it=PrimitiveList2D.begin();it!=PrimitiveList2D.end();++it){
		if(it->second->Priority==Priority && it->second->DrawNum+VertexNum<=UnitPrimitiveSize2D){
			//�����ɍ����̂���������
			it->second->DrawNum+=VertexNum;
			return it->second;
		}
	}
	//�����̂��Ȃ������ꍇ
	CPrimitive2DManager * pPrimitive2DMgr=new CPrimitive2DManager(Priority);
	PrimitiveList2D.insert(std::pair<Sint32,CPrimitive2DManager*>(Priority,pPrimitive2DMgr));
	pPrimitive2DMgr->pPrimitive->Begin();//�V�������������J�n����Ă��Ȃ�����
	pPrimitive2DMgr->DrawNum+=VertexNum;
	Manager::CPageManager::GetInstance()->GetNowPage()->LogPrint("MKPrimitive2D :%+03d,   %p",Priority,pPrimitive2DMgr);
	return pPrimitive2DMgr;
}
CRenderManager::CFontSprite2DManager * CRenderManager::GetCFontSprite2DManager(Sint32 FontID,Sint32 StrLen,Sint32 Priority){
	//�t�H���g��Ԃ�
	CFontManager * pFontManager=CFontManager::GetInstance();
	if(FontID>=(Sint32)pFontManager->GetCFontNum())return NULL;//�e�N�X�`��ID���s��
	for(tFontSpriteList2D::iterator it=FontSpriteList2D.begin();it!=FontSpriteList2D.end();++it){
		if(it->second->Priority==Priority && it->second->FontID==FontID && it->second->DrawNum+StrLen<=UnitPrimitiveSize2D){
			//�����ɍ����̂���������
			it->second->DrawNum+=StrLen;
			return it->second;
		}
	}
	//�����̂��Ȃ������ꍇ
	CFontSprite2DManager * pFontSpr2DMgr=new CFontSprite2DManager(FontID,Priority);
	FontSpriteList2D.insert(std::pair<Sint32,CFontSprite2DManager*>(Priority,pFontSpr2DMgr));
	pFontSpr2DMgr->pFontSpr->Begin();//�V�������������J�n����Ă��Ȃ�����
	pFontSpr2DMgr->DrawNum+=StrLen;
	Manager::CPageManager::GetInstance()->GetNowPage()->LogPrint("MKFontSprite2D:%+03d,%02d,%p",Priority,FontID,pFontSpr2DMgr);
	return pFontSpr2DMgr;
}
void CRenderManager::GabageCollection(Sint32 MaxCollectNum){
	
	//�K�[�x�[�W�R���N�^
	//�I�u�W�F�N�g�����������Ƃ��ɃX�v���C�g�������炷�����B
	//MaxGarbageNum�͍ő又�����B��������Ȃ����邱�Ƃ�1�t���[���ł̏��������点��B
	Sint32 _MaxCollectNum=MaxCollectNum;//�e�I�u�W�F�N�g�ɂ���MaxCollectNum�񏈗�������̂�
	Manager::CPageManager * pPageManager=Manager::CPageManager::GetInstance();
	//�N���g���ĂȂ��X�v���C�g�ɂ��āA�폜����B
	for(tSpriteList2D::iterator it=SpriteList2D.begin();it!=SpriteList2D.end();){
		if(it->second->UnUsedFrame>300){
			pPageManager->GetNowPage()->LogPrint("GCSprite2D    :%+03d,%02d,%p",it->second->Priority,it->second->TextureID,it->second );
			CSprite2DManager * pSpr2DMgr=it->second ;//�o�b�N�A�b�v�p
			SpriteList2D.erase(it++);
			SAFE_RELEASE(pSpr2DMgr->pSpr);
			if((--_MaxCollectNum)==0)break;//������==0(0�̎��قږ�����J��Ԃ�)
		}else{
			++it;
		}		
	}
	_MaxCollectNum=MaxCollectNum;
	//�N���g���ĂȂ��|�C���g�ɂ��āA�폜����B
	for(tPointList2D::iterator it=PointList2D.begin();it!=PointList2D.end();){
		if(it->second->UnUsedFrame>300){
			pPageManager->GetNowPage()->LogPrint("GCPoint2D     :%+03d,   %p",it->second->Priority,it->second );
			CPoint2DManager * pPoint2DMgr=it->second;//�o�b�N�A�b�v�p
			PointList2D.erase(it++);
			SAFE_RELEASE(pPoint2DMgr->pPoint);
			if((--_MaxCollectNum)==0)break;//������==0(0�̎��قږ�����J��Ԃ�)
		}else{
			++it;
		}		
	}
	_MaxCollectNum=MaxCollectNum;
	//�N���g���ĂȂ����C���ɂ��āA�폜����B
	for(tLineList2D::iterator it=LineList2D.begin();it!=LineList2D.end();){
		if(it->second->UnUsedFrame>300){
			pPageManager->GetNowPage()->LogPrint("GCLine2D      :%+03d,   %p",it->second->Priority,it->second );
			CLine2DManager * pLine2DMgr=it->second;//�o�b�N�A�b�v�p
			LineList2D.erase(it++);
			SAFE_RELEASE(pLine2DMgr->pLine);
			if((--_MaxCollectNum)==0)break;//������==0(0�̎��قږ�����J��Ԃ�)
		}else{
			++it;
		}		
	}
	_MaxCollectNum=MaxCollectNum;
	//�N���g���ĂȂ��v���~�e�B�u�ɂ��āA�폜����B
	for(tPrimitiveList2D::iterator it=PrimitiveList2D.begin();it!=PrimitiveList2D.end();){
		if(it->second->UnUsedFrame>300){
			pPageManager->GetNowPage()->LogPrint("GCPrimitive2D :%+03d,   %p",it->second->Priority,it->second );
			CPrimitive2DManager * pPrimitive2DMgr=it->second;//�o�b�N�A�b�v�p
			PrimitiveList2D.erase(it++);
			SAFE_RELEASE(pPrimitive2DMgr->pPrimitive);
			if((--_MaxCollectNum)==0)break;//������==0(0�̎��قږ�����J��Ԃ�)
		}else{
			++it;
		}		
	}
	_MaxCollectNum=MaxCollectNum;
	//�N���g���ĂȂ��t�H���g�X�v���C�g�ɂ��āA�폜����B
	for(tFontSpriteList2D::iterator it=FontSpriteList2D.begin();it!=FontSpriteList2D.end();){
		if(it->second->UnUsedFrame>600){//�t�H���g�́A�����̎�Ԃ��傫���̂�
			pPageManager->GetNowPage()->LogPrint("GCFontSprite2D:%+03d,%02d,%p" ,it->second->Priority,it->second->FontID,it->second );
			CFontSprite2DManager * pFontSpr2DMgr=it->second;//�o�b�N�A�b�v�p
			FontSpriteList2D.erase(it++);
			SAFE_RELEASE(pFontSpr2DMgr->pFontSpr);
			if((--_MaxCollectNum)==0)break;//������==0(0�̎��قږ�����J��Ԃ�)
		}else{
			++it;
		}		
	}
}
