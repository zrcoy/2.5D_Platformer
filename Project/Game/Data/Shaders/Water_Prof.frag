#version 120

uniform sampler2D u_TextureSampler;

varying vec2 v_UVCoord;

varying float v_HeightOffset;

//varying vec2 v_UV;

void main()
{


	//Change the color of the ripple based on it's height to help make the ripples stand out
	

	gl_FragColor=vec4(v_HeightOffset,v_HeightOffset,v_HeightOffset,1);;
}
