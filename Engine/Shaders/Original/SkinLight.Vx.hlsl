//--------------------------------------------------------------

//--------------------------------------------------------------

// Enable data
#define SRV_BoneWorldIn
#define SRV_InvBind
#define CBV_ProjectionMatrix
#define CBV_ViewMatrix
#define CBV_WorldMatrix
#define CBV_LightColor
#define CBV_LightPos

#include "ShaderMappings.hlsli"

// ------------------------------------------------------
// Sematics Vertex Input:
//      POSITION, TEXCOORD, BLENDWEIGHT, BLENDINDICES
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
    float2 tex : TEXCOORD; // uv location
};

struct AppData_weights  // vertex constant buffer, slot 4 (VertexSlot::Weights)
{
    float4 w : BLENDWEIGHT; // weight location
};

struct AppData_joints  // vertex constant buffer, slot 5 (VertexSlot::Joints)
{
    uint4 j : BLENDINDICES; // joints location
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
VertexShaderOutput SkinLight_Main(AppData_pos inPos,
                                        AppData_tex inTex,
										AppData_norm inNorm,
                                        AppData_weights inWeight,
                                        AppData_joints inJoint)
{
    VertexShaderOutput outValue;

    row_major matrix skinWorld = mul(mul(InvBind[inJoint.j.x].m, BoneWorldIn[inJoint.j.x].m), inWeight.w.x) +
	                             mul(mul(InvBind[inJoint.j.y].m, BoneWorldIn[inJoint.j.y].m), inWeight.w.y) +
                                 mul(mul(InvBind[inJoint.j.z].m, BoneWorldIn[inJoint.j.z].m), inWeight.w.z) +
                                 mul(mul(InvBind[inJoint.j.w].m, BoneWorldIn[inJoint.j.w].m), inWeight.w.w);
    
    // M = world * Skin* view * Proj
    row_major matrix Mat = mul(mul(mul(skinWorld, WorldMatrix), ViewMatrix), ProjectionMatrix);
	
    //  out = pos * world * Skin * View * Proj
    outValue.position = mul(float4(inPos.position, 1.0f), Mat);
    
    // Texture
	outValue.tex = inTex.tex;

	// color calculation
	row_major matrix mvMatrix = mul(mul(skinWorld, WorldMatrix),ViewMatrix);
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
