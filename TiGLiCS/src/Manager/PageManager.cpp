#include "Manager/PageManager.h"
#include "Engine/Engine.h"
#include <map>
using namespace std;
using namespace TiGLiCS;
using namespace Manager;

CPageManager * CPageManager::Instance=new CPageManager();

void CPage::addObject(){
	//���ۂ̃I�u�W�F�N�g�̓o�^
	if(AddQueue.size()!=0){
		for(std::vector<Object::IObject*>::iterator it=AddQueue.begin();it!=AddQueue.end();++it){	
			Object::CObjectContainer *pObjContainer = new Object::CObjectContainer(*it);
			(*it)->SetCObjectContainer(pObjContainer);
			PtrQueue.insert(pObjContainer);
			ProcessQueue.insert(pObjContainer);
			(*it)->Init();
		}
		AddQueue.clear();//�I������̂ō폜
	}
}

void CPage::delObject(){
	//���ۂ̃I�u�W�F�N�g�폜
	if(DeleteQueue.size()!=0){
		for(std::vector<Object::IObject*>::iterator it=DeleteQueue.begin();it!=DeleteQueue.end();++it){
			Object::PtrPriorityList::iterator itf = PtrQueue.find((*it)->GetCObjectContainer());
			if(itf!=PtrQueue.end()){
				(*itf)->pObj->Release();
				(*itf)->isDead=true;
				PtrQueue.erase(itf);
			}
		}
		DeleteQueue.clear();		
	}
}


void CPage::AddObject(Object::IObject *obj){
	//�I�u�W�F�N�g�̓o�^
	AddQueue.push_back(obj);	
}


void CPage::DeleteObject(Object::IObject *obj){
	//�I�u�W�F�N�g�̍폜
	obj->OnDie();
	DeleteQueue.push_back(obj);
}

void CPage::Exec(){
	//�������s		
	CEngine * pEngine=TiGLiCS::CEngine::GetInstance();
	CRenderManager* pRenderManager=Manager::CRenderManager::GetInstance();
	Renderer::IRender* pRender=pEngine->GetIRender();
	Math::Point2DI ScreenSize=pEngine->GetScreenSize();

#ifdef TIGLICS_DEBUG
	Manager::CPageManager * pPageManager = Manager::CPageManager::GetInstance();
	Sint32 FrameRate=pEngine->GetFrameRate();

	QueryPerformanceCounter(&t1);
	int Stack_Max=STACK_SIZE;
	int Stack_Min=0;
	int tmp_stack_size=0;
	Object::IObject * tpObj=NULL;
	DataArr[2]=GetAddQueueNum();
#endif
	//�����Ƃ��ŏ��Ɏ��s
	if(pFrameManager!=NULL){
		pFrameManager->BeforeProcess();
	}

	this->addObject();//�I�u�W�F�N�g�ǉ������B3D�΍�

	//BeforeRenderBegin
	for(Object::ProcessPriorityList::iterator it=ProcessQueue.begin();it!=ProcessQueue.end();){
		if((*it)->isDead){
			Object::CObjectContainer * pObjCtnr=(*it);
			Object::IObject * pObj=pObjCtnr->pObj;

			ProcessQueue.erase(it++);
			SAFE_DELETE(pObjCtnr);
			SAFE_DELETE(pObj);
		}else{
			(*it)->pObj->BeforeRenderBegin();
			++it;
		}
	}
	//�`��J�n
	pRenderManager->Begin();

	// ��ʂւ̕`����J�n
	//   Renderer::IRender�C���^�[�t�F�C�X�։�ʂւ̕`����J�n���邱�Ƃ�ʒm���܂��B
	//   ���̊֐����Ă΂Ȃ��Ɖ�ʂւ̕`�悪�������s���܂���B

	for(Object::ProcessPriorityList::iterator it=ProcessQueue.begin();it!=ProcessQueue.end();++it){	
		if(!(*it)->pObj->_RunProcess()){
			(*it)->pObj->Die();
		}else{
			(*it)->pObj->Draw();
		}
#ifdef TIGLICS_DEBUG
		tmp_stack_size=(*it)->pObj->GetRestProcessStack();
		if(Stack_Max>tmp_stack_size){
			Stack_Max=tmp_stack_size;
			tpObj=(*it)->pObj;
		}
		if(Stack_Min<tmp_stack_size){
			Stack_Min=tmp_stack_size;
		}
#endif
	}
	if(pFrameManager!=NULL){
		pFrameManager->AfterProcess();
	}
	pRenderManager->End();
#ifdef TIGLICS_DEBUG
	if(tpObj!=NULL && !tpObj->isDead() && Stack_Max<=0){
		DMessageBox("Stack Over Frow!\nClass:%s\nAddress:%p\nStackRest:%x",typeid(*tpObj).name(),tpObj,tpObj->GetRestProcessStack());
	}
	this->Log2Print(12,"PageNum     :%02d",pPageManager->GetPageNum());
	this->Log2Print(13,"NowPageID   :%02d",PageID);

	this->Log2Print(10,"MinStackRest:%08X",Stack_Max);
	this->Log2Print(9,"MaxStackRest:%08X",Stack_Min);
	this->Log2Print(8,"FreeStackNum:%08d",Object::CFiberMemoryManager::GetStackMemNum());

	DataArr[3]=GetDeleteQueueNum();
#endif

	this->delObject();//�I�u�W�F�N�g�������

	
#ifdef TIGLICS_DEBUG
	DataArr[0]=GetObjectNum();
	QueryPerformanceCounter(&t2);;
#endif	
	
	static Sint32 GCFrameCount=0;
	static char buf[256]={'\0'};
#ifdef TIGLICS_DEBUG
	static Sint32 FrameCount=0;
	const Sint32 SamplingRate=6;
	static double dtime[32]={0};//�f�o�b�O�p
#endif
	

#ifdef TIGLICS_DEBUG
	QueryPerformanceCounter(&t3);
#endif	

	//�`����s
	/////////////////////////////////////////////////////////////////////////////////////////////
	// ��ʃN���A
	/////////////////////////////////////////////////////////////////////////////////////////////
	// ����ʂ̃N���A
	pRender->Clear( BackColor);
	/////////////////////////////////////////////////////////////////////////////////////////////
	// ��ʂւ̃X�v���C�g�`��
	/////////////////////////////////////////////////////////////////////////////////////////////

	pRender->Begin();

	//�X�v���C�g�}�l�[�W���`��
	pRenderManager->Rendering();
#ifdef TIGLICS_DEBUG
	//���O������쐬
	Sint32 totalLineNum=0;
	for(Sint32 i=MAX_TASK_LOG_ROW-1;i>=0;--i){
		Sint32 linenum=1,loglen;
		Sint32 idx=(i+NowLogRow+1)%MAX_TASK_LOG_ROW;
		loglen=strlen(log_str[idx]);
		for(Sint32 j=0;j<loglen;++j){
			if(log_str[idx][j]=='\n')
				++linenum;
		}
		pRender->DebugPrint(Math::Point2DI(5,ScreenSize.y-5-12*(linenum+totalLineNum)),CColor(255,128,128,255),log_str[idx]);	
		totalLineNum+=linenum;
	}
	//���O������쐬2
	totalLineNum=0;
	for(Sint32 i=0;i<MAX_TASK_LOG_ROW;++i){
		Sint32 linenum=1,loglen;
		Sint32 idx=(0+i)%MAX_TASK_LOG_ROW;
		loglen=strlen(log2_str[idx]);
		for(Sint32 j=0;j<loglen;++j){
			if(log2_str[idx][j]=='\n')
				++linenum;
		}
		pRender->DebugPrint(Math::Point2DI(ScreenSize.x-170,ScreenSize.y-5-12*(linenum+totalLineNum)),CColor(255,128,128,255),log2_str[idx]);	
		totalLineNum+=linenum;
	}

	//�f�o�b�O���o��
	pRender->DebugPrint(Math::Point2DI(ScreenSize.x-270,0),CColor(255,128,128,255),buf);		
	pRender->DebugPrint(Math::Point2DI(0,0),Selene::CColor(255,255,255,255),
		"ObjectNum:%d\nAddQueue=%d DeleteQueue=%d",
	DataArr[0],DataArr[2],DataArr[3]);
#endif
	// ��ʂւ̕`�������
	//  Renderer::IRender�C���^�[�t�F�C�X�ɑ΂��āA
	//  ��ʂւ̕`�悪�����������Ƃ�ʒm���܂��B
	pRender->End();
	//�K�[�x�[�W�R���N�^
	GCFrameCount=(GCFrameCount+1)%10;
	if(GCFrameCount==0){
		pRenderManager->GabageCollection(1);
		Object::CFiberMemoryManager::GCStackMem(Sint32(Object::CFiberMemoryManager::GetStackMemNum()/16.0));
	}
#ifdef TIGLICS_DEBUG
	t7=t6;
	QueryPerformanceCounter(&t6); 
	QueryPerformanceCounter(&t4); 
	QueryPerformanceFrequency(&t5);
	dtime[0]=(double)(t2.QuadPart-t1.QuadPart)*1000/t5.QuadPart;
	dtime[1]=(double)(t4.QuadPart-t3.QuadPart)*1000/t5.QuadPart;
	dtime[2]=(double)(t4.QuadPart-t1.QuadPart)*1000/t5.QuadPart;
	dtime[3]=((1000.0/FrameRate)-dtime[2])/(1000.0/FrameRate)*100;
	dtime[12]=1.0/((((double)t6.QuadPart-t7.QuadPart)/t5.QuadPart)*FrameRate)*100.0;
	if(++FrameCount>SamplingRate){
		FrameCount=0;
		dtime[8]=dtime[4]/SamplingRate;
		dtime[9]=dtime[5]/SamplingRate;
		dtime[10]=dtime[6]/SamplingRate;
		dtime[11]=dtime[7]/SamplingRate;
		dtime[14]=dtime[13]/SamplingRate;
		dtime[4]=0;
		dtime[5]=0;
		dtime[6]=0;
		dtime[7]=0;
		dtime[13]=0;
	}else{		
		dtime[4]+=dtime[0];
		dtime[5]+=dtime[1];
		dtime[6]+=dtime[2];
		dtime[7]+=dtime[3];
		dtime[13]+=dtime[12];
	}

	sprintf(buf,"Process  :%06.3f msec Average:%06.3f\n"
				"Rendering:%06.3f msec Average:%06.3f\n"
				"CycleTime:%06.3f msec Average:%06.3f\n"
				"Remain   :%+06.2f msec Average:%+06.2f\n"
				"FrameRate:%03.0f percent Average:%06.2f\n",
				dtime[0],dtime[8],
				dtime[1],dtime[9],
				dtime[2],dtime[10],
				dtime[3],dtime[11],
				dtime[12],dtime[14]
	);
#endif
}

void CPage::Release(){


	//�S�I�u�W�F�N�g�ɍ폜����
	for(Object::ProcessPriorityList::iterator it=ProcessQueue.begin();it!=ProcessQueue.end();++it){
		(*it)->pObj->Die();
	}

	//�t���[���}�l�[�W���̉��
	SAFE_DELETE(pFrameManager);

	//�����蔻��}�l�[�W���̉��
	SAFE_DELETE(pCollisionManager2D);

	//�폜�L���[�̏���
	this->delObject();

	//�ǉ��L���[�̐���
	for(std::vector<Object::IObject*>::iterator it=AddQueue.begin();it!=AddQueue.end();++it){
		SAFE_DELETE(*it);
	}
}

void CPage::LogPrint(const char *src,...){
#ifdef TIGLICS_DEBUG
	va_list args;
	va_start(args,src);
	vsnprintf(log_str[(++NowLogRow)%MAX_TASK_LOG_ROW],(size_t)MAX_TASK_LOG_SIZE,src,args);
#endif
}
void CPage::Log2Print(Sint32 LineNum,const char *src,...){
#ifdef TIGLICS_DEBUG
	va_list args;
	va_start(args,src);
	vsnprintf(log2_str[LineNum],(size_t)MAX_TASK_LOG_SIZE,src,args);
#endif
}

void CPageManager::Exec(){
	CPage* pPage=GetNowPage();
	NextPageID=NowPageID;
	bNowPageDelete=false;
	if(pPage!=NULL){
		pPage->Exec();
	}else{
		TiGLiCS::CEngine::GetInstance()->End();
	}
	if(bNowPageDelete==true){
		this->DeletePage(NowPageID);
	}
	NowPageID=NextPageID;
}

CPage* CPageManager::GetNowPage(){
	return GetPage(NowPageID);
}

CPage* CPageManager::CreatePage(Sint32 PageID){
	if(PageList.size()!=0){//����Ȃ��
		tPageList::iterator it=PageList.find(PageID);
		if(it==PageList.end()){//����ID���������
			CPage * pPage=new CPage(PageID);
			PageList.insert(pair<Sint32,CPage*>(PageID,pPage));
			return pPage;
		}else{
			return NULL;
		}
	}else{
		NowPageID=PageID;
		CPage * pPage=new CPage(PageID);
		PageList.insert(pair<Sint32,CPage*>(PageID,pPage));
		return pPage;
	}
}

void CPageManager::Release(){
	for(tPageList::iterator it=Instance->PageList.begin();it!=Instance->PageList.end();){
		SAFE_DELETE(it->second);
		Instance->PageList.erase(it++);
	}
	delete Instance;
}

bool CPageManager::DeletePage(Sint32 PageID){
	//�y�[�W�̍폜�B���Ɏ��s����y�[�W�͍폜�ł��Ȃ�
	if(PageID!=NextPageID){
		tPageList::iterator it=PageList.find(PageID);
		if(it!=PageList.end()){
			SAFE_DELETE(it->second);
			PageList.erase(it++);
			return true;
		}else{
			return false;
		}
	}else{
		return false;
	}
}
bool CPageManager::SetNextPage(Sint32 PageID,bool isNowPageDelete){
	tPageList::iterator it=PageList.find(PageID);
	if(it!=PageList.end()){
		NextPageID=PageID;
		bNowPageDelete=isNowPageDelete;
		return true;
	}else{
		return false;
	}
}
CPage* CPageManager::GetPage(Sint32 PageID){
	tPageList::iterator it=PageList.find(PageID);
	if(it!=PageList.end()){
		return it->second;
	}else{
		return NULL;
	}
}