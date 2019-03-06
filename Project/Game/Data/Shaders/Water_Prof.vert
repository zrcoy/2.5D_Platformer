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

uniform float u_Time;

uniform vec3 u_Origin[3];
uniform float u_RangeOfRipple[3];

varying float v_HeightOffset;

void main()
{
	

	float amplitude=5;
	float speed=5.0;
	float freq=20.0;

	v_HeightOffset=0;
	vec3 objectPos = a_Position;
	

	float offset=0;


	for(int i=0;i<1;i++)
	{
		float d = distance(objectPos, u_Origin[i]);
		
		// taper off the ripple
		float maxDist=0.5;
		float fallOff=(1 - d/u_RangeOfRipple[i]);
		fallOff = clamp(fallOff,0.0,1.0);

		// if in a certain range do ripple stuff
		if(d <= u_RangeOfRipple[i] )
		{

			offset = sin( freq * d - u_Time *speed)  * fallOff ;

			objectPos.y += offset * amplitude;
	
			
			v_HeightOffset = offset;
			


		}

	}//end for

		vec4 worldPos = u_WorldMatrix * vec4(objectPos,1);
		vec4 viewPos = u_ViewMatrix * worldPos;

		vec4 clipPos = u_ProjectionMatrix * viewPos;
		gl_Position = clipPos;

		v_UVCoord = a_UV;
}
