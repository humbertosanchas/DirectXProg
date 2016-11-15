// Vertex shader for an unlit vertex colour shader
//
//

#include "VertexPositionNormalColor.hlsli"

PS_INPUT main( VS_INPUT input )
{
	PS_INPUT output;

	// transform the input position using world * view * projection
	//  by using the multiplication operator
	output.Pos = mul(input.Pos, worldViewProjectionMatrix);
	
	// set the color to be interpolated by the rasterizer
	output.Color = input.Color; 

	// transform the normal to world space but ignore the 
	output.WorldNormal = mul(float4(input.Normal, 0), worldMatrixIT).xyz;

	return output;
}