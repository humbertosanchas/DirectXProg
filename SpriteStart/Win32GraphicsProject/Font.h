#include <string>

#ifndef H_FONT
#define H_FONT

#include "SpriteFont.h"

using namespace std;

#define FC_BLACK  DirectX::Colors::Black
#define FC_RED    DirectX::Colors::Red
#define FC_GREEN  DirectX::Colors::Green
#define FC_BLUE   DirectX::Colors::Blue

//
// Wrapper for a directX font
//
class FontType
{
 public:

    void PrintMessage(int posX, int posY, wstring message, DirectX::FXMVECTOR color);
    void InitializeFont(ID3D11Device* pDevice, ID3D11DeviceContext* pDC, wstring fileName);

    FontType(void);
    FontType(ID3D11Device* pDevice, ID3D11DeviceContext* pDC, wstring fileName);
    ~FontType();

private:

	DirectX::SpriteBatch*	 pBatch;
	DirectX::SpriteFont*	 pFont;
};

#endif