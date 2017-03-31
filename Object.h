#pragma once

#include "Include.h"

class Object{
	GLuint m_vao;
	GLuint m_vbo;

public:
	struct Vertex{
		GLfloat position[2];
	};

	Object(const GLint dimension, const GLsizei vertexCount, const Vertex* vertex);

	virtual ~Object();

	void bind() const;

	Object(const Object&) = delete;
	Object& operator=(const Object&) = delete;
	Object(Object&&) = default;
	Object& operator=(Object&&) = default;
};

class Shape{
	const bool m_fill;
	std::shared_ptr<const Object> m_object;

protected:
	const GLsizei m_vertexCount;

public:
	Shape(const GLint size, const GLsizei vertexCount, const Object::Vertex* vertex, const bool fill);

	void draw() const;

	virtual void execute() const;
};

