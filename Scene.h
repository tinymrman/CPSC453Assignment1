/*
 * Scene.h
 *	Class for storing objects in a scene
 *  Created on: Sep 10, 2018
 *      Author: cb-ha
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <vector>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Geometry.h"

//Forward declaration of classes
//(note this is necessary because these are pointers and it allows the #include to appear in the .cpp file)
class RenderingEngine;

class Scene {
public:
	Scene(RenderingEngine* renderer);
	virtual ~Scene();

	//Send geometry to the renderer
	void displayScene();
	void changeToTriangleScene();
	void changeToCircleScene();
    
    void changeToNestedSquareScene();
    void changeToSpiralScene();
    void changeToSierpinskiTriangleScene();
    void changeToRandomSierpinskiScene();
    void changeToBarnsleyFernScene();
    void changeToHilbertCurveScene();

	void iterationUp();
	void iterationDown();

private:
    void drawAllSquares();
    void drawSpiral();
    void drawAllTriangles();
    void drawRandomSierpinskiTriangle();
    void drawBarnsleyFern();
    void drawHilbertCurve();
    
    void drawSquareFinishingAtStartingPointForNextIteration(std::vector<glm::vec3>& pointsForIteration,
        const glm::vec3& colourForIteration, Geometry& currentGeometry);
    std::vector<glm::vec3> getPointsForNextIteration(std::vector<glm::vec3>& pointsForIteration);
    glm::vec3 getMidpoint(glm::vec3& firstPoint, glm::vec3& secondPoint);
    std::vector<glm::vec3> drawSingleSquareWithNestedDiamond(std::vector<glm::vec3>& outerSquareVertices);
    void decrementNumberOfIterations();
    void hilbertA(glm::vec3& currentPosition, int currentLevel, float segmentLength, Geometry& hilbertCurve);
    void hilbertB(glm::vec3& currentPosition, int currentLevel, float segmentLength, Geometry& hilbertCurve);
    void hilbertC(glm::vec3& currentPosition, int currentLevel, float segmentLength, Geometry& hilbertCurve);
    void hilbertD(glm::vec3& currentPosition, int currentLevel, float segmentLength, Geometry& hilbertCurve);
    
private:
    int numberOfIterations;
    
	RenderingEngine* renderer;
	std::string sceneType;

	//list of objects in the scene
	std::vector<Geometry> objects;
};

#endif /* SCENE_H_ */
