#include "Objects/Sprite2D.h"
#include "Manager/Collision.h"
#include "Engine/Engine.h"
#include "Manager/PageManager.h"
#include <cstdio>
using namespace Selene;
using namespace TiGLiCS;
using namespace Object;
CSprite2D::CSprite2D(CPage *pPage,
			  Math::Point2DF &pos,//スプライト座標
			  Sint32 Angle,//回転角
			  Sint32 ProcessPriority//処理優先度
			  ):CObject(pPage,ProcessPriority)
			  ,pos(pos),Angle(Angle),bCollisionDetect2D(false)
{
	this->pRenderManager=TiGLiCS::Manager::CRenderManager::GetInstance();
}
CSprite2D::~CSprite2D(){	
	//あたり判定リストの消去	
	for(Collision2D::CollisionData2DList::iterator it=CollisionList2D.begin();it!=CollisionList2D.end();++it){
		delete (*it);
	}
}
int CSprite2D::AddCollisionData(Collision2D::CCollisionData2D *pCollisionData2D){
	if(bCollisionDetect2D==false){//当たり判定が無効なときに追加可能
		CollisionList2D.push_back(pCollisionData2D);
		return (int)CollisionList2D.size();
	}else{
		return -1;
	}
}

int CSprite2D::AddCollisionData(Math::Vector2D *vecArray,Sint32 vecNum,bool isAbsPos){
	if(bCollisionDetect2D==false){//任意領域の場合の時		
		Math::Vector2D* pts=new Math::Vector2D[vecNum];
		for(int i=0;i<vecNum;++i){
			pts[i]=vecArray[i];
		}
		CollisionList2D.push_back((Collision2D::CCollisionData2D*)new Collision2D::CPolygon2DCollisionData(this,pts,vecNum,isAbsPos));
		return (int)CollisionList2D.size();
	}else{
		return -1;
	}
}
int CSprite2D::AddCollisionData(Math::Rect2DF &Rect,bool isAbsPos){
	if(bCollisionDetect2D==false){//四角形の時
		Float x0 = Rect.x;
		Float y0 = Rect.y;
		Float x1 = Rect.x + Rect.w;
		Float y1 = Rect.y + Rect.h;
		Math::Vector2D* pts=new Math::Vector2D[5];
		pts[0]=Math::Vector2D(x0,y0);
		pts[1]=Math::Vector2D(x1,y0);
		pts[2]=Math::Vector2D(x1,y1);
		pts[3]=Math::Vector2D(x0,y1);
		pts[4]=Math::Vector2D(x0,y0);

		CollisionList2D.push_back((Collision2D::CCollisionData2D*)new Collision2D::CPolygon2DCollisionData(this,pts,5,isAbsPos));
		return (int)CollisionList2D.size();
	}else{
		return -1;
	}
}
int CSprite2D::AddCollisionData(Collision::CCircle &cpos,bool isAbsPos){
	if(bCollisionDetect2D==false){//円の時
		CollisionList2D.push_back((Collision2D::CCollisionData2D*)new Collision2D::CCircle2DCollisionData(this,cpos,isAbsPos));
		return (int)CollisionList2D.size();
	}else{
		return -1;
	}
}
int CSprite2D::AddCollisionData(Collision::CLine2D &cpos,bool isAbsPos){
	if(bCollisionDetect2D==false){//線の時
		CollisionList2D.push_back((Collision2D::CCollisionData2D*)new Collision2D::CLine2DCollisionData(this,cpos,isAbsPos));
		return (int)CollisionList2D.size();
	}else{
		return -1;
	}
}
int CSprite2D::AddCollisionData(Math::Vector2D &cpos,bool isAbsPos){
	if(bCollisionDetect2D==false){//点の時
		CollisionList2D.push_back((Collision2D::CCollisionData2D*)new Collision2D::CPoint2DCollisionData(this,cpos,isAbsPos));
		return (int)CollisionList2D.size();
	}else{
		return -1;
	}
}
void CSprite2D::DrawCollisionData(Sint32 Priority){
	Math::Point2DF pos1,pos2;
	Math::Vector2D vpos1,vpos2;
	for(Collision2D::CollisionData2DList::iterator it=CollisionList2D.begin();it!=CollisionList2D.end();++it){
		switch((*it)->GetCollisionType()){
		case Collision2D::coPoint2D:
			vpos1=((Collision2D::CPoint2DCollisionData*)*it)->retpos;
			pRenderManager->DrawPoint(Math::Point2DF(vpos1.x,vpos1.y),CColor(0,0,0,128),Priority);
			break;
		case Collision2D::coLine2D:
			vpos1=((Collision2D::CLine2DCollisionData*)*it)->retpos.vStart;
			vpos2=((Collision2D::CLine2DCollisionData*)*it)->retpos.vEnd;
			pRenderManager->DrawLine(Math::Point2DF(vpos1.x,vpos1.y),Math::Point2DF(vpos2.x,vpos2.y),CColor(0,0,0,128),Priority);
			break;
		case Collision2D::coCircle2D:
			vpos1=((Collision2D::CCircle2DCollisionData*)*it)->retpos.vCenter;
			pRenderManager->DrawCircle(Math::Point2DF(vpos1.x,vpos1.y),((Collision2D::CCircle2DCollisionData*)*it)->retpos.fRadius,
				CColor(0,0,0,128),Priority);
			break;
		case Collision2D::coPolygon2D:
			pRenderManager->DrawPolygon(((Collision2D::CPolygon2DCollisionData*)*it)->retpos.pPts,
				((Collision2D::CPolygon2DCollisionData*)*it)->retpos.Count,CColor(0,0,0,128),Priority);
			break;
		default:break;
		}
	}
}
void CSprite2D::EnableCollisionDetect(){
	if(bCollisionDetect2D==false){
		pPage->GetCCollisionManager2D()->RegisterCollisionObject(this);
		bCollisionDetect2D=true;
		UpdateCollisionData();
	}
}
void CSprite2D::UpdateCollisionData(){	
	//あたり判定リストの消去	
	for(Collision2D::CollisionData2DList::iterator it=CollisionList2D.begin();it!=CollisionList2D.end();++it){
		(*it)->UpdatePos();
	}
}
void CSprite2D::DisableCollisionDetect(){
	if(bCollisionDetect2D==true){
		pPage->GetCCollisionManager2D()->UnRegisterCollisionObject(this);
		bCollisionDetect2D=false;
	}
}
int CSprite2D::CollisionCheck2D(Collision2D::CCollisionResult2D * &result){
	if(bCollisionDetect2D==true){
		return pPage->GetCCollisionManager2D()->CollisionCheck(this,result);
	}else{
		return 0;
	}
}
void CSprite2D::Update(){
	UpdateCollisionData();
	CObject::Update();
}
void CSprite2D::Update(Sint32 FrameCount){
	UpdateCollisionData();
	CObject::Update(FrameCount);
}