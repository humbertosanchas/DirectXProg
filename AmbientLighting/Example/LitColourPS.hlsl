//
// Pixel shader for an unlit vertex colour shader
//

#include "VertexPositionNormalColor.hlsli"

float4 main(PS_INPUT input) : SV_TARGET
{
	// The interpolated color 
	//
	return AmbientLighting(input.Color, ambientColour);
}