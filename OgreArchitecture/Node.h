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

	Vector3 position;
	Vector3 scale;
	Vector3 rotation;

	D3DXMATRIX worldToMatrix;

	bool isActive = true;
	constexpr bool activeSelf() { return isActive; };

	void setPosition(const float x = 0.0f, const float y = 0.0f, const float z = 0.0f);
	void setScale(const float x = 0.0f, const float y = 0.0f, const float z = 0.0f);
	void yaw(const float amount);
	void pitch(const float amount);
	void roll(const float amount);

	D3DXMATRIX& GetWorldMatrix(const Vector3& _position, const Vector3& _rotation, const Vector3& _scale) const;
	D3DXMATRIX& GetMatrix() const;

	virtual void Update(void);
	virtual void Render(void);
};

END