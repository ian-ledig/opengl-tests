#pragma once

#include <vector>
#include <cstdint>

class Mesh {
public:
    class Format {
    public:
        struct Attribute {
            unsigned size;
            unsigned stride;
            unsigned offset;
        };

    private:
        std::vector<Attribute> _sizes;

    public:
        Format();
        Format(std::initializer_list<Attribute> list);

        void apply() const;
        int attributeCount() const;
    };

public:
    Mesh();
    Mesh(unsigned max_vertex_size, unsigned max_element_size, const Format& format, unsigned draw_mode);
    Mesh(const Mesh& mesh);
    Mesh(Mesh&& mesh) = default;
    Mesh& operator=(Mesh&& mesh) = default;
    Mesh& operator=(const Mesh& mesh);
    virtual ~Mesh();

    virtual void init();
    void deinit();

    unsigned getVaoID() const;
    unsigned getVboID() const;
    unsigned getEboID() const;

    void addInstancedInfo(int index, int vbo, int size, unsigned type, int stride, uint64_t offset) const;
    void set(const std::vector<float>& vertices_data, const std::vector<unsigned>& indices);
    void bind() const;
    void unbind() const;
    virtual void draw(unsigned primitive) const;
    void drawInstanced(unsigned primitive, int count) const;
    unsigned getElementsCount() const;

private:
    void _update_buffers();

    unsigned _vao_id;
    unsigned _vbo_id;
    unsigned _ebo_id;
    unsigned _elements_count;
    std::vector<float> _vertices_data;
    std::vector<unsigned> _indices;

    unsigned _max_vertex_size;
    unsigned _max_element_size;
    Format _format;
    unsigned _draw_mode;
};
