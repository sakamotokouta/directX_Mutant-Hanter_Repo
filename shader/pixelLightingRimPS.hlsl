

#include "common.hlsl"


Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    //法線を正規化して格納する
    float4 normal = normalize(In.Normal);

    //ランバート
    float light = -dot(Light.Direction.xyz, normal.xyz);
    

    //テクスチャから色をサンプリングする
    outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
    outDiffuse.rgb *= saturate(light + 0.5);
    outDiffuse.a = In.Diffuse.a;

    //視線ベクトル
    float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
    eyev = normalize(eyev);

    //リムライティング
    float rim = 1.0 + dot(eyev, normal.xyz);
    rim = pow(rim, 3) * 2.0;
    rim = saturate(rim);
    

    outDiffuse.rgb += rimColor * rim;
    


}

