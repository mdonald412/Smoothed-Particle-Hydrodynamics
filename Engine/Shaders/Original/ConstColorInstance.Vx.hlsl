//--------------------------------------------------------------

//--------------------------------------------------------------

// Enable data
#define CBV_ProjectionMatrix
#define CBV_ViewMatrix
#define CBV_WorldMatrix
#define CBV_Instance
#define CBV_LightColor

#include "ShaderMappings.hlsli"

// ------------------------------------------------------
// Sematics Vertex Input:
//      POSITION - used in vertex layout description
//      COLOR - used in vertex layout description
// ------------------------------------------------------

struct AppData_pos  //  vertex constant buffer, slot 0 (VertexSlot::Position)
{
	float3 position : POSITION;
};

struct AppData_instance  //  vertex constant buffer, slot 0 (VertexSlot::Position)
{
	unsigned int index : SV_InstanceID;
};

// ------------------------------------------------------------
// Sematics Vertex Output:
//      COLOR - Input to the Pixel Shader
//      SV_POSIION - System Value goes to the raster stage
// ------------------------------------------------------------
struct VertexShaderOutput
{
	float4 color : COLOR;
	float4 position : SV_POSITION;
};

// ----------------------------------------------------------
//  Vertex Shader Main()
// ----------------------------------------------------------
VertexShaderOutput ConstColorInstance_Main(AppData_pos inPos, AppData_instance inInstance)
{
	VertexShaderOutput outValue;
//
	// Mat = World * View * Proj
	matrix goBetween = WorldMatrix;

	goBetween._41 = instancePos[inInstance.index].x;
	goBetween._42 = instancePos[inInstance.index].y;
	goBetween._43 = instancePos[inInstance.index].z;

	row_major matrix Mat = mul(mul(goBetween, ViewMatrix), ProjectionMatrix);

	outValue.position = mul(float4(inPos.position, 1.0f), Mat);
	outValue.color = float4( LightColor.xyz, 1.0f);


	return outValue;
}

// --- End of File ---
