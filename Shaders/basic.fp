#version 120

uniform	mat4 projection;
uniform	mat4 view;
uniform	mat4 model;
uniform mat4 inv_model;

uniform sampler2D fTexture0;

varying vec4 fColor;
varying vec3 fNormal;
varying vec2 fUv;
varying vec4 fEyePos;

/* Fog Exp2*/
float getFog(float z, float density)
{
  return (1 - clamp(exp(-pow(density * z, 2.0)), 0.0, 1.0));
}

void main(void)
{
  /* Density of the fog */
  float density = 0.07;

  vec4 fOutColor = texture2D(fTexture0, fUv);
  float factor = getFog(abs(fEyePos.z / fEyePos.w), density);

  /* Color Fog = vec4(0.7, 0.7, 0.7, 1.0) => grey */
  gl_FragColor = mix(fOutColor, vec4(0.7, 0.7, 0.7, 1.0), factor);
}
