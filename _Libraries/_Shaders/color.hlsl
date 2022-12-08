// ����� Shader�� �ٷ�� �����̴�

struct VertexInput
{
    float4 position : POSITION0;
    float4 color : COLOR0;
};

// float4�� vector4�� �ǹ��ϴ� ����
// POSITION0; �� �ø�ƽ��?? ��� ��
// �츮�� �ۼ��� �ֵ��� position�� ������ ����

struct PixelInput
{
    float4 position = SV_POSITION0;
    float4 color : COLOR0;
};

// �츮�� �Է��� input�� �������� output���ٰ� �־��ְ�

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