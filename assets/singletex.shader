{
  "name":"singletex",
  "variables":{
    "diffuse":"Texture",
    "metallic":"Float",
    "roughness":"Float"
  },
  
  "lightmapping":{
    "diffuse_texture":"diffuse"
  },

  "vertex":"
layout(location=0) in vec3 pos;
layout(location=1) in vec3 normal;
layout(location=2) in vec3 tangent;
layout(location=3) in vec2 texCoord;

uniform mat4 _MV;
uniform mat4 _P;
uniform mat4 _MVP;

out V2F {
    vec3 normal;
    vec3 tangent;
    vec2 uv;
} v2f;

void main(){
    gl_Position = _MVP*vec4(pos, 1);
    v2f.normal = normalize((_MV * vec4(normal, 0)).xyz);
    v2f.tangent = normalize((_MV * vec4(tangent, 0)).xyz);
    v2f.uv = texCoord;
}",

  "fragment":"
in V2F {
    vec3 normal;
    vec3 tangent;
    vec2 uv;
} v2f;

uniform int _object_id;

uniform sampler2D diffuse;
uniform float metallic;
uniform float roughness;

layout (location=0) out vec4 outColor; //rgb?
layout (location=1) out vec4 outNormal; //xyz
layout (location=2) out vec4 outSpec; //metal rough occlu flags2
layout (location=3) out vec4 outEmi; //????

layout (location=4) out ivec4 _outObjectID;

void main() {
    outColor = texture(diffuse, v2f.uv);
    outNormal.xyz = normalize(v2f.normal);
    outSpec.r = metallic;
    outSpec.g = roughness;
    outSpec.b = 1;
    outSpec.a = 0;
    outEmi = vec4(0, 0, 0, 0);
    
    _outObjectID.x = _object_id;
}"
}