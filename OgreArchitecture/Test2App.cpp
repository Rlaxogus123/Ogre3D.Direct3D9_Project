#include "DXUT.h"
#include "Test2App.h"
#include "MyMath.h"

USING(Tipp7)

Test2App::Test2App(void)
{
}

void Test2App::Init()
{
    SceneManager::Init();

    Tipp7::SceneNode* n_camera = this->createChildSceneNode("MainCamera");
    Tipp7::Camera* cam = this->createCamera("myCam");
    n_camera->setPosition(0, 0, -100);
    n_camera->attachObject(cam);

    Tipp7::SceneNode* n_airship = this->createChildSceneNode("model0");
    Tipp7::Entity* entity = this->createEntity("AirEntity", L"Models/SphereModel.x");
    entity->SetTexture(dynamic_cast<Texture2D*>(RM::GetInstance()->GetResources("red")));
    n_airship->attachObject(entity);
    n_airship->setScale(0.05f, 0.05f, 0.05f);
    n_airship->setPosition(0, -10, 0);

    Tipp7::SceneNode* n_model1 = this->createChildSceneNode("model1");
    Tipp7::Entity* entity2 = this->createEntity("AirEntity", L"Models/SphereModel.x");
    entity2->SetTexture(dynamic_cast<Texture2D*>(RM::GetInstance()->GetResources("red")));
    n_model1->attachObject(entity2);
    n_model1->setScale(0.05f, 0.05f, 0.05f);
    n_model1->setPosition(0, -10, 0);

    Tipp7::SceneNode* n_model2 = this->createChildSceneNode("model2");
    Tipp7::Entity* entity3 = this->createEntity("AirEntity", L"Models/SphereModel.x");
    entity3->SetTexture(dynamic_cast<Texture2D*>(RM::GetInstance()->GetResources("orange")));
    n_model2->attachObject(entity3);
    n_model2->setScale(0.05f, 0.05f, 0.05f);
    n_model2->setPosition(0, -10, 0);

    Tipp7::SceneNode* n_model3 = this->createChildSceneNode("model3");
    Tipp7::Entity* entity4 = this->createEntity("AirEntity", L"Models/SphereModel.x");
    entity4->SetTexture(dynamic_cast<Texture2D*>(RM::GetInstance()->GetResources("orange")));
    n_model3->attachObject(entity4);
    n_model3->setScale(0.05f, 0.05f, 0.05f);
    n_model3->setPosition(0, -10, 0);

    MeshManager::GetInstance()->createPlane(
        "ground",
        400, 400, 10, 10,
        7, 7
    );

    Tipp7::SceneNode* n_ground = this->createChildSceneNode("Ground");
    Tipp7::Entity* groundEntity = this->createEntity("GroundEntity", "ground");
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

void Test2App::Update()
{
    SceneManager::Update();

    SceneNode* node = this->getSceneNode("MainCamera");
    SceneNode* p1 = this->getSceneNode("model0");
    SceneNode* p2 = this->getSceneNode("model1");
    SceneNode* r = this->getSceneNode("model2");
    SceneNode* r2 = this->getSceneNode("model3");

    static float timelike = 0.0f;
    if (timelike < 1) timelike += Time::deltaTime;
    else timelike = 0;

    Vector3 pos1(-50, 1, 0);
    Vector3 pos2(50, 0, 0);
    p1->setPosition(pos1);
    p2->setPosition(pos2);

    D3DXQUATERNION q0(0, pos1.x, pos1.y, pos1.z);
    D3DXQUATERNION q1(0, pos2.x, pos2.y, pos2.z);

    MyMath::myD3DXVec3Slerp(&r->position, &pos1, &pos2, timelike);
    MyMath::myD3DXVec3Lerp(&r2->position, &pos1, &pos2, timelike);

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

    if (DXUTIsKeyDown(VK_SPACE)) node->setTranslate(Vector3(0, 1, 0));
    if (DXUTIsKeyDown(VK_SHIFT)) node->setTranslate(Vector3(0, -1, 0));
}

void Test2App::Render()
{
    SceneManager::Render();
}

void Test2App::Exit()
{
    SceneManager::Exit();
}
