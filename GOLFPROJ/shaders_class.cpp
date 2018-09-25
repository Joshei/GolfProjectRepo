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


//test---another test--and one more--

//#include <GL/glew.h>
//#include <GL/GL.h>
//used with initial single page
unsigned int VAO1, VBO1;

std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
//test

std::vector< glm::vec2 > uvs;
std::vector< glm::vec3 > normals; // Won't be used at the moment.
std::vector< glm::vec3 >vertices;

std::vector < glm::vec3 >  temp_vertices;
std::vector < glm::vec2 >  temp_uvs;
std::vector < glm::vec3 >  temp_normals;






FILE * file;



//unsigned int VBO1, VAO1;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//std::vector< glm::vec3 >vertices2;



int main()
{
	std::vector<unsigned int> indices;


	//GLuint elementbuffer;
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);




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







	//// set up vertex data (and buffer(s)) and configure vertex attributes
	//// ------------------------------------------------------------------
	//float vertices2[] = {
	//    // positions         // colors
	//     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
	//    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
	//     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
	//};

	//18 indexes

	//int checktthis = sizeof(vertices2);

	//unsigned int VBO, VAO;
	//glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &VBO);
	//// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	//glBindVertexArray(VAO);

	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	//// position attribute
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);
	//// color attribute
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	//// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	//// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	//// glBindVertexArray(0);

	//////////////////////////////added by Josh














//second set to display

//	float vertices2[] = {
//		// positions         // colors
//		0.2f, -0.2f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
//		-0.2f, -0.2f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
//		0.0f,  0.2f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
//	};




	//////////////////////////////


	//loads the image file (.obj)
	//int a = functionLoadA();

	//testimagegiven.obj
	//cubeimag.obj
	//file = fopen("C:/images for opengl/marble.obj", "r");
	file = fopen("C:/images for opengl/.obj", "r");
	if (file == NULL) {
		printf("Impossible to open the file !\n");
		return;
	}

	//////////
	//////////////////////////////

	//builds the array for rendering and uses the old code there to set
	//up the bufferdata
	//int b = loadobjmodelandrender();


	//this will be a class taken from : loading.cpp to : //endofcodesection


	////externed in common.h
	//glGenVertexArrays(1, &VAO1);
	//glGenBuffers(1, &VBO1);
	//// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	//glBindVertexArray(VAO1);

	//glBindBuffer(GL_ARRAY_BUFFER, VBO1);


	////glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);




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
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			//uvIndices.push_back(uvIndex[0]);
			//uvIndices.push_back(uvIndex[1]);
			//uvIndices.push_back(uvIndex[2]);
			//normalIndices.push_back(normalIndex[0]);
			//normalIndices.push_back(normalIndex[1]);
			//i added this:
			//normalIndices.push_back(normalIndex[2]);
		}//this was missing from source code



	}//uncertain

	// //PROCESSING DATA
	// // For each vertex of each triangle
	
	//for (unsigned int i = 0; i < vertexIndices.size(); i++) {

	for (unsigned int i = 0; i < vertexIndices.size(); i++) {

		//has verices loaded in 
		unsigned int g = vertexIndices[i];

		

		//unsigned int g;
		//check this should be fine
		glm::vec3 vertex = temp_vertices[g-1 ];


		//chech this as out?
		vertices.push_back(vertex);


	}

	//int xx = vertices.size();

	///////////////////




	//signed int VBO1;// , VAO1;
	glGenVertexArrays(1, &VAO1);
	glGenBuffers(1, &VBO1);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO1);


	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(temp_vertices),temp_vertices, GL_STATIC_DRAW);



	//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	////just moved here

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(0);







	//static const GLfloat g_color_buffer_data[] = {
	//	0.583f,  0.771f,  0.014f
	//};



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
		//0.583f,  0.771f,  0.014f
		
		


		


	
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






//	 color attribute
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//	glEnableVertexAttribArray(1);


	//endofcodesection



	//possibly put render code in here!  If so, no need for common.h externs!

	//could try moving this if there is a failure during testing!
	//glBindVertexArray(VAO1);
	//glDrawArrays(GL_TRIANGLES, 0, 3);

	///////////////////











	//////////////////////////////







	//all this, now in function:  loadobjmodelandrender();


	//unsigned int VBO1, VAO1;
	//glGenVertexArrays(1, &VAO1);
	//glGenBuffers(1, &VBO1);
	//// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	//glBindVertexArray(VAO1);

	//glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	//
	//
	////glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);






	//out of the function completes this and renders



	// position attribute
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//	// color attribute
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);



	/////////////////////////////




	//glm::mat4 transform = { {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1} };

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);
		//
		// render
		// ------

		ourShader.use();


		// Enable depth test
		//glEnable(GL_DEPTH_TEST);
		// Accept fragment if it closer to the camera than the former one
		//glDepthFunc(GL_LESS);


		//glClearColor(0.2f, 1.3f, 0.3f, 1.0f);

		//glClear(GL_COLOR_BUFFER_BIT);

	

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glClear(GL_COLOR_BUFFER_BIT);

		//glEnable(GL_CULL_FACE);

		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_FRONT);
		// render the triangle-
		
		/////////////////////
		

		


		glm::mat4 model = { {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1} };
		glm::mat4 view = { {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1} };
		glm::mat4 projection = { {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1} };


		

	
		
		
		

		

		
		
				
		//yplane third arg    2nd arg y axis
		//model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

		//https://stackoverflow.com/questions/36635824/how-to-scale-a-model-in-opengl

		glm::vec3 scale =  glm::vec3(.1, .1, .1);
		model = glm::scale(model, scale);

		
		view = glm::rotate(view, (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 1.0f));




		//1:
		//2: around the y axis
		//3: aroond the z axis

		


		


		
		//view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));

	//	projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);


		

		//ourShader.use();


		//transform = glm::translate(transform, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
		//transform = glm::scale(transform, glm::vec3(.2, .2, .2));

		unsigned int transformLoc1 = glGetUniformLocation(ourShader.ID, "model");
		//glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));

		unsigned int transformLoc2 = glGetUniformLocation(ourShader.ID, "view");
		//glUniformMatrix4fv(transformLoc2, 1, GL_FALSE, glm::value_ptr(view));

		///unsigned int transformLoc3 = glGetUniformLocation(ourShader.ID, "projection");
		///glUniformMatrix4fv(transformLoc3, 1, GL_FALSE, glm::value_ptr(model));





		//glm::vec3 scale = glm::vec3(10, 10, 10);


		//glm::mat4 modelMatrix = glm::mat4();
		//modelMatrix = glm::scale(modelMatrix, scale);
		//
		//GLuint location = glGetUniformLocation(ourShader.ID, "model");
		//glUniformMatrix4fv(location , 1, false, glm::value_ptr(modelMatrix));


		////Model = glm::translate(Model, glm::vec3(0.1f, 0.2f, 0.5f));
		//
		//////Model = glm::translate(Model, glm::vec3(0.1f, 0.2f, 0.5f));

		////model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		//
		//
		//model = glm::translate(model, glm::vec3(10.0f, 0.0f, -3.0f));
		////
		////
		//projection = glm::perspective(glm::radians(65.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		////// retrieve the matrix uniform locations
		//
		//
		//unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
		//unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
		
		
		
		
		//////// pass them to the shaders (3 different ways)
		glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(transformLoc2, 1, GL_FALSE, &view[0][0]);
		//////// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		//
		////ourShader.setMat4("model", model);

//		ourShader.setMat4("projection", projection);




		//////////////////////






		//glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		//could try moving this if there is a failure during testing!
		glBindVertexArray(VAO1);

		//glDisable(GL_CULL_FACE);


		//glDrawElements(GL_TRIANGLES, 36,GL_UNSIGNED_INT, &vertexIndices);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	//glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);

	glDeleteVertexArrays(1, &VAO1);
	glDeleteBuffers(1, &VBO1);
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


//v 0.5f -0.5f 0.0f 
//v 0.5f -0.5f 0.0f  
//v 0.0f  0.5f 0.0f