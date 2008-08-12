#include "Manager/SoundManager.h"
#include "Engine/Engine.h"
using namespace Selene;
using namespace TiGLiCS;
using namespace Manager;

CSoundManager * CSoundManager::Instance=new CSoundManager();

CSound::CSound(const char * FileName,Sint32 LayerCount){//コンストラクタ
	this->pSound=CEngine::GetInstance()->GetICore()->CreateSoundFromFile(FileName,LayerCount,false);
	this->NowLayer=0;
	this->LayerCount=LayerCount;
}
