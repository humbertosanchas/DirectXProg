//
// BGTD 9201
//	Source file for the unlit colour shader
//
//

#include <D3Dcompiler.h>
#include "LitColourShader.h"
#include <DirectXColors.h>

using namespace DirectX;

//
// Aligns with the constants inside the shader
//
struct ShaderConstants
{
	Matrix	worldMatrix;
	Matrix  viewMatrix;
	Matrix  projectionMatrix;
	Matrix  worldViewProjectionMatrix;
	Matrix  worldMatrixIT;
};



//-----------------------------------------------------
//-----------------------------------------------------
LitColourShader::LitColourShader()
{
	pVertexShaderBlob = nullptr;
	pVertexShader = nullptr;
	pPixelShaderBlob = nullptr;
	pPixelShader = nullptr;
	pConstantBuffer = nullptr;
	lightingValues.ambientLight = Color(0.2f, 0.2f, 0.2f, 1.0f);
	lightingValues.directionalLightColor = Colors::LightBlue.v;
	lightingValues.directionalLightVector = Vector4(1, 0, 0, 0);
}

//-----------------------------------------------------
//-----------------------------------------------------
LitColourShader::~LitColourShader()
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
void LitColourShader::LoadShader(ID3D11Device* pDevice)
{
	// load the vertex shader
	HRESULT hr = D3DReadFileToBlob(L"LitColourVS.cso", &pVertexShaderBlob);
	if (FAILED(hr))
	{
		OutputDebugString(L"Couldn't load vertex shader");
		assert(0);
		return;
	}

	// load the pixel shader
	hr = D3DReadFileToBlob(L"LitColourPS.cso", &pPixelShaderBlob);
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

	// create the lights buffer
	LightConstants lightConstants;
	lightConstants.ambientLight = DirectX::Colors::LightYellow.v;

	bufferDesc.ByteWidth = sizeof(lightConstants);
	data.pSysMem = &lightConstants;

	hr = pDevice->CreateBuffer(&bufferDesc, &data, &pLightsBuffer);
	if (FAILED(hr))
	{
		OutputDebugString(L"Couldn't create lights buffer");
		assert(0);
		return;
	}



}

//-----------------------------------------------------
// get the information for the shader
//-----------------------------------------------------
const void * LitColourShader::GetVertexShaderBinary()
{
	if (pVertexShaderBlob != nullptr)
	{
		return pVertexShaderBlob->GetBufferPointer();
	}
	return nullptr;
}
size_t	LitColourShader::GetVertexShaderBinarySize()
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
void LitColourShader::SetShaders(ID3D11DeviceContext* pContext, const Matrix& world, const Matrix& view, const Matrix& projection)
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
	pConstants->worldMatrixIT = world.Invert(); // .Transpose().Transpose() cancels out

	// commit the changes
	pContext->Unmap(pConstantBuffer, 0);


	// if the lights have change, up load them as well
	if (lightsDirty)
	{
		pContext->Map(pLightsBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &constantResource);

		LightConstants* pLightConstants = (LightConstants*)constantResource.pData;
		*pLightConstants = lightingValues;

		pContext->Unmap(pLightsBuffer, 0);
		lightsDirty = false;
	}



	// set the shader
	pContext->VSSetShader(pVertexShader, NULL, 0);
	pContext->PSSetShader(pPixelShader, NULL, 0);

	// set the shader constants - matrices at 0, lights at 1
	pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
	pContext->VSSetConstantBuffers(1, 1, &pLightsBuffer);
	pContext->PSSetConstantBuffers(0, 1, &pConstantBuffer);
	pContext->PSSetConstantBuffers(1, 1, &pLightsBuffer);
}

//-----------------------------------------------------
// Sets the ambient light color
//-----------------------------------------------------
void LitColourShader::SetAmbientLight(Color clr)
{
	lightsDirty = true;
	lightingValues.ambientLight = clr;

}


//-----------------------------------------------------
// Sets the directional light
//-----------------------------------------------------
void LitColourShader::SetDirectionalLight(Color clr, Vector3 direction)
{
	lightsDirty = true;
	lightingValues.directionalLightColor = clr;

	// flip the direction of the vector so aligning with the normal is brightest
	lightingValues.directionalLightVector = Vector4(-direction.x, -direction.y, -direction.z, 0);

}


