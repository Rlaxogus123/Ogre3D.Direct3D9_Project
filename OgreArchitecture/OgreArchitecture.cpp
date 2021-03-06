//--------------------------------------------------------------------------------------
// File: OgreArchitecture.cpp
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

/*
    Ogre3D to DirectX3D9 1.0.0

    Copyright 2021 Tipp7 and other contributors
    Release Under the MIT License

    Contact by >> acekimcp@gmail.com

    Last Update 2021.08.19
*/
#include "DXUT.h"
#include "resource.h"

#include "MyMath.h"
#include "RM.h"
#include "Time.h"
#include "Root.h"

#include "TestApp.h"
#include "Test2App.h"
#include "GameApp.h"
#include "ProjectileApp.h"
#include "SquadApp.h"
#include "ShaderTest.h"
#include "AseApp.h"


USING(Tipp7)

SceneManager* scnMgr;

bool CALLBACK IsD3D9DeviceAcceptable( D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat,
                                      bool bWindowed, void* pUserContext )
{
    IDirect3D9* pD3D = DXUTGetD3D9Object();
    if( FAILED( pD3D->CheckDeviceFormat( pCaps->AdapterOrdinal, pCaps->DeviceType,
                                         AdapterFormat, D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING,
                                         D3DRTYPE_TEXTURE, BackBufferFormat ) ) )
        return false;
    return true;
}


bool CALLBACK ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, void* pUserContext )
{
    return true;
}


HRESULT CALLBACK OnD3D9CreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                     void* pUserContext )
{
    srand(time(NULL));
    RM::GetInstance()->preLoadTextures();
    Tipp7::Root::GetInstance()->RootInit();
    Root::GetInstance()->createSceneManager("AseApp", new AseApp());
    Root::GetInstance()->createSceneManager("ShaderTest", new ShaderTest());
    Root::GetInstance()->createSceneManager("SquadApp", new SquadApp());
    Root::GetInstance()->createSceneManager("TestApp", new TestApp());
    Root::GetInstance()->createSceneManager("Test2App", new Test2App());
    Root::GetInstance()->createSceneManager("GameApp", new GameApp());
    Root::GetInstance()->createSceneManager("ProjectileApp", new ProjectileApp());
    return S_OK;
}


HRESULT CALLBACK OnD3D9ResetDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                    void* pUserContext )
{
    return S_OK;
}


void CALLBACK OnFrameMove( double fTime, float fElapsedTime, void* pUserContext )
{
    Time::deltaTime = fElapsedTime * Time::scaleTime;
    Time::totalTime = fTime;
    Root::GetInstance()->RootUpdate();
}


void CALLBACK OnD3D9FrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
    HRESULT hr;

    V( pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB( 0, 0, 0, 0 ), 1.0f, 0 ) );

    if( SUCCEEDED( pd3dDevice->BeginScene() ) )
    {
        Root::GetInstance()->RootRender();
        V( pd3dDevice->EndScene() );
    }
}


LRESULT CALLBACK MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
                          bool* pbNoFurtherProcessing, void* pUserContext )
{
    return 0;
}


void CALLBACK OnD3D9LostDevice( void* pUserContext )
{
}


void CALLBACK OnD3D9DestroyDevice( void* pUserContext )
{
    Root::GetInstance()->RootExit();
}


//INT WINAPI wWinMain( HINSTANCE, HINSTANCE, LPWSTR, int )
int main(void)
{
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    DXUTSetCallbackD3D9DeviceAcceptable( IsD3D9DeviceAcceptable );
    DXUTSetCallbackD3D9DeviceCreated( OnD3D9CreateDevice );
    DXUTSetCallbackD3D9DeviceReset( OnD3D9ResetDevice );
    DXUTSetCallbackD3D9FrameRender( OnD3D9FrameRender );
    DXUTSetCallbackD3D9DeviceLost( OnD3D9LostDevice );
    DXUTSetCallbackD3D9DeviceDestroyed( OnD3D9DestroyDevice );
    DXUTSetCallbackDeviceChanging( ModifyDeviceSettings );
    DXUTSetCallbackMsgProc( MsgProc );
    DXUTSetCallbackFrameMove( OnFrameMove );

    DXUTInit( true, true );
    DXUTSetHotkeyHandling( true, false, true );
    DXUTSetCursorSettings( true, true );
    DXUTCreateWindow( L"OgreArchitecture" );
    DXUTCreateDevice( true, SCW, SCH );
        
    DXUTMainLoop();

    return DXUTGetExitCode();
}


