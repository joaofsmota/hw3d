float4 main(float2 inPos : POSITION) : SV_POSITION
{
    return float4(inPos, 0.f, 1.f);
}