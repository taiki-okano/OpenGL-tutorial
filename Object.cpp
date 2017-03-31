#include "Object.h"

Object::Object(const GLint dimension, const GLsizei vertexCount, const Object::Vertex* vertex){
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), vertex, GL_STATIC_DRAW);

	glVertexAttribPointer(0, dimension, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
}

Object::~Object(){
	glDeleteBuffers(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
}

void Object::bind() const{
	glBindVertexArray(m_vao);
}

Shape::Shape(const GLint size, const GLsizei vertexCount, const Object::Vertex* vertex, const bool fill) : m_fill(fill), m_object(new Object(size, vertexCount, vertex)), m_vertexCount(vertexCount){}

void Shape::draw() const{
	m_object -> bind();
	execute();
}

void Shape::execute() const{
	if(m_fill){
		glDrawArrays(GL_TRIANGLE_FAN, 0, m_vertexCount);
	}
	else{
		glDrawArrays(GL_LINE_LOOP, 0, m_vertexCount);
	}
}

