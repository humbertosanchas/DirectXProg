//
// BGTD 9201 
//	Example of an unlit vertex coloured shader
//

#include <d3d11_1.h>
#include <SimpleMath.h>

using DirectX::SimpleMath::Matrix;

class UnlitColourShader
{
public:

	UnlitColourShader();
	~UnlitColourShader();

	// load and create the shader
	void LoadShader(ID3D11Device* pDevice);

	// get the information for the shader
	const void* GetVertexShaderBinary();
	size_t		GetVertexShaderBinarySize();

	// set the shaders
	void SetShaders(ID3D11DeviceContext* pContext, const Matrix& world, const Matrix& view, const Matrix& projection);

private:

	// data read from files
	ID3DBlob*			pVertexShaderBlob;
	ID3DBlob*			pPixelShaderBlob;

	// shaders
	ID3D11VertexShader* pVertexShader;
	ID3D11PixelShader*  pPixelShader;

	// constants
	ID3D11Buffer*		pConstantBuffer;

};


