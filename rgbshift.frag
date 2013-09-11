#version 150

uniform sampler2D frameTexture;
uniform float globalTime;

in Vertex {
	vec4 colour;
	vec2 uv;
} IN;

out vec4 out_colour;

void main(void ) {	
   	out_colour = texture(frameTexture, IN.uv); 
}

