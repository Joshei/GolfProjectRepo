#version 330 core

layout (location = 0) in vec3 aPos;

layout (location = 1) in vec3 aColor;




////

out vec3 ourColor;











//uniform mat4 MVP;

uniform mat4 modelMatrix;



uniform mat4 view;

uniform mat4 projection;



void main()

{






	ourColor = aColor;



	//gl_Position =  MVP   *( vec4(aPos, 1.0f))    ;

    gl_Position =  projection * view * modelMatrix * ( vec4(aPos, 1.0f))    ;





  

	



} 