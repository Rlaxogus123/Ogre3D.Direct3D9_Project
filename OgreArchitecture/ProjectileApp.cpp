#include "DXUT.h"
#include "ProjectileApp.h"
#include "CollisionManager.h"
#include "MyMath.h"

USING(Tipp7)

ProjectileApp::ProjectileApp(void)
{
    this->setAmbientLight(1, 1, 1);
}

void ProjectileApp::Init()
{
    SceneManager::Init();
    this->setAmbientLight(1, 1, 1);

    Tipp7::SceneNode* n_camera = this->createChildSceneNode("MainCamera");
    Tipp7::Camera* cam = this->createCamera("myCam");
    n_camera->attachObject(cam);
    n_camera->setPosition(0, 5, 0);

    MeshManager::GetInstance()->createPlane(
        "ground",
        4000, 4000, 100, 100,
        70, 70
    );

    Tipp7::SceneNode* n_ground = this->createChildSceneNode("n_ground");
    Tipp7::Entity* groundEntity = this->createEntity("groundEntity", "ground");
    groundEntity->SetTexture(dynamic_cast<Texture2D*>(RM::GetInstance()->GetResources("brick1")));
    n_ground->attachObject(groundEntity);
    n_ground->setPosition(0, 0, 0);

    Tipp7::SceneNode* n_arrow = this->createChildSceneNode("n_arrow");
    Tipp7::Entity* arrowEntity = this->createEntity("arrowEntity", L"Models/MyArrow.x");
    arrowEntity->SetTexture(dynamic_cast<Texture2D*>(RM::GetInstance()->GetResources("red")));
    n_arrow->attachObject(arrowEntity);
    n_arrow->setScale(0.2, 0.1, 0.1);
    n_arrow->setPosition(0, 50, 50);

    Tipp7::SceneNode* n_sphere = this->createChildSceneNode("n_sphere");
    Tipp7::Entity* sphereEntity = this->createEntity("sphereEntity", L"Models/SphereModel.x");
    n_sphere->attachObject(sphereEntity);
    n_sphere->setScale(0.1, 0.1, 0.1);
    n_sphere->setPosition(firstPos);
    n_sphere->setBoundCircle(5);
    n_sphere->showBoundCircle(true);

    Tipp7::SceneNode* n_center = this->createChildSceneNode("n_center");
    Tipp7::Entity* sphereEntity2 = this->createEntity("sphereEntity2", L"Models/SphereModel.x");
    sphereEntity2->SetTexture(dynamic_cast<Texture2D*>(RM::GetInstance()->GetResources("red")));
    n_center->attachObject(sphereEntity2);
    n_center->setScale(0.03, 0.03, 0.03);

    Tipp7::SceneNode* n_pivot = this->createChildSceneNode("n_pivot");
    n_pivot->showBoundCircle(true);

    //Tipp7::SceneNode* n_childarrow = n_sphere->createChildSceneNode("n_arrow");
    //Tipp7::Entity* arrowEntity2 = this->createEntity("arrowEntity", L"Models/MyArrow.x");
    //arrowEntity2->SetTexture(dynamic_cast<Texture2D*>(RM::GetInstance()->GetResources("red")));
    //n_childarrow->attachObject(arrowEntity2);
    //n_childarrow->setScale(2,1,1);

    font0 = new Font2D(L"Arial", 3);
    font1 = new Font2D(L"Arial", 2, 700, Vector2(0, 50));
    font2 = new Font2D(L"Arial", 3, 700, Vector2(0, 200));
    font3 = new Font2D(L"Arial", 3, 700, Vector2(0, 250));

    for (int i = 0; i < 50; i++)
    {
        n_effect[i] = this->createChildSceneNode("n_effect" + i);
        effect[i] = this->createEntity("effect" + i, L"Models/SphereModel.x");
        effect[i]->SetTexture(dynamic_cast<Texture2D*>(RM::GetInstance()->GetResources("orange")));

        n_effect[i]->attachObject(effect[i]);
        n_effect[i]->setPosition(firstPos + Vector3(i * 10, 0, 0));
        n_effect[i]->setScale(0.02f, 0.02f, 0.02f);
    }
}

void ProjectileApp::Update()
{
    SceneManager::Update();

    SceneNode* sphere = this->getSceneNode("n_sphere");
    SceneNode* center = this->getSceneNode("n_center");
    SceneNode* pivot = this->getSceneNode("n_pivot");
    SceneNode* ground = this->getSceneNode("n_ground");
    SceneNode* cam = this->getSceneNode("MainCamera");
    SceneNode* arrow = this->getSceneNode("n_arrow");

    char buff[255];
    sprintf(buff, "TimeAmount : %.2f", timeAmount);
    font0->SetString(buff);
    sprintf(buff, "curTime : %.2f", time);
    font1->SetString(buff);
    sprintf(buff, "Angle : %d", angle);
    font2->SetString(buff);
    sprintf(buff, "Power : %.2f", power);
    font3->SetString(buff);

    if (DXUTWasKeyPressed('1')) timeAmount = 1;
    if (DXUTWasKeyPressed('2')) timeAmount = 2;
    if (DXUTWasKeyPressed('3')) timeAmount = 3;
    if (DXUTWasKeyPressed('4')) timeAmount = 4;
    if (DXUTWasKeyPressed('5')) timeAmount = 5;

    if (DXUTWasKeyPressed(VK_SPACE))
    {
        isFire = !isFire;
        if (!isFire) time = 0;
    }
    if (isFire) time += Time::deltaTime * timeAmount;

    if (DXUTIsKeyDown(VK_RIGHT)) power += Time::deltaTime * 20;
    if (DXUTIsKeyDown(VK_LEFT)) {
        if (power > 0) power -= Time::deltaTime * 20;
        else power = 0;
    }
    if (DXUTIsKeyDown(VK_UP))
    {
        angle++;
        if (angle > 90) angle = 90;
    }
    if (DXUTIsKeyDown(VK_DOWN)) {
        angle--;
        if (angle < 0) angle = 0;
    }

    arrow->roll(angle);
    D3DXMATRIX rot;
    Vector3 angleVector(power, 0, 0);
    D3DXMatrixRotationZ(&rot, D3DXToRadian(angle));
    D3DXVec3TransformCoord(&angleVector, &angleVector, &rot);

    //////////////////////////////
    float vAngle = atan2(angleVector.y, angleVector.x);
    float v = MyMath::myD3DXVec3Length(&angleVector);

    sphere->position.x = firstPos.x + (v * time * cos(vAngle));
    sphere->position.y = firstPos.y + ((v * time * sin(vAngle)) - (9.807f * (time * time) / 2));
    //////////////////////////////

    if (CollisionManager::GetInstance()->Sphere_VS_Plane(&sphere->getPosition(), sphere->boundCircle, &ground->getPosition(), &ground->getUp()))
    {
        isFire = false;
        time = 0;
    }

    for (int i = 0; i < 50; i++)
    {
        MyMath::myProjectileMotion(&n_effect[i]->position, &firstPos, &angleVector, i * 0.2f);
    }
    //float centerX = ((pow(v, 2) * sin(vAngle) * cos(vAngle)) / 9.807f);
    //float centerY = ((pow(v, 2) * pow(sin(vAngle), 2)) / (2 * 9.807f));
    //
    //float finalPivot = pow(centerX, 2) / (4 * centerY);
    //center->position.x = firstPos.x + centerX;
    //center->position.y = firstPos.y + centerY - finalPivot;
    //center->position.z = firstPos.z;
    //
    //pivot->position.x = firstPos.x + centerX;
    //pivot->position.y = firstPos.y + centerY - finalPivot;
    //pivot->position.z = firstPos.z;
    //pivot->setBoundCircle(finalPivot);


    if (DXUTIsKeyDown('W')) cam->setTranslate(cam->foward);
    if (DXUTIsKeyDown('S')) cam->setTranslate(-cam->foward);
    if (DXUTIsKeyDown('A')) cam->setTranslate(-cam->right);
    if (DXUTIsKeyDown('D')) cam->setTranslate(cam->right);

    if (pointlock)
    {
        D3DVIEWPORT9 viewPort;
        Vector3 screenPos;

        DEVICE->GetViewport(&viewPort);

        POINT preP;
        POINT p = { viewPort.Width / 2, viewPort.Height / 2 };
        GetCursorPos(&preP);
        ClientToScreen(DXUTGetHWND(), &p);

        if (preP.x > p.x)
        {
            float amount = preP.x - p.x;
            preP.x -= amount;
            cam->yaw(cam->getRotation().y + (amount * aimAmount));
        }
        if (preP.x < p.x)
        {
            float amount = p.x - preP.x;
            preP.x += amount;
            cam->yaw(cam->getRotation().y - (amount * aimAmount));
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
    if (DXUTWasKeyPressed('M')) Root::GetInstance()->ReloadSceneManager("TestApp");
    if (DXUTWasKeyPressed('N')) Root::GetInstance()->ReloadSceneManager("GameApp");

    if (DXUTWasKeyPressed(VK_F1)) pointlock = !pointlock;
    if (DXUTWasKeyPressed(VK_ESCAPE)) Root::GetInstance()->RootExit();
}

void ProjectileApp::Render()
{
    SceneManager::Render();
}

void ProjectileApp::Exit()
{
    SceneManager::Exit();
}
