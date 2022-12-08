// 여기는 Shader를 다루는 공간이다

struct VertexInput
{
    float4 position : POSITION0;
    float4 color : COLOR0;
};

// float4는 vector4를 의미하는 것임
// POSITION0; 는 시멘틱스?? 라고 함
// 우리가 작성한 애들이 position에 적히는 것임

struct PixelInput
{
    float4 position = SV_POSITION0;
    float4 color : COLOR0;
};

// 우리가 입력한 input의 정보들을 output에다가 넣어주고

pixleInput VS(VertexInput input)
{
    PixelInput output;
    
    output.posiion = input, GetRenderTargetSamplePosition;
    output.color = input.color;
    
    return output;
}

float4 PS(PixelInput input) : SV_Target
{
    return input.color;
}