//
// Pixel shader for an unlit vertex colour shader
//

#include "VertexPositionColor.hlsli"

float4 main(PS_INPUT input) : SV_TARGET
{
	PS_INPUT output;
	// The interpolated color 
	//
	output.Color = input.Color;
	
	return output.Color;
}