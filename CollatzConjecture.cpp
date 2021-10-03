#include "CollatzConjecture.h"

CollatzConjecture::CollatzConjecture(int collatzNumber, bool& drawXAxisRuler, bool& drawYAxisRuler, GLfloat& xUnit, GLfloat& yUnit, int screenWidth, int screenHeight, GLfloat asixAdj)
    : numberOfEntries(0), collatzTable(), currFillIndex(1), currentWriteIndex(0), axisXUnit(xUnit), axisYUnit(yUnit), axisAdjustment(asixAdj)
{
    CollatzConjectureFillTable(collatzNumber);
    AdjustAxisUnits(drawXAxisRuler, drawYAxisRuler, axisXUnit, axisYUnit, screenWidth, screenHeight);
}

int CollatzConjecture::CollatzConjectureFillTable(int n)
{
    std::cout << "(" << CollatzConjecture::currFillIndex << ", " << n << ")" << std::endl;

    CollatzConjecture::collatzTable[CollatzConjecture::currFillIndex] = n;
    CollatzConjecture::currFillIndex++;
    CollatzConjecture::numberOfEntries++;

    if (n == 1)
    {
        return 0;
    }

    if (n % 2 == 0)
    {
        return CollatzConjecture::CollatzConjectureFillTable(n / 2);
    }
    else
    {
        return CollatzConjecture::CollatzConjectureFillTable(3 * n + 1);
    }
}

void CollatzConjecture::RenderCollatzConjecture()
{
    GLfloat initPosX = CollatzConjecture::axisAdjustment;
    GLfloat initPosY = CollatzConjecture::axisAdjustment;
    GLfloat posX[2];
    GLfloat posY[2];

    for (int collatzTableIdx = 1; collatzTableIdx <= CollatzConjecture::numberOfEntries; ++collatzTableIdx)
    {
        GLfloat point[] =
        {
           CollatzConjecture::axisAdjustment + (CollatzConjecture::axisXUnit * collatzTableIdx),
           CollatzConjecture::axisAdjustment + CollatzConjecture::collatzTable[collatzTableIdx] * CollatzConjecture::axisYUnit
        };

        glPointSize(3.0f);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_FLOAT, 0, point);
        glDrawArrays(GL_POINTS, 0, 1);

        CollatzConjecture::currentWriteIndex++;

        //do not print last line to x 0
        if (collatzTableIdx == CollatzConjecture::numberOfEntries) break;

        posX[0] = CollatzConjecture::axisAdjustment + (collatzTableIdx) * CollatzConjecture::axisXUnit;
        posY[0] = CollatzConjecture::axisAdjustment + CollatzConjecture::collatzTable[collatzTableIdx] * CollatzConjecture::axisYUnit;
        posX[1] = CollatzConjecture::axisAdjustment + (collatzTableIdx + 1) * CollatzConjecture::axisXUnit;
        posY[1] = CollatzConjecture::axisAdjustment + CollatzConjecture::collatzTable[collatzTableIdx + 1] * CollatzConjecture::axisYUnit;

        GLfloat line[] =
        {
            posX[0], posY[0],
            posX[1], posY[1]
        };

        glLineWidth(0.2f);
        glEnable(GL_LINE_SMOOTH);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_FLOAT, 0, line);
        glDrawArrays(GL_LINES, 0, 2);
    }
}

void CollatzConjecture::AdjustAxisUnits(bool& drawXAxisRuler, bool& drawYAxisRuler, GLfloat& xUnit, GLfloat &yUnit, int screenWidth, int screenHeight)
{
    unsigned largestYNumber = 0;
    for (int i = 0; i < CollatzConjecture::numberOfEntries; ++i)
    {
        if (CollatzConjecture::collatzTable[i] > largestYNumber)
        {
            largestYNumber = CollatzConjecture::collatzTable[i];
            std::cout << "largestNumber=" << largestYNumber << std::endl;
        }
    }

    if (largestYNumber > screenHeight / yUnit)
    {
        yUnit = ((screenHeight - screenHeight * 0.04) / (GLfloat)largestYNumber);
        if (yUnit < 3.0f) drawYAxisRuler = false;
    }

    if (CollatzConjecture::numberOfEntries > screenWidth / xUnit)
    {
        xUnit = (GLfloat)(screenWidth / CollatzConjecture::numberOfEntries);
        if (xUnit < 3.0f) drawYAxisRuler = false;
    }
}