#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

//out vec2 TexCoord;



//uniform mat4 MVP;
uniform mat4 modelMatrix;
uniform mat4 translate;
uniform mat4 view;
uniform mat4 projection;

void main()
{

	//ourColor = aColor;

	//gl_Position =  MVP   *( vec4(aPos, 1.0f))    ;
    gl_Position =  projection * view * modelMatrix * translate * ( vec4(aPos, 1.0f))    ;

	ourColor = vec3(0.5, 1.0, 0);

  //  TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	

} 