#pragma once

NAMESPACE(Tipp7)

class Node
{
public:
	Node(void) {};
	virtual ~Node(void) {};

	list<Node*> childgroup;
	Node* parent = nullptr;
	string nodeName = "";

	Vector3 position = { 0,0,0 };
	Vector3 scale = { 1,1,1 };
	Vector3 rotation = { 0,0,0 };

	D3DXMATRIX& GetMatrix() const;
	D3DXMATRIX& GetEulerMatrix() const;

	bool isActive = true;
	constexpr bool activeSelf() { return isActive; };

	void setDirection(const Vector3 _dir);

	void setTranslate(const float x = 0.0f, const float y = 0.0f, const float z = 0.0f);
	void setTranslate(const Vector3 _vec);

	void setPosition(const float x = 0.0f, const float y = 0.0f, const float z = 0.0f);
	void setPosition(const Vector3 _vec);

	void setScale(const float x = 0.0f, const float y = 0.0f, const float z = 0.0f);
	void yaw(const float amount);
	void pitch(const float amount);
	void roll(const float amount);

	Vector3 getPosition() { return position; }
	Vector3 getScale()    { return scale; }
	Vector3 getRotation() { return rotation; }

	virtual void Update(void);
	virtual void Render(void);
	virtual void Exit(void);
};

END