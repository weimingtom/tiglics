#include "Objects/Object.h"
#include "Manager/PageManager.h"
#include "Manager/InputManager.h"
#include "Engine/Engine.h"
using namespace Selene;
using namespace TiGLiCS;
using namespace TiGLiCS::Object;
CObject::CObject(CPage *pPage,Sint32 ProcessPriority)
	:CFiber(),pPage(pPage),ProcessPriority(ProcessPriority),WaitNum(0),bDead(false)
{
}
bool CObject::_RunProcess(){
	return this->Run();
}
void CObject::Update(Sint32 FrameNum){//�w��t���[���ҋ@
	this->WaitNum=FrameNum-1;
	
	while(WaitNum>0){
		--WaitNum;
		Update();//�ҋ@
	}
	Update();//�Œ���͑ҋ@
	WaitNum=0;//���̒l�����������΍�
}
void CObject::Update(){
	OnUpdate();
	Suspend();//�Œ���͑ҋ@
}
void CObject::Die(){
	if(bDead==false){
		this->bDead=true;
		this->pPage->DeleteObject(this);
	}
}
Bool CObject::isScreenOut(Math::Point2DF &pos){
	Math::Point2DI ScreenSize(TiGLiCS::CEngine::GetInstance()->GetScreenSize());
	return !Collision::Point_Rect(Math::Vector2D(pos.x,pos.y),Math::Rect2DF(0,0,(float)ScreenSize.x,(float)ScreenSize.y));
}
Sint32 CObject::GetKey(eVirtualKeyCode KeyCode){
	return Manager::CInputManager::GetInstance()->GetKey(KeyCode);
}
void CObject::AddObject(IObject* pObject){
	pPage->AddObject(pObject);
}
Math::Point2DI CObject::GetScreenSize(){
	return TiGLiCS::CEngine::GetInstance()->GetScreenSize();
}
Sint32 CObject::GetFrameRate(){
	return TiGLiCS::CEngine::GetInstance()->GetFrameRate();
}
void CObject::End(){
	return TiGLiCS::CEngine::GetInstance()->End();
}