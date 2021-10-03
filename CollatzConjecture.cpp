#include "CollatzConjecture.h"

CollatzConjecture::CollatzConjecture(int collatzNumber, bool& drawXAxisRuler, bool& drawYAxisRuler, GLfloat& xUnit, GLfloat& yUnit, int screenWidth, int screenHeight, GLfloat asixAdj)
    : numberOfEntries(0), currFillIndex(1), currentWriteIndex(0), xUnit(xUnit), yUnit(yUnit), axisAdjustment(asixAdj)
{
    CollatzConjectureFillTable(collatzNumber);
    AdjustAxisUnits(drawXAxisRuler, drawYAxisRuler, xUnit, yUnit, screenWidth, screenHeight);
}

int CollatzConjecture::CollatzConjectureFillTable(int n)
{
    std::cout << "(" << CollatzConjecture::currFillIndex << ", " << n << ")" << std::endl;

    collatzVec.push_back(n);

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

void CollatzConjecture::RenderCollatzConjecture(GLfloat currentAxisXUnit, GLfloat currentAxisYUnit, GLfloat red, GLfloat green, GLfloat blue)
{
    GLfloat initPosX = CollatzConjecture::axisAdjustment;
    GLfloat initPosY = CollatzConjecture::axisAdjustment;
    GLfloat posX[2];
    GLfloat posY[2];

    glColor3f(red, green, blue);

    for (int collatzTableIdx = 1; collatzTableIdx <= CollatzConjecture::numberOfEntries; ++collatzTableIdx)
    {
        GLfloat point[] =
        {
           CollatzConjecture::axisAdjustment + (currentAxisXUnit * collatzTableIdx),
           CollatzConjecture::axisAdjustment + collatzVec.at(collatzTableIdx - 1) * currentAxisYUnit
        };

        glPointSize(3.0f);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_FLOAT, 0, point);
        glDrawArrays(GL_POINTS, 0, 1);

        CollatzConjecture::currentWriteIndex++;

        //do not print last line to x 0
        if (collatzTableIdx == CollatzConjecture::numberOfEntries) break;

        posX[0] = CollatzConjecture::axisAdjustment + (collatzTableIdx) *currentAxisXUnit;
        posY[0] = CollatzConjecture::axisAdjustment + collatzVec.at(collatzTableIdx - 1) * currentAxisYUnit;
        posX[1] = CollatzConjecture::axisAdjustment + (collatzTableIdx + 1) * currentAxisXUnit;
        posY[1] = CollatzConjecture::axisAdjustment + collatzVec.at(collatzTableIdx) * currentAxisYUnit;

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

    glColor3f(1.0f, 1.0f, 1.0f);
}

void CollatzConjecture::AdjustAxisUnits(bool& drawXAxisRuler, bool& drawYAxisRuler, GLfloat& xUnit, GLfloat &yUnit, int screenWidth, int screenHeight)
{
    int largestYNumber = 0;
    for (int i = 0; i < CollatzConjecture::numberOfEntries; ++i)
    {
        if (collatzVec.at(i) > largestYNumber)
        {
            largestYNumber = collatzVec.at(i);
            std::cout << "largestNumber=" << largestYNumber << std::endl;
        }
    }

    if (largestYNumber > screenHeight / yUnit)
    {
        CollatzConjecture::yUnit = ((GLfloat)(screenHeight - screenHeight * 0.04) / (GLfloat)largestYNumber);
        yUnit = CollatzConjecture::yUnit;
        if (yUnit < 3.0f) drawYAxisRuler = false;
    }

    if (CollatzConjecture::numberOfEntries > screenWidth / xUnit)
    {
        CollatzConjecture::xUnit = (GLfloat)(screenWidth / CollatzConjecture::numberOfEntries);
        xUnit = CollatzConjecture::xUnit;
        if (xUnit < 3.0f) drawYAxisRuler = false;
    }
}