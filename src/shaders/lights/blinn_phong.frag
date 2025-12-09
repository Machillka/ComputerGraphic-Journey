#version 330 core

// 环境光设置
uniform vec4 lightColor;
uniform vec3 lightPos;
// 观测者位置 (相机位置)
uniform vec3 viewPos;
// 环境光参数
uniform float ambientStrength = 0.1;
uniform float shininess = 32.0;
// 自身物体颜色
uniform vec4 objColor;

in vec3 FragPos;
in vec3 Normal;
out vec4 FragColor;

void main()
{
    float kc = 1.0;
    float kl = 0.09;
    float kq = 0.032;

    vec3 norm = normalize(Normal);
    // 向量方向 从当前像素指向光源
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 viewDir = normalize(viewPos - FragPos);
    // 半程向量的单位向量
    vec3 halfDir = normalize(lightPos + viewPos);

    vec4 ambient = ambientStrength * lightColor;
    vec4 diffuse = max(dot(norm, lightPos), 0.0) * lightColor;
    vec4 specular = pow(max(dot(norm, halfDir), 0.0), shininess) * lightColor;

    vec4 res = (ambient + diffuse + specular) * objColor;

    float d = length(lightPos - FragPos);
    float attenuation = 1.0 / (kc + kl * d + kq * d * d);
    res *= attenuation;


    FragColor = vec4(res.rgb, 1.0);
}