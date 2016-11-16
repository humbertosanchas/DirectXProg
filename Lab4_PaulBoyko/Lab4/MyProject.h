#ifndef _MyProject_h
#define _MyProject_h

#include "DirectX.h"
#include "Font.h"
#include "TextureType.h"
#include "IndexedPrimitive.h"
#include "Diamond.h"
#include "EightSidedThing.h"
#include "PointyShape.h"
//Paul Boyko Nov 16 2016
//Drawing 3D Shapes with Index and Vertex Buffer
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

	IndexedPrimitive indexPrim;
	Diamond diamond;
	EightSidedThing eightSideThing;
	PointyShape pointyShape;


	float rotation;

	Matrix worldMatrix;
	Matrix diamondWorldMatrix;
	Matrix eightSideThingWorldMatrix;
	Matrix pointyShapeWorldMatrix;
	Matrix treeTrunkWorldMatrix;
	Matrix treeTopWorldMatrix;
	Matrix viewMatrix;
	Matrix projectionMatrix;

	// mouse variables
	Vector2 mousePos;
	Vector2 mouseDelta;
	bool buttonDown;

	// for camera controls
	Vector3 cameraPos;
	Vector2 cameraRotationSpeed;
	Vector2 cameraRotation;
	float cameraRadius;
	float cameraRadiusSpeed;

	void UpdateCamera(float deltaTime);

	// call when the mouse is released
	void OnMouseDown();
	void OnMouseMove();

};

#endif