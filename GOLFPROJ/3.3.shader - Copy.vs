//#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
}



//#version 330 core
//layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aColor;

////in vec3 incolor = (1,1,1)
//out vec3 ourColor;

//void main()
//{
//    gl_Position = vec4(aPos, 1.0);
//    //ourColor = aColor;
//	ourColor = aColor;
//
//}


//layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec2 aTexCoord;

//out vec2 TexCoord;

//uniform mat4 model;
//uniform mat4 model = {.1,.1,.1.2,.2,.2,.1,.1,.1.2,.1,.1,.1.2,.2,.2};
//uniform mat4 view;
//uniform mat4 projection;



//void main()
//{
//	//gl_Position = projection sfdsdf* view * model * vec4(aPos, 1.0);
//	gl_Position = model * vec4(aPos, 1.0);
//	//* vec4(aPos, 1.0);
//	//TexCoord = vec2(aTexCoord.x, aTexCoord.y);
//}



//#version 330 core
//layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aColor;

//out vec3 ourColor;

//void main()
//{
 //   gl_Position = vec4(aPos, 1.0);
 //   ourColor = aColor;
//}
