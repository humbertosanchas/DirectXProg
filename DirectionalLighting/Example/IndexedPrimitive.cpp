//
// BGTD 9201
//	Class that represents a simple IndexedPrimitive
//

#include "IndexedPrimitive.h"
#include <DirectXColors.h>
#include <VertexTypes.h>
#include <vector>

static bool faceNormals = true;



// Temporary collection types used when generating the geometry.
typedef std::vector<VertexPositionNormalColor> VertexCollection;
typedef std::vector<uint16_t> IndexCollection;

// create a 20-sided sphere like object
static void CreateIcosahedron(VertexCollection& vertices, IndexCollection& indices, float size)
{

	static const float  t = 1.618033988749894848205f; // (1 + sqrt(5)) / 2
	static const float t2 = 1.519544995837552493271f; // sqrt( 1 + sqr( (1 + sqrt(5)) / 2 ) )

	static const XMVECTORF32 verts[12] =
	{
		{ t / t2, 1.f / t2, 0 },
		{ -t / t2, 1.f / t2, 0 },
		{ t / t2, -1.f / t2, 0 },
		{ -t / t2, -1.f / t2, 0 },
		{ 1.f / t2, 0, t / t2 },
		{ 1.f / t2, 0, -t / t2 },
		{ -1.f / t2, 0, t / t2 },
		{ -1.f / t2, 0, -t / t2 },
		{ 0, t / t2, 1.f / t2 },
		{ 0, -t / t2, 1.f / t2 },
		{ 0, t / t2, -1.f / t2 },
		{ 0, -t / t2, -1.f / t2 }
	};

	static const uint32_t faces[20 * 3] =
	{
		0, 8, 4,
		0, 5, 10,
		2, 4, 9,
		2, 11, 5,
		1, 6, 8,
		1, 10, 7,
		3, 9, 6,
		3, 7, 11,
		0, 10, 8,
		1, 8, 10,
		2, 9, 11,
		3, 11, 9,
		4, 2, 0,
		5, 0, 2,
		6, 1, 3,
		7, 3, 1,
		8, 6, 4,
		9, 4, 6,
		10, 5, 7,
		11, 7, 5
	};

	for (size_t j = 0; j < _countof(faces); j += 3)
	{
		uint32_t v0 = faces[j];
		uint32_t v1 = faces[j + 1];
		uint32_t v2 = faces[j + 2];

		XMVECTOR normal;
		if (faceNormals)
		{
			normal = XMVector3Cross(verts[v1].v - verts[v0].v, verts[v2].v - verts[v0].v);
			normal = XMVector3Normalize(normal);
		}

		size_t base = vertices.size();
		indices.push_back(base);
		indices.push_back(base + 1);
		indices.push_back(base + 2);

		// Duplicate vertices to use face normals
		XMVECTOR position = XMVectorScale(verts[v0], size);
		if (!faceNormals) normal = XMVector3Normalize(position);
		vertices.push_back(VertexPositionNormalColor(position, normal, DirectX::Colors::White));

		position = XMVectorScale(verts[v1], size);
		if (!faceNormals) normal = XMVector3Normalize(position);
		vertices.push_back(VertexPositionNormalColor(position, normal, DirectX::Colors::White));

		position = XMVectorScale(verts[v2], size);
		if (!faceNormals) normal = XMVector3Normalize(position);
		vertices.push_back(VertexPositionNormalColor(position, normal, DirectX::Colors::White));
	}

	assert(vertices.size() == 20 * 3);
	assert(indices.size() == 20 * 3);
}


// ------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------
IndexedPrimitive::IndexedPrimitive()
{
	pVertexBuffer = nullptr;
	pInputLayout = nullptr;
	pIndexBuffer = nullptr;

	numVerts = 0;
	numIndices = 0;
}

// ------------------------------------------------------------------------------------
//
// ------------------------------------------------------------------------------------
IndexedPrimitive::~IndexedPrimitive()
{
	// Make sure we clean up what ever we allocated!
	if (pVertexBuffer != nullptr)
	{
		pVertexBuffer->Release();
		pVertexBuffer = nullptr;
	}
	if (pIndexBuffer != nullptr)
	{
		pIndexBuffer->Release();
		pIndexBuffer = nullptr;
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
void IndexedPrimitive::InitializeGeometry(ID3D11Device* pDevice)
{
	// build the icosahedron
	VertexCollection vertices;
	IndexCollection indices;
	CreateIcosahedron(vertices, indices, 1.0f);

	//
	numVerts = vertices.size();
	numIndices = indices.size();


	// describe the vertex buffer we are trying to create
	D3D11_BUFFER_DESC desc;
	desc.ByteWidth = numVerts * sizeof(VertexPositionNormalColor);
	desc.Usage = D3D11_USAGE_IMMUTABLE;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	// setup the subresource data - tells D3D what data to use to initialize
	// the vertexbuffer with
	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = vertices.data();

	// create the vertex buffer
	HRESULT hr = pDevice->CreateBuffer(&desc, &data, &pVertexBuffer);
	if (FAILED(hr))
	{
		OutputDebugString(L"FAILED TO CREATE VERTEX BUFFER");
		assert(false);
	}


	// set up  the index buffer
	D3D11_BUFFER_DESC indexBufferDesc;
	indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	indexBufferDesc.ByteWidth = numIndices * sizeof(uint16_t);
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = indices.data();

	hr = pDevice->CreateBuffer(&indexBufferDesc, &indexData, &pIndexBuffer);
	if (FAILED(hr))
	{
		OutputDebugString(L"FAILED TO CREATE INDEX BUFFER");
		assert(false);
	}
}

// ------------------------------------------------------------------------------------
// Initialzes the shaders
// ------------------------------------------------------------------------------------
void IndexedPrimitive::InitializeInputLayout(ID3D11Device* pDevice, const void* pBinary, size_t binarySize)
{
	// create the input layout
	HRESULT hr = pDevice->CreateInputLayout(VertexPositionNormalColor::InputElements,
		VertexPositionNormalColor::InputElementCount,
		pBinary, binarySize,
		&pInputLayout);
	if (FAILED(hr))
	{
		OutputDebugString(L"Failed to create input layout");
		assert(0);
	}
}

// ------------------------------------------------------------------------------------
// Draw the IndexedPrimitive
// ------------------------------------------------------------------------------------
void IndexedPrimitive::Draw(ID3D11DeviceContext* pDeviceContext)
{
	// Set up our input layout
	pDeviceContext->IASetInputLayout(pInputLayout);

	//  tell D3D we are drawing a triangle list
	pDeviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//  Tell the device which vertex buffer we are using
	UINT stride = sizeof(VertexPositionNormalColor);
	UINT offset = 0;
	pDeviceContext->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);

	// Set the index buffer
	pDeviceContext->IASetIndexBuffer(pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	//	tell it to draw the primitive
	pDeviceContext->DrawIndexed(numIndices, 0, 0);
}


