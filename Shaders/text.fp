#version 120

uniform	mat4 projection;
uniform	mat4 view;

uniform sampler2D fTexture0;

varying vec4 fColor;
varying vec2 fUv;

void main(void)
{
  gl_FragColor = texture2D(fTexture0, fUv);
}
