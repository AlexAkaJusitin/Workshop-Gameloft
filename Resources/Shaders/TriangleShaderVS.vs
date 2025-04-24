attribute vec3 a_posL;
attribute vec3 a_color; 
varying vec3 v_color;
uniform mat4 u_rotation;
void main()
{
vec4 posL = vec4(a_posL, 5.0);
//gl_Position = posL;
v_color = a_color;
gl_Position = posL * u_rotation;

}
   