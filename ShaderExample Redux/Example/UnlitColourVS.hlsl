// Vertex shader for an unlit vertex colour shader
//
//

#include "VertexPositionColor.hlsli"

PS_INPUT main( VS_INPUT input )
{
	PS_INPUT output;

	// transform the input position using world * view * projection
	//  by using the multiplication operator
	output.Pos = mul(input.Pos, worldViewProjectionMatrix);
	
	
	
	// set the color to be interpolated by the rasterizer
	output.Color = input.Color; 

	return output;
}