#include "CollatzConjecture.h"

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

void CollatzConjecture::RenderCollatzConjecture(GLfloat* axisXUnit, GLfloat* axisYUnit, const GLfloat axisAdjustment)
{
    GLfloat initPosX = (GLfloat)axisAdjustment;
    GLfloat initPosY = (GLfloat)axisAdjustment;
    GLfloat posX[2];
    GLfloat posY[2];

    for (int i = 1; i <= CollatzConjecture::numberOfEntries; ++i)
    {
        GLfloat point[] =
        {
            axisAdjustment + (*axisXUnit * i),
            axisAdjustment + CollatzConjecture::collatzTable[i] * *axisYUnit
        };

        glPointSize(3.0f);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_FLOAT, 0, point);
        glDrawArrays(GL_POINTS, 0, 1);

        CollatzConjecture::currentWriteIndex++;

        //do not print last line
        if (i == CollatzConjecture::numberOfEntries) break;

        posX[0] = axisAdjustment + (i) * *axisXUnit;
        posY[0] = axisAdjustment + CollatzConjecture::collatzTable[i] * *axisYUnit;
        posX[1] = axisAdjustment + (i + 1) * *axisXUnit;
        posY[1] = axisAdjustment + CollatzConjecture::collatzTable[i + 1] * *axisYUnit;

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