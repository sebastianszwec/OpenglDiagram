#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

class CollatzConjecture
{
public:
	GLfloat xUnit;
	GLfloat yUnit;
	GLfloat axisAdjustment;
	std::vector<int> collatzVec;

private:
	int numberOfEntries;
	int currFillIndex;
	int currentWriteIndex;

public:
	CollatzConjecture(int collatzNumber, bool& drawXAxisRuler, bool& drawYAxisRuler, GLfloat& xUnit, GLfloat& yUnit, int screenWidth, int screenHeight, GLfloat asixAdj);

	int CollatzConjectureFillTable(int n);
	void RenderCollatzConjecture(GLfloat currentAxisXUnit, GLfloat currentAxisYUnit, GLfloat red, GLfloat green, GLfloat blue);
	void AdjustAxisUnits(bool& drawXAxisRuler, bool& drawYAxisRuler, GLfloat& xUnit, GLfloat& yUnit, int screenWidth, int screenHeight);
};