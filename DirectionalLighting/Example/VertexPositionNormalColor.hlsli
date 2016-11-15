
// Header file for using a vertex containing position and color
//
//
//

// constants that are needed by the shader
cbuffer VS_CONSTANT_BUFFER : register(b0)
{
	matrix worldMatrix;					
	matrix viewMatrix;				
	matrix projectionMatrix;
	matrix worldViewProjectionMatrix;
	matrix worldMatrixIT; // inverse transpose of the worldMatrix
};

// constants that are used to do lighting
cbuffer LIGHT_BUFFER : register(b1)
{
	float4 ambientColour;

	float4 directionalLightColor;
	float4 directionalLightVector;

	float4 directionalLightColor2;
	float4 directionalLightVector2;
}


// vertex shader input
//  This is information that comes from the vertices
struct VS_INPUT
{
	float4 Pos : SV_POSITION;	// position
	float3 Normal: NORMAL;		// normal
	float4 Color : COLOR;		// colour
};

// pixel shader input
//  Information that is passed from vertex to pixel shader
struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float3 WorldNormal : TEXCOORD0;
	float4 Color : COLOR;
};


// function that will calculate ambient lighting
//
float4 AmbientLighting(float4 materialColour, float4 lightColour)
{
	return materialColour * lightColour;
}

// Given a light and normal, calculate the colour of the directional light contribution
//
float4 DiffuseLighting(float3 lightVector, float3 normal, float4 lightColor, float4 matColor)
{
	// Diffuse lighting calculate, take the dot product between the light and normal vectors
	//	this is the same as cosine of the angle between the vectors
	float intensity = max(0, dot(normal, lightVector));

	// multiply the material color by the light color, modulated by the 
	//  angle calculation
	return intensity * lightColor * matColor;

}