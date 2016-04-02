
varying vec4 fragmentNormal;
varying vec4 vertexCoord;
varying vec4 eyePos;

void main(void)
{
   vec4 a = gl_Vertex;
   //a.x = a.x * 0.5;
   //a.y = a.y * 0.5;
   fragmentNormal = vec4(gl_Normal.xyz,0.0);
   vertexCoord = gl_Vertex;
   eyePos = -(gl_ModelViewMatrix * a);

   gl_Position = gl_ModelViewProjectionMatrix * a;
}      