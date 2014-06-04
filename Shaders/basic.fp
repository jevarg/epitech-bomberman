#version 130

uniform	mat4 projection;
uniform	mat4 view;
uniform	mat4 model;

/*uniform int nbLight;*/

uniform sampler2D fTexture0;

in vec4 fColor;
in vec3 fNormal;
in vec2 fUv;
in vec4 fEyePos;

struct Light
{
  vec3	pos;
  vec3	color;
  vec3	ambient;
  float	power;
  float	d;
};

/* in Light light[nbLight]; */

/* Fog Exp2 */
float getFog(float z, float density)
{
  return (1 - clamp(exp(-pow(density * z, 2.0)), 0.0, 1.0));
}

vec3 getLight(vec3 Color, vec3 Normal)
{
  vec3 l = vec3(0, 1.0, 0);
  vec3 LightColor = vec3(1.0, 1.0, 1.0);
  float LightPower = 0.5;
  float d = 1;
  return (Color * LightPower * LightColor * clamp(abs(dot(Normal, l)), 0.0, 1.0) / (d * d));
}

void main(void)
{
  /* Density of the fog */
  float density = 0.07;

  vec4 fOutColor = texture2D(fTexture0, fUv);
  float factor = getFog(abs(fEyePos.z / fEyePos.w), density);
  vec3 color = getLight(fOutColor.xyz, fNormal);

  gl_FragColor = vec4(color.xyz, fOutColor.w);
  /* Color Fog = vec4(0.7, 0.7, 0.7, 1.0) => grey */
  /* gl_FragColor = mix(color, vec4(0.7, 0.7, 0.7, color.w), factor); */
}
