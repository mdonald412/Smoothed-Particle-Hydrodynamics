//--------------------------------------------------------------

//--------------------------------------------------------------

// Enable data
#define CBV_ProjectionMatrix
#define CBV_ViewMatrix
#define CBV_WorldMatrix
#define CBV_Instance
#define CBV_LightColor
#define CBV_LightPos
#define UAV_Positions
#define SRV_Positions

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


struct AppData_norm  // vertex constant buffer, slot 2 (VertexSlot::Norm)
{
	float3 norm: NORMAL;  // norm location
};


struct AppData_tex  // vertex constant buffer, slot 3 (VertexSlot::TexCoord)
{
	float2 tex: TEXCOORD;  // uv location
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
	float2 tex : TEXCOORD;
	float4 color : COLOR;
	float4 position : SV_POSITION;
};

// ----------------------------------------------------------
//  Vertex Shader Main()
// ----------------------------------------------------------
VertexShaderOutput FlatTextureInstance_Main(AppData_pos inPos, AppData_tex inTex, AppData_norm inNorm, AppData_instance inInstance)
{
	VertexShaderOutput outValue;

	// Mat = World * View * Proj
	// POSSIBILITY 1
	matrix goBetween = WorldMatrix;

	goBetween._41 = instancePos[inInstance.index].x;
	goBetween._42 = instancePos[inInstance.index].y;
	goBetween._43 = instancePos[inInstance.index].z;

	row_major matrix Mat = mul(mul(goBetween, ViewMatrix), ProjectionMatrix);

	//   position = vec4(inPos.xyz,1) * Mat
	//   color    = vec4(inColor.rgb,1)
	outValue.position = mul(float4(inPos.position, 1.0f), Mat);
	outValue.tex = inTex.tex;

	// color calculation
	row_major matrix mvMatrix = mul(goBetween,ViewMatrix);
	float3x3 mNormalMatrix;



	mNormalMatrix[0] = normalize(mvMatrix[0].xyz);
	mNormalMatrix[1] = normalize(mvMatrix[1].xyz);
	mNormalMatrix[2] = normalize(mvMatrix[2].xyz);
	float3 vA = mul(inNorm.norm.xyz, mNormalMatrix);
	float3 vNorm = normalize( vA );

	// Get vLightDir
	float4 ecPosition;
	float3 ecPosition3;
	ecPosition = mul(float4(inPos.position,1.0f) , mvMatrix);
	ecPosition3 = ecPosition.xyz / ecPosition.w;
	float3 vLightDir = normalize(LightPos.xyz - ecPosition3);

	// Get vFragColor
	float fDot = max(0.0, dot(vNorm, vLightDir));
	outValue.color.xyz = LightColor.xyz * fDot;
	outValue.color.w = 1.0f;

	return outValue;
}

// --- End of File ---
