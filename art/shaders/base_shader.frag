
/*struct gl_LightSourceParameters 
{   
   vec4 ambient;              // Aclarri   
   vec4 diffuse;              // Dcli   
   vec4 specular;             // Scli   
   vec4 position;             // Ppli   
   vec4 halfVector;           // Derived: Hi   
   vec3 spotDirection;        // Sdli   
   float spotExponent;        // Srli   
   float spotCutoff;          // Crli                              
                              // (range: [0.0,90.0], 180.0)   
   float spotCosCutoff;       // Derived: cos(Crli)                 
                              // (range: [1.0,0.0],-1.0)   
   float constantAttenuation; // K0   
   float linearAttenuation;   // K1   
   float quadraticAttenuation;// K2  
};    


uniform gl_LightSourceParameters gl_LightSource[gl_MaxLights];
*/
/*
struct gl_MaterialParameters  
{   
   vec4 emission;    // Ecm   
   vec4 ambient;     // Acm   
   vec4 diffuse;     // Dcm   
   vec4 specular;    // Scm   
   float shininess;  // Srm  
} test;  
*/

//uniform gl_MaterialParameters gl_FrontMaterial;  
//uniform gl_MaterialParameters gl_BackMaterial;   
varying vec4 fragmentNormal;
varying vec4 vertexCoord;
varying vec4 eyePos;
void main (void)  
{
	vec4 L = vertexCoord-gl_LightSource[0].position;
	L = normalize(L);
	vec4 N = normalize(fragmentNormal);
	vec4 V = normalize(eyePos);
	vec4 h = normalize(L + V);
	float spec = max(dot(N, h), 0.0);
	vec4 specular = max(vec4(0.0),gl_FrontMaterial.specular * pow(spec, gl_FrontMaterial.shininess));
   gl_FragColor = gl_FrontMaterial.ambient + max(vec4(0.0), dot(N, L)) * gl_FrontMaterial.diffuse + specular;  
   gl_FragColor.a = 1.0;
   //gl_FragColor = gl_FrontMaterial.shininess.rrrr;
   //gl_FragColor = max(vec4(0.0), dot(L, N)) * gl_FrontMaterial.diffuse;
   //gl_FragColor.a = 1.0;
}   