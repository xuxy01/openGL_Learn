#version 330 core

out vec4 FragColor;

in vec2 outUV;

uniform sampler2D texture0;

const float offset = 1.0 / 300.0;  

void main()
{
    FragColor = texture(texture0, outUV);

    //反相
    FragColor = 1.0 - texture(texture0, outUV);

    //灰阶
    float average = 0.2126 * FragColor.r + 0.7152 * FragColor.g + 0.0722 * FragColor.b;
    FragColor = vec4(average, average, average, 1.0);

    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // 左上
        vec2( 0.0f,    offset), // 正上
        vec2( offset,  offset), // 右上
        vec2(-offset,  0.0f),   // 左
        vec2( 0.0f,    0.0f),   // 中
        vec2( offset,  0.0f),   // 右
        vec2(-offset, -offset), // 左下
        vec2( 0.0f,   -offset), // 正下
        vec2( offset, -offset)  // 右下
    );
    float kernel[9] = float[](
        -1, -1, -1,
        -1,  9, -1,
        -1, -1, -1
    );

    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
    {
        col += vec3(texture(texture0, outUV + offsets[i])) *  kernel[i];
    }


    FragColor = vec4(col, 1.0);

    float blurKernel[9] = float[](
        1.0 / 16, 2.0 / 16, 1.0 / 16,
        2.0 / 16, 4.0 / 16, 2.0 / 16,
        1.0 / 16, 2.0 / 16, 1.0 / 16  
    );

    vec3 blurCol = vec3(0.0);
    for(int i = 0; i < 9; i++)
    {
        blurCol += vec3(texture(texture0, outUV + offsets[i])) *  blurKernel[i];
    }
    
    FragColor = vec4(blurCol, 1.0);


    float edgeKernel[9] = float[](
        1, 1, 1,
        1,-8, 1,
        1, 1, 1
    );

    vec3 edgeCol = vec3(0.0);
    for(int i = 0; i < 9; i++)
    {
        edgeCol += vec3(texture(texture0, outUV + offsets[i])) *  edgeKernel[i];
    }
    
    FragColor = vec4(edgeCol, 1.0);

}