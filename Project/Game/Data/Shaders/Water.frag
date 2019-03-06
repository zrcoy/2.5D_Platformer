#version 120

uniform sampler2D u_TextureSampler;

varying vec2 v_UVCoord;

varying float v_HeightOffset;

//varying vec2 v_UV;

void main()
{
	//gl_FragColor=vec4(1,1,1,1);
	gl_FragColor = texture2D( u_TextureSampler, v_UVCoord );

	vec4 color =texture2D(u_TextureSampler,v_UVCoord);

	color.a=1;

	//color *= vec4(.7,.4,0,1);

	//Change the color of the ripple based on it's height to help make the ripples stand out
	color += vec4((1-v_HeightOffset),v_HeightOffset,v_HeightOffset,1);

	gl_FragColor=color;
}
