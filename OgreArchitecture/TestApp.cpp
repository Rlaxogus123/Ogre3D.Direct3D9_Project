#include "DXUT.h"
#include "TestApp.h"

USING(Tipp7)

TestApp::TestApp(void)
{
}

void TestApp::Init()
{
    SceneManager::Init();

    this->setAmbientLight(0.2f,0.2f,0.2f);
    //
    Tipp7::SceneNode* n_camera = this->createChildSceneNode("MainCamera");
    Tipp7::Camera* cam = this->createCamera("myCam");
    n_camera->setPosition(0, 0, -100);
    n_camera->attachObject(cam);
    //
    Tipp7::SceneNode* n_airship = this->createChildSceneNode("model0");
    Tipp7::Entity* entity = this->createEntity("AirEntity", L"Models/SphereModel.x");
    entity->SetEffect(dynamic_cast<Shader*>(RM::GetInstance()->GetResources("MLS")));
    entity->SetTexture(dynamic_cast<Texture2D*>(RM::GetInstance()->GetResources("terrain")));
    n_airship->attachObject(entity);
    n_airship->setPosition(0, -10, 0);
    //
    //Tipp7::SceneNode* n_teapot = this->createChildSceneNode("model1");
    //Tipp7::Entity* entity2 = this->createEntity("Teapot1", L"Models/MyCutieZombie.x");
    //entity2->SetEffect(L"Shaders/PhongUV.fx");
    //n_teapot->attachObject(entity2);
    //n_teapot->setPosition(10, 1, 1);
    //n_teapot->setScale(2, 2, 2);
    //
    //Tipp7::SceneNode* n_teapot2 = n_teapot->createChildSceneNode("child_model2");
    //Tipp7::Entity* entity3 = this->createEntity("Teapot2", L"Models/teapot.x");
    //n_teapot2->attachObject(entity3);
    //n_teapot2->setPosition(15, 1, 1);
    //n_teapot2->setScale(3, 2, 2);
    //
    Tipp7::SceneNode* n_pLight = this->createChildSceneNode("light");
    Tipp7::Light* dirLight = this->createLight("myLight");
    dirLight->setType(LightType::POINT);
    dirLight->setDiffuseColor(1, 1, 1);
    n_pLight->attachObject(dirLight);
    n_pLight->setPosition(100, 0, 0);
    
    MeshManager::GetInstance()->createPlane(
        "ground",
        400, 400, 100, 100,
        7, 7
    );

    Tipp7::SceneNode* n_ground = this->createChildSceneNode("Ground");
    Tipp7::Entity* groundEntity = this->createEntity("GroundEntity", "ground");
    groundEntity->SetEffect(dynamic_cast<Shader*>(RM::GetInstance()->GetResources("MLS")));
    groundEntity->SetTexture(dynamic_cast<Texture2D*>(RM::GetInstance()->GetResources("brick1")));
    n_ground->attachObject(groundEntity);
    n_ground->setPosition(0, -10, 0);

    //Tipp7::SceneNode* n_park = this->createChildSceneNode("ParkDongWan");
    //Tipp7::Entity* entity_park = this->createEntity("entity_park", L"Models/SphereModel.x");
    //entity_park->SetEffect(L"Shaders/MyFirstShader.fx");
    //n_park->attachObject(entity_park);
    //n_park->setPosition(-20, -10, 10);
    //n_park->setScale(5, 5, 5);
}

void TestApp::Update()
{
   SceneManager::Update();

   SceneNode* node = this->getSceneNode("MainCamera");
   SceneNode* light = this->getSceneNode("light");
   //
   //parent->roll(parent->rotation.z + 1);
   //

   if (light->getPosition().x < 100)
       light->setTranslate(1, 0, 0);
   else
       light->setPosition(-100, 100, 0);

   if (DXUTIsKeyDown('W')) node->setPosition(node->getPosition().x, node->getPosition().y, node->getPosition().z + 1);
   if (DXUTIsKeyDown('S')) node->setPosition(node->getPosition().x, node->getPosition().y, node->getPosition().z - 1);
   if (DXUTIsKeyDown('A')) node->setPosition(node->getPosition().x - 1, node->getPosition().y, node->getPosition().z);
   if (DXUTIsKeyDown('D')) node->setPosition(node->getPosition().x + 1, node->getPosition().y, node->getPosition().z);
   if (DXUTIsKeyDown('Q')) node->yaw(node->getRotation().y - 1);
   if (DXUTIsKeyDown('E')) node->yaw(node->getRotation().y + 1);
   if (DXUTIsKeyDown('R')) node->pitch(node->getRotation().x - 1);
   if (DXUTIsKeyDown('F')) node->pitch(node->getRotation().x + 1);
   
   if (DXUTWasKeyPressed('T')) this->isWireFrame = !this->isWireFrame;
   if (DXUTWasKeyPressed('L')) this->getEntity("AirEntity")->SetTexture(dynamic_cast<Texture2D*>(RM::GetInstance()->GetResources("brick1")));
   if (DXUTWasKeyPressed('M')) this->getEntity("AirEntity")->SetTexture(dynamic_cast<Texture2D*>(RM::GetInstance()->GetResources("checker")));

   if (DXUTWasKeyPressed(VK_ESCAPE)) Root::GetInstance()->RootExit();
   if (DXUTIsKeyDown('V'))
       Root::GetInstance()->ReloadSceneManager("TestApp");

   if (DXUTIsKeyDown(VK_SPACE)) node->setPosition(node->getPosition().x, node->getPosition().y + 1, node->getPosition().z);
   if (DXUTIsKeyDown(VK_SHIFT)) node->setPosition(node->getPosition().x, node->getPosition().y - 1, node->getPosition().z);
}

void TestApp::Render()
{
    SceneManager::Render();
}

void TestApp::Exit()
{
    SceneManager::Exit();
}
