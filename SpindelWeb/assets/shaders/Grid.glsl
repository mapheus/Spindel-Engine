#type vertex
#version 410 core

layout(location = 0) in vec3 posa;

out vec3 nearPoint;
out vec3 farPoint;

out mat4 view;
out mat4 proj;

uniform mat4 u_View;
uniform mat4 u_Projection;

// Grid position are in clipped space
vec3 gridPlane[6] = vec3[] (
    vec3(1, 1, 0), vec3(-1, -1, 0), vec3(1, -1, 0),
    vec3(-1, -1, 0), vec3(1, 1, 0), vec3(-1, 1, 0)
);

vec3 UnprojectPoint(float x, float y, float z) {
    mat4 viewInv = inverse(u_View);
    mat4 projInv = inverse(u_Projection);
    vec4 unprojectedPoint =  projInv * vec4(x, y, z, 1.0);
    unprojectedPoint /= unprojectedPoint.w;
    return (viewInv*unprojectedPoint).xyz;
}

void main() {
    vec3 p = gridPlane[gl_VertexID].xyz;
    nearPoint = UnprojectPoint(p.x, p.y, -1.0).xyz; // unprojecting on the near plane
    farPoint = UnprojectPoint(p.x, p.y, 1.0).xyz; // unprojecting on the far plane
    view = u_View;
    proj = u_Projection;
    gl_Position = vec4(p, 1.0); // using directly the clipped coordinates
}

#type fragment
#version 410 core

in vec3 nearPoint;
in vec3 farPoint;
in mat4 view;
in mat4 proj;

layout(location = 0) out vec4 outColor;


vec4 grid(vec3 fragPos3D, float scale, bool drawAxis) {
    vec2 coord = fragPos3D.xz * scale;
    vec2 derivative = fwidth(coord);
    vec2 grid = abs(fract(coord - 0.5) - 0.5) / derivative;
    float line = min(grid.x, grid.y);
    float minimumz = min(derivative.y, 1);
    float minimumx = min(derivative.x, 1);
    vec4 color = vec4(0.2, 0.2, 0.2, 1.0 - min(line, 1.0));
    // z axis
    if(fragPos3D.x > -1 * minimumx && fragPos3D.x < 1 * minimumx)
        color.z = 1.0;
    // x axis
    if(fragPos3D.z > -1 * minimumz && fragPos3D.z < 1 * minimumz)
        color.x = 1.0;
    return color;
}
float computeDepth(vec3 pos) {
    vec4 clip_space_pos = proj * view * vec4(pos.xyz, 1.0);
    return (clip_space_pos.z / clip_space_pos.w);
}
float computeLinearDepth(vec3 pos) {
    vec4 clip_space_pos = proj * view * vec4(pos.xyz, 1.0);
    float clip_space_depth = (clip_space_pos.z / clip_space_pos.w) * 2.0 - 1.0; // put back between -1 and 1
    float linearDepth = (2.0 * 0.01 * 1000) / (1000 + 0.01 - clip_space_depth * (1000 - 0.01)); // get linear value between 0.01 and 100
    return linearDepth / 1000; // normalize
}
void main() {
    float t = -nearPoint.y / (farPoint.y - nearPoint.y);
    vec3 fragPos3D = nearPoint + t * (farPoint - nearPoint);
    gl_FragDepth = (
        (gl_DepthRange.diff * computeDepth(fragPos3D)) +
        gl_DepthRange.near + gl_DepthRange.far) / 2.0;
        float linearDepth = computeLinearDepth(fragPos3D);
    float fading = max(0, (0.5 - linearDepth));

    outColor = (grid(fragPos3D, 0.25, true) + grid(fragPos3D, 0.125, true))* float(t > 0); // adding multiple resolution for the grid
    outColor.a *= fading;
}