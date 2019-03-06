#version 120

uniform sampler2D u_TextureSampler;

varying vec2 v_UVCoord;

void main()
{
	//gl_FragColor=vec4(1,1,1,1);
	gl_FragColor = texture2D( u_TextureSampler, v_UVCoord );
}
