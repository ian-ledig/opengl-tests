#version 430 core

#define LOCAL_SIZE_X 16
#define LOCAL_SIZE_Y 16
#define GAUSS_RADIUS 4

layout (local_size_x = LOCAL_SIZE_X, local_size_y = LOCAL_SIZE_Y, local_size_z = 1) in;

layout (binding = 0) uniform sampler2D inputImage;
layout (binding = 1, rgba8) writeonly uniform image2D outputImage;

const float weights[GAUSS_RADIUS + 1] = float[](
    0.2270270270,
    0.1945945946,
    0.1216216216,
    0.0540540541,
    0.0162162162
);

uniform vec2 resolution;

shared vec4 tile[LOCAL_SIZE_Y + 2 * GAUSS_RADIUS][LOCAL_SIZE_X];

void main()
{
    int width  = int(resolution.x);
    int height = int(resolution.y);

    ivec2 localID  = ivec2(gl_LocalInvocationID.xy);
    ivec2 groupID  = ivec2(gl_WorkGroupID.xy);

    int groupBaseX = groupID.x * LOCAL_SIZE_X;
    int groupBaseY = groupID.y * LOCAL_SIZE_Y;

    int gx = groupBaseX + localID.x;
    int gy = groupBaseY + localID.y;

    vec2 texelSize = 1.0 / resolution;

    int clampedX = clamp(gx, 0, width  - 1);
    int clampedY = clamp(gy, 0, height - 1);

    int sharedX = localID.x;
    int sharedY = localID.y + GAUSS_RADIUS;

    vec2 centerUV = (vec2(clampedX, clampedY) + 0.5) * texelSize;
    tile[sharedY][sharedX] = texture(inputImage, centerUV);

    if (localID.y < GAUSS_RADIUS)
    {
        int haloTopY    = groupBaseY + localID.y - GAUSS_RADIUS;
        int haloBottomY = groupBaseY + LOCAL_SIZE_Y + localID.y;

        haloTopY    = clamp(haloTopY,    0, height - 1);
        haloBottomY = clamp(haloBottomY, 0, height - 1);

        vec2 haloTopUV    = (vec2(clampedX, haloTopY)    + 0.5) * texelSize;
        vec2 haloBottomUV = (vec2(clampedX, haloBottomY) + 0.5) * texelSize;

        tile[localID.y][sharedX] = texture(inputImage, haloTopUV);
        tile[LOCAL_SIZE_Y + GAUSS_RADIUS + localID.y][sharedX] = texture(inputImage, haloBottomUV);
    }

    barrier();

    vec4 color = tile[sharedY][sharedX] * weights[0];
    for (int i = 1; i <= GAUSS_RADIUS; ++i)
    {
        color += tile[sharedY - i][sharedX] * weights[i];
        color += tile[sharedY + i][sharedX] * weights[i];
    }

    if (gx < width && gy < height)
    {
        imageStore(outputImage, ivec2(gx, gy), color);
    }
}


