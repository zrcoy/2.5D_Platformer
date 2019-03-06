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
	

	float scale=2;
	float speed=1.0;
	float frequency=1.0;
	v_HeightOffset=0;
	vec3 objectPos = a_Position;
	

	float value1;


	for(int i=0;i<1;i++)
	{
		float d = distance(objectPos, u_Origin[i]);
		float dSquare=d*d;
		// taper off the ripple
		float scaleOffset=(1 - d/u_RangeOfRipple[i]);


		// if in a certain range do ripple stuff
		if(d <= u_RangeOfRipple[i] )
		{

			value1 = scale * sin(u_Time + frequency * d * speed) * scaleOffset;

			objectPos.y += value1;
	
			//if(value1<0){value1=0;}
			v_HeightOffset += value1;
			

		//	float offsetX2=0.8;
		//	float offsetZ2=0.8;
		//	float offsetX3=0.1;
		//	float offsetZ3=0.1;

			// Store object space position.

		//	value2 = scale * sin(u_Time * speed * frequency + offsetVert + (objectPos.x * offsetX2) + (objectPos.z * offsetZ2));
		//	value3 = scale * sin(u_Time * speed * frequency + offsetVert + (objectPos.x * offsetX3) + (objectPos.z * offsetZ3));


			//objectPos.y += value2;
			//objectPos.y += value3;

			//objectPos.y += sin((objectPos.x + u_Time)*3.5)*3.0;
			//objectPos.y += sin(objectPos.x + u_Time);
			//objectPos.y += sin((objectPos.z + u_Time)*3.5)*3.0;

			// Calculate world space position.
	
	

			// Calculate view space position.
			//vec2 viewpos = worldpos.xy + u_CameraTranslation;

			// Calculate clip space position.
			//vec2 clippos = viewpos * u_ProjectionScale;

			// Store final position in gl_Position
	

			//v_UVCoord*=u_UVScale;
			//v_UVCoord+=u_UVOffset;
		}

	}//end for

		vec4 worldPos = u_WorldMatrix * vec4(objectPos,1);
		vec4 viewPos = u_ViewMatrix * worldPos;

		vec4 clipPos = u_ProjectionMatrix * viewPos;
		gl_Position = clipPos;

		v_UVCoord = a_UV;
}
