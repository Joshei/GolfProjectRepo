#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec4 ourColor;

//out vec2 TexCoord;



//uniform mat4 MVP;
uniform mat4 modelMatrix;
//uniform mat4 model2;
uniform mat4 view;
//uniform mat4 projection;

void main()
{

	//ourColor = aColor;

	//gl_Position =  MVP   *( vec4(aPos, 1.0f))    ;
    gl_Position =  view * modelMatrix * ( vec4(aPos, 1.0f))    ;

	ourColor = vec4(0.5, 0.0, 0.0, 1.0);

  //  TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	

} 