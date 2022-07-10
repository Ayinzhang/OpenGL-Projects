#version 330 core
in vec3 fragPos;
in vec3 normal;
in vec2 texCoord;
out vec4 fragColor;
uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 cameraPos;
struct Material
{
   vec3 ambient;
   sampler2D diffuse;
   sampler2D specqular;
   float shininess;
};
struct DirectionalLight
{
   vec3 pos;
   vec3 dir;
   vec3 color;
};
struct PointLight
{
   vec3 pos;
   vec3 dir;
   vec3 color;
   vec3 attenuation;
};
struct SpotLight
{
   vec3 pos;
   vec3 dir;
   vec3 color;
   vec3 attenuation;
   vec2 cosPhy;
};
uniform Material material;
uniform DirectionalLight dLight;
vec3 CalcDirctionalLight(DirectionalLight light,vec3 uNormal,vec3 dirToCamera)
{
   vec3 diffColor = light.color * max(0,dot(uNormal,light.dir)) * texture(material.diffuse,texCoord).xyz;
   vec3 specVec = reflect(-light.dir,uNormal);
   vec3 specColor = light.color * pow(max(0,dot(specVec,dirToCamera)),material.shininess) * texture(material.specqular,texCoord).xyz;
   vec3 result = diffColor + specColor;
   return result;
}
vec3 CalcPointLight(PointLight light,vec3 uNormal,vec3 dirToCamera)
{
   float dist = length(light.pos-fragPos);
   float attenuation = 1 / (light.attenuation.x + light.attenuation.y*dist + light.attenuation.z*dist*dist);
   vec3 diffColor = light.color * attenuation * max(0,dot(uNormal,normalize(light.pos-fragPos))) * texture(material.diffuse,texCoord).xyz;
   vec3 specVec = reflect(-light.dir,uNormal);
   vec3 specColor = light.color * pow(max(0,dot(specVec,dirToCamera)),material.shininess) * texture(material.specqular,texCoord).xyz;
   vec3 result = diffColor + specColor;
   return result;
}
vec3 CalcSpotLight(SpotLight light,vec3 uNormal,vec3 dirToCamera)
{
   float dist = length(light.pos-fragPos);
   float attenuation = 1 / (light.attenuation.x + light.attenuation.y*dist + light.attenuation.z*dist*dist);
   float spotRatio = 0;
   float cosTheta = dot(normalize(light.pos-fragPos),-light.dir);
   if(cosTheta > light.cosPhy.x) spotRatio = 1;
   else if(cosTheta > light.cosPhy.y) spotRatio = (cosTheta - light.cosPhy.y) / (light.cosPhy.x - light.cosPhy.y);
   vec3 diffColor = light.color * attenuation * max(0,dot(uNormal,normalize(light.pos-fragPos))) * texture(material.diffuse,texCoord).xyz;
   vec3 specVec = reflect(-light.dir,uNormal);
   vec3 specColor = light.color * pow(max(0,dot(specVec,dirToCamera)),material.shininess) * texture(material.specqular,texCoord).xyz;
   vec3 result = diffColor + specColor;
   return result;
}
void main()
{
   vec3 result = vec3(0,0,0);
   vec3 uNormal = normalize(normal);
   vec3 dirToCamera = normalize(cameraPos - fragPos);
   result += CalcDirctionalLight(dLight,uNormal,dirToCamera);
   //result += CalcPointLight(pLight,uNormal,dirToCamera);
   //result += CalcSpotLight(pLight,uNormal,dirToCamera);
   fragColor = vec4(result,1);
}