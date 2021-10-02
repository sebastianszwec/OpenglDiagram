#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

class CollatzConjecture
{
public:
	int numberOfEntries;
	unsigned int collatzTable[1000];
	int currFillIndex;
	int currentWriteIndex;

	CollatzConjecture()
		: numberOfEntries(0), collatzTable(), currFillIndex(1), currentWriteIndex(0)
	{}

	int CollatzConjectureFillTable(int n);
	void RenderCollatzConjecture(GLfloat* axisXUnit, GLfloat* axisYUnit, const GLfloat axisAdjustment);
};
