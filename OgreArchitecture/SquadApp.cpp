#include "DXUT.h"
#include "SquadApp.h"
#include "MyMath.h"

USING(Tipp7)

SquadApp::SquadApp(void)
{
}

void SquadApp::Init()
{
    SceneManager::Init();
    circle = 0;
    points = 0;
    time = 0;

    Tipp7::SceneNode* n_camera = this->createChildSceneNode("MainCamera");
    Tipp7::Camera* cam = this->createCamera("myCam");
    n_camera->setPosition(0, 0, -100);
    n_camera->attachObject(cam);
    n_camera->createQuaternion();

    MeshManager::GetInstance()->createPlane(
        "ground",
        120000,120000, 10, 10,
        2100,2100
    );

    Tipp7::SceneNode* n_ground = this->createChildSceneNode("Ground");
    Tipp7::Entity* groundEntity = this->createEntity("GroundEntity", "ground");
    groundEntity->SetTexture(dynamic_cast<Texture2D*>(RM::GetInstance()->GetResources("brick1")));
    n_ground->attachObject(groundEntity);
    n_ground->setPosition(0, -10, 0);

    Tipp7::SceneNode* n_airship = this->createChildSceneNode("model0");
    Tipp7::Entity* entity = this->createEntity("AirEntity", L"Models/MyArrow.x");
    entity->SetTexture(dynamic_cast<Texture2D*>(RM::GetInstance()->GetResources("orange")));
    n_airship->attachObject(entity);
    n_airship->setPosition(0, 0, 100);
    n_airship->setScale(0.3f,0.3f,0.3f);

    catmull_list.clear();
    quaternion_list.clear();

    CreatePoint();
    CreatePoint();
    CreatePoint();
    CreatePoint();

    font0 = new Font2D(L"Arial", 2, 700, Vector2(20, 20));
    font1 = new Font2D(L"Arial", 2, 700, Vector2(20, 75));
}

void SquadApp::Update()
{
    SceneManager::Update();
    SceneNode* node = this->getSceneNode("MainCamera");
    SceneNode* air = this->getSceneNode("model0");

    time += Time::deltaTime;
    if (time >= 1.0f) {
        CreatePoint();
        circle++;
        time = 0;
    }

    char buff[255];
    sprintf(buff, "Time : %.2f / 1.0", time);
    font1->SetString(buff);

    D3DXQUATERNION Q;
    
    string movable = "";
    string rotate = "";
    
    if (moveType == SHOWCASE::CATMULL) {
        movable = "Catmull-rom";
        node->setPosition(*MyMath::myD3DXVec3CatmullRom(&node->position, &catmull_list[0 + circle], &catmull_list[1 + circle], &catmull_list[2 + circle], &catmull_list[3 + circle], time));
    }
    if (moveType == SHOWCASE::LERP) {
        movable = "Lerp";
        node->setPosition(*D3DXVec3Lerp(&node->position, &catmull_list[1 + circle], &catmull_list[2 + circle], time));
    }
    
    if (rotateType == SHOWCASE::SLERP) {
        rotate = "SLerp";
        Q = *D3DXQuaternionSlerp(&Q, &quaternion_list[1 + circle], &quaternion_list[2 + circle], time);
    }
    if (rotateType == SHOWCASE::SQUAD) {
        rotate = "Squad";
        SettingSquad();
        Q = *D3DXQuaternionSquad(&Q, &quaternion_list[1 + circle], &s0, &s1, &quaternion_list[2 + circle], time);
        // setup quaternion is always normal; s0.length == 1;
        //cout << "s_0 length = " << D3DXQuaternionLength(&s0) << endl;
    }

    sprintf(buff, "[ Press Q or E ] current Spline-State : %s / %s", movable.c_str(), rotate.c_str());
    font0->SetString(buff);

    D3DXMATRIX Ryxn;
    MyMath::__MatrixRotationQuaternionAxis(&Ryxn, &Q, &Vector3(1,0,0));
    D3DXMATRIX Rn = *D3DXMatrixRotationQuaternion(&Rn, &Q);
    D3DXMatrixMultiply(node->matQuaternion, &Ryxn, &Rn);

    if (DXUTWasKeyPressed('T')) this->isWireFrame = !this->isWireFrame;
    if (DXUTWasKeyPressed('Q')) moveType = moveType == SHOWCASE::CATMULL ? SHOWCASE::LERP : SHOWCASE::CATMULL;
    if (DXUTWasKeyPressed('E')) rotateType = rotateType == SHOWCASE::SQUAD ? SHOWCASE::SLERP : SHOWCASE::SQUAD;

    if (DXUTWasKeyPressed(VK_ESCAPE)) Root::GetInstance()->RootExit();
    if (DXUTWasKeyPressed('N')) Root::GetInstance()->ReloadSceneManager("SquadApp");
    if (DXUTWasKeyPressed('M')) Root::GetInstance()->ReloadSceneManager("GameApp");

    if (DXUTIsKeyDown(VK_SPACE)) node->setTranslate(Vector3(0, 1, 0));
    if (DXUTIsKeyDown(VK_SHIFT)) node->setTranslate(Vector3(0, -1, 0));
}

void SquadApp::Render()
{
    SceneManager::Render();
}

void SquadApp::Exit()
{
    SceneManager::Exit();
}

void SquadApp::CreatePoint()
{
    catmull_list.push_back(Vector3(points * 100, rand() % 50 + 1, rand() % 50 + 1));

    Tipp7::SceneNode* sphere = this->createChildSceneNode("sphere");
    Tipp7::Entity* sp = this->createEntity("Sphere", L"Models/SphereModel.x");
    sp->SetTexture(dynamic_cast<Texture2D*>(RM::GetInstance()->GetResources("red")));
    sphere->setScale(0.03f,0.03f,0.03f);
    sphere->attachObject(sp);
    sphere->setPosition(catmull_list[catmull_list.size()-1]);
    points++;

    Vector3 n(0, 0, 0);
    Vector3 cross(0, 1, 0);
    D3DXMATRIX View;
    if (quaternion_list.size() >= 1)
    {
        n = *D3DXVec3Normalize(&n, &(catmull_list[catmull_list.size() - 1] - catmull_list[catmull_list.size() - 2]));
        View = *D3DXMatrixLookAtLH(&View, &catmull_list[catmull_list.size() - 1], &(catmull_list[catmull_list.size() - 1] + n), &cross);
    }
    View._41 = 0;
    View._42 = 0;
    View._43 = 0;
    D3DXMatrixTranspose(&View, &View);
    D3DXQUATERNION q = *D3DXQuaternionRotationMatrix(&q, &View);
    D3DXQuaternionNormalize(&q, &q);
    quaternion_list.push_back(q);
}

void SquadApp::SettingSquad()
{
    D3DXQUATERNION temp;
    D3DXQuaternionSquadSetup(&s0, &s1, &temp, &quaternion_list[0 + circle], &quaternion_list[1 + circle], &quaternion_list[2 + circle], &quaternion_list[3 + circle]);
}
