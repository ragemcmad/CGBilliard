#version 330
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_explicit_uniform_location : enable
// default330.frag: a simple fragment shader
//
// notes:
// GL_ARB_separate_shader_objects is not needed for version >= 410

layout(location = 0) in vec4 texC;
layout(location = 1) in vec4 normalvector;
layout(location = 2) in vec4 vertex;
out vec4 fragColor;
uniform sampler2D colortex;
uniform vec3 lightpositions[4];
uniform vec3 lightintensity[4];
uniform vec3 cameraposition;

// must be at 0
void main()
{
    //ambient
    fragColor = vec4(0.05,0.05,0.05,1)*texture(colortex, vec2(texC.x, texC.y));
    float alpha = fragColor.a;
    vec4 colorSpecAll=vec4(0,0,0,0);
    for(int i = 0;i<4;i++)
    {
        float anglespec = 0;

        vec3 vert = -normalize(vertex.xyz-lightpositions[i]);
        vec3 normal = normalize(normalvector.xyz);
        float angle = dot(vert, normal);

        vec3 cPos = normalize(cameraposition);
        vec3 rayA = normalize(reflect(-vert,normal));
        vec3 rayB = normalize(cPos+vert);
        anglespec = pow(dot(rayA,rayB),32);

        //defuse
        angle = max(angle, 0);
        vec4 color =  texture(colortex, vec2(texC.x, texC.y));
        color.r = color.r * angle *lightintensity[i].r*(1.0/distance(vertex.xyz,lightpositions[i]));
        color.g = color.g * angle *lightintensity[i].g*(1.0/distance(vertex.xyz,lightpositions[i]));
        color.b = color.b * angle *lightintensity[i].b*(1.0/distance(vertex.xyz,lightpositions[i]));

        //Phong spec
        anglespec = max(0,anglespec);

        vec4 colorspec = texture(colortex, vec2(texC.x, texC.y));
        colorspec.r = max(colorspec.r * anglespec,0);
        colorspec.g = max(colorspec.g * anglespec,0);
        colorspec.b = max(colorspec.b * anglespec,0);

        colorSpecAll = colorSpecAll + colorspec;
        //color = vec4(color.rgb,1);
        fragColor = fragColor + color;

    }
    //fragColor.a = alpha;

    fragColor.a= 1;

    fragColor.rgb = mix(fragColor.rgb, colorSpecAll.rgb, 0.5);
     //fragColor.rgb += colorSpecAll.rgb;
}
