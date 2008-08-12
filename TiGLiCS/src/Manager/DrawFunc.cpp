#include "Manager/RenderManager.h"
#include "Engine/Engine.h"

using namespace TiGLiCS;
using namespace TiGLiCS::Manager;
//スプライト系----------------------------------------------------------------------------
void CRenderManager::DrawSprite(Math::Point2DF &Pos, Sint32 TextureID, Sint32 TexRectID ,Sint32 Priority){
	//スプライト描画。回転なし
	CTextureManager * pTextureManager = CTextureManager::GetInstance();
	CSprite2DManager * pSpr2DMgr=GetCSprite2DManager(TextureID,Priority);
	if(pSpr2DMgr==NULL)return;
	Math::Rect2DF TexArea(pTextureManager->GetCTexture(TextureID)->GetTextureArea(TexRectID));
	Math::Rect2DF DrawArea(Pos.x-TexArea.w/2,Pos.y-TexArea.h/2,TexArea.w,TexArea.h);
	pSpr2DMgr->pSpr->DrawSquare(DrawArea,TexArea,DefaultBackColor);
}
void CRenderManager::DrawSprite(Math::Point2DF &Pos, Sint32 TextureID, Sint32 TexRectID ,Sint32 Priority, Sint32 Angle){
	//スプライト描画。回転あり
	CTextureManager * pTextureManager = CTextureManager::GetInstance();
	CSprite2DManager * pSpr2DMgr=GetCSprite2DManager(TextureID,Priority);
	if(pSpr2DMgr==NULL)return;
	Math::Rect2DF TexArea(pTextureManager->GetCTexture(TextureID)->GetTextureArea(TexRectID));
	Math::Rect2DF DrawArea(Pos.x-TexArea.w/2,Pos.y-TexArea.h/2,TexArea.w,TexArea.h);
	pSpr2DMgr->pSpr->DrawSquareRotate(DrawArea,TexArea,DefaultBackColor,Angle);
}
//テキスト系----------------------------------------------------------------------------
void CRenderManager::DrawString(Math::Point2DF &DrawPos,CColor &col,Sint32 FontID,Sint32 Priority,const char *src,...){
	//文字描画
	va_list args;
	va_start(args,src);
	vsnprintf(str_buf,(size_t)1024,src,args);
	CFontSprite2DManager * pFontSpr2DMgr=GetCFontSprite2DManager(FontID,(Sint32)strlen(str_buf),Priority);
	if(pFontSpr2DMgr==NULL)return;
	pFontSpr2DMgr->pFontSpr->DrawString(str_buf,DrawPos,col);
}

//プリミティブ系----------------------------------------------------------------------------

void CRenderManager::FillTriangle(Math::Point2DF &Pos1,Math::Point2DF &Pos2,Math::Point2DF &Pos3,CColor& col,Sint32 Priority){
	//三角形描画
	Renderer::SPrimitiveVertex2D ptPrimitive[1];
	CPrimitive2DManager * pPrimitive2DMgr = GetCPrimitive2DManager(1,Priority);
	ptPrimitive[0].v1.Pos=Math::Vector4D(Pos1.x,Pos1.y);
	ptPrimitive[0].v1.Col=col;
	ptPrimitive[0].v2.Pos=Math::Vector4D(Pos2.x,Pos2.y);
	ptPrimitive[0].v2.Col=col;
	ptPrimitive[0].v3.Pos=Math::Vector4D(Pos3.x,Pos3.y);
	ptPrimitive[0].v3.Col=col;
	pPrimitive2DMgr->pPrimitive->Push(ptPrimitive,1);
}
void CRenderManager::FillRect(Math::Rect2DF &Pos,CColor &col,Sint32 Priority){
	//四角形描画
	Renderer::SPrimitiveVertex2D ptPrimitive[2];
	CPrimitive2DManager * pPrimitive2DMgr = GetCPrimitive2DManager(2,Priority);
	ptPrimitive[0].v1.Pos=Math::Vector4D(Pos.x,Pos.y);
	ptPrimitive[0].v1.Col=col;
	ptPrimitive[0].v2.Pos=Math::Vector4D(Pos.x+Pos.w,Pos.y);
	ptPrimitive[0].v2.Col=col;
	ptPrimitive[0].v3.Pos=Math::Vector4D(Pos.x,Pos.y+Pos.h);
	ptPrimitive[0].v3.Col=col;

	ptPrimitive[1].v1=ptPrimitive[0].v3;
	ptPrimitive[1].v2=ptPrimitive[0].v2;
	ptPrimitive[1].v3.Pos=Math::Vector4D(Pos.x+Pos.w,Pos.y+Pos.h);
	ptPrimitive[1].v3.Col=col;
	pPrimitive2DMgr->pPrimitive->Push(ptPrimitive,2);
}
void CRenderManager::FillRect(Math::Rect2DF &Pos,CColor &col,Sint32 Priority,Sint32 Angle){
	//四角形描画
	float px,py;
	float cx=Pos.x+Pos.w/2,cy=Pos.y+Pos.h/2;
	
	Renderer::SPrimitiveVertex2D ptPrimitive[2];
	CPrimitive2DManager * pPrimitive2DMgr = GetCPrimitive2DManager(2,Priority);
	px=-Math::Sin(Angle)*(Pos.x-cx)+Math::Cos(Angle)*(Pos.y-cy);
	py= Math::Cos(Angle)*(Pos.x-cx)+Math::Sin(Angle)*(Pos.y-cy);
	ptPrimitive[0].v1.Pos=Math::Vector4D(px+cx,py+cy);
	ptPrimitive[0].v1.Col=col;
	px=-Math::Sin(Angle)*(Pos.x+Pos.w-cx)+Math::Cos(Angle)*(Pos.y+Pos.h-cy);
	py= Math::Cos(Angle)*(Pos.x+Pos.w-cx)+Math::Sin(Angle)*(Pos.y+Pos.h-cy);
	ptPrimitive[0].v2.Pos=Math::Vector4D(px+cx,py+cy);
	ptPrimitive[0].v2.Col=col;
	px=-Math::Sin(Angle)*(Pos.x+Pos.w-cx)+Math::Cos(Angle)*(Pos.y-cy);
	py= Math::Cos(Angle)*(Pos.x+Pos.w-cx)+Math::Sin(Angle)*(Pos.y-cy);
	ptPrimitive[0].v3.Pos=Math::Vector4D(px+cx,py+cy);
	ptPrimitive[0].v3.Col=col;
	
	ptPrimitive[1].v1=ptPrimitive[0].v1;
	px=-Math::Sin(Angle)*(Pos.x-cx)+Math::Cos(Angle)*(Pos.y+Pos.h-cy);
	py= Math::Cos(Angle)*(Pos.x-cx)+Math::Sin(Angle)*(Pos.y+Pos.h-cy);
	ptPrimitive[1].v2.Pos=Math::Vector4D(px+cx,py+cy);
	ptPrimitive[1].v2.Col=col;
	ptPrimitive[1].v3=ptPrimitive[0].v2;
	pPrimitive2DMgr->pPrimitive->Push(ptPrimitive,2);
}

void CRenderManager::FillCircle(Math::Point2DF &Pos,float Radius,CColor& col,Sint32 Priority){
	//円描画
	Uint32 Accuracy;//精度。サイズに合わせて調整
	if(Radius<8){
		Accuracy=8;
	}else if(Radius<64){
		Accuracy=16;
	}else if(Radius<512){
		Accuracy=32;
	}else{
		Accuracy=64;
	}
	Renderer::SPrimitiveVertex2D ptPrimitive;
	CPrimitive2DManager * pPrimitive2DMgr = GetCPrimitive2DManager(Accuracy-1,Priority);	

	ptPrimitive.v1.Pos=Math::Vector4D(Pos.x+Radius,Pos.y);
	ptPrimitive.v1.Col=col;
	ptPrimitive.v2.Pos=Math::Vector4D(Pos.x+Radius*Math::Cos(-(Sint32)(DEG_TO_ANGLE(360)/(float)Accuracy)),
									  Pos.y+Radius*Math::Sin(-(Sint32)(DEG_TO_ANGLE(360)/(float)Accuracy)));
	ptPrimitive.v2.Col=col;
	for(Uint32 i=1;i<Accuracy;++i){
		ptPrimitive.v3=ptPrimitive.v2;
		ptPrimitive.v2.Pos=Math::Vector4D(Pos.x+Radius*Math::Cos(-(Sint32)(DEG_TO_ANGLE(360)/(float)Accuracy*i)),
										  Pos.y+Radius*Math::Sin(-(Sint32)(DEG_TO_ANGLE(360)/(float)Accuracy*i)));

		pPrimitive2DMgr->pPrimitive->Push(&ptPrimitive,1);

	}
}

void CRenderManager::FillPolygon(Math::Vector2D *posArray,Sint32 posNum,CColor &col,Sint32 Priority){
	//ポリゴン描画
	Renderer::SPrimitiveVertex2D ptPrimitive[1];
	CPrimitive2DManager * pPrimitive2DMgr = GetCPrimitive2DManager(posNum-2,Priority);
	for(int i=0;i<posNum-2;++i){
		int idx1=(i*2) % posNum;
		int idx2=(idx1+1) % posNum;
		int idx3=(idx2+1) % posNum;
		ptPrimitive[0].v1.Pos=Math::Vector4D(posArray[idx1].x,posArray[idx1].y);
		ptPrimitive[0].v1.Col=col;
		ptPrimitive[0].v2.Pos=Math::Vector4D(posArray[idx2].x,posArray[idx2].y);
		ptPrimitive[0].v2.Col=col;
		ptPrimitive[0].v3.Pos=Math::Vector4D(posArray[idx3].x,posArray[idx3].y);
		ptPrimitive[0].v3.Col=col;
		pPrimitive2DMgr->pPrimitive->Push(ptPrimitive,1);
	}
}
//ライン系----------------------------------------------------------------------------

void CRenderManager::DrawRect(Math::Rect2DF &Pos,CColor &col,Sint32 Priority){
	//四角形描画
	Renderer::SLineVertex2D ptLine[4];
	CLine2DManager * pLine2DMgr = GetCLine2DManager(4,Priority);
	ptLine[0].v1.Pos=Math::Vector4D(Pos.x,Pos.y);
	ptLine[0].v1.Col=col;
	ptLine[0].v2.Pos=Math::Vector4D(Pos.x+Pos.w,Pos.y);
	ptLine[0].v2.Col=col;
	ptLine[1].v1=ptLine[0].v2;
	ptLine[1].v2.Pos=Math::Vector4D(Pos.x+Pos.w,Pos.y+Pos.h);
	ptLine[1].v2.Col=col;
	ptLine[2].v1=ptLine[1].v2;
	ptLine[2].v2.Pos=Math::Vector4D(Pos.x,Pos.y+Pos.h);
	ptLine[2].v2.Col=col;
	ptLine[3].v1=ptLine[2].v2;
	ptLine[3].v2=ptLine[0].v1;
	ptLine[3].v2.Pos.y-=1;//補正。これがないと左上が1ドット欠ける
	pLine2DMgr->pLine->Push(ptLine,4);	
}
void CRenderManager::DrawRect(Math::Rect2DF &Pos,CColor &col,Sint32 Priority,Sint32 Angle){
	//四角形描画(角度付き)
	float px,py;
	float cx=Pos.x+Pos.w/2,cy=Pos.y+Pos.h/2;
	Renderer::SLineVertex2D ptLine[4];
	CLine2DManager * pLine2DMgr = GetCLine2DManager(4,Priority);

	px=-Math::Sin(Angle)*(Pos.x-cx)+Math::Cos(Angle)*(Pos.y-cy);
	py= Math::Cos(Angle)*(Pos.x-cx)+Math::Sin(Angle)*(Pos.y-cy);
	ptLine[0].v1.Pos=Math::Vector4D(px+cx,py+cy);
	ptLine[0].v1.Col=col;
	px=-Math::Sin(Angle)*(Pos.x+Pos.w-cx)+Math::Cos(Angle)*(Pos.y-cy);
	py= Math::Cos(Angle)*(Pos.x+Pos.w-cx)+Math::Sin(Angle)*(Pos.y-cy);
	ptLine[0].v2.Pos=Math::Vector4D(px+cx,py+cy);
	ptLine[0].v2.Col=col;
	ptLine[1].v1=ptLine[0].v2;
	px=-Math::Sin(Angle)*(Pos.x+Pos.w-cx)+Math::Cos(Angle)*(Pos.y+Pos.h-cy);
	py= Math::Cos(Angle)*(Pos.x+Pos.w-cx)+Math::Sin(Angle)*(Pos.y+Pos.h-cy);
	ptLine[1].v2.Pos=Math::Vector4D(px+cx,py+cy);
	ptLine[1].v2.Col=col;
	ptLine[2].v1=ptLine[1].v2;
	px=-Math::Sin(Angle)*(Pos.x-cx)+Math::Cos(Angle)*(Pos.y+Pos.h-cy);
	py= Math::Cos(Angle)*(Pos.x-cx)+Math::Sin(Angle)*(Pos.y+Pos.h-cy);
	ptLine[2].v2.Pos=Math::Vector4D(px+cx,py+cy);
	ptLine[2].v2.Col=col;
	ptLine[3].v1=ptLine[2].v2;
	ptLine[3].v2=ptLine[0].v1;
	//ptLine[3].v2.Pos.y-=1;//補正。これがないと左上が1ドット欠ける
	pLine2DMgr->pLine->Push(ptLine,4);	
}

void CRenderManager::DrawTriangle(Math::Point2DF &Pos1,Math::Point2DF &Pos2,Math::Point2DF &Pos3,CColor &col,Sint32 Priority){
	//三角形描画
	Renderer::SLineVertex2D ptLine[3];
	CLine2DManager * pLine2DMgr = GetCLine2DManager(3,Priority);
	ptLine[0].v1.Pos=Math::Vector4D(Pos1.x,Pos1.y);
	ptLine[0].v1.Col=col;
	ptLine[0].v2.Pos=Math::Vector4D(Pos2.x,Pos2.y);
	ptLine[0].v2.Col=col;
	ptLine[1].v1=ptLine[0].v2;
	ptLine[1].v2.Pos=Math::Vector4D(Pos3.x,Pos3.y);
	ptLine[1].v2.Col=col;
	ptLine[2].v1=ptLine[1].v2;
	ptLine[2].v2=ptLine[0].v1;
	//ptLine[2].v2.Pos.y-=1;//補正。これがないと左上が1ドット欠ける
	pLine2DMgr->pLine->Push(ptLine,3);
	
}
void CRenderManager::DrawLine(Math::Point2DF &Pos1,Math::Point2DF &Pos2,CColor &col,Sint32 Priority){
	//線描画
	Renderer::SLineVertex2D ptLine[1];
	CLine2DManager * pLine2DMgr = GetCLine2DManager(1,Priority);
	ptLine[0].v1.Pos=Math::Vector4D(Pos1.x,Pos1.y);
	ptLine[0].v1.Col=col;
	ptLine[0].v2.Pos=Math::Vector4D(Pos2.x,Pos2.y);
	ptLine[0].v2.Col=col;
	pLine2DMgr->pLine->Push(ptLine,1);
}
void CRenderManager::DrawPolygon(Math::Vector2D *posArray,Sint32 posNum,CColor &col,Sint32 Priority){
	//ポリゴン描画
	Renderer::SLineVertex2D ptLine[1];
	CLine2DManager * pLine2DMgr = GetCLine2DManager(posNum,Priority);
	ptLine[0].v1.Col=col;
	ptLine[0].v2.Col=col;
	for(Sint32 i=0;i<posNum-1;++i){
		ptLine[0].v1.Pos=Math::Vector4D(posArray[i]);
		ptLine[0].v2.Pos=Math::Vector4D(posArray[i+1]);
		pLine2DMgr->pLine->Push(ptLine,1);
	}
}

void CRenderManager::DrawCircle(Math::Point2DF &Pos,float Radius,CColor& col,Sint32 Priority){
	//円描画
	Uint32 Accuracy;//精度。サイズに合わせて調整
	if(Radius<8){
		Accuracy=8;
	}else if(Radius<64){
		Accuracy=16;
	}else if(Radius<512){
		Accuracy=32;
	}else{
		Accuracy=64;
	}
	Renderer::SLineVertex2D ptLine;
	CLine2DManager * pLine2DMgr = GetCLine2DManager(Accuracy,Priority);

	ptLine.v1.Pos=Math::Vector4D(Pos.x+Radius,Pos.y);
	ptLine.v1.Col=col;
	for(Uint32 i=1;i<=Accuracy;++i){
		ptLine.v2=ptLine.v1;
		ptLine.v1.Pos=Math::Vector4D(Pos.x+Radius*Math::Cos((Sint32)(DEG_TO_ANGLE(360)/(float)Accuracy*i)),
										  Pos.y+Radius*Math::Sin((Sint32)(DEG_TO_ANGLE(360)/(float)Accuracy*i)));

		pLine2DMgr->pLine->Push(&ptLine,1);

	}
}

//ポイント系----------------------------------------------------------------------------

void CRenderManager::DrawPoint(Math::Point2DF &Pos,CColor &col,Sint32 Priority){
	//点描画
	CPoint2DManager * pPoint2DMgr = GetCPoint2DManager(Priority);
	Renderer::SVertex2D ptPoint;
	ptPoint.Pos=Math::Vector4D(Pos.x,Pos.y);
	ptPoint.Col=col;
	pPoint2DMgr->pPoint->Push(&ptPoint,1);
}
//ダミー----------------------------------------------------------------------------

void CRenderManager::DrawDummy(Sint32 Priority){//スプライト描画
	//ダミー関数リクエスト
}