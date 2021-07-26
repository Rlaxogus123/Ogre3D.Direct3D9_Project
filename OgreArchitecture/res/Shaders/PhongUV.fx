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

matrix gWorldMatrix;
matrix gViewMatrix;
matrix gProjectionMatrix;

float4 gWorldLightPosition;
float4 gWorldCameraPosition;


struct VS_INPUT
{
   float4 mPosition : POSITION;
   float3 mNormal: NORMAL;
   float2 mTexCoord : TEXCOORD0;
};


struct VS_OUTPUT
{
   float4 mPosition : POSITION; //¿X  X
   float2 mTexCoord : TEXCOORD0;
   float3 mDiffuse : TEXCOORD1; //? ??
   float3 mViewDir: TEXCOORD2; //tT| )??
   float3 mReflection: TEXCOORD3; //??
};


VS_OUTPUT Default_DirectX_Effect_Pass_0_Vertex_Shader_vs_main( VS_INPUT Input )
{
   VS_OUTPUT Output;
   Output.mPosition = mul( Input.mPosition, gWorldMatrix ); // ‘‹ ¿X

   float3 lightDir = Output.mPosition.xyz - gWorldLightPosition.xyz; // Ö¨ ? lX0
   lightDir = normalize(lightDir); //Ö¨ ? x@|t?

   float3 viewDir = normalize(Output.mPosition.xyz - gWorldCameraPosition.xyz); //tT| ? x@|t?
   Output.mViewDir = viewDir; //output??

   Output.mPosition = mul( Output.mPosition, gViewMatrix ); //  ?¿X
   Output.mPosition = mul( Output.mPosition, gProjectionMatrix ); //  , ¿X

   float3 worldNormal = mul( Input.mNormal, (float3x3)gWorldMatrix ); //x@ ? ‘‹ ¿X
   worldNormal = normalize(worldNormal); //x@ ? x@|t?

   Output.mDiffuse = dot(-lightDir, worldNormal); //??
   Output.mReflection = reflect(lightDir, worldNormal); //¨°0 lX0
   Output.mTexCoord = Input.mTexCoord;

   return Output; //?
}
texture EarthNight_Tex
<
   string ResourceName = "..\\..\\..\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Textures\\Earth.jpg";
>;
sampler2D DiffuseSampler = sampler_state
{
   Texture = (EarthNight_Tex);
};

struct PS_INPUT
{
   float2 mTexCoord : TEXCOORD0;
   float3 mDiffuse : TEXCOORD1;  //? ???
   float3 mViewDir: TEXCOORD2;  // tT| ?
   float3 mReflection: TEXCOORD3; // ? ?
};


float4 Default_DirectX_Effect_Pass_0_Pixel_Shader_ps_main(PS_INPUT Input) : COLOR
{
   float3 diffuse = saturate(Input.mDiffuse); 

   float3 reflection = normalize(Input.mReflection); // ? ? x?t?
   float3 viewDir = normalize(Input.mViewDir); // tT| ? x@|t?
   float3 specular = 0; //??lX0
   if ( diffuse.x > 0 )
   {
      specular = saturate(dot(reflection, -viewDir ));
      specular = pow(specular, 20.0f); //p??
   }

   float4 albedo = tex2D(DiffuseSampler, Input.mTexCoord);
   float3 ambient = float3(0.1f, 0.1f, 0.1f); //¸¿

   return float4(ambient + diffuse + specular, 1) + albedo; //? 
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

