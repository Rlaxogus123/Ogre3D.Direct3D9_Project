#include "DXUT.h"
#include "ShaderTest.h"
#include "MyMath.h"

USING(Tipp7)

ShaderTest::ShaderTest(void)
{
}

void ShaderTest::Init()
{
    SceneManager::Init();

    Tipp7::SceneNode* n_camera = this->createChildSceneNode("MainCamera");
    Tipp7::Camera* cam = this->createCamera("myCam");
    n_camera->setPosition(0, 0, -100);
    n_camera->attachObject(cam);

    Tipp7::SceneNode* n_airship = this->createChildSceneNode("model0");
    Tipp7::Entity* entity = this->createEntity("AirEntity", L"Models/SphereModel.x");
    entity->SetEffect(dynamic_cast<Shader*>(RM::GetInstance()->GetResources("Shader_NormalMap-Dir")));
    entity->SetDiffuseMap(dynamic_cast<Texture2D*>(RM::GetInstance()->GetResources("stoneDM")));
    entity->SetNormalMap(dynamic_cast<Texture2D*>(RM::GetInstance()->GetResources("NoneNM")));
    entity->SetSpecularMap(dynamic_cast<Texture2D*>(RM::GetInstance()->GetResources("stoneSM")));

    n_airship->attachObject(entity);
    n_airship->setScale(0.5, 0.5, 0.5);
    n_airship->setPosition(0, 30, 0);

    MeshManager::GetInstance()->createPlane(
        "ground",
        4000, 4000, 10, 10,
        70, 70
    );

    Tipp7::SceneNode* n_ground = this->createChildSceneNode("Ground");
    Tipp7::Entity* groundEntity = this->createEntity("GroundEntity", "ground");
    groundEntity->SetEffect(dynamic_cast<Shader*>(RM::GetInstance()->GetResources("Shader_NormalMap-Dir")));
    groundEntity->SetDiffuseMap(dynamic_cast<Texture2D*>(RM::GetInstance()->GetResources("stoneDM")));
    groundEntity->SetNormalMap(dynamic_cast<Texture2D*>(RM::GetInstance()->GetResources("stoneNM")));
    groundEntity->SetSpecularMap(dynamic_cast<Texture2D*>(RM::GetInstance()->GetResources("stoneSM")));

    n_ground->attachObject(groundEntity);
    n_ground->setPosition(0, -10, 0);
}

void ShaderTest::Update()
{
    SceneManager::Update();

    SceneNode* node = this->getSceneNode("MainCamera");

    static float timelike = 0.0f;
    timelike += Time::deltaTime;
    if (timelike >= 1) timelike = 0;

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

void ShaderTest::Render()
{
    SceneManager::Render();
}

void ShaderTest::Exit()
{
    SceneManager::Exit();
}
