#include "mesh.hpp"
#include <glad/glad.h>
#include <numeric>

Mesh::Mesh(unsigned int vao, unsigned int vbo, unsigned int ebo, unsigned int indicesCount) :
    vao(vao), vbo(vbo), ebo(ebo), indicesCount(indicesCount) {}

Mesh::~Mesh() {}

void Mesh::draw() {
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, nullptr);
}

void Mesh::destroy() {
    if (vao) glDeleteVertexArrays(1, &vao); vao = 0;
    if (vbo) glDeleteBuffers(1, &vbo); vbo = 0;
    if (ebo) glDeleteBuffers(1, &ebo); ebo = 0;
}

Mesh* Mesh::create(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<unsigned char>& attributes) {
    unsigned int vao, vbo, ebo, indicesCount;

    indicesCount = indices.size();

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    unsigned int totalStride = std::accumulate(attributes.begin(), attributes.end(), 0);

    unsigned int stride = 0;
    unsigned int index = 0;
    for (unsigned char attr : attributes) {
        glVertexAttribPointer(index, attr, GL_FLOAT, GL_FALSE, totalStride * sizeof(float), (GLvoid*)(stride * sizeof(float)));
        glEnableVertexAttribArray(index);
        stride += attr;
        index++;
    }

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);

    return new Mesh(vao, vbo, ebo, indicesCount);
}