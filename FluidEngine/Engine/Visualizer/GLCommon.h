#pragma once

namespace Engine
{
	// This file contains OpenGL type forwardings in order to avoid including GL.h
	// header files.

	// Base GL types
	using GLenum = unsigned int;
	using GLboolean = unsigned char;
	using GLbitfield = unsigned int;
	using GLbyte = signed char;
	using GLshort = short;
	using GLint = int;
	using GLsizei = int;
	using GLubyte = unsigned char;
	using GLushort = unsigned short;
	using GLuint = unsigned int;
	using GLhalf = unsigned short;
	using GLfloat = float;
	using GLclampf = float;
	using GLdouble = double;
	using GLclampd = double;
	using GLvoid = void;

}