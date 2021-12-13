#include "DXUT.h"
#include "TestApp.h"
#include "MyMath.h"

USING(Tipp7)

TestApp::TestApp(void)
{
}

void TestApp::Init()
{
    SceneManager::Init();
    this->setAmbientLight(0.1f,0.1f,0.1f);

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
    n_airship->createQuaternion();
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
    Tipp7::SceneNode* n_pLight = this->createChildSceneNode("light1");
    Tipp7::Light* dirLight = this->createLight("myLight1");
    dirLight->setType(LightType::POINT);
    dirLight->setDiffuseColor(1, 1, 1, 0.5f);
    dirLight->setSpecularColor(1, 1, 1);
    dirLight->setPowerScale(125);
    n_pLight->attachObject(dirLight);
    n_pLight->setPosition(-100, 100, 0);

    Tipp7::SceneNode* n_pLight1 = this->createChildSceneNode("light2");
    Tipp7::Light* dirLight1 = this->createLight("myLight2");
    dirLight1->setType(LightType::POINT);
    dirLight1->setPowerScale(100);
    dirLight1->setDiffuseColor(1, 0, 0);
    n_pLight1->attachObject(dirLight1);
    n_pLight1->setPosition(100, 0, 0);

    Tipp7::SceneNode* n_pLight2 = this->createChildSceneNode("light3");
    Tipp7::Light* dirLight2 = this->createLight("myLight3");
    dirLight2->setType(LightType::POINT);
    dirLight2->setPowerScale(100);
    dirLight2->setDiffuseColor(0, 1, 0);
    n_pLight2->attachObject(dirLight2);
    n_pLight2->setPosition(100, 0, 100);

    Tipp7::SceneNode* n_pLight3 = this->createChildSceneNode("light4");
    Tipp7::Light* dirLight3 = this->createLight("myLight4");
    dirLight3->setType(LightType::POINT);
    dirLight3->setPowerScale(100);
    dirLight3->setDiffuseColor(0, 0, 1);
    n_pLight3->attachObject(dirLight3);
    n_pLight3->setPosition(100, 0, -100);
    
    MeshManager::GetInstance()->createPlane(
        "ground",
        400, 400, 10, 10,
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

    D3DXQUATERNION q1(3, 6, 4, 31);
    D3DXQUATERNION q2(3,6,4,31);
    cout << "Before收收收收收收收收收收收收收" << endl;
    MyMath::__ShowQuaternion(&q1, "D3DX");
    MyMath::__ShowQuaternion(&q2, "_MY_");
    cout << "After收收收收收收收收收收收收收" << endl;
    D3DXQuaternionLn(&q1, &q1);
    MyMath::myD3DXQuaternionLn(&q2, &q2);
    MyMath::__ShowQuaternion(&q1, "D3DX");
    MyMath::__ShowQuaternion(&q2, "_MY_");
}

void TestApp::Update()
{
   SceneManager::Update();

   SceneNode* node = this->getSceneNode("MainCamera");
   SceneNode* model = this->getSceneNode("model0");
   SceneNode* light = this->getSceneNode("light1");
   //
   //parent->roll(parent->rotation.z + 1);
   //

   if (light->getPosition().x < 100)
       light->setTranslate(1, 0, 0);
   else light->setPosition(-100, 100, 0);

   static float angle = 0.0f;
   angle += Time::deltaTime * 30;

   //D3DXQUATERNION* qq = new D3DXQUATERNION();
   D3DXQUATERNION Q = *MyMath::myD3DXQuaternionRotationAxis(&Q, &Vector3(1, 1, 0), D3DXToRadian(angle));
   
   if (isMy) D3DXMatrixRotationQuaternion(model->matQuaternion, &Q);
   else MyMath::myD3DXMatrixRotationQuaternion(model->matQuaternion, &Q);
   if (DXUTWasKeyPressed('Z'))
       isMy = !isMy;
   //model->quaternion = qq;
   //model

   //MyMath::myD3DXVec3RotationAxis(&node->position , &Vector3(30,0,-100), &Vector3(0,0,1), D3DXToRadian(angle));

   Vector3 v_axis(0, 0, 1);
   D3DXQUATERNION q = *MyMath::myD3DXQuaternionRotationAxis(&q, &v_axis, D3DXToRadian(angle));
   D3DXQUATERNION _q = *MyMath::myD3DXQuaternionConjugate(&_q, &q);
   D3DXQUATERNION p(0, 10, -100, 0);
   
   D3DXQUATERNION p1 = *MyMath::myD3DXQuaternionMultiply(&p1, &_q, &p);
   D3DXQUATERNION _p = *MyMath::myD3DXQuaternionMultiply(&p, &p1, &q);
    
   node->setPosition(_p.x, _p.y, _p.z);

   if (DXUTIsKeyDown('Q')) node->yaw(node->getRotation().y - 1);
   if (DXUTIsKeyDown('E')) node->yaw(node->getRotation().y + 1);

   if (DXUTIsKeyDown('W')) node->setTranslate(node->foward);
   if (DXUTIsKeyDown('S')) node->setTranslate(-node->foward);
   if (DXUTIsKeyDown('A')) node->setTranslate(-node->right);
   if (DXUTIsKeyDown('D')) node->setTranslate(node->right);
   if (DXUTIsKeyDown('R')) node->pitch(node->getRotation().x - 1);
   if (DXUTIsKeyDown('F')) node->pitch(node->getRotation().x + 1);
   
   if (DXUTWasKeyPressed('T')) this->isWireFrame = !this->isWireFrame;
   if (DXUTWasKeyPressed('L')) this->getEntity("AirEntity")->SetTexture(dynamic_cast<Texture2D*>(RM::GetInstance()->GetResources("brick1")));
   if (DXUTWasKeyPressed('M')) this->getEntity("AirEntity")->SetTexture(dynamic_cast<Texture2D*>(RM::GetInstance()->GetResources("checker")));

   if (DXUTWasKeyPressed(VK_ESCAPE)) Root::GetInstance()->RootExit();
   if (DXUTWasKeyPressed('N')) Root::GetInstance()->ReloadSceneManager("ProjectileApp");
   if (DXUTWasKeyPressed('M')) Root::GetInstance()->ReloadSceneManager("GameApp");

   if (DXUTIsKeyDown(VK_SPACE)) node->setTranslate(Vector3(0,1,0));
   if (DXUTIsKeyDown(VK_SHIFT)) node->setTranslate(Vector3(0, -1, 0));
}

void TestApp::Render()
{
    SceneManager::Render();
}

void TestApp::Exit()
{
    SceneManager::Exit();
}
