#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <chrono>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <thread>
#include <string>

#define GLT_IMPLEMENTATION
// #define STB_IMAGE_IMPLEMENTATION

#include "camera.h"
#include "glText.h"
#include "sea.h"
#include "shader.h"
#include "ship.h"
#include "treasure.h"
#include "model.h"
#include "cannonball.h"

std::vector<Cannonball> cannonballs(0);

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void keyCallFunc(GLFWwindow *window, int key, int scancode, int action,
                 int mode);
void HUD(GLTtext *textObj);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

// camera
Camera camera(glm::vec3(0.0f, -0.5f, 0.1f));

// Number of Enemy Ships
int numEnemyShips = 2;
int dead = 0;
int autoShoot = 0;

// Score
int score = 0;
int treasureCount = 0;
int health = 100;
int shoot = 0;
std::chrono::steady_clock::time_point startTime;

// Infinite
glm::mat4 infinite = glm::mat4(1.0f);

void AutoShoot() 
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(7000));
        autoShoot = 1;
    }
}

int main()
{
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    GLFWwindow *window =
        glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // char *cwd = get_current_dir_name();
    // cout << "Current working directory: " << cwd << endl;
    // free(cwd);

    // build and compile our shader program
    Shader ourShader("../Glitter/Shaders/vertex.shader", "../Glitter/Shaders/fragment.shader");

    // enable depth testing for 3d
    glEnable(GL_DEPTH_TEST);

    // Keybindings
    glfwSetKeyCallback(window, keyCallFunc);

    Ship ship(glm::vec3(0.0f), 0.0f, ourShader);
    Ship enemy[numEnemyShips];

    for (int i = 0; i < numEnemyShips; i++)
        enemy[i].ship(glm::vec3(2 * (float(rand()) / float((RAND_MAX))) - 1.0f, 2 * (float(rand()) / float((RAND_MAX))) - 1.0f, 0.0f), 0.0f, ourShader);

    Treasure chest(glm::vec3(2 * (float(rand()) / float((RAND_MAX))) - 1.0f, 2 * (float(rand()) / float((RAND_MAX))) - 1.0f, 0.01f), 0.0f, ourShader);

    Cannonball bullets[10];

    Sea sea;
    sea.init();
    sea.buffers();

    gltInit();

    GLTtext *textObj = gltCreateText();

    stbi_set_flip_vertically_on_load(true);

    startTime = std::chrono::steady_clock::now();

    std::thread t1(AutoShoot);
    t1.detach();

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // render
        glClearColor(0.831f, 0.945f, 0.976f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // make transformations
        glm::mat4 transform = glm::mat4(1.0f); // identity matrix

        ourShader.use();
        ourShader.setMat4("transform", transform);
        ourShader.setMat4("infinite", infinite);

        // view matrix
        glm::mat4 view = camera.GetViewMatrix(glm::vec3(0.0f));
        ourShader.setMat4("view", view);

        // projection matrix
        glm::mat4 projection = glm::perspective(
            glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT,
            0.1f, 100.0f);
        ourShader.setMat4("projection", projection);

        ourShader.setMat4("infinite", glm::mat4(1.0f));

        sea.draw();

        ship.draw(ourShader);

        if (shoot == 1)
        {
            int i = 0;
            for (; i < 10 && bullets[i].display; i++)
                ;
            if (i < 10)
            {
                bullets[i].display = true;
                bullets[i].whoShot = false;
                bullets[i].cannonball(glm::vec3(0.0f), glm::vec3(0.0f, 0.3f, 0.0f), ourShader);
                cannonballs.push_back(bullets[i]);
            }
            shoot = 0;
        }

        for (int i = 0; i < cannonballs.size(); i++)
        {
            cannonballs[i].move();
            if (cannonballs[i].dist(infinite) > 1.5f)
            {
                cannonballs[i].display = false;
                cannonballs.erase(cannonballs.begin() + i);
                i--;
            }
            else if(cannonballs[i].dist(infinite) < 0.07f)
            {
                cannonballs[i].display = false;
                cannonballs.erase(cannonballs.begin() + i);
                i--;
                health -= 10;
            }
            else
            {
                for (int j = 0; j < numEnemyShips; j++)
                {
                    if (cannonballs[i].dist(infinite, enemy[j].getModel()) < 0.1f && enemy[j].display)
                    {
                        score += 50;
                        enemy[j].display = false;
                        dead++;
                        cannonballs[i].display = false;
                        cannonballs.erase(cannonballs.begin() + i);
                        i--;
                        break;
                    }
                }
            }
        }

        for (int i = 0; i < cannonballs.size(); i++)
        {
            if ((cannonballs[i].whoShot == false)/* && (cannonballs[i].display == true)*/)
                cannonballs[i].draw(ourShader);
        }

        ourShader.setMat4("infinite", infinite);

        for (int i = 0; i < cannonballs.size(); i++)
        {
            if ((cannonballs[i].whoShot == true)/* && (cannonballs[i].display == true)*/)
                cannonballs[i].draw(ourShader);
        }

        if (chest.dist(infinite) < 0.07f && chest.display)
        {
            score += 100;
            treasureCount += 1;
            chest.display = false;
        }

        if (chest.display)
            chest.draw(ourShader);

        for (int i = 0; i < numEnemyShips; i++)
        {

            if (enemy[i].dist(infinite) < 0.07f && enemy[i].display)
            {
                health -= 30;
                score += 30;
                enemy[i].display = false;
                dead++;
            }

            if (enemy[i].display)
            {
                enemy[i].translateTowards(infinite);
                enemy[i].draw(ourShader);
            }
        }

        if (health <= 0)
        {
            glfwSetWindowShouldClose(window, true);
        }

        if (dead == numEnemyShips && !chest.display)
        {
            infinite = glm::mat4(1.0f);
            chest.display = true;
            chest.treasure(glm::vec3(2 * (float(rand()) / float((RAND_MAX))) - 1.0f, 2 * (float(rand()) / float((RAND_MAX))) - 1.0f, 0.01f), 0.0f, ourShader);
            dead = 0;
            for (int i = 0; i < numEnemyShips; i++)
            {
                enemy[i].display = true;
                enemy[i].ship(glm::vec3(2 * (float(rand()) / float((RAND_MAX))) - 1.0f, 2 * (float(rand()) / float((RAND_MAX))) - 1.0f, 0.0f), 0.0f, ourShader);
            }
            while(cannonballs.size() > 0)
            {
                cannonballs[0].display = false;
                cannonballs.erase(cannonballs.begin());
            }
        }

        if (autoShoot == 1)
        {
            for (int j = 0; j < numEnemyShips; j++)
            {
                if(!enemy[j].display)
                    continue;
                int i = 0;
                for (; i < 10 && bullets[i].display; i++)
                    ;
                if (i < 10)
                {
                    bullets[i].display = true;
                    bullets[i].whoShot = true;
                    glm::vec3 pos = enemy[j].getModel() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
                    glm::vec3 dir = glm::normalize(infinite * enemy[j].getModel() * glm::vec4(0.0f, -0.6f, 0.0f, 1.0f) - infinite * enemy[j].getModel() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)) / 5.0f;
                    bullets[i].cannonball(pos, dir, ourShader);
                    cannonballs.push_back(bullets[i]);
                }
            }
            autoShoot = 0;
        }

        chest.rotate(0.01f);

        HUD(textObj);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    sea.del();
    // ship.del();
    gltDeleteText(textObj);
    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this
// frame and react accordingly
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width
    // and height will be significantly larger than specified on retina
    // displays.
    glViewport(0, 0, width, height);
}

void keyCallFunc(GLFWwindow *window, int key, int scancode, int action,
                 int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    switch (key)
    {
    case GLFW_KEY_1:
        camera.Position = glm::vec3(0.0f, 0.0f, 2.0f);
        break;
    case GLFW_KEY_2:
        camera.Position = glm::vec3(0.0f, -0.5f, 0.1f);
        break;
    case GLFW_KEY_W:
        infinite = glm::translate(glm::mat4(1.0f),
                                  glm::vec3(0.0f, -0.005f, 0.0f)) *
                   infinite;
        break;
    case GLFW_KEY_S:
        infinite =
            glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.005f, 0.0f)) *
            infinite;
        break;
    case GLFW_KEY_A:
        infinite = glm::mat4(cos(0.02f), -sin(0.02f), 0, 0, sin(0.02f),
                             cos(0.02f), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1) *
                   infinite;
        break;
    case GLFW_KEY_D:
        infinite = glm::mat4(cos(-0.02f), -sin(-0.02f), 0, 0, sin(-0.02f),
                             cos(-0.02f), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1) *
                   infinite;
        break;
    case GLFW_KEY_SPACE:
        shoot = 1;
        break;
    }
}

void HUD(GLTtext *textObj)
{
    gltBeginDraw();
    char text[256];
    sprintf(text, "Score: %d\nHealth: %d\nNo of Treasures Collected: %d\nTime Elapsed: %ld", score, health, treasureCount, std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - startTime).count());
    gltSetText(textObj, text);
    // std::cout << text << std::endl;
    gltDrawText2DAligned(textObj, (GLfloat)(2 * SCR_WIDTH / 10),
                         (GLfloat)(SCR_HEIGHT / 10), 1.0f, GLT_CENTER,
                         GLT_CENTER);
    gltEndDraw();
}