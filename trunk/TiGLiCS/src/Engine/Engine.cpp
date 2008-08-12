#include "TiGLiCSAll.h"
#include <cstring>
#include <typeinfo>

using namespace TiGLiCS;

float TiGLiCS::drand(void){
	//あまり精度は高くないが、ゲームに使うなら十分
	return (float)rand()/((float)RAND_MAX+1);
}
float TiGLiCS::drand(float min,float max){
	return (float)(min+(max-min)*rand()/((float)RAND_MAX+1));
}
CEngine * CEngine::Instance=new CEngine();
bool CEngine::Init(const char * Title,Selene::eFrameRate FrameRate,bool DrawDebugTitle,
				 Sint32 ScreenWidth,Sint32 ScreenHeight,bool isFullScreen,
				 const char * RootPath,const char * CurrentPath,bool isDebugMode){
	//----------------------------------------------------------------------------
	// システムの初期化
	//----------------------------------------------------------------------------
	// Seleneのシステムを初期化しています。
	// 起動時に必ず呼び出してください。
	System::Initialize();

	//----------------------------------------------------------------------------
	// コアの生成
	//----------------------------------------------------------------------------
	// システムからICoreインターフェイスを取得しています。
	// アプリケーションウィンドウに関するインターフェイスであり、
	// システム内に１つだけ存在します。
	pCore = System::CreateCore();
	
	//----------------------------------------------------------------------------
	// 初期化
	//----------------------------------------------------------------------------
	// ICoreインターフェイスの初期化を行います。
	// アプリケーションウィンドウに関しての各種初期化が行われます。
	if (!pCore->Initialize(Title, FrameRate ) )
		goto EXIT;
	pCore->SetBenchMode(isDebugMode);
	//-----------------------------------------------------------------
	// タイトルバーに情報を表示
	//-----------------------------------------------------------------
	pCore->EnableDrawTitleInformation( DrawDebugTitle );

	//-----------------------------------------------------------------
	// ウィンドウ作成
	//-----------------------------------------------------------------
	// ICoreインターフェイス内の情報に従ってアプリケーション
	// ウィンドウを生成します。
	// IGraphicCardからの情報を元に画面解像度などを変更する場合は、
	// ICore::Start()を呼び出す前に行ってください。
	pCore->Start( ScreenWidth, ScreenHeight, true );
	
	//-----------------------------------------------------------------
	// グラフィックカードを取得
	//-----------------------------------------------------------------
	// グラフィックカードに関しての初期化を行います。
	// IGraphicCardインターフェイスからは接続された
	// グラフィックカードの能力を取得する事が可能です。
	// IGraphicCardインターフェイスは1つのICoreインターフェイスに対して1つしか存在しません。
	pGraphicCard = pCore->CreateGraphicCard( GRAPHIC_CARD_DEFAULT_NO );
	if ( pGraphicCard == NULL ) goto EXIT;

	//-----------------------------------------------------------------
	// ウィンドウ作成
	//-----------------------------------------------------------------
	// ICoreインターフェイス内の情報に従ってアプリケーション
	// ウィンドウを生成します。
	// IGraphicCardからの情報を元に画面解像度などを変更する場合は、
	// ICore::Start()を呼び出す前に行ってください。
	pCore->Start( ScreenWidth, ScreenHeight, !isFullScreen );

	//-----------------------------------------------------------------
	// レンダラーを取得
	//-----------------------------------------------------------------
	// 作成したグラフィックカードから画面描画用のレンダラーを取得します。
	// Renderer::IRenderインターフェイスは1つのIGraphicCardインターフェイスに対して1つしか存在しません。
	pRender = pGraphicCard->CreateRender();
	if ( pRender == NULL ) goto EXIT;
	

	//-----------------------------------------------------------------
	// マウス取得
	//-----------------------------------------------------------------
	pMouse = pCore->GetMouse();
	if ( pMouse == NULL ) goto EXIT;
	//-----------------------------------------------------------------
	// キーボードの取得
	//-----------------------------------------------------------------
	pKeyboard = pCore->GetKeyboard();

	//-----------------------------------------------------------------
	// テクスチャの読み込み
	//-----------------------------------------------------------------
	// テクスチャ生成用のオプション設定
	//  0,0,0 の色をカラーキーに設定
	Conf.SetColorKey( CColor(0,0,0,255) );
	Conf.SetFormat( FORMAT_TEXTURE_32BIT );
	Conf.SetMipmapEnable( true );	

	//-----------------------------------------------------------------
	// ファイル登録
	//-----------------------------------------------------------------
	// ファイルマネージャーを生成
	pFileMgr = pCore->CreateFileManager();
	// コアに設定
	pCore->SetFileManager( pFileMgr );
	// ルートディレクトリを設定
	pFileMgr->SetRootPath( 0, RootPath );
	// ルートディレクトリに対して読み込むカレントディレクトリ設定
	pFileMgr->SetCurrentPath( CurrentPath );
		
	//フレームレートと画面サイズの初期化
	this->ScreenSize.x=ScreenWidth;
	this->ScreenSize.y=ScreenHeight;
	switch(FrameRate){
		case FRAME_RATE_15:this->FrameRate=15;break;
		case FRAME_RATE_20:this->FrameRate=20;break;
		case FRAME_RATE_30:this->FrameRate=30;break;
		case FRAME_RATE_60:this->FrameRate=60;break;
		default:this->FrameRate=60;//デフォルトは60にしておく
	}


	//描画マネージャの初期化。
	Manager::CRenderManager *pRenderManager=Manager::CRenderManager::GetInstance();
	pRenderManager->SetBackgroundColor(CColor(255,255,255,255));
	//描画タイプの設定
	pRender->SetDrawType(DRAW_TYPE_BLEND  );


	return true;
EXIT:
	DMessageBox("TiGLiCS初期化エラー");
	return false;
}

void CEngine::Exec(){
	Selene::Peripheral::IKeyboard * pKeyboard=this->GetIKeyboard();
	Sint32 * KeyState=Manager::CInputManager::GetInstance()->_GetKeyStateArr();
	//キーの入力状況取得
	for(Sint32 i=0;i<=0xFF;++i){
		if(pKeyboard->GetKeyData((eVirtualKeyCode)i)){
			++KeyState[i];
		}else{
			KeyState[i]=0;
		}
	}
	//この後にページの動作
	Manager::CPageManager::GetInstance()->Exec();
}




void CEngine::_Release(void){//解放処理
	//ページマネージャの解放
	Manager::CPageManager::Release();
	//ファイバのスタック解放
	Object::CFiberMemoryManager::ClearStackMem();
	//描画マネージャの解放
	Manager::CRenderManager::Release();
	//フォントマネージャの解放
	Manager::CFontManager::Release();
	//テクスチャマネージャの解放
	Manager::CTextureManager::Release();
	//サウンドマネージャの解放
	Manager::CSoundManager::Release();
	//インプットマネージャの海保う
	Manager::CInputManager::Release();
	// ファイルマネージャー解放
	SAFE_RELEASE( pFileMgr );

	// レンダラーの解放
	SAFE_RELEASE( pRender );

	// グラフィックカードの解放
	SAFE_RELEASE( pGraphicCard );
	// コアの解放
	SAFE_RELEASE( pCore );

	//--------------------------------------------------------
	// システムの解放
	//--------------------------------------------------------
	// アプリケーションの終了時に必ず呼び出して下さい。
	// またこの関数を呼び出す前に取得した全ての
	// インターフェイスを解放してください。
	System::Finalize();
}


void TiGLiCS::DMessageBox(const char *src,...){
	char buff[256];
	va_list args;
	va_start(args,src);
	vsnprintf(buff,(size_t)256,src,args);
	MessageBox(NULL,buff,"Debug",MB_OK);
}
