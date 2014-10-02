//--------------------------------------------------------------------------//
// iq / rgba  .  tiny codes  .  2008                                        //
// Lev Panov . lev.panov@gmail.com  2014                                    //
//--------------------------------------------------------------------------//

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <GL/gl.h>
#include <math.h>
#include "glext.h"
//#include "main.h"

using namespace std;
#pragma warning(disable:4244)

#define XRES    800
#define YRES    600

//--------------------------------------------------------------------------//

#include "shader.h"

const static PIXELFORMATDESCRIPTOR pfd = {0,0,PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


const static char *funcNames[] = { "glCreateProgram",
                                   "glCreateShader",
                                   "glShaderSource",
                                   "glCompileShader",
                                   "glAttachShader",
                                   "glLinkProgram",
                                   "glUseProgram",
								   "glGetShaderiv",
								   "glGetShaderInfoLog",
								   "glUniform1f",
								   "glGetUniformLocation" };

static void *funcPtrs[11];

#define oglCreateProgram	((PFNGLCREATEPROGRAMPROC)funcPtrs[0])
#define oglCreateShader		((PFNGLCREATESHADERPROC)funcPtrs[1])
#define oglShaderSource		((PFNGLSHADERSOURCEPROC)funcPtrs[2])
#define oglCompileShader	((PFNGLCOMPILESHADERPROC)funcPtrs[3])
#define oglAttachShader		((PFNGLATTACHSHADERPROC)funcPtrs[4])
#define oglLinkProgram		((PFNGLLINKPROGRAMPROC)funcPtrs[5])
#define oglUseProgram		((PFNGLUSEPROGRAMPROC)funcPtrs[6])
#define oglGetShaderiv		((PFNGLGETSHADERIVPROC)funcPtrs[7])
#define oglGetShaderInfoLog ((PFNGLGETSHADERINFOLOGPROC)funcPtrs[8])
#define oglUniform1f		((PFNGLUNIFORM1FPROC)funcPtrs[9]) 
#define oglGetUniformLocation	((PFNGLGETUNIFORMLOCATIONPROC)funcPtrs[10]) 


#define GL_COMPILE_STATUS                 0x8B81

static RECT rec = { 0, 0, XRES, YRES };

//--------------------------------------------------------------------------//
static LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	// salvapantallas
	if( uMsg==WM_SYSCOMMAND && (wParam==SC_SCREENSAVE || wParam==SC_MONITORPOWER) )
		return( 0 );

	// boton x o pulsacion de escape
	if( uMsg==WM_CLOSE || uMsg==WM_DESTROY || (uMsg==WM_KEYDOWN && wParam==VK_ESCAPE) )
		{
		PostQuitMessage(0);
        return( 0 );
		}

    if( uMsg==WM_CHAR )
        {
        if( wParam==VK_ESCAPE )
            {
            PostQuitMessage(0);
            return( 0 );
            }
        }

    return( DefWindowProc(hWnd,uMsg,wParam,lParam) );
}

string readFile2(const string &fileName)
{
	ifstream ifs(fileName.c_str(), ios::in | ios::binary | ios::ate);

	ifstream::pos_type fileSize = ifs.tellg();
	ifs.seekg(0, ios::beg);

	vector<char> bytes(fileSize);
	ifs.read(&bytes[0], fileSize);

	return string(&bytes[0], fileSize);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{ 
    WNDCLASS wc;

    // create window
    ZeroMemory( &wc, sizeof(WNDCLASS) );
    wc.style         = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hPrevInstance;
    wc.lpszClassName = "wnd";

    if( !RegisterClass(&wc) )
        return( 0 );

    const int dws = WS_VISIBLE | WS_CAPTION | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_SYSMENU;
    AdjustWindowRect( &rec, dws, 0 );
    HWND hWnd = CreateWindowEx( WS_EX_APPWINDOW | WS_EX_WINDOWEDGE, wc.lpszClassName, "accio", dws,
                               (GetSystemMetrics(SM_CXSCREEN)-rec.right+rec.left)>>1,
                               (GetSystemMetrics(SM_CYSCREEN)-rec.bottom+rec.top)>>1,
                               rec.right-rec.left, rec.bottom-rec.top, 0, 0, hPrevInstance, 0 );
    if( !hWnd )
        return( 0 );

    HDC hDC=GetDC(hWnd);
    if( !hDC )
        return( 0 );

    // init opengl
    int pf = ChoosePixelFormat(hDC,&pfd);
    if( !pf )
        return( 0 );
    
    if( !SetPixelFormat(hDC,pf,&pfd) )
        return( 0 );

    HGLRC hRC = wglCreateContext(hDC);
    if( !hRC )
        return( 0 );

    if( !wglMakeCurrent(hDC,hRC) )
        return( 0 );

    // init extensions
    for( int i=0; i<(sizeof(funcPtrs)/sizeof(void*)); i++ )
    {
        funcPtrs[i] = wglGetProcAddress( funcNames[i] );
        if( !funcPtrs[i] )
            return 0;
    }

    // create shader
    int p = oglCreateProgram();
//    int v = oglCreateShader(GL_VERTEX_SHADER);
//    oglShaderSource(v, 1, &vertexShader, 0);
//    oglCompileShader(v);
//    oglAttachShader(p,v);
    int f = oglCreateShader(GL_FRAGMENT_SHADER);	

	const string shaderSource = readFile2("shader.frag");
	const char* src = shaderSource.c_str();
	oglShaderSource(f, 1, &src, 0);

    //oglShaderSource(f, 1, &fragmentShader, 0);
    oglCompileShader(f);

	int success = 0;
	oglGetShaderiv(f, GL_COMPILE_STATUS, &success);
	FILE* logFile = fopen("log.txt", "w");
	if (!success) {
		int logSize = 0;
		oglGetShaderiv(f, GL_INFO_LOG_LENGTH, &logSize);

		char* errorLog = new char[logSize];
		oglGetShaderInfoLog(f, logSize, &logSize, &errorLog[0]);

		fprintf(logFile, "Shader compilation log:\n%s", errorLog);
		
		delete errorLog;
		return -1;
	}

    oglAttachShader(p,f);
    oglLinkProgram(p);
    oglUseProgram(p);
    ShowCursor(0); 

    // run
/*
    do
    { 
        glColor3f(t,sinf(.25f*t),0.0f);
        glRects(-1,-1,1,1);
        SwapBuffers(hDC); //wglSwapLayerBuffers( hDC, WGL_SWAP_MAIN_PLANE );
    }while ( !GetAsyncKeyState(VK_ESCAPE) );
*/
	double PCFreq = 0.0;
	__int64 CounterStart = 0;

	LARGE_INTEGER li;
	QueryPerformanceFrequency(&li);
	PCFreq = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;

	FILE* timeFile = fopen("time.txt", "w");

	int timeLoc = oglGetUniformLocation(p, "t");

	FILE* locFile = fopen("loc.txt", "w");
	fprintf(locFile, "Location: %d\n", timeLoc);
	fclose(locFile);

    int done = 0;
    while( !done )
    {
		QueryPerformanceCounter(&li);
		float time = double(li.QuadPart - CounterStart) / PCFreq;
        //const float t = /*.0025f*/(float)(GetTickCount()&65535);
						

        MSG msg;
        while( PeekMessage(&msg,0,0,0,PM_REMOVE) )
        {
            if( msg.message==WM_QUIT ) done=1;
		    TranslateMessage( &msg );
            DispatchMessage( &msg );
        }

		//glColor3f(time, 0.0f/*sinf(.25f*t)*/, 0.0f);
		//glColor3us((unsigned int)(10 * (GetTickCount())), 0, 0);
		
		oglUniform1f(timeLoc, time / 1000.0);
		
		//if (time - int(time) > 0.9)
		//	return 0;
		//fprintf(stderr, "%f\n", time);

        glRects(-1,-1,1,1);
        SwapBuffers( hDC );
    }

    ExitProcess( 0 );

    return 0;
}
