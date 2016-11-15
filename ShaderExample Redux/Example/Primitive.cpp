//
// BGTD 9201
//	Class that represents a simple primitive
//

#include "Primitive.h"
#include <DirectXColors.h>

// Step 1
//  Define the structure
struct VertexPositionColor
{
	Vector3 position;
	Color   color;
};


// Step 2
//  Create an array of vertices
const int NUM_VERTS = 3;
VertexPositionColor vertices[NUM_VERTS] =
{
	{ Vector3(0.0f, 1.0f, 0.0f), Colors::Red.v },
	{ Vector3(1.0f, -1.0f, 0.0f), Colors::Green.v },
	{ Vector3(-1.0f, -1.0f, 0.0f), Colors::Blue.v }
};

// ------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------
Primitive::Primitive()
{
	pVertexBuffer = nullptr;
	pInputLayout = nullptr;
}

// ------------------------------------------------------------------------------------
//
// ------------------------------------------------------------------------------------
Primitive::~Primitive()
{
	// Make sure we clean up what ever we allocated!
	if (pVertexBuffer != nullptr)
	{
		pVertexBuffer->Release();
		pVertexBuffer = nullptr;
	}

	if (pInputLayout != nullptr)
	{
		pInputLayout->Release();
		pInputLayout = nullptr;
	}
}

// ------------------------------------------------------------------------------------
// Initialize the vertex buffer
// ------------------------------------------------------------------------------------
void Primitive::InitializeGeometry(ID3D11Device* pDevice)
{
	// Step 3
	// Create the buffer

	// describe the vertex buffer we are trying to create
	D3D11_BUFFER_DESC desc;
	desc.ByteWidth = NUM_VERTS * sizeof(VertexPositionColor);
	desc.Usage = D3D11_USAGE_IMMUTABLE;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	// setup the subresource data - tells D3D what data to use to initialize
	// the vertexbuffer with
	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = vertices;

	// create the vertex buffer
	HRESULT hr = pDevice->CreateBuffer(&desc, &data, &pVertexBuffer);
	if (FAILED(hr))
	{
		OutputDebugString(L"FAILED TO CREATE VERTEX BUFFER");
		assert(false);
	}
}

// ------------------------------------------------------------------------------------
// Initialzes the shaders
// ------------------------------------------------------------------------------------
void Primitive::InitializeInputLayout(ID3D11Device* pDevice, const void* vsBinary, size_t vsBinarySize)
{
	//	Define the vertex input layout
	D3D11_INPUT_ELEMENT_DESC layoutDesc[] =
	{
		// first input element: position
		{ "SV_Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	// create the input layout object
	HRESULT hr = pDevice->CreateInputLayout(
		layoutDesc, 2,
		vsBinary, vsBinarySize,
		&pInputLayout
		);
	if (FAILED(hr))
	{
		OutputDebugString(L"Could not create input layout");
		assert(false);
	}
}

// ------------------------------------------------------------------------------------
// Draw the primitive
// ------------------------------------------------------------------------------------
void Primitive::Draw(ID3D11DeviceContext* pDeviceContext)
{
	// Set up our input layout
	pDeviceContext->IASetInputLayout(pInputLayout);

	//  tell D3D we are drawing a triangle list
	pDeviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//  Tell the device which vertex buffer we are using
	UINT stride = sizeof(VertexPositionColor);
	UINT offset = 0;
	pDeviceContext->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);

	// Step 11
	//	tell it to draw the first three vertices
	pDeviceContext->Draw(NUM_VERTS, 0);
}


