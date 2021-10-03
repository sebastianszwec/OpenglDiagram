#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

class CollatzConjecture
{
public:
	GLfloat axisXUnit;
	GLfloat axisYUnit;
	GLfloat axisAdjustment;

private:
	int numberOfEntries;
	unsigned int collatzTable[1000];
	int currFillIndex;
	int currentWriteIndex;

public:
	CollatzConjecture(int collatzNumber, bool& drawXAxisRuler, bool& drawYAxisRuler, GLfloat& xUnit, GLfloat& yUnit, int screenWidth, int screenHeight, GLfloat asixAdj);

	int CollatzConjectureFillTable(int n);
	void RenderCollatzConjecture();
	void AdjustAxisUnits(bool& drawXAxisRuler, bool& drawYAxisRuler, GLfloat& xUnit, GLfloat& yUnit, int screenWidth, int screenHeight);
};
