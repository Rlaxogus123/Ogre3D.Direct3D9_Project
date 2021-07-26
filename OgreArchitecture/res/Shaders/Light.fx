//**************************************************************//
//  Effect File exported by RenderMonkey 1.6
//
//  - Although many improvements were made to RenderMonkey FX  
//    file export, there are still situations that may cause   
//    compilation problems once the file is exported, such as  
//    occasional naming conflicts for methods, since FX format 
//    does not support any notions of name spaces. You need to 
//    try to create workspaces in such a way as to minimize    
//    potential naming conflicts on export.                    
//    
//  - Note that to minimize resulting name collisions in the FX 
//    file, RenderMonkey will mangle names for passes, shaders  
//    and function names as necessary to reduce name conflicts. 
//**************************************************************//

//--------------------------------------------------------------//
// Default_DirectX_Effect
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Pass 0
//--------------------------------------------------------------//
string Default_DirectX_Effect_Pass_0_Model : ModelData = "..\\..\\..\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Models\\Sphere.3ds";

float4x4 gViewMatrix : View;
float4x4 gWorldMatrix : World;
float4x4 gProjectionMatrix : Projection;

float4 gWorldLightPosition
<
   string UIName = "gWorldLightPosition";
   string UIWidget = "Direction";
   bool UIVisible =  false;
   float4 UIMin = float4( -10.00, -10.00, -10.00, -10.00 );
   float4 UIMax = float4( 10.00, 10.00, 10.00, 10.00 );
   bool Normalize =  false;
> = float4( 500.00, 500.00, -500.00, 1.00 );

struct VS_INPUT{
   float4 mPosition: POSITION;  //? \?? 
   float3 mNormal: NORMAL;  // ? ? 
};


struct VS_OUTPUT{
   float4 mPosition: POSITION; // \?ÀX ? 
   float3 mDiffuse: TEXCOORD1; // ? 

};

VS_OUTPUT Default_DirectX_Effect_Pass_0_Vertex_Shader_vs_main(VS_INPUT input)
{
   VS_OUTPUT output;
   
   output.mPosition = mul(input.mPosition, gWorldMatrix);
   
   float3 lightDirection = output.mPosition.xyz - gWorldLightPosition.xyz;
  
   
   output.mPosition = mul(output.mPosition, gViewMatrix);
   output.mPosition = mul(output.mPosition, gProjectionMatrix);
   
   lightDirection = normalize(lightDirection);
   float3 worldNormal = mul(input.mNormal , (float3x3)gWorldMatrix );
   worldNormal= normalize( worldNormal );
   
   output.mDiffuse = dot(-lightDirection , worldNormal);
   
   return output;
}
struct PS_INPUT
{
   float3 mDiffuse : TEXCOORD1;
};


float4 Default_DirectX_Effect_Pass_0_Pixel_Shader_ps_main(PS_INPUT Input) : COLOR
{
   float3 diffuse = saturate(Input.mDiffuse);
   return float4(diffuse, 1);
}
//--------------------------------------------------------------//
// Technique Section for Default_DirectX_Effect
//--------------------------------------------------------------//
technique Default_DirectX_Effect
{
   pass Pass_0
   {
      VertexShader = compile vs_2_0 Default_DirectX_Effect_Pass_0_Vertex_Shader_vs_main();
      PixelShader = compile ps_2_0 Default_DirectX_Effect_Pass_0_Pixel_Shader_ps_main();
   }

}

