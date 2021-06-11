#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

bool shouldSort = false;

class Rect {
    public:
        float height;
        Rect(float h) {
            this->height = h;
        }
};

float RandomNumber(float min, float max) {
    return (min + 1) + (((float)rand()) / (float)RAND_MAX) * (max - (min + 1));
}

vector<Rect> selectionSort(vector<Rect> v) {
    for (int i = 0; i < v.size(); i++) {
        Rect current = v[i];
        float min = v[i].height;
        int minIndex = i;
        for (int j = i; j < v.size(); j++) {
            if (v[j].height < min) {
                min = v[j].height;
                minIndex = j;
            }
        }
        swap(v[i], v[minIndex]);
    }

    return v;
}


// Run algorithm on ENTER input
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
        shouldSort = !shouldSort; // Assigns the opposite value to shouldSort
    }
}


int main() {
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(1200, 600, "Sorting", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);


    vector<Rect> vector;
    for (int i = 0; i < 20; i++) {
        float height = RandomNumber(-1, 1);
        Rect r(height);
        vector.push_back(r);
    }
   

    while (!glfwWindowShouldClose(window))
    {
        /* Render */
        glClear(GL_COLOR_BUFFER_BIT);

        if (shouldSort) {
            auto v = selectionSort(vector);
            for (int i = 0; i < v.size(); i++) {
                Rect rect = v[i];

                glBegin(GL_POLYGON);
                glColor3f(1.0, 0, 0);
                glVertex2f(-0.91 + i * 0.1, rect.height);
                glVertex2f(-0.91 + i * 0.1, -1);
                glVertex2f(-1 + i * 0.1, -1);
                glVertex2f(-1 + i * 0.1, rect.height);
                glEnd();
            }
        }
        else {
            for (int i = 0; i < vector.size(); i++) {

                Rect rect = vector[i];

                glBegin(GL_POLYGON);
                glColor3f(1.0, 0, 0);
                glVertex2f(-0.91 + i * 0.1, rect.height);
                glVertex2f(-0.91 + i * 0.1, -1);
                glVertex2f(-1 + i * 0.1, -1);
                glVertex2f(-1 + i * 0.1, rect.height);
                glEnd();
            }
        }

        glfwSetKeyCallback(window, key_callback);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}