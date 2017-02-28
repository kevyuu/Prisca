// GLFW
#include "render.h"
#include <GLFW/glfw3.h>
#include <iostream>

#include "prisca.h"

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// The MAIN function, from here we start the application and run the game loop
int main()
{
    std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);    
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }    

    // Define the viewport dimensions
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);  
    
    Prisca::Init();
    GLRender::Init(width, height);

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        if (glfwGetWindowAttrib(window, GLFW_FOCUSED)) {
            double mouse_x, mouse_y;
            glfwGetCursorPos(window, &mouse_x, &mouse_y);
            Prisca::g_UIState.mouse_pos = {(float)mouse_x, HEIGHT - (float)mouse_y};
        } else {
            Prisca::g_UIState.mouse_pos = {-1, -1};
        }

        Prisca::g_UIState.mouse_down = glfwGetMouseButton(window, 1) == GLFW_PRESS;
        Prisca::NewFrame();
        
        if (Prisca::Button(1, {{10.0f, 10.0f}, {200.0f, 200.0f}}, {0.2f, 0.5f, 0.0f, 1.0f})) {
            std::cout<<"You click the button\n"<<std::endl;
        }

        if (Prisca::Button(2, {{210.0f, 210.0f}, {310.0f, 310.0f}}, {0.0f, 0.2f, 0.5f, 1.0f})) {
            std::cout<<"You click the second button\n"<<std::endl;
        }
        
        GLRender::Render(&Prisca::g_RenderOutput);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }

    GLRender::Cleanup();
    Prisca::Cleanup();

    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}