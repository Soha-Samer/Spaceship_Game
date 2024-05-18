#include "Angel.h"
#include "Sphere.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <cmath>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>



using namespace std;


//camera
typedef Angel::vec3 point3;
typedef Angel::vec4  color4;
typedef Angel::vec4  point4;


GLuint program;  // Declare program as a global variable
GLuint vao, vbo1, vbo2, ibo1, vPosition, modelAttrib, viewAttrib, projectionAttrib, colorAttrib, vTexture, texture1, texture2;
GLuint loc;
glm::mat4 model;

glm::vec3 cameraPos, cameraTarget, cameraDirection, cameraRight, cameraUp, cameraFront;
glm::mat4 view, projection;

glm::mat4 trans;
float translate = 0.f;

float speed = 0.1f, yaw = -90.0f;




// Vertices of a unit cube centered at origin
point4 cubevertices[8] = {
    point4(-0.5, -0.5,  0.5, 1.0),
    point4(-0.5,  0.5,  0.5, 1.0),
    point4(0.5,  0.5,  0.5, 1.0),
    point4(0.5, -0.5,  0.5, 1.0),
    point4(-0.5, -0.5, -0.5, 1.0),
    point4(-0.5,  0.5, -0.5, 1.0),
    point4(0.5,  0.5, -0.5, 1.0),
    point4(0.5, -0.5, -0.5, 1.0)
};

// Indices for drawing triangles
GLuint cubeindices[36] = {
    0, 1, 2, 0, 2, 3,  // Front face
    4, 5, 6, 4, 6, 7,  // Back face
    1, 5, 6, 1, 6, 2,  // Right face
    0, 4, 7, 0, 7, 3,  // Left face
    3, 2, 6, 3, 6, 7,  // Top face
    0, 1, 5, 0, 5, 4   // Bottom face
};

// Texture coordinates for the cube
vec2 cubeTexCoords[8] = {
    vec2(0.0, 0.0),  // Vertex 0
    vec2(0.0, 1.0),  // Vertex 1
    vec2(1.0, 1.0),  // Vertex 2
    vec2(1.0, 0.0),  // Vertex 3
    vec2(0.0, 0.0),  // Vertex 4
    vec2(0.0, 1.0),  // Vertex 5
    vec2(1.0, 1.0),  // Vertex 6
    vec2(1.0, 0.0)   // Vertex 7
};




const int NumVertices = 9;  // 3 triangles


point3 spaceshippoints[NumVertices];

int Index = 0;



//----------------------------------------------------------------------------

void triangle(const point3& a, const point3& b, const point3& c)
{
    spaceshippoints[Index++] = a;
    spaceshippoints[Index++] = b;
    spaceshippoints[Index++] = c;
    
}




//----------------------------------------------------------------------------


void initTexture() {
    stbi_set_flip_vertically_on_load(true);

    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, channels;
    unsigned char* data = stbi_load("image.jpg", &width, &height, &channels, 0);



    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        std::cout << "image loaded";


    }


    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char* data2 = stbi_load("Color-Green.jpg", &width, &height, &channels, 0);

    if (data2)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
        std::cout << "image 2 loaded";


    }

    stbi_image_free(data);




}

void init(void)
{
    point3 spaceshipVertices[] = {
        point3(-0.5, 0.25,0.0), point3(0.5, 0.25,0.0), point3(0.0, 0.75,0.0),   // Top triangle vertices
        point3(-0.5, 0.25,0.0), point3(-0.5, -0.75,0.0), point3(0.5, -0.75,0.0),  // Left rectangle vertices
        point3(0.5, 0.25,0.0), point3(0.5, -0.75,0.0), point3(-0.5, 0.25,0.0)  // Right rectangle vertices
    };

    


    // Create a vertex array object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);



    // Create and initialize a buffer object

   
    glGenBuffers(1, &vbo1);
    glBindBuffer(GL_ARRAY_BUFFER, vbo1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(spaceshipVertices), spaceshipVertices, GL_STATIC_DRAW);








      //cube  
    glGenBuffers(1, &vbo2);
    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubevertices) + sizeof(cubeTexCoords), NULL, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(cubevertices), cubevertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(cubevertices), sizeof(cubeTexCoords), cubeTexCoords);

    glGenBuffers(1, &ibo1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeindices), cubeindices, GL_STATIC_DRAW);

    //cube_end


    vTexture = glGetAttribLocation(program, "vertexTexture");
    glEnableVertexAttribArray(vTexture);
    glVertexAttribPointer(vTexture, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(cubevertices)));



    // Load shaders and use the resulting shader program

     program = InitShader("vshader.glsl", "fshader.glsl");
    glUseProgram(program);




    // Initialize the vertex position attribute from the vertex shader    
     loc = glGetAttribLocation(program, "vertexPosition");



     vTexture = glGetAttribLocation(program, "vertexTexture");
     glEnableVertexAttribArray(vTexture);



   

    //camera

    modelAttrib = glGetUniformLocation(program, "model");
    viewAttrib = glGetUniformLocation(program, "view");
    projectionAttrib = glGetUniformLocation(program, "projection");
    colorAttrib = glGetUniformLocation(program, "color");


    cameraPos = glm::vec3(0.0f, 0.0f, 2.0f);
    cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    cameraDirection = glm::normalize(cameraPos - cameraTarget);
    cameraRight = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), cameraDirection));
    cameraUp = glm::cross(cameraDirection, cameraRight);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

    projection = glm::perspective(glm::radians(45.f), 1.f, 0.1f, 100.0f);
    glUniformMatrix4fv(projectionAttrib, 1, GL_FALSE, glm::value_ptr(projection));

  
    initTexture();

    

    glClearColor(1.0, 1.0, 1.0, 1.0); /* white background */

    glEnable(GL_DEPTH_TEST);




}

//----------------------------------------------------------------------------

void display(void)
{
    // Clear

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


   

    //camera
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    glUniformMatrix4fv(viewAttrib, 1, GL_FALSE, glm::value_ptr(view));


    //spacehship
    glBindBuffer(GL_ARRAY_BUFFER, vbo1);
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    view = glm::mat4(1.0);
    glUniformMatrix4fv(viewAttrib, 1, GL_FALSE, glm::value_ptr(view));

    //model matrix for spaceship
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0, 0, -10));
    glUniformMatrix4fv(modelAttrib, 1, GL_FALSE, glm::value_ptr(model));

    // Activate and bind texture only for the cube
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glUniform1i(glGetUniformLocation(program, "tex"), 0);

    //Drawspaceship
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);
    
     //CUBE BINDING AND DRAWING

    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(loc);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo1);



    // Texture coordinates for the cube
    glVertexAttribPointer(vTexture, 2, GL_FLOAT, false, 0, BUFFER_OFFSET(sizeof(cubevertices)));
    glEnableVertexAttribArray(vTexture);



    glActiveTexture(GL_TEXTURE);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glUniform1i(glGetUniformLocation(program, "tex"), 0);


    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    glUniformMatrix4fv(viewAttrib, 1, GL_FALSE, glm::value_ptr(view));
    //model matrix for cube
    model = glm::mat4(1.0f);
    model=glm::scale(model, glm::vec3(100, 100, 100));
    glUniformMatrix4fv(modelAttrib, 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //cube end


     // Flush
    glFlush();

    glutSwapBuffers();



}

//----------------------------------------------------------------------------
void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 033:
        exit(EXIT_SUCCESS);
        break;
    case 'r':
        cameraPos += speed * cameraFront;

        break;
    case 'f':
        cameraPos -= speed * cameraFront;

        break;
    case 'w':
        cameraPos -= speed * cameraUp;

        //trans = glm::translate(trans, glm::vec3(model, speed * cameraFront, 0.0f));

        //model = glm::translate(model, speed * cameraFront);  // Translate the model in the direction of the camera's movement
        //glUniformMatrix4fv(modelAttrib, 1, GL_FALSE, glm::value_ptr(model));

        break;
    case 's':
        cameraPos += speed * cameraUp;


      

        break;
    case 'a':
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;

      

        break;
    case 'd':
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;

        break;

    case 'q':
        yaw -= 1.0f;
        cameraDirection.x = glm::cos(glm::radians(yaw));
        cameraDirection.z = glm::sin(glm::radians(yaw));
        cameraFront = glm::normalize(cameraDirection);
        break;
    case 'e':
        yaw += 1.0f;
        cameraDirection.x = glm::cos(glm::radians(yaw));
        cameraDirection.z = glm::sin(glm::radians(yaw));
        cameraFront = glm::normalize(cameraDirection);
        break;
    }

    
}

void idle(void)
{


    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(1024, 1024);
    glutInitContextVersion(3, 2);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutCreateWindow("SpaceShip");


 

    glewInit();

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}