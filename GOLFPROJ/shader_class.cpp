#define GLFW_INCLUDE_NONE 

/////////
//#include "shader_s.h"
//#include <glew.h>


#include <glad/include/glad/glad.h>
//#include "glad.h"

#include <GLFW/glfw3.h>

//#include <gl/gl.h>  
//#include <gl/glu.h>
//#include <c:/openglusage/GLU.h>


//#include <gl/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include <glm/>
//#include <C:/openglusage/headershader/common.h>
//#include <C:/openglusage/headershader/loader.h>
#include <vector>
#include <windows.h>
#include <string>
//#include <fstream>
#include <sstream>
#include <iostream>
#include <fstream>
//////////////////

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);



float gcurrentime = 0;

FILE * glog;

FILE * glogadjuster;

int gtextsavingison = 0;


float grotateadjuster = 0;





class Shader
{
public:
	unsigned int ID;
	// constructor generates the shader on the fly
	// ------------------------------------------------------------------------
	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr)
	{
		// 1. retrieve the vertex/fragment source code from filePath
		std::string vertexCode;
		std::string fragmentCode;
		std::string geometryCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		std::ifstream gShaderFile;
		// ensure ifstream objects can throw exceptions:
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			// read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// close file handlers
			vShaderFile.close();
			fShaderFile.close();
			// convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
			// if geometry shader path is present, also load a geometry shader
			if (geometryPath != nullptr)
			{
				gShaderFile.open(geometryPath);
				std::stringstream gShaderStream;
				gShaderStream << gShaderFile.rdbuf();
				gShaderFile.close();
				geometryCode = gShaderStream.str();
			}
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char * fShaderCode = fragmentCode.c_str();
		// 2. compile shaders
		unsigned int vertex, fragment;
		// vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");
		// fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");
		// if geometry shader is given, compile geometry shader
		unsigned int geometry;
		if (geometryPath != nullptr)
		{
			const char * gShaderCode = geometryCode.c_str();
			geometry = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geometry, 1, &gShaderCode, NULL);
			glCompileShader(geometry);
			checkCompileErrors(geometry, "GEOMETRY");
		}
		// shader Program
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		if (geometryPath != nullptr)
			glAttachShader(ID, geometry);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");
		// delete the shaders as they're linked into our program now and no longer necessery
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		if (geometryPath != nullptr)
			glDeleteShader(geometry);

	}
	// activate the shader
	// ------------------------------------------------------------------------
	void use()
	{
		glUseProgram(ID);
	}
	// utility uniform functions
	// ------------------------------------------------------------------------
	void setBool(const std::string &name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	// ------------------------------------------------------------------------
	void setInt(const std::string &name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void setFloat(const std::string &name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void setVec2(const std::string &name, const glm::vec2 &value) const
	{
		glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void setVec2(const std::string &name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
	}
	// ------------------------------------------------------------------------
	void setVec3(const std::string &name, const glm::vec3 &value) const
	{
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void setVec3(const std::string &name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
	}
	// ------------------------------------------------------------------------
	void setVec4(const std::string &name, const glm::vec4 &value) const
	{
		glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void setVec4(const std::string &name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
	}
	// ------------------------------------------------------------------------
	void setMat2(const std::string &name, const glm::mat2 &mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void setMat3(const std::string &name, const glm::mat3 &mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void setMat4(const std::string &name, const glm::mat4 &mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

private:
	// utility function for checking shader compilation/linking errors.
	// ------------------------------------------------------------------------
	void checkCompileErrors(GLuint shader, std::string type)
	{
		GLint success;
		GLchar infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}
};





/////////////////////


//void output(int x, int y, float r, float g, float b, char *string);
void output();

//for world (getveritces)
#define _colus   8
#define _depth   8

#define BITMAP_ID 0x4D42		      // the universal bitmap ID


//used in intializeterrain
#define MAP_X	32//32				         // size of map along x-axis
#define MAP_Z	32//32				         // size of map along z-axis
#define MAP_SCALE	.0f		         // the scale of the terrain map


int* gindices = 0;

bool LoadtheTextures(void);

unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader);
void InitializeTerrain();

int getIndicesCount(int _width, int _height);

int* getIndices(int _width, int _height);


//uses defines now
float* getVertices(void);

int getVerticesCount(int width, int height);


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

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

unsigned int		   land;			      // the land texture object

unsigned char*	      imageData;		   // the map image data

////// Terrain Data
float terrain[MAP_X][MAP_Z][3];		// heightfield terrain data (0-255); 256x256


float gvertices[300];// = new float[getVerticesCount(width, height)];

int i = 0;


//288 (vertices)
GLfloat g_vertex_buffer_data_land[( _colus * 18 * _depth) ] = {};



int main()

{

	


	//float answer = (2.93 + 2.66 + 2.73) / 3;

	glog = fopen("log.txt.txt", "w");


	//glog = fopen("log.txt.txt", "w");

	
	//glog = fopen("log.txt", "w");
	//glog << "Writing this to a file!.\n";
	//glog.close();
	
	std::vector<unsigned int> indices;


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

	


	int j = 0;



	



	

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


	
	//columns, depth
	getVertices();



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


	//count is number of indices
	int count = _colus * 18 *  _depth;

	GLfloat tempcolor1[1], tempcolor2[1], tempcolor3[1];
	
	//(count of vertices is nubmer of triangles times 3)
	//9 vertices per triangle (x,y,z) and two triangles per grid square (column)
	GLfloat g_color_buffer_data[(_colus * 18 * _depth) ];

	//assumde count is divisable by three
	for (int i = 0; i < count;)
	{
		tempcolor1[0] = (rand() % 999);

		if (tempcolor1 != 0)
		{
			tempcolor1[0] = tempcolor1[0] / 999;
		}
		
		
		tempcolor2[0] = (rand() % 999);

		if (tempcolor2 != 0)
		{
			tempcolor2[0] = tempcolor1[0] / 999;

		}
		
		tempcolor3[0] = (rand() % 999);

		if (tempcolor3 != 0)
		{
			tempcolor3[0] = tempcolor1[0] / 999;
		}

		g_color_buffer_data[i] =   *tempcolor1;
		g_color_buffer_data[i+1] = *tempcolor2;
		g_color_buffer_data[i+2] = *tempcolor3;
		
		i = i + 3;


	}



	//static const GLfloat g_color_buffer_data[] = {

	//	//0
	//	0.183f,  0.171f,  0.314f,
	//	0.783f,  0.471f,  0.514f,
	//	0.683f,  0.671f,  0.614f,
	//	0.583f,  0.371f,  0.014f,
	//	0.383f,  0.371f,  0.314f,
	//	//5
	//	0.283f,  0.271f,  0.214f,
	//	0.183f,  0.371f,  0.814f,
	//	0.583f,  0.771f,  0.014f,
	//	0.283f,  0.271f,  0.214f,
	//	0.183f,  0.171f,  0.514f,
	//	//10
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	//15
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	//20
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	//25
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	//30
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	//35

	//	//////////////

	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	//5
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	//10
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	//15
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	//20
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	//25
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	//30
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	//35 - 70
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,

	//	//75 next...
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	0.583f,  0.771f,  0.014f,
	//	0.183f, 0.171f, 0.314f,
	//	0.783f, 0.471f, 0.514f,
	//	//80
	//	0.683f, 0.671f, 0.614f,
	//	0.583f, 0.371f, 0.014f,
	//	0.383f, 0.371f, 0.314f,
	//	0.283f, 0.271f, 0.214f,
	//	0.183f, 0.371f, 0.814f,
	//	//85
	//	0.583f, 0.771f, 0.014f,
	//	0.283f, 0.271f, 0.214f,
	//	0.683f, 0.671f, 0.614f,
	//	0.583f, 0.371f, 0.014f,
	//	0.383f, 0.371f, 0.314f,

	//		0.583f, 0.771f, 0.014f,
	//		0.283f, 0.271f, 0.214f,
	//		0.683f, 0.671f, 0.614f,
	//		0.583f, 0.371f, 0.014f,
	//		0.383f, 0.371f, 0.314f,

	//		0.583f, 0.771f, 0.014f,
	//		0.283f, 0.271f, 0.214f,
	//		0.683f, 0.671f, 0.614f,
	//		0.583f, 0.371f, 0.014f,
	//		0.383f, 0.371f, 0.314f,

	//		0.383f, 0.371f, 0.314f,

	//};







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



	





///////////////////////////////////////////////
//		 RENDER LOOP
///////////////////////////// -----------

	ourShader.use();

	glfwSetKeyCallback(window, key_callback);


	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		//processInput(window);
		//
		// render
		// ------



		


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		


		glm::mat4 modelMatrix = { {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1} };
		glm::mat4 model = { {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1} };
		glm::mat4 view = { {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1} };
		glm::mat4 projection = { {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1} };
		glm::mat4 MVP = { {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1} };

		

		//glm::vec3 scale = glm::vec3(1, 1, 1);

		//modelMatrix = glm::scale(modelMatrix, scale);



		//modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0.0f));


		//glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 305.0f);

		
		
		
		gcurrentime = (float)glfwGetTime();

		//////////////////////

		if (gtextsavingison == 1)
		{
			//glog = fopen("log.txt.txt", "w");

			//fprintf(glog, "\n a %f\n", gcurrentime);


			//fprintf(glog, "before rotate", "w");

			//fclose(glog);
			//gtextsavingison = 0;
			//fclose(glog);
			//gtextsavingison = 0;
			//gtextsavingison = 2;

		}

		///////////////////////

		if (gtextsavingison == 1)
		{
			fprintf(glog, "\nbefore rotate: %f \n", gcurrentime);

		}

		//////////////////////


		modelMatrix = glm::translate(modelMatrix, glm::vec3(2, 0, 0.10f));

		
		grotateadjuster = 0.139;
		//x    y    z
		modelMatrix = glm::rotate(modelMatrix, 3.0f + grotateadjuster, glm::vec3(0.0f, 1.5f, 0.2f));

		if (gtextsavingison == 1)
		{
			//glog = fopen("log.txt.txt", "w");

			//fprintf(glog, "\n a %f\n", gcurrentime);
			//glog = fopen("log.txt.txt", "w");


			//glog = fopen("log.txt.txt", "w");


			fprintf(glog, "after rotate %f\n", gcurrentime);

			//fprintf(glog, "average: \n", );


			fclose(glog);
			//gtextsavingison = 0;
			//fclose(glog);
			//gtextsavingison = 0;
			gtextsavingison = 2;

		}




		//revolve around axis
		//modelMatrix = glm::rotate(model, (float)(55+180+.5+.1), glm::vec3(0.0f, 1.0f,0.00f));
		
		//second (y) up and down
		//modelMatrix = glm::translate(modelMatrix, glm::vec3(-.35, -0.2, 0.0f));



		view = glm::lookAt(

		//////////	//glm::vec3(32 * 20 / 2, 150, 32 * 20 / 2), // Camera is at (4,3,3), in World Space

			//glm::vec3(-1.8, .5, 1.2),
			glm::vec3(0, 0, 2), // Camera is at (4,3,3), in World Space


			glm::vec3(0, 0, 0), // and looks at the origin
			glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);

		////////


		GLuint MatrixID = glGetUniformLocation(ourShader.ID, "modelMatrix");
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &modelMatrix[0][0]);


		unsigned int transformLoc2 = glGetUniformLocation(ourShader.ID, "view");
		glUniformMatrix4fv(transformLoc2, 1, GL_FALSE, glm::value_ptr(view));


		// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
		//projection = glm::perspective(45.0f, (float)SCREEN_SIZE.x / (float)SCREEN_SIZE.y, 1.0f, 200.0f);



		// model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 0.0f, 0.0f));



		//projection = glm::ortho(0.0f, 800.0f, 800.0f, 0.0f);






		//I call it : height angle
		projection = glm::perspective(glm::radians(60.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		





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

		





		//unsigned int transformLoc1 = glGetUniformLocation(ourShader.ID, "model");
		//glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));


		

		//////// pass them to the shaders (3 different ways)
//		glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
//		glUniformMatrix4fv(transformLoc2, 1, GL_FALSE, &view[0][0]);
		//////// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.

		ourShader.setMat4("projection", projection);









		

		




		//couls x depth x 18 vertices for two triangles per column
		glDrawArrays(GL_TRIANGLES, 0, _depth * _colus * 18);

		//		static const GLushort cubeIndices[] = {
		//	0, 1, 2, 3, 7, 1, 5, 4, 7, 6, 2, 4, 0, 1
		//		};






			

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





static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);

	}

	else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		//readyforpressing = 1;
		grotateadjuster = grotateadjuster + .001;

	}

	//saves adjuster
	else if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
	{
		//readyforpressing = 1;
		//grotateadjuster = grotateadjuster + .001;
		glogadjuster= fopen("logadjuster.txt", "w");

		fprintf(glogadjuster, "\ntotal adjustment is: %f", grotateadjuster);

		fclose(glogadjuster);


	}




	else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS && gtextsavingison == 0)
	{

		//turned off
		//if (gtextsavingison == 1)
		{
			//glog = fopen("log.txt.txt", "w");

			//fprintf(glog, "\npressed space (off):  %f\n", gcurrentime);
			gtextsavingison = 1;
			//fclose(glog);


		}
	}



}




//void processInput(GLFWwindow *window)

	



//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && gtextsavingison == 0)
//	{
//
//		//turned off
//		//if (gtextsavingison == 0)
//		{
//			//glog = fopen("log.txt.txt", "w");
//
//			//fprintf(glog, "\npressed space (off):  %f\n", gcurrentime);
//			gtextsavingison = 1;
//			//fclose(glog);
//
//
//		}
//	}



		//turned on
		//else
		//{

		//	//gcurrentime

		//	//std::time_t t = std::time(0);   // get time now
		//	//glog = fopen("log.txt.txt", "w");
		//	//fprintf(glog, "\npressed space(on):  %f\n", gcurrentime );
		//	//printf();
		//	//char output[] = ""
		//	//log << "key turned on\n";
		//	gtextsavingison = 1;
		//	//fclose(glog);
		//}
	//}


//}

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
//	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, landInfo.biHeight, landInfo.biWidth, GL_RGB, GL_UNSIGNED_BYTE, landTexture);

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


//16 triangeles (depth 1)
//16 triangles  (depth 2)
//each triangle 9 indexces
//so 16*16*9 = 

//
float* getVertices(void) {

	//using defines
	int incol = _colus;
	int depth = _depth;

	
	int i = 0;
	
	
	

	float scaleit = 1;

	//up and down : a value of one is one row and than exits

	//so it will be zero on the first loop
	int counter = 0;

		

	int tempdepth = 0;
	int tempdepth2 = 0;
	
	//writes two rows: left and right triangles, and right and left triangles per iteration.
	
	//odd rows
	for (; tempdepth < depth; tempdepth++)
	{

		//odd rows
		for (int col = 0; col < incol; col++)
		{
			//GLfloat matrix1[3][3] = {tempdepth,0,row, tempdepth,0,(row+1), (tempdepth+1),0,(row+1)};
			//GLfloat matrix1[3][3] = {tempdepth,0,row, tempdepth,0,(row-1), (tempdepth+1),0,(row-1)};

		//first triangle : odd rows : A



			//was : GLfloat matrix1[3][3] = { col,0,tempdepth - 1, col + 1,0,(tempdepth), (col),0,(tempdepth) };

			GLfloat matrix1[3][3] = { col,0,tempdepth - 1, col + 1,0,(tempdepth), (col),0,(tempdepth) };

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


			//int matrix2[3][3] = {col,0,(tempdepth + 2 ), (col+1),0,(tempdepth + 2), (col+1),0,(tempdepth + 1 ) };
			//int matrix2[3][3] = {col,0,(tempdepth - 2 ), (col+1),0,(tempdepth - 2), (col+1),0,(tempdepth - 1 ) };

			//first triangle : even tempdepths : B

			//was: int matrix2[3][3] = { col + 1,0,(tempdepth - 1), (col + 1),0,(tempdepth), (col),0,(tempdepth - 1) };

			int matrix2[3][3] = { col + 1,0,(tempdepth - 1), (col + 1),0,(tempdepth), (col),0,(tempdepth - 1) };


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

	}//tempdepth
	
	
	/////////////////////

	////set to one
	//tempdepth2 = 1 ;

	////if the depth is greater than one plus the even depths
	//for (; tempdepth2 < depth; tempdepth2++)
	//
	//{
	//	//tempdepth= 0;



	//	//even row : columns:


	//	for (int col = 0; col < incol; col++)
	//	{



	//		//first triangle : odd rows : A
	//		GLfloat matrix1[3][3] = { col + 1 ,0,tempdepth2 - 2 , col+1,0,(tempdepth2-1), (col),0,(tempdepth2 - 2) };

	//		//vertex 1
	//		g_vertex_buffer_data_land[0 + counter] = matrix1[0][0] * scaleit;
	//		g_vertex_buffer_data_land[1 + counter] = matrix1[0][1] * scaleit;
	//		g_vertex_buffer_data_land[2 + counter] = matrix1[0][2] * scaleit;
	//		//vertex 2
	//		g_vertex_buffer_data_land[3 + counter] = matrix1[1][0] * scaleit;
	//		g_vertex_buffer_data_land[4 + counter] = matrix1[1][1] * scaleit;
	//		g_vertex_buffer_data_land[5 + counter] = matrix1[1][2] * scaleit;

	//		g_vertex_buffer_data_land[6 + counter] = matrix1[2][0] * scaleit;
	//		g_vertex_buffer_data_land[7 + counter] = matrix1[2][1] * scaleit;
	//		g_vertex_buffer_data_land[8 + counter] = matrix1[2][2] * scaleit;


	//		//int matrix2[3][3] = {col,0,(tempdepth + 2 ), (col+1),0,(tempdepth + 2), (col+1),0,(tempdepth + 1 ) };
	//		//int matrix2[3][3] = {col,0,(tempdepth - 2 ), (col+1),0,(tempdepth - 2), (col+1),0,(tempdepth - 1 ) };

	//		//first triangle : even tempdepths : B
	//		int matrix2[3][3] = { col + 1,0,(tempdepth2 - 2), (col + 1 ),0,(tempdepth2-1), (col),0,(tempdepth2 - 1) };


	//		g_vertex_buffer_data_land[9 + counter] = matrix2[0][0] * scaleit;
	//		g_vertex_buffer_data_land[10 + counter] = matrix2[0][1] * scaleit;
	//		g_vertex_buffer_data_land[11 + counter] = matrix2[0][2] * scaleit;

	//		g_vertex_buffer_data_land[12 + counter] = matrix2[1][0] * scaleit;
	//		g_vertex_buffer_data_land[13 + counter] = matrix2[1][1] * scaleit;
	//		g_vertex_buffer_data_land[14 + counter] = matrix2[1][2] * scaleit;

	//		g_vertex_buffer_data_land[15 + counter] = matrix2[2][0] * scaleit;
	//		g_vertex_buffer_data_land[16 + counter] = matrix2[2][1] * scaleit;
	//		g_vertex_buffer_data_land[17 + counter] = matrix2[2][2] * scaleit;


	//		counter = counter + 18;

	//	}
	//}

	//










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



//void output(int x, int y, float r, float g, float b, char *string)
 void output()
{

	
	char  string[] = "test";
	
	//glColor3f(0, 1, 0.);
	//glRasterPos2i(10,10);
	
	
	int len, i;
	len = (int)strlen(string);
	for (i = 0; i < len; i++) {
		//glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string[i]);


		//glutBitmapCharacter(GLUT_BITMAP_8_BY_13, "hello");
	}
}


 
 ////////////////////////////////


 



