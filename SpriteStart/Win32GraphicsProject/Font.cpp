#include <string>
#include "Font.h"

using namespace std;

//----------------------------------------------------------------------------------------------------------------
void FontType::PrintMessage(int posX, int posY, wstring message, DirectX::FXMVECTOR color)
{
	DirectX::XMFLOAT2 pos;
	pos.x = (float) posX;
	pos.y = (float) posY;

	pBatch->Begin();
	pFont->DrawString( pBatch, message.c_str(), pos, color );
	pBatch->End();
}

//----------------------------------------------------------------------------------------------------------------
void FontType::InitializeFont(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, wstring fileName)
{
	pBatch = new DirectX::SpriteBatch( pContext );
	pFont = new DirectX::SpriteFont( pDevice, fileName.c_str() );
}

//----------------------------------------------------------------------------------------------------------------
FontType::FontType(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, wstring fileName)
{
	InitializeFont(pDevice, pContext, fileName);
}

//----------------------------------------------------------------------------------------------------------------
FontType::FontType(void)
{
	pBatch = NULL;
	pFont = NULL;
}
//----------------------------------------------------------------------------------------------------------------
FontType::~FontType()
{
	delete pBatch;
	delete pFont;
}