#ifndef _MyProject_h
#define _MyProject_h

#include "DirectX.h"
#include "Font.h"
#include "TextureType.h"
#include <GeometricPrimitive.h>

// forward declare the sprite batch

using namespace DirectX;
using namespace DirectX::SimpleMath;


//----------------------------------------------------------------------------------------------
// Main project class
//	Inherits the directx class to help us initalize directX
//----------------------------------------------------------------------------------------------

class MyProject : public DirectXClass
{
public:
	// constructor
	MyProject(HINSTANCE hInstance);
	~MyProject();

	// Initialize any directX objects
	void InitializeObjects();

	// window message handler
	LRESULT ProcessWindowMessages(UINT msg, WPARAM wParam, LPARAM lParam);

	// Called by the render loop to render a single frame
	void Render(void);

	// Called by directX framework to allow you to update any scene objects
	void Update(float deltaTime);

	// Compute the view and projection matrices
	void ComputeViewProjection();

private:

	// geometric primtive
	std::unique_ptr<GeometricPrimitive> primitive;

	Matrix worldMatrix;
	Matrix viewMatrix;
	Matrix projectionMatrix;

	float rotation;

	// mouse variables
	Vector2 mousePos;
	Vector2 mouseDelta;
	bool buttonDown;

	Vector3 cameraPos;
	bool wireFrame;

	// call when the mouse is released
	void OnMouseDown();
	void OnMouseMove();

};

#endif