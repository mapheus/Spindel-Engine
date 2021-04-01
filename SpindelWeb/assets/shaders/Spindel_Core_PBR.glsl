#type vertex
#version 430 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_Texcoords;
layout(location = 3) in vec3 a_Tangent;
layout(location = 4) in vec3 a_Bitangent;


uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out VS_OUT
{
    vec3 v_Position;
	vec3 v_Normal;
	vec2 v_Texcoords;
} vs_out;

void main()
{
	vs_out.v_Texcoords = a_Texcoords;
	vs_out.v_Normal = vec3(u_ViewProjection *u_Transform* vec4(a_Normal, 0));
    vs_out.v_Position = vec3(u_ViewProjection *u_Transform* vec4(a_Position, 1));
	gl_Position = u_ViewProjection *u_Transform* vec4(a_Position, 1);
}

#type fragment
#version 430 core

uniform vec3 u_CameraPosition;

uniform vec4 u_Color;
uniform float u_Metallic;
uniform float u_Roughness;
float ao = 0.8;
vec3 lightColor = vec3(0.9, 0.7, 0.9);
vec3 lightPos = vec3(3, 3, -3);

in VS_OUT
{
    vec3 v_Position;
	vec3 v_Normal;
	vec2 v_Texcoords;
} fs_in;

out vec4 f_Color;

uniform sampler2D u_Texture;

const float PI = 3.14159265359;

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a      = roughness*roughness;
    float a2     = a*a;
    float NdotH  = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;
	
    float num   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;
	
    return num / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float num   = NdotV;
    float denom = NdotV * (1.0 - k) + k;
	
    return num / denom;
}
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2  = GeometrySchlickGGX(NdotV, roughness);
    float ggx1  = GeometrySchlickGGX(NdotL, roughness);
	
    return ggx1 * ggx2;
}
vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(max(1.0 - cosTheta, 0.0), 5.0);
}  

void main()
{		
    vec3 albedo = texture(u_Texture, fs_in.v_Texcoords).rgb;
    vec3 N = normalize(fs_in.v_Normal);
    vec3 V = normalize(u_CameraPosition - fs_in.v_Position);

    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, vec3(albedo), u_Metallic);
	           
    // reflectance equation
    vec3 Lo = vec3(0.0);
    for(int i = 0; i < 4; ++i) 
    {
        // calculate per-light radiance
        vec3 L = normalize(lightPos - fs_in.v_Position);
        vec3 H = normalize(V + L);
        float distance    = length(lightPos - fs_in.v_Position);
        float attenuation = 1.0 / (distance * distance);
        vec3 radiance     = lightColor * attenuation;        
        
        // cook-torrance brdf
        float NDF = DistributionGGX(N, H, u_Roughness);        
        float G   = GeometrySmith(N, V, L, u_Roughness);      
        vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0);       
        
        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;
        kD *= 1.0 - u_Metallic;	  
        
        vec3 numerator    = NDF * G * F;
        float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0);
        vec3 specular     = numerator / max(denominator, 0.001);  
            
        // add to outgoing radiance Lo
        float NdotL = max(dot(N, L), 0.0);                
        Lo += (kD * vec3(albedo) / PI + specular) * radiance * NdotL; 
    }   
  
    vec3 ambient = vec3(0.03) * vec3(albedo) * ao;
    vec3 color = ambient + Lo;
	
    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2));  
   
    f_Color = vec4(color, 1.0);
}  