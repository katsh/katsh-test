//グローバル
cbuffer global
{
	matrix g_mW;//ワールド行列
	matrix g_mWVP; //ワールドから射影までの変換行列
	float4 g_vLightDir;  //ライトの方向ベクトル
	float4 g_Diffuse=float4(1,0,0,0); //拡散反射(色）
};

//構造体
struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR0;
};

//
//バーテックスシェーダー
//
VS_OUTPUT VS( float4 Pos : POSITION ,float4 Normal : NORMAL)
{   
	VS_OUTPUT output = (VS_OUTPUT)0;
	
	output.Pos=mul(Pos,g_mWVP);
	Normal.w=0;//w=0で移動成分を反映させない（原理はシェーダーグルが詳しい）
	Normal=mul(Normal,g_mW);
	Normal=normalize(Normal);

	output.Color=1.0 * g_Diffuse * dot(Normal,g_vLightDir);//この式はランバートの余弦則

    return output;
}

//
//ピクセルシェーダー
//
float4 PS( VS_OUTPUT input  ) : SV_Target
{
    return input.Color;    
}