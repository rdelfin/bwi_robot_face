#include <vector>
#include <GL/glut.h>
#include "glm/glm.hpp"

void load_obj(const char* filename, std::vector<glm::vec4> &vertices, std::vector<glm::vec3> &normals, std::vector<GLushort> &elements);