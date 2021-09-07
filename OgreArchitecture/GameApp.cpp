#include "DXUT.h"
#include "GameApp.h"
#include "CollisionManager.h"

USING(Tipp7)

GameApp::GameApp(void)
{
}

void GameApp::Init()
{
    SceneManager::Init();
    this->setAmbientLight(1,1,1);

    Tipp7::SceneNode* n_airship = this->createChildSceneNode("model0");
    Tipp7::Entity* entity = this->createEntity("AirEntity", L"Models/Airship.x");
    entity->SetTexture(dynamic_cast<Texture2D*>(RM::GetInstance()->GetResources("terrain")));
    n_airship->setBoundCircle(20);
    n_airship->showBoundCircle(true);
    n_airship->attachObject(entity);
    n_airship->setPosition(0, 0, 100);

    Tipp7::SceneNode* nChar = this->createChildSceneNode("Character");
    Tipp7::Entity* entityChar = this->createEntity("CharEntity", L"Models/MyCutieZombie.x");
    nChar->setBoundCircle(10);
    nChar->setPosition(0, 0, -100);
    nChar->setScale(6,6,6);
    nChar->attachObject(entityChar);

    Tipp7::SceneNode* n_camera = nChar->createChildSceneNode("MainCamera");
    Tipp7::Camera* cam = this->createCamera("myCam");
    n_camera->setPosition(0, 3, 0);
    n_camera->attachObject(cam);

    MeshManager::GetInstance()->createPlane(
        "ground",
        4000, 4000, 100, 100,
        70, 70
    );

    Tipp7::SceneNode* n_ground = this->createChildSceneNode("Ground");
    Tipp7::Entity* groundEntity = this->createEntity("GroundEntity", "ground");
    groundEntity->SetTexture(dynamic_cast<Texture2D*>(RM::GetInstance()->GetResources("brick1")));
    n_ground->attachObject(groundEntity);
    n_ground->setPosition(0, 0, 0);

    Tipp7::SceneNode* n_ground2 = this->createChildSceneNode("Ground2");
    Tipp7::Entity* groundEntity2 = this->createEntity("GroundEntity2", "ground");
    groundEntity2->SetTexture(dynamic_cast<Texture2D*>(RM::GetInstance()->GetResources("checker")));
    n_ground2->attachObject(groundEntity2);
    n_ground2->setPosition(0, 0, 300);
    n_ground2->pitch(-45);
}

void GameApp::Update()
{
    SceneManager::Update();

    SceneNode* ground = this->getSceneNode("Ground");
    SceneNode* wall = this->getSceneNode("Ground2");
    SceneNode* model = this->getSceneNode("model0");
    SceneNode* character = this->getSceneNode("Character");
    SceneNode* cam = character->GetChild("MainCamera");

    //if (CollisionManager::GetInstance()->Sphere_VS_Sphere(
    //    model->getPosition(), model->boundCircle, character->getPosition(), character->boundCircle
    //)) {
    //    cout << "Collision Detective!" << endl;
    //}

    if (DXUTIsKeyDown('W')) character->setTranslate(character->foward);
    if (DXUTIsKeyDown('S')) character->setTranslate(-character->foward);
    if (DXUTIsKeyDown('A')) character->setTranslate(-character->right);
    if (DXUTIsKeyDown('D')) character->setTranslate(character->right);

    if (DXUTIsKeyDown(VK_SPACE)) model->setTranslate(model->up);
    if (DXUTIsKeyDown(VK_SHIFT)) model->setTranslate(-model->up);
    if (DXUTIsKeyDown(VK_RIGHT)) model->setTranslate(Vector3(1, 0, 0));
    if (DXUTIsKeyDown(VK_LEFT)) model->setTranslate(Vector3(-1, 0, 0));
    if (DXUTIsKeyDown(VK_UP)) model->setTranslate(Vector3(0,0,1));
    if (DXUTIsKeyDown(VK_DOWN)) model->setTranslate(Vector3(0, 0, -1));

    if (CollisionManager::GetInstance()->Sphere_VS_Plane(
        &model->getPosition(), model->boundCircle,
        &ground->getPosition(), &ground->up))
    {
        cout << "Ground Collision Detective!!" << endl;
    }
    else if (CollisionManager::GetInstance()->Sphere_VS_Plane(
        &model->getPosition(), model->boundCircle,
        &wall->getPosition(), &wall->up))
    {
        cout << "Wall Collision Detective!!" << endl;
    }
    else cout << "NoCollision" << endl;

    if (pointlock)
    {
        D3DVIEWPORT9 viewPort;
        Vector3 screenPos;

        DEVICE->GetViewport(&viewPort);

        POINT preP;
        POINT p = {viewPort.Width/2, viewPort.Height/2};
        GetCursorPos(&preP);
        ClientToScreen(DXUTGetHWND(), &p);

        if (preP.x > p.x)
        {
            float amount = preP.x - p.x;
            preP.x -= amount;
            character->yaw(character->getRotation().y + (amount * aimAmount));
        }
        if (preP.x < p.x)
        {
            float amount = p.x - preP.x;
            preP.x += amount;
            character->yaw(character->getRotation().y - (amount * aimAmount));
        }
        if (preP.y > p.y)
        {
            float amount = preP.y - p.y;
            preP.y -= amount;

            float amount2 = cam->getRotation().x + (amount * aimAmount);
            if (amount2 >= 90) amount2 = 89;
            cam->pitch(amount2);
        }
        if (preP.y < p.y)
        {
            float amount = p.y - preP.y;
            preP.y += amount;

            float amount2 = cam->getRotation().x - (amount * aimAmount);
            if (amount2 <= -90) amount2 = -89;
            cam->pitch(amount2);
        }

        SetCursorPos(preP.x, preP.y);
    }

    if (DXUTWasKeyPressed('T')) this->isWireFrame = !this->isWireFrame;
    if (DXUTWasKeyPressed('M')) Root::GetInstance()->ReloadSceneManager("ProjectileApp");
    if (DXUTWasKeyPressed('N')) Root::GetInstance()->ReloadSceneManager("TestApp");

    if (DXUTWasKeyPressed(VK_F1)) pointlock = !pointlock;
    if (DXUTWasKeyPressed(VK_F5)) cam->setPosition(0, 3, -15);
    if (DXUTWasKeyPressed(VK_F6)) cam->setPosition(0, 3, 0);
    if (DXUTWasKeyPressed(VK_ESCAPE)) Root::GetInstance()->RootExit();
}

void GameApp::Render()
{
    SceneManager::Render();
}

void GameApp::Exit()
{
    SceneManager::Exit();
}
