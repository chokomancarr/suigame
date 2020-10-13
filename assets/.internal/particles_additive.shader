{
  "name":"Particles (Additive)",
  "type":"Overlay",
  "variables":{
    "tex":"Texture",
    "col":"Color"
  },
  "options":{
    "blend":["One", "One"],
    "zfunc":"LEqual",
    "zwrite":"0"
  },

  "vertex":"
layout(location=0) in vec3 pos;
layout(location=1) in vec3 normal; //this is not used
layout(location=2) in vec3 tangent; //this is not used
layout(location=3) in vec2 texCoord;
layout(location=4) in vec4 particleColor;

uniform mat4 _MV;
uniform mat4 _P;
uniform mat4 _MVP;

out vec2 v2f_uv;
out vec4 v2f_col;

void main(){
    gl_Position = _MVP*vec4(pos, 1);
    v2f_uv = texCoord;
    v2f_col = particleColor;
}",

  "fragment":"
in vec2 v2f_uv;
in vec4 v2f_col;

uniform int _object_id;

uniform sampler2D tex;
uniform vec4 col;

layout (location=0) out vec4 outColor; //rgb?
layout (location=1) out vec4 outNormal; //xyz
layout (location=2) out vec4 outSpec; //metal rough occlu flags2
layout (location=3) out vec4 outEmi; //????

layout (location=4) out ivec4 _out_attrs; //????

void main() {
    outColor = col * v2f_col;
    outColor.a *= texture(tex, v2f_uv).r;
    outNormal.xyz = vec3(0);
    outSpec.r = 0;
    outSpec.g = 1;
    outSpec.b = 1;
    outSpec.a = 0;
    outEmi = vec4(0);
    
    _out_attrs.r = _object_id;
}"
}