#version 150

uniform	vec4 diffuse;

in Data{
	vec3 normal;
	vec3 l_dir;
};

out vec4 outputF;

void main()
{
float i= max(0, dot(normal,l_dir));
 //if(i<0.3) c= vec4(0,2);
 // if(i<0,5) c=(0,4);
 //else if (i<0,7) c=(0,6);
 //else c=(0,8);
 
 
 
 outputF = i*diffuse;
 

}
