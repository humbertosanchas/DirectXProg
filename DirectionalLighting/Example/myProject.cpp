#include "MyProject.h"
#include <Windowsx.h> // for GET__LPARAM macros
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <DirectXColors.h>
#include <sstream>
#include <CommonStates.h>


using namespace DirectX;
using namespace DirectX::SimpleMath;

// helper function
//
// returns a random float between 0 & 1
float RandFloat() { return float(rand())/float(RAND_MAX); } 

static const float CAMERA_SPEED = XM_PI * 0.2f;

//----------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nShowCmd)
{
	MyProject application(hInstance);    // Create the class variable

	if( application.InitWindowsApp(L"DirectX 3D", nShowCmd) == false )    // Initialize the window, if all is well show and update it so it displays
	{
		return 0;                   // Error creating the window, terminate application
	}

	if( application.InitializeDirect3D() )
	{
		application.SetDepthStencil(true);      // Tell DirectX class to create and maintain a depth stencil buffer
		application.InitializeObjects();
		application.MessageLoop();				// Window has been successfully created, start the application message loop
	}

	return 0;
}

//----------------------------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------------------------
MyProject::MyProject(HINSTANCE hInstance)
	: DirectXClass(hInstance)
{
	mousePos = Vector2(clientWidth * 0.5f, clientHeight * 0.5f);
	buttonDown = false;
	
	ClearColor = Color(DirectX::Colors::Black.v);

	cameraPos = Vector3(0, 0, 6);

	cameraRadius = 8;
	cameraRadiusSpeed = 0;

	cameraRotation = Vector2::Zero;
	cameraRotationSpeed = Vector2::Zero;

	lightYaw = 0;
	lightPitch = 0;
}

//----------------------------------------------------------------------------------------------
// Destructor
//----------------------------------------------------------------------------------------------
MyProject::~MyProject()
{
}

//----------------------------------------------------------------------------------------------
// Initialize any fonts we need to use here
//----------------------------------------------------------------------------------------------
void MyProject::InitializeObjects()
{
	// load the shader
	shader.LoadShader(D3DDevice);

	worldMatrix = Matrix(); // identity matrix

	primitive.InitializeGeometry(D3DDevice);
	primitive.InitializeInputLayout(D3DDevice, shader.GetVertexShaderBinary(), shader.GetVertexShaderBinarySize());

}

//----------------------------------------------------------------------------------------------
// Window message handler
//----------------------------------------------------------------------------------------------
LRESULT MyProject::ProcessWindowMessages(UINT msg, WPARAM wParam, LPARAM lParam)
{
	// for mouse positions
	Vector2 pos((float)GET_X_LPARAM(lParam), (float)GET_Y_LPARAM(lParam));

	switch (msg )
	{
	case WM_MOUSEMOVE:
		mouseDelta = pos - mousePos;
		mousePos = pos;
		OnMouseMove();
		return 0;
	case WM_LBUTTONUP:
		buttonDown = false;
		mouseDelta = pos - mousePos;
		mousePos = pos;
		break;
	case WM_LBUTTONDOWN:
		buttonDown = true;
		mouseDelta = pos - mousePos;
		mousePos = pos;
		OnMouseDown();
		break;
	case WM_KEYUP:
		if (wParam >= '0' && wParam <= '4')
		{
			PresentInterval = wParam - '0';
		}
		else if (wParam == VK_UP)	{	cameraRotationSpeed.y = 0;	}
		else if (wParam == VK_DOWN) {	cameraRotationSpeed.y = 0; }
		else if (wParam == VK_LEFT) {	cameraRotationSpeed.x = 0; }
		else if (wParam == VK_RIGHT){	cameraRotationSpeed.x = 0; }
		else if (wParam == VK_ADD)  {	cameraRadiusSpeed = 0; }
		else if (wParam == VK_SUBTRACT)  { cameraRadiusSpeed = 0; }
		else if (wParam == VK_SPACE)
		{
			cameraRotation = Vector2::Zero;
			cameraRadius   = 6;
		}

		else if (wParam == 'R') { shader.SetAmbientLight(Colors::Red.v); }
		else if (wParam == 'G') { shader.SetAmbientLight(Colors::Green.v);  }
		else if (wParam == 'B') { shader.SetAmbientLight(Colors::Blue.v); }
		else if (wParam == 'W') { shader.SetAmbientLight(Colors::White.v); }
		else if (wParam == 'K') { shader.SetAmbientLight(Colors::DarkGray.v); }


		break;
	case WM_KEYDOWN:
		if (wParam == VK_UP)	{ cameraRotationSpeed.y = CAMERA_SPEED; }
		else if (wParam == VK_DOWN) { cameraRotationSpeed.y = -CAMERA_SPEED; }
		else if (wParam == VK_LEFT) { cameraRotationSpeed.x = -CAMERA_SPEED; }
		else if (wParam == VK_RIGHT){ cameraRotationSpeed.x = CAMERA_SPEED; }
		else if (wParam == VK_ADD)  { cameraRadiusSpeed = -1.0f; }
		else if (wParam == VK_SUBTRACT)  { cameraRadiusSpeed = 1.0f; }
		break;

	}

	// let the base class handle remaining messages
	return DirectXClass::ProcessWindowMessages(msg, wParam, lParam);
}

//----------------------------------------------------------------------------------------------
// Called by the render loop to render a single frame
//----------------------------------------------------------------------------------------------
void MyProject::Render(void)
{
	// calculate camera matrices
	ComputeViewProjection();

	// set up the shader
	shader.SetShaders(DeviceContext, worldMatrix, viewMatrix, projectionMatrix);

	// draw the primitive
	primitive.Draw(DeviceContext);

	// render the base class
	DirectXClass::Render();
}

//----------------------------------------------------------------------------------------------
// Called every frame to update objects.
//	deltaTime: how much time in seconds has elapsed since the last frame
//----------------------------------------------------------------------------------------------
void MyProject::Update(float deltaTime)
{
	UpdateCamera(deltaTime);


	// update the yaw of the light at 4 seconds / revolution
	lightYaw = lightYaw + deltaTime * 90.0f * XM_PI / 180.0f;

	// calculate the facing direction using the updated yaw
	Vector3 dir = Matrix::CreateFromYawPitchRoll(lightYaw, lightPitch, 0).Forward();

	// set the directional light
	shader.SetDirectionalLight(Color(0.6f, 0.7f, 0.8f), dir);


}


//----------------------------------------------------------------------------------------------
// Called when the mouse is released
//----------------------------------------------------------------------------------------------
void MyProject::OnMouseDown()
{

	// this is called when the left mouse button is clicked
	// mouse position is stored in mousePos variable
}

//----------------------------------------------------------------------------------------------
// Called when the mouse is moved
//----------------------------------------------------------------------------------------------
void MyProject::OnMouseMove()
{
}

//----------------------------------------------------------------------------------------------
// Computes the view and camera matrix
//----------------------------------------------------------------------------------------------
void MyProject::ComputeViewProjection()
{
	viewMatrix = Matrix::CreateLookAt(cameraPos, Vector3::Zero, Vector3::UnitY);
	projectionMatrix = Matrix::CreatePerspectiveFieldOfView(60.0f * XM_PI / 180.0f, (float)clientWidth / (float)clientHeight, 1, 20);
}

//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
void MyProject::UpdateCamera(float deltaTime)
{
	const float VERT_LIMIT = XM_PI * 0.35f;

	// update the radius
	cameraRadius += cameraRadiusSpeed * deltaTime;
	if (cameraRadius < 1) cameraRadius = 1;


	// update the rotation amounts
	cameraRotation += cameraRotationSpeed * deltaTime;

	// clamp the vertical rotation
	if (cameraRotation.y < -VERT_LIMIT) cameraRotation.y = -VERT_LIMIT;
	else if (cameraRotation.y > VERT_LIMIT) cameraRotation.y = VERT_LIMIT;

	// calculate the height
	cameraPos.y = cameraRadius * sinf(cameraRotation.y);
	float r = cameraRadius * cosf(cameraRotation.y);

	// calculate the orbit
	cameraPos.x = sinf(cameraRotation.x) * r;
	cameraPos.z = cosf(cameraRotation.x) * r;
}