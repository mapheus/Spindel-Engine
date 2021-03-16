#type vertex
#version 330 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_Texcoords;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec2 v_Texcoords;
void main()
{
	v_Texcoords = a_Texcoords;
	gl_Position = u_ViewProjection *u_Transform* vec4(a_Position, 1);
}

#type fragment
#version 330 core
in vec2 v_Texcoords;

out vec4 f_Color;

uniform sampler2D tex;
void main()
{
	f_Color = texture(tex, v_Texcoords);
}