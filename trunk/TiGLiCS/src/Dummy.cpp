#include "TiGLiCSAll.h"
#pragma warning(disable:4189)
using namespace TiGLiCS;

void TiGLiCS_DummyFunc(){
	CEngine *pEngine=CEngine::GetInstance();
	pEngine->Release();
}
