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
//#include <open32.h>

#include <string.h>
#include <iostream>
#include <windows.h>

//#include <C:/openglusage/
#include <gl/gl.h>
#include <gl/glu.h>

#define BITMAP_ID 0x4D42		      // the universal bitmap ID


//used in intializeterrain
#define MAP_X	32//32				         // size of map along x-axis
#define MAP_Z	32//32				         // size of map along z-axis
#define MAP_SCALE	.0f		         // the scale of the terrain map


//int gwidth;
//int gheight;
//float* gvertices = 0;
int* gindices = 0;




bool LoadtheTextures(void);

unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader);
void InitializeTerrain();



int getIndicesCount(int _width, int _height);

int* getIndices(int _width, int _height);

//int getIndicesCount(int _width, int _height);

//int getVerticesCount(int _width, int _height);

float* getVertices(int depth, int columns);

int getVerticesCount(int width, int height);





//test---another test--and one more--

//#include <GL/glew.h>
//#include <GL/GL.h>
//used with initial single page
GLuint VAO1, VBO1;

std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
//test

std::vector< glm::vec2 > uvs;
std::vector< glm::vec3 > normals; // Won't be used at the moment.
std::vector< glm::vec3 >vertices;

std::vector < glm::vec3 >  temp_vertices, temp_vertices1, mathvertices;
std::vector < glm::vec2 >  temp_uvs;
std::vector < glm::vec3 >  temp_normals;



////// Texture Information
BITMAPINFOHEADER	bitmapInfoHeader;	// temp bitmap info header
BITMAPINFOHEADER	landInfo;

unsigned char * landTexture;
FILE * file;



//unsigned int VBO1, VAO1;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//std::vector< glm::vec3 >vertices2;



unsigned int		   land;			      // the land texture object

unsigned char*	      imageData;		   // the map image data

////// Terrain Data
float terrain[MAP_X][MAP_Z][3];		// heightfield terrain data (0-255); 256x256

//GLfloat g_vertex_buffer_data_land[24];


//gvertices = new float[getVerticesCount(width, height)];

//10x10x3
float gvertices[300];// = new float[getVerticesCount(width, height)];


//int i = 0;
int i = 0;

//indices
//8 x 3
GLfloat g_vertex_buffer_data_land[36*2] = {};

//		-1.0f, -1.0f,  0.0f ,
//		//
//			1.0f, -1.0f,  0.0f,
//			0.0f,  1.0f,  0.0f,
//
//
//1.0,  1.0,  1.0,
//-1.0, -1.0, -1.0,
//1.0, -1.0, -1.0, };


//-1.0,  1.0, -1.0,
//1.0,  1.0, -1.0,

int main()

{




	std::vector<unsigned int> indices;


	//	//GLuint elementbuffer;
	//	glGenBuffers(1, &elementbuffer);
	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);




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





	//this is original load from.obj and use face and vertices to draw a model
	//the new code is send through:
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);



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
	file = fopen("C:/images for opengl/cube100.obj", "r");
	if (file == NULL) {
		printf("Impossible to open the file !\n");
		return(1);
	}


	char  filename[] = "terrain2.bmp";

	imageData = LoadBitmapFile(filename, &bitmapInfoHeader);
	if (imageData == NULL) {
		printf("Impossible to open the second file !\n");
		return(1);
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




	//vertices
	//getVertices(1,0);




	/////////////////




	int j = 0;



	//for (unsigned int i = 0; i < vertexIndices.size(); i++) {

	//	//has verices loaded in 
	//	//unsigned int g = vertexIndices[i];



	//	//unsigned int g;
	//	//check this should be fine
	//	//glm::vec3 vertex = vertices[g - 1];


	//	//chech this as out?
	//	//vertices.push_back(vertex);


	//	//fills this temporary array for experimentation in a linear fashion
	//	g_vertex_terrain_data[j] = vertex.x;
	//	j++;
	//	g_vertex_terrain_data[j] = vertex.y;
	//	j++;
	//	g_vertex_terrain_data[j] = vertex.z;
	//	j++;
	//}



	/////////////////


	//GLfloat g_vertex_buffer_data[36 * 3];

	//int j = 0;



	//for (unsigned int i = 0; i < vertexIndices.size(); i++) {

	//	//has verices loaded in 
	//	unsigned int g = vertexIndices[i];



	//	//unsigned int g;
	//	//check this should be fine
	//	glm::vec3 vertex = temp_vertices[g - 1];


	//	//chech this as out?
	//	vertices.push_back(vertex);


	//	//fills this temporary array for experimentation in a linear fashion
	//	g_vertex_buffer_data[j] = vertex.x;
	//	j++;
	//	g_vertex_buffer_data[j] = vertex.y;
	//	j++;
	//	g_vertex_buffer_data[j] = vertex.z;
	//	j++;
	//}


	//GLfloat g_vertex_buffer_data[36*3];

	////three times the amount for x y and z in linear fasion
	////to check the .obj file as a structure because it was malformed 
	////with loading code
	//for (int i = 0; i < 36 * 3;)
	//{
	//	glm::vec3 tempvector = temp_vertices1.pop_back();

	//	int x = tempvector.x;

	//	g_vertex_buffer_data[i] = x;
	//	i++;

	//	int y = tempvector.y;
	//	g_vertex_buffer_data[i] = y;
	//	i++;

	//	int z = tempvector.z;
	//	g_vertex_buffer_data[i] = z;
	//	i++;
	//}



	//right here put into a structure : 

	//// An array of 3 vectors which represents 3 vertices
	//static const GLfloat g_vertex_buffer_data[] = {
	//   -1.0f, -1.0f, 0.0f,
	//   1.0f, -1.0f, 0.0f,
	//   0.0f,  1.0f, 0.0f,
	//};



	//SETTING UP A VERTEX ARRAY OBJECT

	//signed int VBO1;// , VAO1;
	glGenVertexArrays(1, &VAO1);
	//glGenBuffers(1, &VBO1);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO1);










	//////////////////////////////////////////

	//CREATING FOR OPENGL - CREATING A BUFFER - for cube that is loaded from .obj
	//and parsed to data

	// This will identify our vertex buffer
	//GLuint vertexbufferint;
	//// Generate 1 buffer, put the resulting identifier in vertexbuffer
	//glGenBuffers(1, &vertexbufferint);
	//// The following commands will talk about our 'vertexbuffer' buffer
	//glBindBuffer(GL_ARRAY_BUFFER, vertexbufferint);
	//// Give our vertices to OpenGL.   heh, heh, heh
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);




	///////////////////////////////////
	//THIS IS FOR LAND


	//InitializeTerrain();
	//LoadtheTextures();


	//sets g_vertex_buffer_data_land

	//width , height : there are two triangles for each width column
	//two columns : (four triangles)
	//times two columns : 8 triangles

	//depth, row
	getVertices(2, 1);



	// This will identify our vertex buffer
	GLuint vertexbufferLAND;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbufferLAND);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbufferLAND);
	// Give our vertices to OpenGL.   heh, heh, heh
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data_land), g_vertex_buffer_data_land, GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbufferLAND);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);








	//see this:  https://stackoverflow.com/questions/5915753/generate-a-plane-with-triangle-strips
	/////////////////////////////////

	//stopped here, need to fill buffer data for render

	//getIndices
	//getVertices







		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(temp_vertices),temp_vertices, GL_STATIC_DRAW);
		//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
		//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);






	////////////////////////////THIS  IS THE COLOR USAGE FOR CUBE WORKING FINE COMMENTED OUT TO GET LAND WORKING!
	//10/1/18
	//

	static const GLfloat g_color_buffer_data[] = {

		//0
		0.183f,  0.171f,  0.314f,
		0.783f,  0.471f,  0.514f,
		0.683f,  0.671f,  0.614f,
		0.583f,  0.371f,  0.014f,
		0.383f,  0.371f,  0.314f,
		//5
		0.283f,  0.271f,  0.214f,
		0.183f,  0.371f,  0.814f,
		0.583f,  0.771f,  0.014f,
		0.283f,  0.271f,  0.214f,
		0.183f,  0.171f,  0.514f,
		//10
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		//15
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		//20
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		//25
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		//30
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		//35

		//////////////

		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		//5
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		//10
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		//15
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		//20
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		//25
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		//30
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		//35 - 70
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,

		0.583f,  0.771f,  0.014f,
		0.583f,  0.771f,  0.014f,




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



	//glDisableVertexAttribArray(1);


////////////////////END OF WAS WORKING COLORS FOR CUBE////





		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

		//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);








///////////////////////////////////////////////
//		 RENDER LOOP
///////////////////////////// -----------

	ourShader.use();



	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);
		//
		// render
		// ------



		// Enable depth test
		//glEnable(GL_DEPTH_TEST);
		// Accept fragment if it closer to the camera than the former one
		//glDepthFunc(GL_LESS);


		//glClearColor(0.2f, 1.3f, 0.3f, 1.0f);

		//glClear(GL_COLOR_BUFFER_BIT);



		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glClear(GL_COLOR_BUFFER_BIT);

		//glEnable(GL_CULL_FACE);


		//glCullFace(GL_FRONT);




		glm::mat4 modelMatrix = { {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1} };
		glm::mat4 model = { {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1} };
		glm::mat4 view = { {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1} };
		glm::mat4 projection = { {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1} };
		glm::mat4 MVP = { {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1} };



		//glm::vec3 scale = glm::vec3(1, 1, 1);

		//modelMatrix = glm::scale(modelMatrix, scale);


		modelMatrix = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.2f));



		//view = glm::lookAt(

		//	//glm::vec3(32 * 20 / 2, 150, 32 * 20 / 2), // Camera is at (4,3,3), in World Space

		//	glm::vec3(1, 1, 2), // Camera is at (4,3,3), in World Space


		//	glm::vec3(1, 0, 0), // and looks at the origin
		//	glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		//);

		glm::translate(modelMatrix, glm::vec3(1.25, 0.0, 1.0f));










		GLuint MatrixID = glGetUniformLocation(ourShader.ID, "modelMatrix");
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &modelMatrix[0][0]);


		unsigned int transformLoc2 = glGetUniformLocation(ourShader.ID, "view");
		glUniformMatrix4fv(transformLoc2, 1, GL_FALSE, glm::value_ptr(view));




		// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
		//projection = glm::perspective(45.0f, (float)SCREEN_SIZE.x / (float)SCREEN_SIZE.y, 1.0f, 200.0f);



		 //model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 0.0f, 0.0f));




		//projection = glm::perspective(glm::radians(1.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);




		// Remember, matrix multiplication is the other way around
		//MVP = projection * view * model;



		//// Get a handle for our "MVP" uniform.
		//// Only at initialisation time.
		//GLuint MatrixID = glGetUniformLocation(ourShader.ID, "MVP");

		//// Send our transformation to the currently bound shader,
		//// in the "MVP" uniform
		//// For each model you render, since the MVP will be different (at least the M part)
		//glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);





		//yplane third arg    2nd arg y axis
		//model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

		//https://stackoverflow.com/questions/36635824/how-to-scale-a-model-in-opengl









		//model  = glm::translate(model, glm::vec3(-0.5, -0.5, 0.0f));

		//1:
		//2: around the y axis
		//3: aroond the z axis









		//unsigned int transformLoc1 = glGetUniformLocation(ourShader.ID, "model");
		//glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));


		//?///unsigned int transformLoc3 = glGetUniformLocation(ourShader.ID, "projection");
		//?///glUniformMatrix4fv(transformLoc3, 1, GL_FALSE, glm::value_ptr(model));







		//unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
		//unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");




		//////// pass them to the shaders (3 different ways)
//		glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
//		glUniformMatrix4fv(transformLoc2, 1, GL_FALSE, &view[0][0]);
		//////// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.

		//ourShader.setMat4("projection", projection);









		// 1ST ATTRIBUTE BUFFER : VERTICES
		//SETTING UP FOR CUBE TO DISPLAY WORKS

		//glEnableVertexAttribArray(0);
		//glBindBuffer(GL_ARRAY_BUFFER, vertexbufferint);
		//glVertexAttribPointer(
		//	0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		//	3,                  // size
		//	GL_FLOAT,           // type
		//	GL_FALSE,           // normalized?
		//	0,                  // stride
		//	(void*)0            // array buffer offset
		//);


		//////////SAME AS ABOVE, NOW TRYING TO DISPLAY LAND/////




		//glBegin(GL_);
		//glEnd();



		//for (i = 0; i < 32 - 1; i++) {
		//	glBegin(GL_TRIANGLE_STRIP);
		//	for (j = 0; j < 32; j++) {


		//use enable instead
		//glEnableClientState(GL_VERTEX_ARRAY);


		//glVertexPointer(3, GL_FLOAT, 0, getVertices(width, height));
		//glDrawElements(GL_TRIANGLE_STRIP, getIndicesCount(width, height), GL_UNSIGNED_INT, getIndices(width, height));
		//glDisableClientState(GL_VERTEX_ARRAY);


		//glVertexAttribPointer


//# of indices
//8 triangles

		//row x xcol * 6
		glDrawArrays(GL_TRIANGLES, 0, 1 * 4 * 9);

		//		static const GLushort cubeIndices[] = {
		//	0, 1, 2, 3, 7, 1, 5, 4, 7, 6, 2, 4, 0, 1
		//		};






			//	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, cubeIndices);
				//glDisableVertexAttribArray(0);



				//glBegin(GL_TRIANGLE_STRIP);




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



//
// LoadBitmapFile
// desc: Returns a pointer to the bitmap image of the bitmap specified
//       by filename. Also returns the bitmap header information.
//		   No support for 8-bit bitmaps.
unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
	FILE *filePtr;							      // the file pointer
	BITMAPFILEHEADER	bitmapFileHeader;		// bitmap file header
	unsigned char		*bitmapImage;			// bitmap image data
	int					imageIdx = 0;		   // image index counter
	unsigned char		tempRGB;				   // swap variable

	// open filename in "read binary" mode
	filePtr = fopen(filename, "rb");
	if (filePtr == NULL)
		return NULL;

	// read the bitmap file header
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);

	// verify that this is a bitmap by checking for the universal bitmap id
	if (bitmapFileHeader.bfType != BITMAP_ID)
	{
		fclose(filePtr);
		return NULL;
	}

	// read the bitmap information header
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);

	// move file pointer to beginning of bitmap data
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

	// allocate enough memory for the bitmap image data
	bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);

	// verify memory allocation
	if (!bitmapImage)
	{
		free(bitmapImage);
		fclose(filePtr);
		return NULL;
	}

	// read in the bitmap image data
	fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);

	// make sure bitmap image data was read
	if (bitmapImage == NULL)
	{
		fclose(filePtr);
		return NULL;
	}

	// swap the R and B values to get RGB since the bitmap color format is in BGR
	for (imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 3)
	{
		tempRGB = bitmapImage[imageIdx];
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
		bitmapImage[imageIdx + 2] = tempRGB;
	}

	// close the file and return the bitmap image data
	fclose(filePtr);
	return bitmapImage;
}

// InitializeTerrain()
// desc: initializes the heightfield terrain data

//GLfloat g_vertex_buffer_data_land[32 * 32 * 3];
void InitializeTerrain()
{
	int i = 0;
	// loop through all of the heightfield points, calculating
	// the coordinates for each point
	for (int z = 0; z < MAP_Z; z++)
	{
		//int z = 0;
		for (int x = 0; x < 32; x++)// MAP_X; x++)
		{



			g_vertex_buffer_data_land[i] = float(x)*MAP_SCALE;
			//if (g_vertex_buffer_data_land[i] > 1)g_vertex_buffer_data_land[i] = 1;

			//			terrain[x][z][0] = float(x)*MAP_SCALE;

			g_vertex_buffer_data_land[i + 1] = (float)imageData[(z*MAP_Z + x) * 3];
			//if (g_vertex_buffer_data_land[i+1] > 1)g_vertex_buffer_data_land[i+1] = 1;


			//			terrain[x][z][1] = (float)imageData[(z*MAP_Z + x) * 3];

			g_vertex_buffer_data_land[i + 2] = -float(z)*MAP_SCALE;
			//if (g_vertex_buffer_data_land[i] > 1)g_vertex_buffer_data_land[i+2] = 1;


			//			terrain[x][z][2] = -float(z)*MAP_SCALE;

			i = i + 3;

		}
	}


	/*g_vertex_buffer_data_land[0] = 0;
	g_vertex_buffer_data_land[1] = 2;
	g_vertex_buffer_data_land[2] = 0;
	g_vertex_buffer_data_land[3] = 1;
	g_vertex_buffer_data_land[4] = 2;
	g_vertex_buffer_data_land[5] = 0;
	g_vertex_buffer_data_land[6] = 2;
	g_vertex_buffer_data_land[7] = 2;
	g_vertex_buffer_data_land[8] = 0;*/


	//	-1.0f, -1.0f, 0.0f,
	//		1.0f, -1.0f, 0.0f,
	//		0.0f, 1.0f, 0.0f,

		//0,2,0,1,2,0,2,2,0
		/*g_vertex_buffer_data_land[0] = 0;
		g_vertex_buffer_data_land[1] = 2;
			g_vertex_buffer_data_land[2] = 0;
			g_vertex_buffer_data_land[3] = 1;
			g_vertex_buffer_data_land[4] = 2;
			g_vertex_buffer_data_land[5] = 0;
			g_vertex_buffer_data_land[6] = 2;
			g_vertex_buffer_data_land[7] = 2;
			g_vertex_buffer_data_land[8] = 0;

	*/

	//float xx = g_vertex_buffer_data_land[3071];
	//float yy = g_vertex_buffer_data_land[3072];

}

bool LoadtheTextures(void)
{


	char dirvar[] = "green.bmp";

	if (dirvar == NULL) {
		printf("Impossible to open this bitmap file !\n");
		return(1);
	}


	// load the land texture data
	landTexture = LoadBitmapFile(dirvar, &landInfo);
	if (!landTexture)
		return false;
	//
		// generate the land texture as a mipmap
	glGenTextures(1, &land);
	glBindTexture(GL_TEXTURE_2D, land);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//link this against glu32.lib 
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, landInfo.biHeight, landInfo.biWidth, GL_RGB, GL_UNSIGNED_BYTE, landTexture);

	return true;
}



////////////////////////////


//internal
int getVerticesCount(int width, int height) {
	return width * height * 3;
}

//internal
int getIndicesCount(int width, int height) {
	return (width*height) + (width - 1)*(height - 2);
}

float* getVertices(int depth, int row) {
	//	if (gvertices) return gvertices;

		//gvertices = new float[getVerticesCount(width, height)];
	int i = 0;


	//std::vector< glm::vec3 > tempmathvertices;

	float scaleit = .125;

	//up and down : a value of one is one row and than exits

	//so it will be zero on the first loop
	int counter = 0;

		//
		//for (int row = 0; row; row++) {

			//counter = counter + 18;


			//across left to right - one column is two triangles
			//for (int colu = 0; colu < 5; colu++) {
				//gvertices[i++] = (float)col;
				//gvertices[i++] = 0.0f;
				//gvertices[i++] = (float)row;
				//mathvertices
				//tempmathvertices.




	//float colu = 0;
	//row = 0;


	for (int depth = 0; depth < 4; depth++)
	{
		//GLfloat matrix1[3][3] = {colu,0,row, colu,0,(row+1), (colu+1),0,(row+1)};
		//GLfloat matrix1[3][3] = {colu,0,row, colu,0,(row-1), (colu+1),0,(row-1)};

	//first triangle : odd rows : A
		GLfloat matrix1[3][3] = { depth,0,row - 1, depth + 1,0,(row), (depth),0,(row) };

		//vertex 1
		g_vertex_buffer_data_land[0 + counter] = matrix1[0][0] * scaleit;
		g_vertex_buffer_data_land[1 + counter] = matrix1[0][1] * scaleit;
		g_vertex_buffer_data_land[2 + counter] = matrix1[0][2] * scaleit;
		//vertex 2
		g_vertex_buffer_data_land[3 + counter] = matrix1[1][0] * scaleit;
		g_vertex_buffer_data_land[4 + counter] = matrix1[1][1] * scaleit;
		g_vertex_buffer_data_land[5 + counter] = matrix1[1][2] * scaleit;

		g_vertex_buffer_data_land[6 + counter] = matrix1[2][0] * scaleit;
		g_vertex_buffer_data_land[7 + counter] = matrix1[2][1] * scaleit;
		g_vertex_buffer_data_land[8 + counter] = matrix1[2][2] * scaleit;


		//int matrix2[3][3] = {depth,0,(row + 2 ), (depth+1),0,(row + 2), (depth+1),0,(row + 1 ) };
		//int matrix2[3][3] = {depth,0,(row - 2 ), (depth+1),0,(row - 2), (depth+1),0,(row - 1 ) };

		//first triangle : even rows : B
		int matrix2[3][3] = { depth + 1,0,(row - 1), (depth + 1),0,(row), (depth),0,(row - 1) };


		g_vertex_buffer_data_land[9 + counter] = matrix2[0][0] * scaleit;
		g_vertex_buffer_data_land[10 + counter] = matrix2[0][1] * scaleit;
		g_vertex_buffer_data_land[11 + counter] = matrix2[0][2] * scaleit;

		g_vertex_buffer_data_land[12 + counter] = matrix2[1][0] * scaleit;
		g_vertex_buffer_data_land[13 + counter] = matrix2[1][1] * scaleit;
		g_vertex_buffer_data_land[14 + counter] = matrix2[1][2] * scaleit;

		g_vertex_buffer_data_land[15 + counter] = matrix2[2][0] * scaleit;
		g_vertex_buffer_data_land[16 + counter] = matrix2[2][1] * scaleit;
		g_vertex_buffer_data_land[17 + counter] = matrix2[2][2] * scaleit;


		counter = counter + 18;

	}







	////row++;
	////GLfloat matrix1[3][3] = { colu,0,row - 1, colu + 1,0,(row), (colu),0,(row) };

	////first triangle again : A
	//GLfloat matrixa[3][3] = { (colu + 1),0,(row - 1), (colu + 2),0,(row), (colu + 1),0,(row) };
	////vertex 1
	//g_vertex_buffer_data_land[18 + counter] = matrixa[0][0] * scaleit;
	//g_vertex_buffer_data_land[19 + counter] = matrixa[0][1] * scaleit;
	//g_vertex_buffer_data_land[20 + counter] = matrixa[0][2] * scaleit;
	////vertex 2
	//g_vertex_buffer_data_land[21 + counter] = matrixa[1][0] * scaleit;
	//g_vertex_buffer_data_land[22 + counter] = matrixa[1][1] * scaleit;
	//g_vertex_buffer_data_land[23 + counter] = matrixa[1][2] * scaleit;

	//g_vertex_buffer_data_land[24 + counter] = matrixa[2][0] * scaleit;
	//g_vertex_buffer_data_land[25 + counter] = matrixa[2][1] * scaleit;
	//g_vertex_buffer_data_land[26 + counter] = matrixa[2][2] * scaleit;



	////colum is changing not row
	////row++;

	////int matrix2[3][3] = { colu + 1,0,(row - 1), (colu + 1),0,(row), (colu),0,(row - 1) };

	////second triangle again :  B 
	//int matrixb[3][3] = { (colu + 2),0,(row - 1), (colu + 2),0,(row), (colu + 1),0,(row - 1) };

	//////vertex 1
	//g_vertex_buffer_data_land[27 + counter] = matrixb[0][0] * scaleit;
	//g_vertex_buffer_data_land[28 + counter] = matrixb[0][1] * scaleit;
	//g_vertex_buffer_data_land[29 + counter] = matrixb[0][2] * scaleit;
	//////vertex 2
	//g_vertex_buffer_data_land[30 + counter] = matrixb[1][0] * scaleit;
	//g_vertex_buffer_data_land[31 + counter] = matrixb[1][1] * scaleit;
	//g_vertex_buffer_data_land[32 + counter] = matrixb[1][2] * scaleit;

	//g_vertex_buffer_data_land[33 + counter] = matrixb[2][0] * scaleit;
	//g_vertex_buffer_data_land[34 + counter] = matrixb[2][1] * scaleit;
	//g_vertex_buffer_data_land[35 + counter] = matrixb[2][2] * scaleit;





	//counter = counter + 18;

	//}

			//g_vertex_buffer_data_land[i]= (float)col;
			//g_vertex_buffer_data_land[i++] = 0.0f;
			//g_vertex_buffer_data_land[i++] = (float)row;









		//}
//	}


	/*g_vertex_buffer_data_land[0] = 0.0f;
	g_vertex_buffer_data_land[1] = 0;
	g_vertex_buffer_data_land[2] = 0.0f;
	g_vertex_buffer_data_land[3] = 0.0f;
	g_vertex_buffer_data_land[4] = 0.0f;
	g_vertex_buffer_data_land[5] = 1.0f;
	g_vertex_buffer_data_land[6] = 1.0f;
	g_vertex_buffer_data_land[7] = 0.0f;
	g_vertex_buffer_data_land[8] = 1.0f;

	g_vertex_buffer_data_land[0] = 0.0f;
	g_vertex_buffer_data_land[1] = 0;
	g_vertex_buffer_data_land[2] = 2.0f;
	g_vertex_buffer_data_land[3] = 1.0f;
	g_vertex_buffer_data_land[4] = 0.0f;
	g_vertex_buffer_data_land[5] = 2.0f;
	g_vertex_buffer_data_land[6] = 1.0f;
	g_vertex_buffer_data_land[7] = 0.0f;
	g_vertex_buffer_data_land[8] = 1.0f;

*/



	return gvertices;
}

int* getIndices(int width, int height) {
	if (gindices) return gindices;


	//https://stackoverflow.com/questions/5915753/generate-a-plane-with-triangle-strips


	//
	gindices = new int[getIndicesCount(width, height)];

	int i = 0;

	for (int row = 0; row < height - 1; row++) {
		if ((row & 1) == 0) { // even rows
			for (int col = 0; col < width; col++) {
				gindices[i++] = col + row * width;
				gindices[i++] = col + (row + 1) * width;
			}
		}
		else { // odd rows
			for (int col = width - 1; col > 0; col--) {
				gindices[i++] = col + (row + 1) * width;
				gindices[i++] = col - 1 + +row * width;
			}
		}
	}
	//if ((mHeight & 1) && mHeight > 2) {
	//	mpIndices[i++] = (mHeight - 1) * mWidth;
	//}

	return gindices;
}



////////////////////////////////