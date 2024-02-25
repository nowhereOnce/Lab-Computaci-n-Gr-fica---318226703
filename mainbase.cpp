#include <stdio.h>
#include <glew.h>
#include <glfw3.h>

#include <stdlib.h>
#include <time.h>

//Dimensiones de la ventana
const int WIDTH = 800, HEIGHT = 600;
float rojo, verde, azul = 0.0f;
int contador = 0;


int main()
{
    //Inicializaci�n de GLFW
    if (!glfwInit())
    {
        printf("Fall� inicializar GLFW");
        glfwTerminate();
        return 1;
    }
    //Asignando variables de GLFW y propiedades de ventana
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //para solo usar el core profile de OpenGL y no tener retrocompatibilidad
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //CREAR VENTANA
    GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Practica 1 ejercicio 1", NULL, NULL);


    //En caso de que falle la ventana
    if (!mainWindow)
    {
        printf("Fallo en crearse la ventana con GLFW");
        glfwTerminate();
        return 1;
    }
    //Obtener tama�o de Buffer (los dos ultimos parametros sirven para poder redimensionar la ventana, pero ahorita creo que no importa mucho eso)
    int BufferWidth, BufferHeight;
    glfwGetFramebufferSize(mainWindow, &BufferWidth, &BufferHeight);

    //asignar el contexto (indicar la ventana activa)
    glfwMakeContextCurrent(mainWindow);

    //permitir nuevas extensiones
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        printf("Fall� inicializaci�n de GLEW");
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    //A PARTIR DE AQUI SON PURAS LINEAS DE GL    
    // Asignar valores de la ventana y coordenadas
    //Asignar Viewport
    glViewport(0, 0, BufferWidth, BufferHeight); //acomoda en el origen y pone el tama�o con ayuda de los buffers
    printf("Version de Opengl: %s \n", glGetString(GL_VERSION));
    printf("Marca: %s \n", glGetString(GL_VENDOR));
    printf("Renderer: %s \n", glGetString(GL_RENDERER));
    printf("Shaders: %s \n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    //Loop mientras no se cierra la ventana
    //Mientras no se cierre la ventana con alt f4 o con click para cerrar se ejecuta lo siguiente
    //(la condicion de adentro del while se hace true)

    double lastTime = glfwGetTime();
    double currentTime;
    while (!glfwWindowShouldClose(mainWindow))
    {
        // Obtener tiempo actual
        currentTime = glfwGetTime();

        // Verificar si han pasado 2 segundos
        if (currentTime - lastTime >= 2.0)
        {
            // Generar colores aleatorios
            float rojo = (float)rand() / RAND_MAX;
            float verde = (float)rand() / RAND_MAX;
            float azul = (float)rand() / RAND_MAX;

            // Limpiar la ventana con el color aleatorio
            glClearColor(rojo, verde, azul, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // Intercambiar b�feres
            glfwSwapBuffers(mainWindow);

            // Actualizar el �ltimo tiempo
            lastTime = currentTime;
        }

        // Poll de eventos
        glfwPollEvents();
    }


    return 0;
}
