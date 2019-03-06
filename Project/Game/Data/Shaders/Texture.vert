#version 120

attribute vec3 a_Position;
attribute vec2 a_UV;
attribute vec4 a_Color;

uniform mat4 u_WorldMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;
//uniform vec2 u_CameraTranslation;
//uniform vec2 u_ProjectionScale;

uniform vec2 u_UVScale;
uniform vec2 u_UVOffset;

varying vec2 v_UVCoord;

uniform bool u_FacingRight;

void main()
{
	// Store object space position.
	vec3 objectPos = a_Position;

	// Calculate world space position.
	vec4 worldPos = u_WorldMatrix * vec4(objectPos,1);

	vec4 viewPos = u_ViewMatrix * worldPos;

	vec4 clipPos = u_ProjectionMatrix * viewPos;

	// Calculate view space position.
	//vec2 viewpos = worldpos.xy + u_CameraTranslation;

	// Calculate clip space position.
	//vec2 clippos = viewpos * u_ProjectionScale;

	// Store final position in gl_Position
    gl_Position = clipPos;

	if (u_FacingRight) {
		v_UVCoord = a_UV;
	} else {
		v_UVCoord = vec2(a_UV.x == 0 ? 1 : 0, a_UV.y);
	}
}
