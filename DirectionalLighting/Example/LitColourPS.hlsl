//
// Pixel shader for an unlit vertex colour shader
//

#include "VertexPositionNormalColor.hlsli"

float4 main(PS_INPUT input) : SV_TARGET
{
	// we need to force the normal to be a length of 1
	float3 normal = normalize(input.WorldNormal.xyz);

	float4 finalColor = 
		   AmbientLighting(input.Color, ambientColour) 
		+ DiffuseLighting(directionalLightVector.xyz, normal, directionalLightColor, input.Color)
	    + DiffuseLighting(directionalLightVector2.xyz, normal, directionalLightColor2, input.Color);	

	finalColor.a = 1;

	return finalColor;
}