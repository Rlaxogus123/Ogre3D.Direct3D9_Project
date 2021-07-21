//--------------------------------------------------------------------------------------
// File: OgreArchitecture.cpp
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#include "DXUT.h"
#include "resource.h"
#include "MyMath.h"
#include "Root.h"


USING(Tipp7)

SceneManager* scnMgr;

//--------------------------------------------------------------------------------------
// Rejects any D3D9 devices that aren't acceptable to the app by returning false
//--------------------------------------------------------------------------------------
bool CALLBACK IsD3D9DeviceAcceptable( D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat,
                                      bool bWindowed, void* pUserContext )
{
    // Typically want to skip back buffer formats that don't support alpha blending
    IDirect3D9* pD3D = DXUTGetD3D9Object();
    if( FAILED( pD3D->CheckDeviceFormat( pCaps->AdapterOrdinal, pCaps->DeviceType,
                                         AdapterFormat, D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING,
                                         D3DRTYPE_TEXTURE, BackBufferFormat ) ) )
        return false;
    return true;
}


//--------------------------------------------------------------------------------------
// Before a device is created, modify the device settings as needed
//--------------------------------------------------------------------------------------
bool CALLBACK ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, void* pUserContext )
{
    return true;
}


//--------------------------------------------------------------------------------------
// Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED)
// and aren't tied to the back buffer size
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnD3D9CreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                     void* pUserContext )
{
    Tipp7::Root::GetInstance()->RootInit();

    scnMgr = Tipp7::Root::GetInstance()->createSceneManager("TestScene");
    scnMgr->setAmbientLight(0.2,0.2,0.2);
    
    Tipp7::SceneNode* n_camera = scnMgr->createChildSceneNode("MainCamera");
    Tipp7::SceneNode* n_airship = scnMgr->createChildSceneNode("model0");
    Tipp7::SceneNode* n_teapot = scnMgr->createChildSceneNode("model1");
    Tipp7::SceneNode* n_teapot2 = n_teapot->createChildSceneNode("child_model2");
    Tipp7::SceneNode* n_pLight = scnMgr->createChildSceneNode("light");
    Tipp7::SceneNode* n_ground = scnMgr->createChildSceneNode("Ground");

    Tipp7::Camera* cam = scnMgr->createCamera("myCam");
    n_camera->setPosition(0, 0, -100);
    n_camera->attachObject(cam);

    Tipp7::Entity* entity = scnMgr->createEntity("myEntity", L"Models/Airship.x");
    n_airship->attachObject(entity);
    n_airship->setPosition(0, -10, 0);

    Tipp7::Entity* entity2 = scnMgr->createEntity("myEntity", L"Models/teapot.x");
    n_teapot->attachObject(entity2);
    n_teapot->setPosition(10, 1, 1);
    n_teapot->setScale(2, 2, 2);

    Tipp7::Entity* entity3 = scnMgr->createEntity("myEntity", L"Models/teapot.x");
    n_teapot2->attachObject(entity3);
    n_teapot2->setPosition(15, 1, 1);
    n_teapot2->setScale(3, 2, 2);

    Tipp7::Light* dirLight = scnMgr->createLight("myLight");
    dirLight->setType(LightType::POINT);
    dirLight->setPowerScale(30);
    dirLight->setDiffuseColor(1, 1, 1);
    n_pLight->attachObject(dirLight);
    n_pLight->setPosition(0, 10, 0);
    n_pLight->pitch(-90);

    Tipp7::Plane plane;
    MeshManager::GetInstance()->createPlane(
        "ground",
        plane,
        150, 150,100, 100
    );
    Tipp7::Entity* groundEntity = scnMgr->createEntity("GroundEntity", "ground");
    n_ground->attachObject(groundEntity);
    n_ground->setPosition(0, -10, 0);
    return S_OK;
}


//--------------------------------------------------------------------------------------
// Create any D3D9 resources that won't live through a device reset (D3DPOOL_DEFAULT) 
// or that are tied to the back buffer size 
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnD3D9ResetDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                    void* pUserContext )
{
    return S_OK;
}


//--------------------------------------------------------------------------------------
// Handle updates to the scene.  This is called regardless of which D3D API is used
//--------------------------------------------------------------------------------------
void CALLBACK OnFrameMove( double fTime, float fElapsedTime, void* pUserContext )
{
    Root::GetInstance()->RootUpdate();

    SceneNode* node = scnMgr->getSceneNode("MainCamera");
    SceneNode* parent = scnMgr->getSceneNode("model1");

    parent->roll(parent->rotation.z + 1);

    if (DXUTIsKeyDown('W')) node->setPosition(node->getPosition().x, node->getPosition().y, node->getPosition().z + 1);
    if (DXUTIsKeyDown('S')) node->setPosition(node->getPosition().x, node->getPosition().y, node->getPosition().z - 1);
    if (DXUTIsKeyDown('A')) node->setPosition(node->getPosition().x - 1, node->getPosition().y, node->getPosition().z);
    if (DXUTIsKeyDown('D')) node->setPosition(node->getPosition().x + 1, node->getPosition().y, node->getPosition().z);
    if (DXUTIsKeyDown('Q')) node->yaw(node->getRotation().y - 1);
    if (DXUTIsKeyDown('E')) node->yaw(node->getRotation().y + 1);
    if (DXUTIsKeyDown('R')) node->pitch(node->getRotation().x - 1);
    if (DXUTIsKeyDown('F')) node->pitch(node->getRotation().x + 1);

    if (DXUTWasKeyPressed('T')) scnMgr->isWireFrame = !scnMgr->isWireFrame;

    if (DXUTIsKeyDown(VK_SPACE)) node->setPosition(node->getPosition().x, node->getPosition().y + 1, node->getPosition().z);
    if (DXUTIsKeyDown(VK_SHIFT)) node->setPosition(node->getPosition().x, node->getPosition().y - 1, node->getPosition().z);

}


//--------------------------------------------------------------------------------------
// Render the scene using the D3D9 device
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D9FrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
    HRESULT hr;

    // Clear the render target and the zbuffer 
    V( pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB( 0, 100, 100, 100 ), 1.0f, 0 ) );

    // Render the scene
    if( SUCCEEDED( pd3dDevice->BeginScene() ) )
    {
        Root::GetInstance()->RootRender();
        V( pd3dDevice->EndScene() );
    }
}


//--------------------------------------------------------------------------------------
// Handle messages to the application 
//--------------------------------------------------------------------------------------
LRESULT CALLBACK MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
                          bool* pbNoFurtherProcessing, void* pUserContext )
{
    return 0;
}


//--------------------------------------------------------------------------------------
// Release D3D9 resources created in the OnD3D9ResetDevice callback 
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D9LostDevice( void* pUserContext )
{
}


//--------------------------------------------------------------------------------------
// Release D3D9 resources created in the OnD3D9CreateDevice callback 
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D9DestroyDevice( void* pUserContext )
{
    Root::GetInstance()->RootExit();
}


//--------------------------------------------------------------------------------------
// Initialize everything and go into a render loop
//--------------------------------------------------------------------------------------
//INT WINAPI wWinMain( HINSTANCE, HINSTANCE, LPWSTR, int )
int main(void)
{
    // Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    // Set the callback functions
    DXUTSetCallbackD3D9DeviceAcceptable( IsD3D9DeviceAcceptable );
    DXUTSetCallbackD3D9DeviceCreated( OnD3D9CreateDevice );
    DXUTSetCallbackD3D9DeviceReset( OnD3D9ResetDevice );
    DXUTSetCallbackD3D9FrameRender( OnD3D9FrameRender );
    DXUTSetCallbackD3D9DeviceLost( OnD3D9LostDevice );
    DXUTSetCallbackD3D9DeviceDestroyed( OnD3D9DestroyDevice );
    DXUTSetCallbackDeviceChanging( ModifyDeviceSettings );
    DXUTSetCallbackMsgProc( MsgProc );
    DXUTSetCallbackFrameMove( OnFrameMove );

    // TODO: Perform any application-level initialization here

    // Initialize DXUT and create the desired Win32 window and Direct3D device for the application
    DXUTInit( true, true ); // Parse the command line and show msgboxes
    DXUTSetHotkeyHandling( true, true, true );  // handle the default hotkeys
    DXUTSetCursorSettings( true, true ); // Show the cursor and clip it when in full screen
    DXUTCreateWindow( L"OgreArchitecture" );
    DXUTCreateDevice( true, SCW, SCH );
        
    // Start the render loop
    DXUTMainLoop();

    // TODO: Perform any application-level cleanup here

    return DXUTGetExitCode();
}


