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

    MeshManager::GetInstance()->createPlane(
        "ground",
        400, 400, 10, 10,
        7, 7
    );

    catmull_list.clear();

    CreatePoint();
    CreatePoint();
    CreatePoint();
    CreatePoint();

    Tipp7::SceneNode* n_ground = this->createChildSceneNode("Ground");
    Tipp7::Entity* groundEntity = this->createEntity("GroundEntity", "ground");
    groundEntity->SetTexture(dynamic_cast<Texture2D*>(RM::GetInstance()->GetResources("brick1")));
    n_ground->attachObject(groundEntity);
    n_ground->setPosition(0, -10, 0);

    font_t = new Font2D(L"Arial", 2, 700, Vector2(20, 20));
    font_b = new Font2D(L"Arial", 2, 700, Vector2(20, 20+55));
    font_c = new Font2D(L"Arial", 2, 700, Vector2(20, 20+55+55));
}

void Test2App::Update()
{
    SceneManager::Update();

    SceneNode* node = this->getSceneNode("MainCamera");
    SceneNode* ball = this->getSceneNode("model0");

    time += Time::deltaTime;
    if (time >= 1.0f) {
        CreatePoint();
        circle++;
        time = 0;
    }

    char buff[255];
    sprintf(buff, "T(tight) : %.2f", float_t);
    font_t->SetString(buff);
    sprintf(buff, "B(bias)  : %.2f", float_b);
    font_b->SetString(buff);
    sprintf(buff, "C(continuity) : %.2f", float_c);
    font_c->SetString(buff);

    *MyMath::myD3DXVec3KochanekBartels(&ball->position, &catmull_list[0 + circle], &catmull_list[1 + circle], &catmull_list[2 + circle], &catmull_list[3 + circle], float_t, float_b, float_c,time);
    node->position.x = ball->position.x;

    if (DXUTIsKeyDown('1')) float_t += Time::deltaTime;
    if (DXUTIsKeyDown('2')) float_b += Time::deltaTime;
    if (DXUTIsKeyDown('3')) float_c += Time::deltaTime;

    if (DXUTIsKeyDown('4')) float_t -= Time::deltaTime;
    if (DXUTIsKeyDown('5')) float_b -= Time::deltaTime;
    if (DXUTIsKeyDown('6')) float_c -= Time::deltaTime;

    if (DXUTIsKeyDown('7')) float_t = 0;
    if (DXUTIsKeyDown('8')) float_b = 0;
    if (DXUTIsKeyDown('9')) float_c = 0;

    if (DXUTIsKeyDown('Q')) node->yaw(node->getRotation().y - 1);
    if (DXUTIsKeyDown('E')) node->yaw(node->getRotation().y + 1);

    if (DXUTIsKeyDown('W')) node->setTranslate(node->foward);
    if (DXUTIsKeyDown('S')) node->setTranslate(-node->foward);
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

void Test2App::CreatePoint()
{
    catmull_list.push_back(Vector3(points * 25, rand() % 50 + 1, 0));

    Tipp7::SceneNode* sphere = this->createChildSceneNode("sphere");
    Tipp7::Entity* sp = this->createEntity("Sphere", L"Models/SphereModel.x");
    sp->SetTexture(dynamic_cast<Texture2D*>(RM::GetInstance()->GetResources("orange")));
    sphere->setScale(0.03f, 0.03f, 0.03f);
    sphere->attachObject(sp);
    sphere->setPosition(catmull_list[catmull_list.size() - 1]);
    points++;
}
