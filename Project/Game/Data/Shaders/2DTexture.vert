#version 120

attribute vec2 a_Position;
attribute vec2 a_UV;
attribute vec4 a_Color;

uniform vec2 u_ObjectScale;
uniform float u_ObjectAngleRadians;
uniform vec2 u_ObjectPosition;
uniform vec2 u_CameraTranslation;
uniform vec2 u_ProjectionScale;

varying vec2 v_UV;


void main()
{
	// Store object space position.
	vec2 objectpos = a_Position;

	// Calculate world space position.
	vec2 worldpos = objectpos * u_ObjectScale;
	worldpos = vec2( worldpos.x * cos(u_ObjectAngleRadians) - worldpos.y * sin(u_ObjectAngleRadians),
                     worldpos.x * sin(u_ObjectAngleRadians) + worldpos.y * cos(u_ObjectAngleRadians) );
	worldpos += u_ObjectPosition;

	// Calculate view space position.
	vec2 viewpos = worldpos + u_CameraTranslation;

	// Calculate clip space position.
	vec2 clippos = viewpos * u_ProjectionScale;

	// Store final position in gl_Position
    gl_Position = vec4( clippos, 0, 1 );

	v_UV = a_UV;
}
