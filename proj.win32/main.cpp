#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"
#include "Settings.h"

USING_NS_CC;

// uncomment below line, open debug console
// #define USE_WIN32_CONSOLE

int APIENTRY _tWinMain(HINSTANCE hInstance,
						HINSTANCE hPrevInstance,
						LPTSTR    lpCmdLine,
						int       nCmdShow)
{
#ifdef ENABLE_LOGGING
	HANDLE hMemLogFile;

	int iStrLen = strlen(CSettings::MemLeaksLogFilePath) + 1; // Plus NULL;
	wchar_t *pFileName = new wchar_t[iStrLen];
	memset(pFileName, 0, iStrLen);
	MultiByteToWideChar(  CP_ACP, NULL, CSettings::MemLeaksLogFilePath, -1, pFileName, iStrLen );


	hMemLogFile = CreateFile(pFileName, GENERIC_WRITE, 
		FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 
		FILE_ATTRIBUTE_NORMAL, NULL);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, hMemLogFile);
	_CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_FILE );
	_CrtSetReportFile( _CRT_ERROR, hMemLogFile );
	_CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_FILE );
	_CrtSetReportFile( _CRT_ASSERT, hMemLogFile );

	_CrtMemState _ms; 
	_CrtMemCheckpoint(&_ms); // now forget about objects created before
#endif


    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

#ifdef USE_WIN32_CONSOLE
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
#endif

    // create the application instance
    AppDelegate app;
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
	eglView->setFrameSize(CSettings::BackgroundWidth, CSettings::BackgroundHeight);

    int ret = CCApplication::sharedApplication()->run();

#ifdef USE_WIN32_CONSOLE
    FreeConsole();
#endif

	//----
#ifdef ENABLE_LOGGING
	_CrtMemDumpAllObjectsSince(&_ms); // dump leaks
	CloseHandle(hMemLogFile);
#endif
	//----

	return ret;
}
