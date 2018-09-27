/*
 * Scene.cpp
 *
 *  Created on: Sep 10, 2018
 *  Author: John Hall
 */

#include "Scene.h"

#include "RenderingEngine.h"

//**Must include glad and GLFW in this order or it breaks**
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace
{
    const glm::vec3 TEAL_COLOUR(0.25f, 0.75f, 0.75f);
    const glm::vec3 GOLD_COLOUR(0.7f, 0.7f, 0.5f);
    const glm::vec3 BLUE_COLOUR(0.25f, 0.0f, 0.75f);
    const glm::vec3 RED_COLOUR(0.5f, 0.25f, 0.1f);
}

Scene::Scene(RenderingEngine* renderer)
: numberOfIterations(1), renderer(renderer)
{
	changeToNestedSquareScene();
}

Scene::~Scene()
{
}

//Note this method was adapted from http://www.latenightpc.com/blog/archives/2007/11/13/the-hilbert-curve-in-javal-lua-and-c
void Scene::changeToHilbertCurveScene()
{
    sceneType = "HILBERT_CURVE_SCENE";
    numberOfIterations = 1;
    
    drawHilbertCurve();
}

void Scene::drawHilbertCurve()
{
    objects.clear();
    Geometry hilbertCurve;
    hilbertCurve.drawMode = GL_LINE_STRIP;
    float segmentLength = 1.0f / (2.0f * static_cast<float>(numberOfIterations));
    glm::vec3 startingPoint(-1.0f, -1.0f, 1.0);
    hilbertA(startingPoint, numberOfIterations, segmentLength, hilbertCurve);
    
    RenderingEngine::assignBuffers(hilbertCurve);
    RenderingEngine::setBufferData(hilbertCurve);
    objects.push_back(hilbertCurve);
}

void Scene::hilbertA(glm::vec3& currentPosition, int currentLevel, float segmentLength, Geometry& hilbertCurve)
{
    if (currentLevel > 0)
    {
        hilbertB(currentPosition, currentLevel-1, segmentLength, hilbertCurve);
        
        currentPosition = glm::vec3(currentPosition[0], currentPosition[1] + segmentLength, 1.0);
        hilbertCurve.verts.push_back(currentPosition);
        hilbertCurve.colors.push_back(RED_COLOUR);
        
        hilbertA(currentPosition, currentLevel-1, segmentLength, hilbertCurve);
        
        currentPosition = glm::vec3(currentPosition[0] + segmentLength, currentPosition[1], 1.0);
        hilbertCurve.verts.push_back(currentPosition);
        hilbertCurve.colors.push_back(RED_COLOUR);
        
        hilbertA(currentPosition, currentLevel-1, segmentLength, hilbertCurve);
        
        currentPosition = glm::vec3(currentPosition[0], currentPosition[1] - segmentLength, 1.0);
        hilbertCurve.verts.push_back(currentPosition);
        hilbertCurve.colors.push_back(RED_COLOUR);
        
        hilbertC(currentPosition, currentLevel-1, segmentLength, hilbertCurve);
    }
}

void Scene::hilbertB(glm::vec3& currentPosition, int currentLevel, float segmentLength, Geometry& hilbertCurve)
{
    if (currentLevel > 0)
    {
        hilbertA(currentPosition, currentLevel-1, segmentLength, hilbertCurve);
        
        currentPosition = glm::vec3(currentPosition[0] + segmentLength, currentPosition[1], 1.0);
        hilbertCurve.verts.push_back(currentPosition);
        hilbertCurve.colors.push_back(RED_COLOUR);
        
        hilbertB(currentPosition, currentLevel-1, segmentLength, hilbertCurve);
        
        currentPosition = glm::vec3(currentPosition[0], currentPosition[1] + segmentLength, 1.0);
        hilbertCurve.verts.push_back(currentPosition);
        hilbertCurve.colors.push_back(RED_COLOUR);
        
        hilbertB(currentPosition, currentLevel-1, segmentLength, hilbertCurve);
        
        currentPosition = glm::vec3(currentPosition[0] - segmentLength, currentPosition[1], 1.0);
        hilbertCurve.verts.push_back(currentPosition);
        hilbertCurve.colors.push_back(RED_COLOUR);
        
        hilbertD(currentPosition, currentLevel-1, segmentLength, hilbertCurve);
    }
}

void Scene::hilbertC(glm::vec3& currentPosition, int currentLevel, float segmentLength, Geometry& hilbertCurve)
{
    if (currentLevel > 0)
    {
        hilbertD(currentPosition, currentLevel-1, segmentLength, hilbertCurve);
        
        currentPosition = glm::vec3(currentPosition[0] - segmentLength, currentPosition[1], 1.0);
        hilbertCurve.verts.push_back(currentPosition);
        hilbertCurve.colors.push_back(RED_COLOUR);
        
        hilbertC(currentPosition, currentLevel-1, segmentLength, hilbertCurve);
        
        currentPosition = glm::vec3(currentPosition[0], currentPosition[1] - segmentLength, 1.0);
        hilbertCurve.verts.push_back(currentPosition);
        hilbertCurve.colors.push_back(RED_COLOUR);
        
        hilbertC(currentPosition, currentLevel-1, segmentLength, hilbertCurve);
        
        currentPosition = glm::vec3(currentPosition[0] + segmentLength, currentPosition[1], 1.0);
        hilbertCurve.verts.push_back(currentPosition);
        hilbertCurve.colors.push_back(RED_COLOUR);
        
        hilbertA(currentPosition, currentLevel-1, segmentLength, hilbertCurve);
    }
}

void Scene::hilbertD(glm::vec3& currentPosition, int currentLevel, float segmentLength, Geometry& hilbertCurve)
{
    if (currentLevel > 0)
    {
        hilbertC(currentPosition, currentLevel-1, segmentLength, hilbertCurve);
        
        currentPosition = glm::vec3(currentPosition[0], currentPosition[1] - segmentLength, 1.0);
        hilbertCurve.verts.push_back(currentPosition);
        hilbertCurve.colors.push_back(RED_COLOUR);
        
        hilbertD(currentPosition, currentLevel-1, segmentLength, hilbertCurve);
        
        currentPosition = glm::vec3(currentPosition[0] - segmentLength, currentPosition[1], 1.0);
        hilbertCurve.verts.push_back(currentPosition);
        hilbertCurve.colors.push_back(RED_COLOUR);
        
        hilbertD(currentPosition, currentLevel-1, segmentLength, hilbertCurve);
        
        currentPosition = glm::vec3(currentPosition[0], currentPosition[1] + segmentLength, 1.0);
        hilbertCurve.verts.push_back(currentPosition);
        hilbertCurve.colors.push_back(RED_COLOUR);
    
        hilbertB(currentPosition, currentLevel-1, segmentLength, hilbertCurve);
    }
}

void Scene::changeToBarnsleyFernScene()
{
    sceneType = "BARNSLEY_FERN_SCENE";
    numberOfIterations = 1;
    drawBarnsleyFern();
}

//Note that this method was adapted from https://people.sc.fsu.edu/~jburkardt/cpp_src/fern_opengl/fern.cpp
void Scene::drawBarnsleyFern()
{
    objects.clear();
    Geometry barnsleyFern;
    barnsleyFern.drawMode = GL_POINTS;
    
    double probabilityThresholds[4] = {0.85, 0.92, 0.99};
    int pointsPerIteration = 1e6;
    
    float currentX = static_cast<float>(drand48());
    float currentY = static_cast<float>(drand48());
    
    for (int i = 0; i < pointsPerIteration * numberOfIterations; i++)
    {
        double randomPercentage = drand48();
      
        if(randomPercentage < probabilityThresholds[0])
        {
            currentX =   0.85f * currentX + 0.04f * currentY + 0.0f;
            currentY = -0.04f * currentX + 0.85f * currentY + 1.6f;
        }
        else if(randomPercentage < probabilityThresholds[1])
        {
            currentX = 0.20 * currentX - 0.26 * currentY + 0.0;
            currentY = 0.23 * currentX + 0.22 * currentY + 1.6;
        }
        else if(randomPercentage < probabilityThresholds[2])
        {
            currentX = -0.15 * currentX + 0.28 * currentY + 0.0;
            currentY = 0.26 * currentX + 0.24 * currentY + 0.44;
        }
        else
        {
            currentX = 0.00 * currentX + 0.00 * currentY + 0.0;
            currentY = 0.00 * currentX + 0.16 * currentY + 0.0;
        }
        
        barnsleyFern.verts.push_back(glm::vec3(currentX-0.5f, currentY-1.5f, 1.0f));
        barnsleyFern.colors.push_back(GOLD_COLOUR);
    }

    RenderingEngine::assignBuffers(barnsleyFern);
    RenderingEngine::setBufferData(barnsleyFern);
    objects.push_back(barnsleyFern);
}

void Scene::changeToSierpinskiTriangleScene()
{
    sceneType = "SIERPINSKI_TRIANGLE_SCENE";
    numberOfIterations = 1;
    
    drawAllTriangles();
}
    
void Scene::drawAllTriangles()
{
    objects.clear();
    std::vector<glm::vec3> allTrianglesForIteration;

    allTrianglesForIteration.push_back(glm::vec3(-0.9f, -0.9f, 1.0f));
    allTrianglesForIteration.push_back(glm::vec3(0.9f, -0.9f, 1.0f));
    allTrianglesForIteration.push_back(glm::vec3(0.0f, static_cast<float>(sqrt(1.8*1.8-0.9*0.9)/2.0), 1.0f));

    for(int currentIteration = 1; currentIteration < numberOfIterations; currentIteration++)
    {
        std::vector<glm::vec3> allTrianglesForNextIteration;
        for(int i = 0; i < allTrianglesForIteration.size(); i += 3)
        {
            glm::vec3 bottomMidpoint = getMidpoint(allTrianglesForIteration[i], allTrianglesForIteration[i+1]);
            glm::vec3 leftMidpoint = getMidpoint(allTrianglesForIteration[i], allTrianglesForIteration[i+2]);
            glm::vec3 rightMidpoint = getMidpoint(allTrianglesForIteration[i+1], allTrianglesForIteration[i+2]);
            allTrianglesForNextIteration.push_back(allTrianglesForIteration[i]);
            allTrianglesForNextIteration.push_back(bottomMidpoint);
            allTrianglesForNextIteration.push_back(leftMidpoint);
            allTrianglesForNextIteration.push_back(bottomMidpoint);
            allTrianglesForNextIteration.push_back(allTrianglesForIteration[i+1]);
            allTrianglesForNextIteration.push_back(rightMidpoint);
            allTrianglesForNextIteration.push_back(leftMidpoint);
            allTrianglesForNextIteration.push_back(rightMidpoint);
            allTrianglesForNextIteration.push_back(allTrianglesForIteration[i+2]);
        }
        allTrianglesForIteration = allTrianglesForNextIteration;
    }
    
    float currentRed = 1.0f;
    float currentGreen = 1.0f;
    float currentBlue = 1.0f;
    
    for(int i = 0; i < allTrianglesForIteration.size(); i += 3)
    {
        Geometry singleTriangle;
        singleTriangle.drawMode = GL_TRIANGLES;

        singleTriangle.verts.push_back(allTrianglesForIteration[i]);
        singleTriangle.verts.push_back(allTrianglesForIteration[i+1]);
        singleTriangle.verts.push_back(allTrianglesForIteration[i+2]);
        
        if(i % 9 == 0)
        {
            currentRed -= (9.0f/static_cast<float>(allTrianglesForIteration.size()));
        }
        else if(i % 9 == 3)
        {
            currentGreen -= (9.0f/static_cast<float>(allTrianglesForIteration.size()));
        }
        else if(i % 9 == 6)
        {
            currentBlue -= (9.0f/static_cast<float>(allTrianglesForIteration.size()));
        }
        
        singleTriangle.colors.push_back(glm::vec3(currentRed, currentGreen, currentBlue));
        singleTriangle.colors.push_back(glm::vec3(currentRed, currentGreen, currentBlue));
        singleTriangle.colors.push_back(glm::vec3(currentRed, currentGreen, currentBlue));

        RenderingEngine::assignBuffers(singleTriangle);
        RenderingEngine::setBufferData(singleTriangle);
        objects.push_back(singleTriangle);
    }
}

void Scene::changeToRandomSierpinskiScene()
{
    sceneType = "RANDOM_SIERPINSKI_SCENE";
    numberOfIterations = 1;
    drawRandomSierpinskiTriangle();
}

void Scene::drawRandomSierpinskiTriangle()
{
    objects.clear();
    int pointsPerIteration = 250;
    
    std::vector<glm::vec3> outerTriangle;
    outerTriangle.push_back(glm::vec3(-0.9f, -0.9f, 1.0f));
    outerTriangle.push_back(glm::vec3(0.9f, -0.9f, 1.0f));
    outerTriangle.push_back(glm::vec3(0.0f, static_cast<float>(sqrt(1.8*1.8-0.9*0.9)/2.0), 1.0f));
    
    Geometry randomSierpinski;
    
    glm::vec3 currentPoint = outerTriangle[0];
    randomSierpinski.verts.push_back(currentPoint);
    randomSierpinski.colors.push_back(TEAL_COLOUR);
    for(int i = 0; i < pointsPerIteration * numberOfIterations; i++)
    {
        glm::vec3 nextPoint = getMidpoint(currentPoint, outerTriangle[std::rand()%3]);
        randomSierpinski.verts.push_back(nextPoint);
        randomSierpinski.colors.push_back(TEAL_COLOUR);
        currentPoint = nextPoint;
    }
    
    randomSierpinski.drawMode = GL_POINTS;
    
    RenderingEngine::assignBuffers(randomSierpinski);
    RenderingEngine::setBufferData(randomSierpinski);
    objects.push_back(randomSierpinski);
}

void Scene::changeToSpiralScene()
{
    sceneType = "SPIRAL_SCENE";
    numberOfIterations = 1;
    
    drawSpiral();
}

void Scene::drawSpiral()
{
    objects.clear();
    Geometry spiral;
    int segmentsPerIteration = 50;
    float du = 1.0f / segmentsPerIteration;
    for (float u = 0.0f; u < static_cast<float>(numberOfIterations); u += du)
    {
        spiral.verts.push_back(glm::vec3((u/numberOfIterations)*cos(2.0f*static_cast<float>(M_PI)*u),
                                         (u/numberOfIterations)*sin(2.0f*static_cast<float>(M_PI)*u),
                                         1.0));
        spiral.colors.push_back(glm::vec3(BLUE_COLOUR[0] + (RED_COLOUR[0] - BLUE_COLOUR[0])*(u/static_cast<float>(numberOfIterations)),
                                          BLUE_COLOUR[1] + (RED_COLOUR[1] - BLUE_COLOUR[1])*(u/static_cast<float>(numberOfIterations)),
                                          BLUE_COLOUR[2] + (RED_COLOUR[2] - BLUE_COLOUR[2])*(u/static_cast<float>(numberOfIterations))));
    }
    
    spiral.drawMode = GL_LINE_STRIP;
    
    RenderingEngine::assignBuffers(spiral);
    RenderingEngine::setBufferData(spiral);
    objects.push_back(spiral);
}

void Scene::changeToNestedSquareScene()
{
    sceneType = "NESTED_SQUARE_SCENE";
    numberOfIterations = 1;
    
    drawAllSquares();
}

void Scene::drawAllSquares()
{
    objects.clear();
    std::vector<glm::vec3> outerSquare;
    
    outerSquare.push_back(glm::vec3(-0.9f, 0.9f, 1.0f));
    outerSquare.push_back(glm::vec3(0.9f, 0.9f, 1.0f));
    outerSquare.push_back(glm::vec3(0.9f, -0.9f, 1.0f));
    outerSquare.push_back(glm::vec3(-0.9f, -0.9f, 1.0f));
    
    for(int i = 0; i < numberOfIterations; i++)
    {
        outerSquare = drawSingleSquareWithNestedDiamond(outerSquare);
    }
}

std::vector<glm::vec3> Scene::drawSingleSquareWithNestedDiamond(
    std::vector<glm::vec3>& outerSquareVertices)
{
    Geometry nestedSquares;
    nestedSquares.drawMode = GL_LINE_STRIP;
    drawSquareFinishingAtStartingPointForNextIteration(outerSquareVertices, TEAL_COLOUR,
        nestedSquares);
    std::vector<glm::vec3> innerDiamondVertices = getPointsForNextIteration(outerSquareVertices);
    drawSquareFinishingAtStartingPointForNextIteration(innerDiamondVertices,
        GOLD_COLOUR, nestedSquares);
    RenderingEngine::assignBuffers(nestedSquares);
    RenderingEngine::setBufferData(nestedSquares);
    objects.push_back(nestedSquares);
    return getPointsForNextIteration(innerDiamondVertices);
}

void Scene::drawSquareFinishingAtStartingPointForNextIteration(
    std::vector<glm::vec3>& pointsForIteration,
    const glm::vec3& colourForIteration, Geometry& currentGeometry)
{
    for(glm::vec3 point: pointsForIteration)
    {
        currentGeometry.verts.push_back(point);
        currentGeometry.colors.push_back(colourForIteration);
    }
    
    currentGeometry.verts.push_back(pointsForIteration[0]);
    currentGeometry.colors.push_back(colourForIteration);
    
    glm::vec3 startingPointForNextIteration = getMidpoint(pointsForIteration[0], pointsForIteration[1]);
    currentGeometry.verts.push_back(startingPointForNextIteration);
    currentGeometry.colors.push_back(colourForIteration);
}

std::vector<glm::vec3> Scene::getPointsForNextIteration(std::vector<glm::vec3>& pointsForIteration)
{
    std::vector<glm::vec3> midpoints;
    for (int i = 0; i < 3; i++)
    {
        midpoints.push_back(getMidpoint(pointsForIteration[i], pointsForIteration[i+1]));
    }
    midpoints.push_back(getMidpoint(pointsForIteration[3], pointsForIteration[0]));
    return midpoints;
}

glm::vec3 Scene::getMidpoint(glm::vec3& firstPoint, glm::vec3& secondPoint)
{
    float x1 = firstPoint[0];
    float y1 = firstPoint[1];

    float x2 = secondPoint[0];
    float y2 = secondPoint[1];
    
    return glm::vec3((x1+x2)/2.0f,(y1+y2)/2.0f, 1.0f);
}

void Scene::iterationUp()
{
    if (sceneType == "NESTED_SQUARE_SCENE")
    {
        numberOfIterations++;
        drawAllSquares();
    }
    else if (sceneType == "SPIRAL_SCENE")
    {
        numberOfIterations++;
        drawSpiral();
    }
    else if (sceneType == "SIERPINSKI_TRIANGLE_SCENE")
    {
        numberOfIterations++;
        drawAllTriangles();
    }
    else if (sceneType == "RANDOM_SIERPINSKI_SCENE")
    {
        numberOfIterations++;
        drawRandomSierpinskiTriangle();
    }
    if (sceneType == "BARNSLEY_FERN_SCENE")
    {
        numberOfIterations++;
        drawBarnsleyFern();
    }
    if (sceneType == "HILBERT_CURVE_SCENE")
    {
        numberOfIterations++;
        drawHilbertCurve();
    }
}

void Scene::iterationDown()
{
    if (sceneType == "NESTED_SQUARE_SCENE")
    {
        decrementNumberOfIterations();
        drawAllSquares();
    }
    else if (sceneType == "SPIRAL_SCENE")
    {
        decrementNumberOfIterations();
        drawSpiral();
    }
    else if (sceneType == "SIERPINSKI_TRIANGLE_SCENE")
    {
        decrementNumberOfIterations();
        drawAllTriangles();
    }
    else if (sceneType == "RANDOM_SIERPINSKI_SCENE")
    {
        decrementNumberOfIterations();
        drawRandomSierpinskiTriangle();
    }
    else if (sceneType == "BARNSLEY_FERN_SCENE")
    {
        decrementNumberOfIterations();
        drawBarnsleyFern();
    }
    else if (sceneType == "HILBERT_CURVE_SCENE")
    {
        decrementNumberOfIterations();
        drawHilbertCurve();
    }
}

void Scene::decrementNumberOfIterations()
{
    numberOfIterations--;
    if(!numberOfIterations) {numberOfIterations = 1;}
}

void Scene::displayScene()
{
	renderer->RenderScene(objects);
}

