#include "DXUT.h"
#include "SceneNode.h"

USING(Tipp7)

void SceneNode::attachObject(MovableObject* _obj)
{
    if (find(movablegroup.begin(), movablegroup.end(), _obj) != movablegroup.end())
    {
        cout << "Already MovableObject is Attached!" << endl;
        return;
    }
    cout << "Attach Success! : " << _obj->movableName << endl;
    _obj->node = (Node*)this;
    movablegroup.push_back(_obj);
}

void SceneNode::detachObject(MovableObject* _obj)
{
    if (find(movablegroup.begin(), movablegroup.end(), _obj) != movablegroup.end())
    {
        cout << "Detach Success! : " << _obj->movableName << endl;
        movablegroup.remove(_obj);
        return;
    }
    cout << "Detach Failed!! Could not find object : " << _obj->movableName << endl;
}

MovableObject* SceneNode::getAttachObject(const string _movableName)
{
    for (auto& it : movablegroup)
    {
        if (it->movableName._Equal(_movableName))
            return it;
    }
    cout << "Could not Find MovableObject : " << _movableName << endl;
    return nullptr;
}


SceneNode* SceneNode::createChildSceneNode(const string _nodeName)
{
    SceneNode* scnNode = new SceneNode();
    scnNode->nodeName = _nodeName;
    scnNode->parent = (Node*)this; // Parent Setting
    for (auto& it : childgroup)
    {
        if (it->nodeName._Equal(_nodeName))
        {
            cout << "This name is Already added : " << _nodeName << endl;
            scnNode->nodeName = _nodeName + "_copy";
        }
    }
    childgroup.push_back(scnNode);
    scnNode->Init();
    return scnNode;
}


SceneNode* SceneNode::GetChild(const string nodeName)
{
    if (childgroup.size() == 0) {
        cout << "childgroup's size is ZERO" << endl;
        return nullptr;
    }
    for (auto& it : childgroup)
    {
        if(it->nodeName._Equal(nodeName))
            return dynamic_cast<SceneNode*>(it);
    }
    cout << "Could not Find Children : " << nodeName << endl;
}

void SceneNode::Init(void)
{
    cout << "SceneNode " << nodeName << " is Initialized" << endl;
    cout << "And parent is ";
    if (parent != nullptr)
        cout << parent->nodeName << endl;
    else cout << "nullptr" << endl;
}

void SceneNode::Update(void)
{
    Node::Update();
    for (auto it : movablegroup)
    {
        if(it->activeSelf())
            it->Update();
    }
}

void SceneNode::Render(void)
{
    Node::Render();
    for (auto it : movablegroup)
    {
        if (it->activeSelf())
            it->Render();
    }
}

void SceneNode::Exit(void)
{
}
