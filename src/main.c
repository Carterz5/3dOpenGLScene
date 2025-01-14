#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <time.h>
#include "renderer.h"
#include "shader.h"
#include "indexbuffer.h"
#include "vertexarray.h"
#include "vertexbuffer.h"
#include "vertexbufferlayout.h"
#include "texture.h"
#include "cglm/cglm.h"
#include "cglm/mat4.h"



#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024




int main(void){


    int width = 0, height = 0;
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1024, 768, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwGetWindowSize(window, &width, &height);


    if (glewInit() != GLEW_OK){
        printf("Error!\n");
    }
    GLCall(const unsigned char *glversion = glGetString(GL_VERSION));
    printf("GL version is |%s|\n", glversion);


    float bgr = 0.10f, bgg = 0.18f, bgb = 0.24f, bga = 1.0f;


    float positions[] =
    { //     COORDINATES     /   TexCoord  //
        -0.5f, 0.0f,  0.5f, 	0.0f, 0.0f,
        -0.5f, 0.0f, -0.5f, 	5.0f, 0.0f,
         0.5f, 0.0f, -0.5f, 	0.0f, 0.0f,
         0.5f, 0.0f,  0.5f, 	5.0f, 0.0f,
         0.0f, 0.8f,  0.0f, 	2.5f, 5.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3,
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4
    };

    float positions2[] =
    { //     COORDINATES     /   TexCoord  //

        //Front
        -2.0f, -0.1f,  0.5f, 	0.0f, 0.7f,
        -1.0f, -0.1f,  0.5f, 	0.5f, 0.7f,
        -1.0f,  0.1f,  0.5f, 	0.5f, 0.99f,
        -2.0f,  0.1f,  0.5f, 	0.0f, 0.99f,

        //Back
        -2.0f, -0.1f,  -2.0f, 	0.0f, 0.7f,
        -1.0f, -0.1f,  -2.0f, 	0.5f, 0.7f,
        -1.0f,  0.1f,  -2.0f, 	0.5f, 0.99f,
        -2.0f,  0.1f,  -2.0f, 	0.0f, 0.99f,

        //Left
        -2.0f, -0.1f,  -2.0f, 	0.0f, 0.7f,
        -2.0f, -0.1f,   0.5f, 	1.0f, 0.7f,
        -2.0f,  0.1f,   0.5f, 	1.0f, 0.99f,
        -2.0f,  0.1f,  -2.0f, 	0.0f, 0.99f,

        //Right
        -1.0f, -0.1f,   0.5f, 	0.0f, 0.7f,
        -1.0f, -0.1f,  -2.0f, 	1.0f, 0.7f,
        -1.0f,  0.1f,  -2.0f, 	1.0f, 0.99f,
        -1.0f,  0.1f,   0.5f, 	0.0f, 0.99f,

        //Top
        -2.0f,  0.1f,  0.5f, 	0.0f, 0.39f,
        -1.0f,  0.1f,  0.5f, 	1.0f, 0.39f,
        -1.0f,  0.1f, -2.0f, 	1.0f, 0.65f,
        -2.0f,  0.1f, -2.0f, 	0.0f, 0.65f,

        //Bottom
        -2.0f,  -0.1f, -2.0f, 	0.0f, 0.0f,
        -1.0f,  -0.1f, -2.0f, 	1.0f, 0.0f,
        -1.0f,  -0.1f,  0.5f, 	1.0f, 0.34f,
        -2.0f,  -0.1f,  0.5f, 	0.0f, 0.34f


    };

    unsigned int indices2[] = {
        // Front face
        0, 1, 2,
        2, 3, 0,

        // Back face
        4, 5, 6,
        6, 7, 4,

        // Left face
        8, 9, 10,
        10, 11, 8,

        // Right face
        12, 13, 14,
        14, 15, 12,

        // Top face
        16, 17, 18,
        18, 19, 16,

        // Bottom face
        20, 21, 22,
        22, 23, 20
    };



    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


    //pyramid
    VertexArray va;
    VA_Construct(&va);

    VertexBuffer vb;
    VB_Construct(positions, 5 * 5 * sizeof(float), &vb);

    VertexBufferLayout vbl;
    VBL_Construct(&vbl);
    VBL_Pushfloat(3, &vbl);
    VBL_Pushfloat(2, &vbl);

    VA_AddBuffer(&vb, &vbl, &va);

    IndexBuffer ib;
    IB_Construct(indices, 18, &ib);

    
    mat4 model;
    glm_mat4_identity(model);

    mat4 mvp;

    Texture brick;
    TX_Construct("../res/textures/brick.png", &brick);
    TX_Bind(0, &brick);

    //rectangle
    VertexArray va2;
    VA_Construct(&va2);

    VertexBuffer vb2;
    VB_Construct(positions2, 5 * 24 * sizeof(float), &vb2);
    
    VertexBufferLayout vbl2;
    VBL_Construct(&vbl2);
    VBL_Pushfloat(3, &vbl2);
    VBL_Pushfloat(2, &vbl2);
    
    VA_AddBuffer(&vb2, &vbl2, &va2);

    IndexBuffer ib2;
    IB_Construct(indices2, 36, &ib2);

    mat4 model2;
    glm_mat4_identity(model2);

    mat4 mvp2;

    Texture grass;
    TX_Construct("../res/textures/grass.png", &grass);
    TX_Bind(1, &grass);


    //shared
    mat4 proj;
    glm_perspective(45.0f, (float)width / height, 0.1f, 100.0f, proj);

    mat4 view;
    glm_mat4_identity(view);
    vec3 viewtranslation = { 0.0f, -0.5f, -2.0f};
    glm_translate(view, viewtranslation);


    vec3 rotationaxis = {0.0f, 1.0f, 0.0f};

    mat4 temp;
    glm_mat4_mul(proj, view, temp);
    glm_mat4_mul(temp, model, mvp);


    Shader shader;
    SH_Construct(&shader,"../res/shaders/Basic.glsl");
    SH_Bind(&shader);
    




    float rotation = 0.0f;

    GLCall(glEnable(GL_DEPTH_TEST));

    VA_Unbind();
    SH_Unbind();
    VB_Unbind();
    IB_Unbind();
    GLCall(glfwSwapInterval(1));
    double lasttime = glfwGetTime();
    const double PHYSICS_TIME_STEP = 1.0 / 60.0;
    double previousTime = glfwGetTime();
    double accumulator = 0.0;
    const int FPS_SAMPLES = 100;
    double fpsSum = 0.0;
    int fpsCount = 0;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        GLCall(glClearColor(bgr,bgg,bgb,bga));
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT))

        //Different way to limit framerate than Cherno. glfwSwapInterval was not working on virtual machine.
        while (glfwGetTime() < lasttime + 1.0/TARGET_FPS) {

        };
        lasttime += 1.0/TARGET_FPS;


        double currentTime = glfwGetTime();
        double frameTime = currentTime - previousTime;
        previousTime = currentTime;


        if (frameTime > 0.25) {
            frameTime = 0.25;
        }

        accumulator += frameTime;

        // Update FPS average
        double currentFPS = 1.0 / frameTime;
        fpsSum += currentFPS;
        fpsCount++;

        // Every 100 frames, output the average FPS and reset
        if (fpsCount == FPS_SAMPLES) {
            double averageFPS = fpsSum / FPS_SAMPLES;
            char title[256];
            snprintf(title, sizeof(title), "FPS: %.2f", averageFPS);
            glfwSetWindowTitle(window, title);
            fpsSum = 0.0;
            fpsCount = 0;
        }

        


        while (accumulator >= PHYSICS_TIME_STEP){

            rotation += 0.01f;


            glm_rotate(model, rotation, rotationaxis);

            glm_mat4_mul(proj, view, temp);
            glm_mat4_mul(temp, model, mvp);

            //SH_SetUniformMat4f(&shader, "u_MVP", mvp);
            glm_mat4_identity(model);
            
            accumulator -= PHYSICS_TIME_STEP;
        }



        
        SH_Bind(&shader);
        //pyramid
        TX_Bind(0, &brick);
        SH_SetUniformMat4f(&shader, "u_MVP", mvp);
        SH_SetUniform1i(&shader, "u_Texture", 0);
        R_Draw_IB(&va, &ib, &shader);


        //Rectangle
        TX_Bind(1, &grass);
        SH_SetUniform1i(&shader, "u_Texture", 1);
        glm_mat4_mul(temp, model2, mvp2);
        SH_SetUniformMat4f(&shader, "u_MVP", mvp2);
        R_Draw_IB(&va2, &ib2, &shader);


        glfwGetWindowSize(window, &width, &height);
        glViewport(0, 0, width, height);


        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


        processInput(window, model, view, proj);


        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    //GLCall(glDeleteProgram(shader));
    SH_Destruct(&shader);
    IB_Destruct(&ib);
    VB_Destruct(&vb);
    VA_Destruct(&va);
    TX_Destruct(&brick);

    glfwTerminate();
    return 0;
}




void processInput(GLFWwindow *window, mat4 *model, mat4 *view, mat4 *projection) {
    static vec3 cameraPos = {0.0f, 0.0f, 3.0f};  // Initial camera position
    static vec3 cameraFront = {0.0f, 0.0f, -1.0f}; // Camera forward direction
    static vec3 cameraUp = {0.0f, 1.0f, 0.0f};    // Camera up direction

    static float yaw = -90.0f;  // Initial yaw (pointing along -Z)
    static float pitch = 0.0f;  // Initial pitch
    static float lastX = 400.0f; // Last mouse X position (assume 800x600 window)
    static float lastY = 300.0f; // Last mouse Y position
    static int firstMouse = 1;  // To handle first mouse movement

    float cameraSpeed = 0.025f;   // Adjust for movement speed
    float mouseSensitivity = 0.2f;  // Adjust for mouse sensitivity

    // Handle ESC key
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);

    // WASD input for movement
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        vec3 scaledFront;
        glm_vec3_scale(cameraFront, cameraSpeed, scaledFront);
        glm_vec3_add(cameraPos, scaledFront, cameraPos);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        vec3 scaledFront;
        glm_vec3_scale(cameraFront, cameraSpeed, scaledFront);
        glm_vec3_sub(cameraPos, scaledFront, cameraPos);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        vec3 cameraRight;
        glm_vec3_cross(cameraFront, cameraUp, cameraRight);
        glm_vec3_normalize(cameraRight);
        glm_vec3_scale(cameraRight, cameraSpeed, cameraRight);
        glm_vec3_sub(cameraPos, cameraRight, cameraPos);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        vec3 cameraRight;
        glm_vec3_cross(cameraFront, cameraUp, cameraRight);
        glm_vec3_normalize(cameraRight);
        glm_vec3_scale(cameraRight, cameraSpeed, cameraRight);
        glm_vec3_add(cameraPos, cameraRight, cameraPos);
    }

    // Spacebar and Left Ctrl input for vertical movement
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        vec3 scaledUp;
        glm_vec3_scale(cameraUp, cameraSpeed, scaledUp);
        glm_vec3_add(cameraPos, scaledUp, cameraPos);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        vec3 scaledDown;
        glm_vec3_scale(cameraUp, cameraSpeed, scaledDown);
        glm_vec3_sub(cameraPos, scaledDown, cameraPos);
    }

    // Mouse input for camera direction
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = 0;
    }

    float xOffset = xpos - lastX;
    float yOffset = lastY - ypos;  // Reversed since Y-coordinates range bottom to top
    lastX = xpos;
    lastY = ypos;

    xOffset *= mouseSensitivity;
    yOffset *= mouseSensitivity;

    yaw += xOffset;
    pitch += yOffset;

    // Constrain the pitch angle to prevent flipping
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    // Update camera front vector based on yaw and pitch
    vec3 front;
    front[0] = cosf(glm_rad(yaw)) * cosf(glm_rad(pitch));
    front[1] = sinf(glm_rad(pitch));
    front[2] = sinf(glm_rad(yaw)) * cosf(glm_rad(pitch));
    glm_vec3_normalize(front);
    glm_vec3_copy(front, cameraFront);

    // Update the view matrix
    glm_lookat(cameraPos, (vec3){cameraPos[0] + cameraFront[0], cameraPos[1] + cameraFront[1], cameraPos[2] + cameraFront[2]}, cameraUp, *view);
}

