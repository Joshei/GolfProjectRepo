#include <C:/openglusage/glad/include/glad/glad.h>
#include <C:/openglusage/GLFW/glfw3.h>

#include <C:/openglusage/glm/glm.hpp>
#include <C:/openglusage/glm/gtc/matrix_transform.hpp>
#include <C:/openglusage/glm/gtc/type_ptr.hpp>


//#include <C:/openglusage/headershader/common.h>
//#include <C:/openglusage/headershader/loader.h>
#include <vector>
#include <C:/Users/Joshua Eirman/Source/repos/GOLFPROJ/GOLFPROJ/shader_s.h>
#include <C:/openglusage/glm/glm.hpp>
#include <iostream>


// An array of 3 vectors which represents 3 vertices
static const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};



//test---another test--and one more--

//#include <GL/glew.h>
//#include <GL/GL.h>
//used with initial single page
//unsigned int VAO1, VBO1;
GLuint elementbuffer;
std::vector< unsigned int > vertexIndices, uvIndices, normalIndices, indicesadjusted;
//test

std::vector< glm::vec2 > uvs;
std::vector< glm::vec3 > normals; // Won't be used at the moment.
std::vector< glm::vec3 >vertices;

std::vector < glm::vec3 >  temp_vertices;
std::vector < glm::vec2 >  temp_uvs;
std::vector < glm::vec3 >  temp_normals;

//std::vector < glm::vec3 >  indicesadjusted;






FILE * file;



//unsigned int VBO1, VAO1;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;





int main()
{
	


	


	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	////////////////////////











	//////////////////////////

	// build and compile our shader program
	// ------------------------------------
	//Shader ourShader("3.3.shader.vs", "3.3.shader.fs"); // you can name your shader files however you like
	Shader ourShader("C:/Users/Joshua Eirman/Source/Repos/GOLFPROJ/GOLFPROJ/3.3.shader.vs",
		"C:/Users/Joshua Eirman/Source/Repos/GOLFPROJ/GOLFPROJ/3.3.shader.fs"); // you can name your shader files however you like



	ourShader.use();



	//// set up vertex data (and buffer(s)) and configure vertex attributes
	//// ------------------------------------------------------------------
	//float vertices2[] = {
	//    // positions         // colors
	//     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
	//    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
	//     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
	//};

	

	GLuint VertexArrayID;

	glGenVertexArrays(1, &VertexArrayID);

	glBindVertexArray(VertexArrayID);





	//////////////////////////////


	
	//file = fopen("C:/images for opengl/marble.obj", "r");
	file = fopen("C:/images for opengl/cube100.obj", "r");
	if (file == NULL) {
		printf("Impossible to open the file !\n");
		return(1);
	}

	


	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

				   // else : parse lineHeader



		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);


		}
		//else if (strcmp(lineHeader, "vt") == 0) {
		//	glm::vec2 uv;
		//	fscanf(file, "%f %f\n", &uv.x, &uv.y);
		//	temp_uvs.push_back(uv);
		//}
		//else if (strcmp(lineHeader, "vn") == 0) {
		//	glm::vec3 normal;
		//	fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
		//	temp_normals.push_back(normal);
		//}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];


			//int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);

			//changed source data .onj file faces to one slash!
			int matches = fscanf(file, "%d/%d %d/%d %d/%d\n", &vertexIndex[0], &uvIndex[0], &vertexIndex[1], &uvIndex[1], &vertexIndex[2], &uvIndex[2]);


			if (matches != 6) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return false;
			}


			std::vector < glm::vec3 >  temp_normals;


			//.push_back((vertexIndex[0]));
			//.push_back((vertexIndex[1]));
			
			//adjsuted for array
			indicesadjusted.push_back((vertexIndex[0])- 1);
			indicesadjusted.push_back((vertexIndex[1]) - 1);
			indicesadjusted.push_back((vertexIndex[2]) - 1);

			vertexIndices.push_back((vertexIndex[0]));
			vertexIndices.push_back((vertexIndex[1]));
			vertexIndices.push_back((vertexIndex[2]));
			//uvIndices.push_back(uvIndex[0]);
			//uvIndices.push_back(uvIndex[1]);
			//uvIndices.push_back(uvIndex[2]);
			//normalIndices.push_back(normalIndex[0]);
			//normalIndices.push_back(normalIndex[1]);
			//i added this:
			//normalIndices.push_back(normalIndex[2]);
		}



	}

	// //PROCESSING DATA, do I ever use this
	
	 





http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/


	// This will identify our vertex buffer
//	GLuint vertexbuffer1;
//	// Generate 1 buffer, put the resulting identifier in vertexbuffer
//	glGenBuffers(1, &vertexbuffer1);
//	// The following commands will talk about our 'vertexbuffer' buffer
//	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer1);
//	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);









	for (unsigned int i = 0; i < vertexIndices.size(); i++) {

		//this holds the indicies
		unsigned int g = ((vertexIndices[i]) - 1 );

		

		
		//check this should be fine
		glm::vec3 vertex = temp_vertices[g ];

		
		//these are the vericies
		//https://gamedev.stackexchange.com/questions/68838/what-is-the-purpose-of-indices-in-3d-rendering
		vertices.push_back(vertex);


	}

	//just loaded...

	

	
//// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	
	
//  http:/ /www.opengl-tutorial.org/intermediate-tutorials/tutorial-9-vbo-indexing/
	
	
	
	//load into vbo
	GLuint vertexbuffer;

	glGenBuffers(1, &vertexbuffer);

	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);




	// Generate a buffer for the indices as well

	GLuint elementbuffer;

	glGenBuffers(1, &elementbuffer);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesadjusted.size() * sizeof(unsigned short), &indicesadjusted[0], GL_STATIC_DRAW);


	
	
	static const GLfloat g_color_buffer_data[] = {
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,

		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,

		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,

		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,

		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,

		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,

		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		
		
		0.583f,  0.771f,  0.014f
		
	
	};



	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

	// 2nd attribute buffer : colors
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);



	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);
		












		glClearColor(0.2f, 1.3f, 0.3f, 1.0f);

	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		

		

		//glm::mat4 model2 = { {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1} };
		glm::mat4 model = { {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1} };
		//glm::mat4 view = { {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1} };
		//glm::mat4 projection = { {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1} };

		//glm::mat4 mad
		
		glm::vec3 scale = glm::vec3(.1, .1, .1);
		model = glm::scale(model, scale);
//		//yplane third arg    2nd arg y axis
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 0.0f, 0.0f));
//
//		//https://stackoverflow.com/questions/36635824/how-to-scale-a-model-in-opengl
//
		
//		//1:
//		//2: around the y axis
//		//3: aroond the z axis
//
		unsigned int transformLoc1 = glGetUniformLocation(ourShader.ID, "model");
		glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
//
//		unsigned int transformLoc2 = glGetUniformLocation(ourShader.ID, "view");
//		//glUniformMatrix4fv(transformLoc2, 1, GL_FALSE, glm::value_ptr(view));


		/////////

		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);





		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

		// Draw the triangles !
		glDrawElements(
			GL_TRIANGLES,      // mode
			vertexIndices.size(),    // count
			GL_UNSIGNED_INT,   // type
			(void*)0           // element array buffer offset
		);


		/////////////


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	

	//glDeleteVertexArrays(1, &VAO1);
	//glDeleteBuffers(1, &VBO1);
	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate(); #include <C:/openglusage/glad/include/glad/glad.h>
#include <C:/openglusage/GLFW/glfw3.h>

#include <C:/openglusage/glm/glm.hpp>
#include <C:/openglusage/glm/gtc/matrix_transform.hpp>
#include <C:/openglusage/glm/gtc/type_ptr.hpp>


		//#include <C:/openglusage/headershader/common.h>
		//#include <C:/openglusage/headershader/loader.h>
#include <vector>
#include <C:/Users/Joshua Eirman/Source/repos/GOLFPROJ/GOLFPROJ/shader_s.h>
#include <C:/openglusage/glm/glm.hpp>
#include <iostream>


//test---another test--and one more--

//#include <GL/glew.h>
//#include <GL/GL.h>
//used with initial single page
//unsigned int VAO1, VBO1;
GLuint elementbuffer;
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices, indicesadjusted;
	//test

	std::vector< glm::vec2 > uvs;
	std::vector< glm::vec3 > normals; // Won't be used at the moment.
	std::vector< glm::vec3 >vertices;

	std::vector < glm::vec3 >  temp_vertices;
	std::vector < glm::vec2 >  temp_uvs;
	std::vector < glm::vec3 >  temp_normals;

	//std::vector < glm::vec3 >  indicesadjusted;






	FILE * file;



	//unsigned int VBO1, VAO1;

	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void processInput(GLFWwindow *window);

	// settings
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;





	int main()
	{






		// glfw: initialize and configure
		// ------------------------------
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
		GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

		// glad: load all OpenGL function pointers
		// ---------------------------------------
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return -1;
		}


		////////////////////////











		//////////////////////////

		// build and compile our shader program
		// ------------------------------------
		//Shader ourShader("3.3.shader.vs", "3.3.shader.fs"); // you can name your shader files however you like
		Shader ourShader("C:/Users/Joshua Eirman/Source/Repos/GOLFPROJ/GOLFPROJ/3.3.shader.vs",
			"C:/Users/Joshua Eirman/Source/Repos/GOLFPROJ/GOLFPROJ/3.3.shader.fs"); // you can name your shader files however you like



		ourShader.use();



		//// set up vertex data (and buffer(s)) and configure vertex attributes
		//// ------------------------------------------------------------------
		//float vertices2[] = {
		//    // positions         // colors
		//     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		//    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		//     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
		//};



		GLuint VertexArrayID;

		glGenVertexArrays(1, &VertexArrayID);

		glBindVertexArray(VertexArrayID);





		//////////////////////////////



		//file = fopen("C:/images for opengl/marble.obj", "r");
		file = fopen("C:/images for opengl/cube100.obj", "r");
		if (file == NULL) {
			printf("Impossible to open the file !\n");
			return(1);
		}




		while (1) {

			char lineHeader[128];
			// read the first word of the line
			int res = fscanf(file, "%s", lineHeader);
			if (res == EOF)
				break; // EOF = End Of File. Quit the loop.

					   // else : parse lineHeader



			if (strcmp(lineHeader, "v") == 0) {
				glm::vec3 vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				temp_vertices.push_back(vertex);


			}
			//else if (strcmp(lineHeader, "vt") == 0) {
			//	glm::vec2 uv;
			//	fscanf(file, "%f %f\n", &uv.x, &uv.y);
			//	temp_uvs.push_back(uv);
			//}
			//else if (strcmp(lineHeader, "vn") == 0) {
			//	glm::vec3 normal;
			//	fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			//	temp_normals.push_back(normal);
			//}
			else if (strcmp(lineHeader, "f") == 0) {
				std::string vertex1, vertex2, vertex3;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];


				//int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);

				//changed source data .onj file faces to one slash!
				int matches = fscanf(file, "%d/%d %d/%d %d/%d\n", &vertexIndex[0], &uvIndex[0], &vertexIndex[1], &uvIndex[1], &vertexIndex[2], &uvIndex[2]);


				if (matches != 6) {
					printf("File can't be read by our simple parser : ( Try exporting with other options\n");
					return false;
				}


				std::vector < glm::vec3 >  temp_normals;


				//.push_back((vertexIndex[0]));
				//.push_back((vertexIndex[1]));

				//adjsuted for array
				indicesadjusted.push_back((vertexIndex[0]) - 1);
				indicesadjusted.push_back((vertexIndex[1]) - 1);
				indicesadjusted.push_back((vertexIndex[2]) - 1);

				vertexIndices.push_back((vertexIndex[0]));
				vertexIndices.push_back((vertexIndex[1]));
				vertexIndices.push_back((vertexIndex[2]));
				//uvIndices.push_back(uvIndex[0]);
				//uvIndices.push_back(uvIndex[1]);
				//uvIndices.push_back(uvIndex[2]);
				//normalIndices.push_back(normalIndex[0]);
				//normalIndices.push_back(normalIndex[1]);
				//i added this:
				//normalIndices.push_back(normalIndex[2]);
			}



		}

		// //PROCESSING DATA, do I ever use this


		for (unsigned int i = 0; i < vertexIndices.size(); i++) {

			//this holds the indicies
			unsigned int g = ((vertexIndices[i]) - 1);




			//check this should be fine
			glm::vec3 vertex = temp_vertices[g];


			//these are the vericies
			//https://gamedev.stackexchange.com/questions/68838/what-is-the-purpose-of-indices-in-3d-rendering
			vertices.push_back(vertex);


		}

		//just loaded...




	//// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).


	//  http:/ /www.opengl-tutorial.org/intermediate-tutorials/tutorial-9-vbo-indexing/



		//load into vbo
		GLuint vertexbuffer;

		glGenBuffers(1, &vertexbuffer);

		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);




		// Generate a buffer for the indices as well

		GLuint elementbuffer;

		glGenBuffers(1, &elementbuffer);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesadjusted.size() * sizeof(unsigned short), &indicesadjusted[0], GL_STATIC_DRAW);




		static const GLfloat g_color_buffer_data[] = {
			0.583f,  0.771f,  0.014f,
			0.583f,  0.771f,  0.014f,
			0.583f,  0.771f,  0.014f,
			0.583f,  0.771f,  0.014f,
			0.583f,  0.771f,  0.014f,

			0.583f,  0.771f,  0.014f,
			0.583f,  0.771f,  0.014f,
			0.583f,  0.771f,  0.014f,
			0.583f,  0.771f,  0.014f,
			0.583f,  0.771f,  0.014f,

			0.583f,  0.771f,  0.014f,
			0.583f,  0.771f,  0.014f,
			0.583f,  0.771f,  0.014f,
			0.583f,  0.771f,  0.014f,
			0.583f,  0.771f,  0.014f,

			0.583f,  0.771f,  0.014f,
			0.583f,  0.771f,  0.014f,
			0.583f,  0.771f,  0.014f,
			0.583f,  0.771f,  0.014f,
			0.583f,  0.771f,  0.014f,

			0.583f,  0.771f,  0.014f,
			0.583f,  0.771f,  0.014f,
			0.583f,  0.771f,  0.014f,
			0.583f,  0.771f,  0.014f,
			0.583f,  0.771f,  0.014f,

			0.583f,  0.771f,  0.014f,
			0.583f,  0.771f,  0.014f,
			0.583f,  0.771f,  0.014f,
			0.583f,  0.771f,  0.014f,
			0.583f,  0.771f,  0.014f,

			0.583f,  0.771f,  0.014f,
			0.583f,  0.771f,  0.014f,
			0.583f,  0.771f,  0.014f,
			0.583f,  0.771f,  0.014f,
			0.583f,  0.771f,  0.014f,


			0.583f,  0.771f,  0.014f


		};



		GLuint colorbuffer;
		glGenBuffers(1, &colorbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

		// 2nd attribute buffer : colors
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);



		// render loop
		// -----------
		while (!glfwWindowShouldClose(window))
		{
			// input
			// -----
			processInput(window);



			glClearColor(0.2f, 1.3f, 0.3f, 1.0f);


			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);




			//glm::mat4 model2 = { {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1} };
			glm::mat4 model = { {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1} };
			//glm::mat4 view = { {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1} };
			//glm::mat4 projection = { {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1} };

			//glm::mat4 mad

			glm::vec3 scale = glm::vec3(.1, .1, .1);
			model = glm::scale(model, scale);
			//		//yplane third arg    2nd arg y axis
			model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 0.0f, 0.0f));
			//
			//		//https://stackoverflow.com/questions/36635824/how-to-scale-a-model-in-opengl
			//

			//		//1:
			//		//2: around the y axis
			//		//3: aroond the z axis
			//
			unsigned int transformLoc1 = glGetUniformLocation(ourShader.ID, "model");
			glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
			//
			//		unsigned int transformLoc2 = glGetUniformLocation(ourShader.ID, "view");
			//		//glUniformMatrix4fv(transformLoc2, 1, GL_FALSE, glm::value_ptr(view));


					/////////

			glEnableVertexAttribArray(0);

			glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);





			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

			// Draw the triangles !
			glDrawElements(
				GL_TRIANGLES,      // mode
				vertexIndices.size(),    // count
				GL_UNSIGNED_INT,   // type
				(void*)0           // element array buffer offset
			);


			/////////////


			// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
			// -------------------------------------------------------------------------------
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		// optional: de-allocate all resources once they've outlived their purpose:
		// ------------------------------------------------------------------------


		//glDeleteVertexArrays(1, &VAO1);
		//glDeleteBuffers(1, &VBO1);
		// glfw: terminate, clearing all previously allocated GLFW resources.
		// ------------------------------------------------------------------
		glfwTerminate();
		return 0;
	}

	// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
	// ---------------------------------------------------------------------------------------------------------
	void processInput(GLFWwindow *window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
	}

	// glfw: whenever the window size changed (by OS or user resize) this callback function executes
	// ---------------------------------------------------------------------------------------------
	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		// make sure the viewport matches the new window dimensions; note that width and 
		// height will be significantly larger than specified on retina displays.
		glViewport(0, 0, width, height);
	}



	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}


