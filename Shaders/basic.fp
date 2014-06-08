#version 120

uniform	mat4 projection;
uniform	mat4 view;
uniform	mat4 model;

uniform sampler2D fTexture0;

varying vec3 fPosition;
varying vec4 fColor;
varying vec3 fNormal;
varying vec2 fUv;
varying vec4 fEyePos;

struct Light
{
  int type;
  vec3	pos;
  vec3	color;
  float	power;

  float C;
  float L;
  float E;
};

uniform int nbLight;
uniform Light light[20];

/* Fog Exp2 */
float getFog(float z, float density)
{
  return (1 - clamp(exp(-pow(density * z, 2.0)), 0.0, 1.0));
}

vec3 getLight(vec3 Color, vec3 Normal)
{
  int i;
  vec3 ret = vec3(1.0, 1.0, 1.0);

  for (i = 0;i < nbLight;i++)
    {
      vec3 l = (view * vec4(light[i].pos.xyz, 1.0)).xyz + (vec3(0.0, 0.0, 0.0) - fEyePos.xyz);
      float d = length(l);
      l = normalize(l);
      vec3 n = normalize(Normal);

      vec3 fAmbient = vec3(0.1, 0.1, 0.1) * Color;
      float fDiffuse = clamp(dot(n, l), 0, 1);
      float fSpec = clamp(dot(normalize(fEyePos.xyz), reflect(-l, n)), 0,1);
      ret *= fAmbient + (Color * light[i].color * light[i].power * fDiffuse)
	+ (Color * light[i].color * light[i].power * pow(fSpec, 5));
    }
  return (ret);
}

void main(void)
{
  /* Density of the fog */
  float density = 0.07;

  vec4 fOutColor = texture2D(fTexture0, fUv);
  float factor = getFog(abs(fEyePos.z / fEyePos.w), density);
  vec3 color = getLight(fOutColor.xyz, fNormal);

  gl_FragColor = vec4(fOutColor.xyz, fOutColor.w);
  /* Color Fog = vec4(0.7, 0.7, 0.7, 1.0) => grey */
  /* gl_FragColor = mix(color, vec4(0.7, 0.7, 0.7, color.w), factor); */
}
