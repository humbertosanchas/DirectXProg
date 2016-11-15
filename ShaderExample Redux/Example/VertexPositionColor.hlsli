
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
};


// vertex shader input
//  This is information that comes from the vertices
struct VS_INPUT
{
	float4 Pos : SV_POSITION;
	float4 Color : COLOR;
};

// pixel shader input
//  Information that is passed from vertex to pixel shader
struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float4 Color : COLOR;
};