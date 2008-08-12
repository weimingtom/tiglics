#include "Manager/TextureManager.h"
#include "Engine/Engine.h"
using namespace TiGLiCS;
using namespace Manager;

CTextureManager * CTextureManager::Instance=new CTextureManager();

CTexture::CTexture(const char * FileName){//�R���X�g���N�^						
	CEngine *pEngine=CEngine::GetInstance();
	pEngine->GetIRender()->SetTextureConfig( (*pEngine->GetCTextureConfig()) );
	Texture=pEngine->GetIRender()->CreateTextureFromFile(FileName );		
}