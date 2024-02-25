//Pr�ctica 2 semestre 2024-2: �ndices, mesh, proyecciones, transformaciones geom�tricas
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
//clases para dar orden y limpieza al c�digo
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f / 180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";
//shaders nuevos se crear�an ac�
static const char* vShader_rojo = "shaders/shader_rojo.vert";
static const char* vShader_cafe = "shaders/shader_cafe.vert";
static const char* vShader_verde = "shaders/shader_verde.vert";
static const char* vShader_verdeClaro = "shaders/shader_verdeClaro.vert";


float angulo = 0.0f;

//color caf� en RGB : 0.478, 0.255, 0.067

//Pir�mide triangular regular
void CreaPiramide()
{
	unsigned int indices[] = {
		0,1,2,
		1,3,2,
		0,1,4,
		1,3,4,
		0,2,4,
		2,3,4

	};
	GLfloat vertices[] = {
		-0.5f, -0.5f,0.5f,	//0
		0.5f,-0.5f,0.5f,	//1
		-0.5f, -0.5f,-0.5f,	//2
		0.5f,-0.5f,-0.5f,	//3
		0.0f,0.5f,0.0f,     //4

	};
	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 15, 18);
	meshList.push_back(obj1);
}

//V�rtices de un cubo
void CrearCubo()
{
	//si tienen color pero estan en el shader (interpolacion de colores)
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat cubo_vertices[] = {
		// front
		-0.5f, -0.5f,  0.5f, 
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		// back
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f
	};
	Mesh* cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(cubo);
}

void CrearLetrasyFiguras()
{

	GLfloat vertices_letras[] = {
		//X			Y			Z			R		G		B
		//LETRA A
		 -0.9f, -0.2f,0.0f,                1.0f, 0.0f, 0.0f,
		 -0.85f, -0.2f, 0.0f,                1.0f, 0.0f, 0.0f,
		 -0.85f,0.0f,0.0f,                1.0f, 0.0f, 0.0f,

		 -0.85f, -0.2f,0.0f,                1.0f, 0.0f, 0.0f,
		 -0.85f,0.0f,0.0f,                1.0f, 0.0f, 0.0f,
		 -0.8f,0.0f,0.0f,                1.0f, 0.0f, 0.0f,

		 -0.85f, -0.0f,0.0f,                1.0f, 0.0f, 0.0f,
		 -0.80f, -0.0f, 0.0f,                1.0f, 0.0f, 0.0f,
		 -0.80f,0.2f,0.0f,                1.0f, 0.0f, 0.0f,

		 -0.80f, -0.0f,0.0f,                1.0f, 0.0f, 0.0f,
		 -0.80f,0.2f,0.0f,                1.0f, 0.0f, 0.0f,
		 -0.75f,0.2f,0.0f,                1.0f, 0.0f, 0.0f,

		-0.8f, 0.2f, 0.0f,                1.0f, 0.0f, 0.0f,
		-0.75f, 0.2f, 0.0f,                1.0f, 0.0f, 0.0f,
		-0.75f, 0.0f, 0.0f,                1.0f, 0.0f, 0.0f,

		-0.75f, 0.2f, 0.0f,                1.0f, 0.0f, 0.0f,
		-0.75f, 0.0f, 0.0f,                1.0f, 0.0f, 0.0f,
		-0.7f, 0.0f, 0.0f,                1.0f, 0.0f, 0.0f,

		-0.75f, 0.0f, 0.0f,                1.0f, 0.0f, 0.0f,
		-0.7f, 0.0f, 0.0f,                1.0f, 0.0f, 0.0f,
		-0.7f, -0.2f, 0.0f,                1.0f, 0.0f, 0.0f,

		-0.7f, 0.0f, 0.0f,                1.0f, 0.0f, 0.0f,
		-0.7f, -0.2f, 0.0f,                1.0f, 0.0f, 0.0f,
		-0.65f, -0.2f, 0.0f,                1.0f, 0.0f, 0.0f,
		
	   -0.85f, 0.0f, 0.0f,                1.0f, 0.0f, 0.0f,
	   -0.70f, -0.05f, 0.0f,                1.0f, 0.0f, 0.0f,
	   -0.70f, 0.0f, 0.0f,                1.0f, 0.0f, 0.0f,

	   -0.70f, -0.05f, 0.0f,                1.0f, 0.0f, 0.0f,
	   -0.85f, -0.05f, 0.0f,                1.0f, 0.0f, 0.0f,
	   -0.85f, 0.0f, 0.0f,                1.0f, 0.0f, 0.0f,

	   //LETRA R 
		-0.65f, -0.2f, 0.0f,               0.0f, 1.0f, 0.0f,
		-0.60f, -0.2f, 0.0f,               0.0f, 1.0f, 0.0f,
		-0.65f, 0.2f, 0.0f,               0.0f, 1.0f, 0.0f,

		-0.60f, 0.2f, 0.0f,               0.0f, 1.0f, 0.0f,
		-0.60f, -0.2f, 0.0f,               0.0f, 1.0f, 0.0f,
		-0.65f, 0.2f, 0.0f,               0.0f, 1.0f, 0.0f,

		-0.60f, 0.2f, 0.0f,               0.0f, 1.0f, 0.0f,
		-0.40f, 0.2f, 0.0f,               0.0f, 1.0f, 0.0f,
		-0.40f, 0.15f, 0.0f,               0.0f, 1.0f, 0.0f,

		-0.60f, 0.2f, 0.0f,               0.0f, 1.0f, 0.0f,
		-0.60f, 0.15f, 0.0f,               0.0f, 1.0f, 0.0f,
		-0.40f, 0.15f, 0.0f,               0.0f, 1.0f, 0.0f,

		-0.45f, -0.05f, 0.0f,               0.0f, 1.0f, 0.0f,
		-0.40f, -0.05f, 0.0f,               0.0f, 1.0f, 0.0f,
		-0.45f, 0.2f, 0.0f,               0.0f, 1.0f, 0.0f,

		-0.40f, 0.2f, 0.0f,               0.0f, 1.0f, 0.0f,
		-0.40f, -0.05f, 0.0f,               0.0f, 1.0f, 0.0f,
		-0.45f, 0.2f, 0.0f,               0.0f, 1.0f, 0.0f,

		-0.60f, 0.0f, 0.0f,               0.0f, 1.0f, 0.0f,
		-0.40f, 0.0f, 0.0f,               0.0f, 1.0f, 0.0f,
		-0.40f, -0.05f, 0.0f,               0.0f, 1.0f, 0.0f,

		-0.60f, 0.0f, 0.0f,               0.0f, 1.0f, 0.0f,
		-0.60f, -0.05f, 0.0f,               0.0f, 1.0f, 0.0f,
		-0.40f, -0.05f, 0.0f,               0.0f, 1.0f, 0.0f,

		-0.65f, 0.0f, 0.0f,               0.0f, 1.0f, 0.0f,
		-0.45f, -0.2f, 0.0f,               0.0f, 1.0f, 0.0f,
		-0.6f, 0.0f, 0.0f,               0.0f, 1.0f, 0.0f,

		-0.6f, 0.0f, 0.0f,               0.0f, 1.0f, 0.0f,
		-0.45f, -0.2f, 0.0f,               0.0f, 1.0f, 0.0f,
		-0.4f, -0.2f, 0.0f,               0.0f, 1.0f, 0.0f,

		//LETRA E 
		-0.35f, -0.2f, 0.0f,              0.0f, 0.0f, 1.0f,
		-0.3f, -0.2f, 0.0f,              0.0f, 0.0f, 1.0f,
		-0.35f, 0.2f, 0.0f,              0.0f, 0.0f, 1.0f,

		-0.3f, 0.2f, 0.0f,              0.0f, 0.0f, 1.0f,
		-0.3f, -0.2f, 0.0f,              0.0f, 0.0f, 1.0f,
		-0.35f, 0.2f, 0.0f,              0.0f, 0.0f, 1.0f,

		-0.3f, 0.2f, 0.0f,              0.0f, 0.0f, 1.0f,
		-0.1f, 0.2f, 0.0f,              0.0f, 0.0f, 1.0f,
		-0.1f, 0.15f, 0.0f,              0.0f, 0.0f, 1.0f,

		-0.3f, 0.2f, 0.0f,              0.0f, 0.0f, 1.0f,
		-0.3f, 0.15f, 0.0f,              0.0f, 0.0f, 1.0f,
		-0.1f, 0.15f, 0.0f,              0.0f, 0.0f, 1.0f,

		 -0.3f, 0.0f, 0.0f,              0.0f, 0.0f, 1.0f,
		 -0.1f, 0.0f, 0.0f,              0.0f, 0.0f, 1.0f,
		 -0.1f, -0.05f, 0.0f,            0.0f, 0.0f, 1.0f,

		 -0.3f, 0.0f, 0.0f,               0.0f, 0.0f, 1.0f,
		 -0.3f, -0.05f, 0.0f,              0.0f, 0.0f, 1.0f,
		 -0.1f, -0.05f, 0.0f,              0.0f, 0.0f, 1.0f,

		 -0.3f, -0.15f, 0.0f,              0.0f, 0.0f, 1.0f,
		 -0.1f, -0.15f, 0.0f,              0.0f, 0.0f, 1.0f,
		 -0.1f, -0.2f, 0.0f,              0.0f, 0.0f, 1.0f,

		 -0.3f, -0.15f, 0.0f,              0.0f, 0.0f, 1.0f,
		 -0.3f, -0.20f, 0.0f,              0.0f, 0.0f, 1.0f,
		 -0.1f, -0.20f, 0.0f,              0.0f, 0.0f, 1.0f,
	};

	MeshColor* letras = new MeshColor();
	letras->CreateMeshColor(vertices_letras, 504);
	meshColorList.push_back(letras);



}


void CreateShaders()
{

	Shader* shader1 = new Shader(); //shader para usar �ndices: objetos: cubo y  pir�mide
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	Shader* shader2 = new Shader();//shader para usar color como parte del VAO: letras 
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);

	//Shader Rojo
	Shader* shader3 = new Shader(); //shader para usar �ndices: objetos: cubo y  pir�mide
	shader3->CreateFromFiles(vShader_rojo, fShader);
	shaderList.push_back(*shader3);

	//Shader Cafe
	Shader* shader4 = new Shader(); //shader para usar �ndices: objetos: cubo y  pir�mide
	shader4->CreateFromFiles(vShader_cafe, fShader);
	shaderList.push_back(*shader4);

	//Shader Verde
	Shader* shader5 = new Shader(); //shader para usar �ndices: objetos: cubo y  pir�mide
	shader5->CreateFromFiles(vShader_verde, fShader);
	shaderList.push_back(*shader5);

	//Shader Verde Claro
	Shader* shader6 = new Shader(); //shader para usar �ndices: objetos: cubo y  pir�mide
	shader6->CreateFromFiles(vShader_verdeClaro, fShader);
	shaderList.push_back(*shader6);
}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	//el orden de la piramide y del cubo importan para ver en que indice se encuentran
	CreaPiramide(); //�ndice 0 en MeshList
	CrearCubo();//�ndice 1 en MeshList
	CrearLetrasyFiguras(); //usa MeshColor, �ndices en MeshColorList
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	//Projection: Matriz de Dimensi�n 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	//glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	glm::mat4 projection = glm::perspective(glm::radians(60.0f), mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	//Model: Matriz de Dimensi�n 4x4 en la cual se almacena la multiplicaci�n de las transformaciones geom�tricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad

	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //fondo negro
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad

		////CREACION DE LAS LETRAS -----------------------------------------------------------------------------------

		////Para las letras hay que usar el segundo set de shaders con �ndice 1 en ShaderList 
		//shaderList[1].useShader();
		//uniformModel = shaderList[1].getModelLocation();
		//uniformProjection = shaderList[1].getProjectLocation();

		////LETRAS
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
  //      //model = glm::scale(model, glm::vec3(0.8));// Hacer la forma m�s peque�a (escalarla)
		////
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[0]->RenderMeshColor();
		//

		


		//CREACION DE LA CASA -----------------------------------------------------------------------------------
		
		//PIRAMIDE (TECHO AZUL)
		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		
		angulo += 0.1; //modificar este valor (velocidad de rotacion pero no se por que)

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.75f, -3.0f));
		model = glm::scale(model, glm::vec3(1.4f, 0.5f, 1.4f));
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh(); //modificar este indice para poder dibujar o el cubo o la piramide


		//CUBO ROJO
		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh(); //modificar este indice para poder dibujar o el cubo o la piramide

		//ARBOLITO 1
		//hojas 1
		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.4f, 0.4f, -3.0f));
		model = glm::scale(model, glm::vec3(0.55f, 1.2f, 0.55f));
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh(); //modificar este indice para poder dibujar o el cubo o la piramide
		
		//tronco1
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.4f, -0.35f, -3.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.4f, 0.25f));
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh(); //modificar este indice para poder dibujar o el cubo o la piramide


		//ARBOLITO 2
		//hojas 2
		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1.4f, 0.4f, -3.0f));
		model = glm::scale(model, glm::vec3(0.55f, 1.2f, 0.55f));
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh(); //modificar este indice para poder dibujar o el cubo o la piramide

		//tronco2
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1.4f, -0.35f, -3.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.4f, 0.25f));
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh(); //modificar este indice para poder dibujar o el cubo o la piramide

		
		//VENTANAS Y PUERTA
		shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.35f, -2.6f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh(); //modificar este indice para poder dibujar o el cubo o la piramide

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.25f, 0.20f, -2.6f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh(); //modificar este indice para poder dibujar o el cubo o la piramide

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.25f, 0.20f, -2.6f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh(); //modificar este indice para poder dibujar o el cubo o la piramide
		


		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}
// inicializar matriz: glm::mat4 model(1.0);
// reestablecer matriz: model = glm::mat4(1.0);
//Traslaci�n
//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
//////////////// ROTACI�N //////////////////
//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
////////////////  ESCALA ////////////////
//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
///////////////////// T+R////////////////
/*model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
*/
/////////////R+T//////////
/*model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
*/