//
// BGTD 9201
//	Source file for the unlit colour shader
//
//

#include <D3Dcompiler.h>
#include "UnlitColourShader.h"

//
// Aligns with the constants inside the shader
//
struct ShaderConstants
{
	Matrix	worldMatrix;
	Matrix  viewMatrix;
	Matrix  projectionMatrix;
	Matrix  worldViewProjectionMatrix;
};


//-----------------------------------------------------
//-----------------------------------------------------
UnlitColourShader::UnlitColourShader()
{
	pVertexShaderBlob = nullptr;
	pVertexShader = nullptr;
	pPixelShaderBlob = nullptr;
	pPixelShader = nullptr;
	pConstantBuffer = nullptr;
}

//-----------------------------------------------------
//-----------------------------------------------------
UnlitColourShader::~UnlitColourShader()
{
	if (pVertexShaderBlob) pVertexShaderBlob->Release();
	if (pVertexShader) pVertexShader->Release();
	if (pPixelShaderBlob) pPixelShaderBlob->Release();
	if (pPixelShader) pPixelShader->Release();
	if (pConstantBuffer) pConstantBuffer->Release();
}

//-----------------------------------------------------
// load and create the shader
//-----------------------------------------------------
void UnlitColourShader::LoadShader(ID3D11Device* pDevice)
{
	// load the vertex shader
	HRESULT hr = D3DReadFileToBlob(L"UnlitColourVS.cso", &pVertexShaderBlob);
	if (FAILED(hr))
	{
		OutputDebugString(L"Couldn't load vertex shader");
		assert(0);
		return;
	}

	// load the pixel shader
	hr = D3DReadFileToBlob(L"UnlitColourPS.cso", &pPixelShaderBlob);
	if (FAILED(hr))
	{
		OutputDebugString(L"Couldn't load pixel shader");
		assert(0);
		return;
	}

	// Create the shaders
	hr = pDevice->CreateVertexShader(pVertexShaderBlob->GetBufferPointer(), pVertexShaderBlob->GetBufferSize(), NULL, &pVertexShader);
	if (FAILED(hr))
	{
		OutputDebugString(L"Couldn't create vertex shader");
		assert(0);
		return;
	}

	hr = pDevice->CreatePixelShader(pPixelShaderBlob->GetBufferPointer(), pPixelShaderBlob->GetBufferSize(), NULL, &pPixelShader);
	if (FAILED(hr))
	{
		OutputDebugString(L"Couldn't create vertex shader");
		assert(0);
		return;
	}


	// ShaderConstants create some initial data
	ShaderConstants initData;

	// Create the constant buffer
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(ShaderConstants);
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = &initData;
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;


	hr = pDevice->CreateBuffer(&bufferDesc, &data, &pConstantBuffer);
	if (FAILED(hr))
	{
		OutputDebugString(L"Couldn't create constant buffer");
		assert(0);
		return;
	}



}

//-----------------------------------------------------
// get the information for the shader
//-----------------------------------------------------
const void * UnlitColourShader::GetVertexShaderBinary()
{
	if (pVertexShaderBlob != nullptr)
	{
		return pVertexShaderBlob->GetBufferPointer();
	}
	return nullptr;
}
size_t	UnlitColourShader::GetVertexShaderBinarySize()
{
	if (pVertexShaderBlob != nullptr)
	{
		return pVertexShaderBlob->GetBufferSize();
	}
	return 0;

}

//-----------------------------------------------------
// set the shaders
//-----------------------------------------------------
void UnlitColourShader::SetShaders(ID3D11DeviceContext* pContext, const Matrix& world, const Matrix& view, const Matrix& projection)
{
	// tell direct x to update the constants inside the shader
	D3D11_MAPPED_SUBRESOURCE constantResource;

	// gets a pointer to write constants to
	pContext->Map(pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &constantResource);
	ShaderConstants* pConstants = (ShaderConstants*) constantResource.pData;

	// when setting the matrices we need to transpose them because the expected order is different in shaders than on CPU
	pConstants->worldMatrix = world.Transpose();
	pConstants->viewMatrix = view.Transpose();
	pConstants->projectionMatrix = projection.Transpose();
	pConstants->worldViewProjectionMatrix = (world*view*projection).Transpose();

	// commit the changes
	pContext->Unmap(pConstantBuffer, 0);


	// set the shader
	pContext->VSSetShader(pVertexShader, NULL, 0);
	pContext->PSSetShader(pPixelShader, NULL, 0);

	// set the shader constants
	pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
}


