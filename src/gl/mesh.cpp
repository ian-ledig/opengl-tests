#include "mesh.h"

#include <GL/glew.h>
#include "gl_utils.h"

#include <iostream>
#include <memory>

void Mesh::_update_buffers()
{
    GL(glBindVertexArray(_vao_id));
    GL(glBindVertexArray(0));

    GL(glBindBuffer(GL_ARRAY_BUFFER, _vbo_id));
    GL(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * _vertices_data.size(), &_vertices_data[0]));
    GL(glBindBuffer(GL_ARRAY_BUFFER, 0));

    GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo_id));
    GL(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(unsigned) * _indices.size(), &_indices[0]));
    GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

    GL(glBindVertexArray(_vao_id));
    GL(glBindVertexArray(0));
}

Mesh::Mesh()
{
}

Mesh::Mesh(unsigned max_vertex_size, unsigned max_element_size, const Format& format, unsigned draw_mode) :
    _vao_id(0U),
    _vbo_id(0U),
    _ebo_id(0U),
    _elements_count(0U),
    _max_vertex_size(max_vertex_size),
    _max_element_size(max_element_size),
    _format(format),
    _draw_mode(draw_mode)
{
}

Mesh::Mesh(const Mesh& other) :
    _vao_id(0U),
    _vbo_id(other._vbo_id),
    _ebo_id(other._ebo_id),
    _elements_count(other._elements_count),
    _max_vertex_size(other._max_vertex_size),
    _max_element_size(other._max_element_size),
    _format(other._format),
    _draw_mode(other._draw_mode)
{
    GL(glGenVertexArrays(1, &_vao_id));

    bind();

    GL(glBindBuffer(GL_ARRAY_BUFFER, _vbo_id));
    GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo_id));

    _format.apply();

    GL(glBindVertexArray(0));
    GL(glBindBuffer(GL_ARRAY_BUFFER, 0));

    GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

Mesh::~Mesh()
{
    if (_vao_id != 0) {
        deinit();
    }
}

Mesh& Mesh::operator=(const Mesh& mesh)
{
    _max_vertex_size = mesh._max_vertex_size;
    _max_element_size = mesh._max_element_size;
    _format = mesh._format;
    _draw_mode = mesh._draw_mode;
    _vertices_data = mesh._vertices_data;
    _indices = mesh._indices;

    GL(glGenBuffers(1, &_vbo_id));
    GL(glGenBuffers(1, &_ebo_id));

    GL(glGenVertexArrays(1, &_vao_id));

    bind();

    GL(glBindBuffer(GL_ARRAY_BUFFER, _vbo_id));
    GL(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _max_vertex_size, nullptr, _draw_mode));

    GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo_id));
    GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * _max_element_size, nullptr, _draw_mode));

    _format.apply();

    GL(glBindVertexArray(0));
    GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

    _elements_count = _indices.size();
    _update_buffers();

    return *this;
}

void Mesh::init()
{
    _elements_count = 0;

    GL(glGenBuffers(1, &_vbo_id));
    GL(glGenBuffers(1, &_ebo_id));

    GL(glGenVertexArrays(1, &_vao_id));

    bind();

    auto vertices = std::make_unique<float[]>(_max_vertex_size);
    auto indices = std::make_unique<unsigned[]>(_max_element_size);

    GL(glBindBuffer(GL_ARRAY_BUFFER, _vbo_id));
    GL(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _max_vertex_size, vertices.get(), _draw_mode));

    GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo_id));
    GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * _max_element_size, indices.get(), _draw_mode));

    _format.apply();

    GL(glBindVertexArray(0));
    GL(glBindBuffer(GL_ARRAY_BUFFER, 0));

    GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

    if (_indices.size() > 0) {
        _elements_count = _indices.size();
        _update_buffers();
    }
}

void Mesh::deinit()
{
    GL(glBindVertexArray(0));
    GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

    GL(glDeleteVertexArrays(1, &_vao_id));
    GL(glDeleteBuffers(1, &_vbo_id));
    GL(glDeleteBuffers(1, &_ebo_id));

    _vao_id = 0;
    _vbo_id = 0;
    _ebo_id = 0;
}

unsigned Mesh::getVaoID() const
{
    return _vao_id;
}

unsigned Mesh::getVboID() const
{
    return _vbo_id;
}

unsigned Mesh::getEboID() const
{
    return _ebo_id;
}

void Mesh::addInstancedInfo(int index, int vbo, int size, unsigned type, int stride, uint64_t offset) const
{
    bind();

    GL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GL(glVertexAttribPointer(index, size, type, GL_FALSE, stride, reinterpret_cast<void*>(offset)));
    GL(glEnableVertexAttribArray(index));
    GL(glBindBuffer(GL_ARRAY_BUFFER, 0));

    GL(glVertexAttribDivisor(index, 1));

    GL(glBindVertexArray(0));
}

void Mesh::set(const std::vector<float>& vertices_data, const std::vector<unsigned>& indices)
{
    if (vertices_data.size() > _max_vertex_size) {
        std::cout << "Error: Too much vertices (" << vertices_data.size() << " | " << _max_vertex_size << ")" << std::endl;
        return;
    }
    if (indices.size() > _max_element_size) {
        std::cout << "Error: Too much indices (" << indices.size() << " | " << _max_element_size << ")" << std::endl;
        return;
    }

    _vertices_data = vertices_data;
    _indices = indices;

    _elements_count = _indices.size();

    if (_vao_id != 0) {
        _update_buffers();
    }
}

void Mesh::bind() const
{
    GL(glBindVertexArray(_vao_id));
}

void Mesh::unbind() const
{
    GL(glBindVertexArray(0));
}

void Mesh::draw(unsigned primitive) const
{
    GL(glDrawElements(primitive, _elements_count, GL_UNSIGNED_INT, 0));
}

void Mesh::drawInstanced(unsigned primitive, int count) const
{
    GL(glDrawElementsInstanced(primitive, _elements_count, GL_UNSIGNED_INT, 0, count));
}

unsigned Mesh::getElementsCount() const
{
    return _elements_count;
}

Mesh::Format::Format() = default;

Mesh::Format::Format(std::initializer_list<Mesh::Format::Attribute> list) : _sizes(list)
{
}

void Mesh::Format::apply() const
{
    auto size = (unsigned)_sizes.size();

    for (unsigned i = 0; i < size; i++) {
        const Attribute* attrib = &_sizes[i];
        void* offset = nullptr;

        if (attrib->offset != 0) {
            offset = (void*)(sizeof(float) * attrib->offset);
        }

        GL(glVertexAttribPointer(i, attrib->size, GL_FLOAT, GL_FALSE, attrib->stride, offset));
        GL(glEnableVertexAttribArray(i));
    }
}

int Mesh::Format::attributeCount() const
{
    return _sizes.size();
}
