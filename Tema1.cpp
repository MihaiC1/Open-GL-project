#include "lab_m1/Tema1/Tema1.h"
#include "lab_m1/Tema1/transform3D.h"

//#include <string>

#include <vector>
#include <iostream>


#include "core/engine.h"
#include "utils/gl_utils.h"




using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}

//glm::vec3 triangleArea()

bool Tema1::SameSide(glm::vec3 p1, glm::vec3 p2, glm::vec3 a, glm::vec3 b) {
	glm::vec3 cp1 = glm::cross(b - a, p1 - a);
	glm::vec3 cp2 = glm::cross(b - a, p2 - a);
	if (glm::dot(cp1, cp2) >= 0) {
		return true;
	}
	else {
		return false;
	}

}
bool Tema1::PointInTriangle(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c) {
	if (SameSide(p, a, b, c) && SameSide(p, b, a, c) && SameSide(p, c, a, b)) {
		return true;
	}
	else {
		return false;
	}
}

bool Tema1::InsideTrack(glm::vec3 car) {
	for (int i = 0; i < track->indices.size(); i += 3) {

		if (PointInTriangle(car, track->vertices.at(track->indices.at(i)).position,
			track->vertices.at(track->indices.at(i + 1)).position,
			track->vertices.at(track->indices.at(i + 2)).position
		))
		{
			return true;
		}
	}
	return false;
}


void Tema1::Init() {

	right = 10.f;
	left = .01f;
	bottom = .01f;
	top = 10.f;
	renderCameraTarget = false;
	fov = 60;
	orthoX = 2.f;
	orthoY = 2.f;
	sensivityOY = 1.5f;
	cameraSpeed = 5.0f;




	glm::ivec2 resolution = window->GetResolution();
	miniViewportArea = ViewportArea(35, 35, resolution.x / 3.5f, resolution.y / 3.5f);

	cameraMiniMap = new implemented::Camera();
	cameraPlayer = new implemented::Camera();

	cameraPlayer->Set(glm::vec3(0, 1.5f, 3.f), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0));
	carPos = cameraPlayer->GetTargetPosition();
	cameraMiniMap->Set(carPos + glm::vec3(0, 5, 0), carPos, glm::vec3(0, 0, 1));
	//cout << carPos << "          " << cameraPlayer->position;

	vector<VertexFormat> verticesTree1{

		VertexFormat(glm::vec3(0, 0,  2), glm::vec3(0.f, 0.1f, 0.f), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(2, 0,  2), glm::vec3(0.f, 0.1f, 0.f), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(0, 2,  2), glm::vec3(0.f, 0.1f, 0.f), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(2, 2,  2), glm::vec3(0.f, 0.1f, 0.f), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0.f, 0.1f, 0.f), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(2, 0,  0), glm::vec3(0.f, 0.1f, 0.f), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(0, 2, 0), glm::vec3(0.f, 0.1f, 0.f), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(2, 2,  0), glm::vec3(0.f, 0.1f, 0.f), glm::vec3(0.2, 0.8, 0)),

	};

	vector<unsigned int> indicesTree1 = {
		0,1,2,
		1,3,2,
		2,3,7,
		2,7,6,
		1,7,3,
		1,5,7,
		6,7,4,
		7,5,4,
		0,4,1,
		1,4,5,
		2,6,4,
		0,2,4
	};

	vector<VertexFormat> verticesTree{

		VertexFormat(glm::vec3(0, 0,  0.5f), glm::vec3(0.5f, 0.35f, 0.05f), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(1, 0,  0.5f), glm::vec3(0.5f, 0.35f, 0.05f), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(0, 1,  0.5f), glm::vec3(0.5f, 0.35f, 0.05f), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(1, 1,  0.5f), glm::vec3(0.5f, 0.35f, 0.05f), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(0, 0, -0.5f), glm::vec3(0.5f, 0.35f, 0.05f), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(1, 0,  -0.5f), glm::vec3(0.5f, 0.35f, 0.05f), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(0, 1, -0.5f), glm::vec3(0.5f, 0.35f, 0.05f), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(1, 1,  -0.5f), glm::vec3(0.5f, 0.35f, 0.05f), glm::vec3(0.2, 0.8, 0)),

	};

	vector<unsigned int> indicesTree = {
		0,1,2,
		1,3,2,
		2,3,7,
		2,7,6,
		1,7,3,
		1,5,7,
		6,7,4,
		7,5,4,
		0,4,1,
		1,4,5,
		2,6,4,
		0,2,4
	};


	vector<VertexFormat> verticesCar{
		VertexFormat(glm::vec3(0, 0,  1), glm::vec3(1, 1, 1), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(1, 0,  1), glm::vec3(1, 1, 1), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(0, 1,  1), glm::vec3(1, 1, 1), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(1, 1,  1), glm::vec3(1, 1, 1), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(0, 0, -1), glm::vec3(1, 1, 1), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(1, 0,  -1), glm::vec3(1, 1, 1), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(0, 1, -1), glm::vec3(1, 1, 1), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(1, 1,  -1), glm::vec3(1, 1, 1), glm::vec3(0.2, 0.8, 0)),



	};

	vector<unsigned int> indicesCar = {
		0,1,2,
		1,3,2,
		2,3,7,
		2,7,6,
		1,7,3,
		1,5,7,
		6,7,4,
		7,5,4,
		0,4,1,
		1,4,5,
		2,6,4,
		0,2,4
	};

	verticesTrackOpponent = {
		VertexFormat(glm::vec3(-7.72, 0,  1.5), glm::vec3(1, 0, 1), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(-3.42, 0,  2.06), glm::vec3(1, 0, 1), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(1.79, 0,  1.33), glm::vec3(1, 0, 1), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(0.2, 0,  -0.98), glm::vec3(1, 0, 1), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(2.58, 0,  -3.21), glm::vec3(1, 0, 1), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(-4.83, 0,  -2.25), glm::vec3(1, 0, 1), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(-6.24, 0,  -3.32), glm::vec3(1, 0, 1), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(-7.95, 0,  -1.5), glm::vec3(1, 0, 1), glm::vec3(0.2, 0.8, 0))
	};

	verticesTrack =
	{
		//F1=0
		VertexFormat(glm::vec3(-7.98, 0,  1.72), glm::vec3(0,0,0), glm::vec3(0.2, 0.8, 0)),
		//J=1
		VertexFormat(glm::vec3(-3.4, 0,  2.33), glm::vec3(0,0,0), glm::vec3(0.2, 0.8, 0)),
		//L=2
		VertexFormat(glm::vec3(2.1, 0,  1.46), glm::vec3(0,0,0), glm::vec3(0.2, 0.8, 0)),
		//L1=3
		VertexFormat(glm::vec3(0.51, 0,  -0.99), glm::vec3(0,0,0), glm::vec3(0.2, 0.8, 0)),
		//M1=4
		VertexFormat(glm::vec3(3, 0, -3.27), glm::vec3(0,0,0), glm::vec3(0.2, 0.8, 0)),
		//P=5
		VertexFormat(glm::vec3(-2.22, 0, -5.32), glm::vec3(0,0,0), glm::vec3(0.2, 0.8, 0)),
		//P1=6
		VertexFormat(glm::vec3(-6.28, 0, -3.98), glm::vec3(0,0,0), glm::vec3(0.2, 0.8, 0)),
		//Q1=7
		VertexFormat(glm::vec3(-8.43, 0, -1.6), glm::vec3(0,0,0), glm::vec3(0.2, 0.8, 0)),





		//R = 8
		VertexFormat(glm::vec3(-7.23, 0,  0.96), glm::vec3(0,0,0), glm::vec3(0.2, 0.8, 0)),
		//R1 = 9
		VertexFormat(glm::vec3(-3.49, 0,  1.32), glm::vec3(0,0,0), glm::vec3(0.2, 0.8, 0)),
		//S1 = 10
		VertexFormat(glm::vec3(0.65, 0,  0.87), glm::vec3(0,0,0), glm::vec3(0.2, 0.8, 0)),
		//T1 = 11
		VertexFormat(glm::vec3(-0.55, 0,  -0.94), glm::vec3(0,0,0), glm::vec3(0.2, 0.8, 0)),
		//U1 = 12
		VertexFormat(glm::vec3(1.19, 0, -3.04), glm::vec3(0,0,0), glm::vec3(0.2, 0.8, 0)),
		//Q = 13
		VertexFormat(glm::vec3(-2.29, 0, -4.02), glm::vec3(0,0,0), glm::vec3(0.2, 0.8, 0)),
		//V1 = 14
		VertexFormat(glm::vec3(-6.22, 0, -2.85), glm::vec3(0,0,0), glm::vec3(0.2, 0.8, 0)),
		//W1 = 15
		VertexFormat(glm::vec3(-7.35, 0, -1.37), glm::vec3(0,0,0), glm::vec3(0.2, 0.8, 0)),

		VertexFormat(glm::vec3(-7.6, 0,  1.34), glm::vec3(1, 0, 1), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(-3.42, 0,  1.82), glm::vec3(1, 0, 1), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(1.36, 0,  1.18), glm::vec3(1, 0, 1), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(0, 0,  -1.21), glm::vec3(1, 0, 1), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(2.2, 0, 3.22), glm::vec3(1, 0, 1), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(-2.28, 0, -4.7), glm::vec3(1, 0, 1), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(-6.58, 0, -3.98), glm::vec3(1, 0, 1), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(-7.84, 0, -1.42), glm::vec3(1, 0, 1), glm::vec3(0.2, 0.8, 0))

	};

	indicesTrack =
	{
		1, 8, 0,
		1, 8, 9,
		9, 1, 2,
		9, 2, 10,
		10, 2, 3,
		10, 3, 11,
		3, 12, 11,
		3, 4, 12,
		12, 4, 5,
		12, 5, 13,
		5, 14, 13,
		5, 6, 14,
		14, 7, 15,
		14, 6, 7,
		15, 0, 8,
		15, 7, 0

	};

	verticesTerrain = {
		//A = 0
		VertexFormat(glm::vec3(-20, -0.1, 10), glm::vec3(0, 1, 0), glm::vec3(0.2, 0.8, 0)),
		//B = 1
		VertexFormat(glm::vec3(-20, -0.1, -15), glm::vec3(0, 1, 0), glm::vec3(0.2, 0.8, 0)),
		//C = 2
		VertexFormat(glm::vec3(15, -0.1, -15), glm::vec3(0, 1, 0), glm::vec3(0.2, 0.8, 0)),
		//D = 3
		VertexFormat(glm::vec3(15, -0.1, 10), glm::vec3(0, 1, 0), glm::vec3(0.2, 0.8, 0))
	};
	indicesTerrain = {
		0, 1, 2,
		1, 3, 2,
		3, 1, 0

	};

	allVertices = {
		//A = 0
		VertexFormat(glm::vec3(-20, -0.1, 10), glm::vec3(0, 1, 0), glm::vec3(0.2, 0.8, 0)),
		//B = 1
		VertexFormat(glm::vec3(-20, -0.1, -15), glm::vec3(0, 1, 0), glm::vec3(0.2, 0.8, 0)),
		//C = 2
		VertexFormat(glm::vec3(15, -0.1, -15), glm::vec3(0, 1, 0), glm::vec3(0.2, 0.8, 0)),
		//D = 3
		VertexFormat(glm::vec3(15, -0.1, 10), glm::vec3(0, 1, 0), glm::vec3(0.2, 0.8, 0)),
		//F1=0
		VertexFormat(glm::vec3(-7.98, 0,  1.72), glm::vec3(0,0,0), glm::vec3(0.2, 0.8, 0)),
		//J=1
		VertexFormat(glm::vec3(-3.4, 0,  2.33), glm::vec3(0,0,0), glm::vec3(0.2, 0.8, 0)),
		//L=2
		VertexFormat(glm::vec3(2.1, 0,  1.46), glm::vec3(0,0,0), glm::vec3(0.2, 0.8, 0)),
		//L1=3
		VertexFormat(glm::vec3(0.51, 0,  -0.99), glm::vec3(0,0,0), glm::vec3(0.2, 0.8, 0)),
		//M1=4
		VertexFormat(glm::vec3(3, 0, -3.27), glm::vec3(0,0,0), glm::vec3(0.2, 0.8, 0)),
		//P=5
		VertexFormat(glm::vec3(-2.22, 0, -5.32), glm::vec3(0,0,0), glm::vec3(0.2, 0.8, 0)),
		//P1=6
		VertexFormat(glm::vec3(-6.28, 0, -3.98), glm::vec3(0,0,0), glm::vec3(0.2, 0.8, 0)),
		//Q1=7
		VertexFormat(glm::vec3(-8.43, 0, -1.6), glm::vec3(0,0,0), glm::vec3(0.2, 0.8, 0)),

		//R = 8
		VertexFormat(glm::vec3(-7.23, 0,  0.96), glm::vec3(0,0,0), glm::vec3(0.2, 0.8, 0)),
		//R1 = 9
		VertexFormat(glm::vec3(-3.49, 0,  1.32), glm::vec3(0,0,0), glm::vec3(0.2, 0.8, 0)),
		//S1 = 10
		VertexFormat(glm::vec3(0.65, 0,  0.87), glm::vec3(0,0,0), glm::vec3(0.2, 0.8, 0)),
		//T1 = 11
		VertexFormat(glm::vec3(-0.55, 0,  -0.94), glm::vec3(0,0,0), glm::vec3(0.2, 0.8, 0)),
		//U1 = 12
		VertexFormat(glm::vec3(1.19, 0, -3.04), glm::vec3(0,0,0), glm::vec3(0.2, 0.8, 0)),
		//Q = 13
		VertexFormat(glm::vec3(-2.29, 0, -4.02), glm::vec3(0,0,0), glm::vec3(0.2, 0.8, 0)),
		//V1 = 14
		VertexFormat(glm::vec3(-6.22, 0, -2.85), glm::vec3(0,0,0), glm::vec3(0.2, 0.8, 0)),
		//W1 = 15
		VertexFormat(glm::vec3(-7.35, 0, -1.37), glm::vec3(0,0,0), glm::vec3(0.2, 0.8, 0)),

		VertexFormat(glm::vec3(-7.6, 0,  1.34), glm::vec3(1, 0, 1), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(-3.42, 0,  1.82), glm::vec3(1, 0, 1), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(1.36, 0,  1.18), glm::vec3(1, 0, 1), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(0, 0,  -1.21), glm::vec3(1, 0, 1), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(2.2, 0, 3.22), glm::vec3(1, 0, 1), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(-2.28, 0, -4.7), glm::vec3(1, 0, 1), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(-6.58, 0, -3.98), glm::vec3(1, 0, 1), glm::vec3(0.2, 0.8, 0)),
		VertexFormat(glm::vec3(-7.84, 0, -1.42), glm::vec3(1, 0, 1), glm::vec3(0.2, 0.8, 0))
	};

	car = CreateMesh("car", verticesCar, indicesCar);
	track = CreateMesh("track", verticesTrack, indicesTrack);
	terrain = CreateMesh("terrain", verticesTerrain, indicesTerrain);
	enemy1 = CreateMesh("car", verticesCar, indicesCar);
	tree = CreateMesh("tree", verticesTree, indicesTree);
	tree1 = CreateMesh("tree1", verticesTree1, indicesTree1);


}
Mesh* Tema1::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices)
{
	unsigned int VAO = 0;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	unsigned int VBO = 0;

	GLuint VBO_ID;
	glGenBuffers(1, &VBO_ID);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);


	unsigned int IBO = 0;

	GLuint IBO_ID;
	glGenBuffers(1, &IBO_ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);


	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));


	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));


	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));

	if (GetOpenGLError() == GL_INVALID_OPERATION)
	{
		cout << "\t[NOTE] : For students : DON'T PANIC! This error should go away when completing the tasks." << std::endl;
		cout << "\t[NOTE] : For developers : This happens because OpenGL core spec >=3.1 forbids null VAOs." << std::endl;
	}
	glBindVertexArray(0);

	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
	meshes[name]->vertices = vertices;
	meshes[name]->indices = indices;
	return meshes[name];

}
void Tema1::FrameStart()
{

	glClearColor(0, 0, 0.8, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();

	glViewport(0, 0, resolution.x, resolution.y);
}
//void Tema1::RenderScene() {
//
//
//    {
//       
//       
//    }
//
//    // TRAFFIC
//    {
//        glm::mat4 modelMatrix = glm::mat4(1);
//        if (traffic_index_1 >= traffic_route_1.size())
//            traffic_index_1 = 0;
//        glm::vec3 P1 = traffic_route_1[traffic_index_1].position;
//        glm::vec3 P2;
//        if (traffic_index_1 == traffic_route_1.size() - 1)
//            P2 = traffic_route_1[0].position;
//        else
//            P2 = traffic_route_1[traffic_index_1 + 1].position;
//        glm::vec3 D = P2 - P1;
//        float thisAngle = atan2(D.x, D.z);
//
//        modelMatrix = glm::translate(modelMatrix, P1 * 4.f + glm::vec3(0, 0.7f, 0));
//        modelMatrix = glm::rotate(modelMatrix, thisAngle, glm::vec3(0, 1, 0));
//        RenderMesh(meshes["traffic1"], shaders["LabShader"], modelMatrix);
//
//        modelMatrix = glm::mat4(1);
//        if (traffic_index_2 >= traffic_route_2.size())
//            traffic_index_2 = 0;
//        P1 = traffic_route_2[traffic_index_2].position;
//        if (traffic_index_2 == traffic_route_2.size() - 1)
//            P2 = traffic_route_2[0].position;
//        else
//            P2 = traffic_route_2[traffic_index_2 + 1].position;
//        D = P2 - P1;
//        thisAngle = atan2(D.x, D.z);
//
//        modelMatrix = glm::translate(modelMatrix, P1 * 4.f + glm::vec3(0, 0.7f, 0));
//        modelMatrix = glm::rotate(modelMatrix, thisAngle, glm::vec3(0, 1, 0));
//        RenderMesh(meshes["traffic2"], shaders["LabShader"], modelMatrix);
//    }
//
//    {
//        glm::mat4 modelMatrix = glm::mat4(1);
//        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.2f, 0));
//        modelMatrix = glm::scale(modelMatrix, glm::vec3(4.f, 0, 4.f));
//        RenderMesh(meshes["track"], shaders["LabShader"], modelMatrix);
//    }
//
//    for (int i = 0; i < treeVertices.size(); i++) {
//        glm::mat4 modelMatrix = glm::mat4(1);
//        modelMatrix = glm::translate(modelMatrix, glm::vec3(treeVertices[i].position.x * 4,
//            treeVertices[i].position.y * 4 + 1,
//            treeVertices[i].position.z * 4));
//        glm::mat4 bushMatrix = modelMatrix;
//        modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 6, 0.5));
//        RenderMesh(meshes["trunk"], shaders["VertexColor"], modelMatrix);
//        bushMatrix = glm::translate(bushMatrix, glm::vec3(0, 3, 0.5));
//        bushMatrix = glm::scale(bushMatrix, glm::vec3(4, 4, 2));
//        RenderMesh(meshes["treeBush"], shaders["LabShader"], bushMatrix);
//    }
//}
void Tema1::RenderScene() {
	glm::mat4 terrainMatrix = glm::mat4(1);
	glm::mat4 treeMatrix = glm::mat4(1);
	for (int i = 0; i < allVertices.size(); i++) {
		if (allVertices.at(i).color == glm::vec3(0, 1, 0)) {
			
			posX = allVertices.at(i).position.x;
			posZ = allVertices.at(i).position.z;
		
			terrainMatrix = glm::translate(terrainMatrix, glm::vec3(posX, 0, posZ));
			terrainMatrix = glm::scale(terrainMatrix, glm::vec3(0.25f));

			treeMatrix = glm::translate(treeMatrix, glm::vec3(posX - 0.1f, 0.2f, posZ - 0.3f));
			treeMatrix = glm::scale(treeMatrix, glm::vec3(0.25f));

			RenderMesh(meshes["tree"], shaders["VertexColor"], terrainMatrix);
			RenderMesh(meshes["tree1"], shaders["VertexColor"], treeMatrix);
		}
	}
	indexForX = (rand() % (allVertices.size() - 0)) + 0;
	indexForZ = (rand() % (allVertices.size() - 0)) + 0;

	//posX = track->vertices.at(track->indices.at(indexForX)).position.x + 1;
	//float posY = track->vertices.at(track->indices.at(i)).position.y + 1;
	//posZ = track->vertices.at(track->indices.at(indexForZ)).position.z + 1;




	{
		glm::mat4 trackMatrix = glm::mat4(1);
		trackMatrix = glm::translate(trackMatrix, glm::vec3(0, 0, 0));
		trackMatrix = glm::scale(trackMatrix, glm::vec3(1));
		RenderMesh(meshes["track"], shaders["VertexColor"], trackMatrix);
	}

	{
		glm::mat4 terrainMatrix = glm::mat4(1);
		terrainMatrix = glm::translate(terrainMatrix, glm::vec3(0, 0, 0));
		terrainMatrix = glm::scale(terrainMatrix, glm::vec3(1));
		RenderMesh(meshes["terrain"], shaders["VertexColor"], terrainMatrix);
	}

	{
		glm::mat4 carMatrix = glm::mat4(1);
		carMatrix = glm::translate(carMatrix, carPos);
		carMatrix = glm::scale(carMatrix, glm::vec3(0.15f));
		carMatrix = glm::rotate(carMatrix, rotationAngle, glm::vec3(0, 1, 0));
		RenderMesh(meshes["car"], shaders["VertexColor"], carMatrix);
	}

	{
		glm::mat4 carMatrix = glm::mat4(1);
		carMatrix = glm::translate(carMatrix, glm::vec3(0, 0, 3));
		carMatrix = glm::scale(carMatrix, glm::vec3(0.15f));
		//carMatrix = glm::rotate(carMatrix, rotationAngle, glm::vec3(0, 1, 0));
		RenderMesh(meshes["car"], shaders["VertexColor"], carMatrix);
	}
}

void Tema1::Update(float deltaTimeSeconds)
{

	glLineWidth(3);
	glPointSize(5);
	camera = cameraPlayer;
	projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, 0.01f, 200.0f);
	RenderScene();

	glClear(GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, miniViewportArea.width, miniViewportArea.height);
	camera = cameraMiniMap;
	projectionMatrix = glm::ortho(left, right, bottom, top, 200.f, 0.01f);
	RenderScene();

	camera = cameraPlayer;

	/*PointInTriangle(camera->GetTargetPosition(), verticesTrack[1].position, verticesTrack[16].position, verticesTrack[0].position);
	PointInTriangle(camera->GetTargetPosition(), verticesTrack[1].position, verticesTrack[16].position, verticesTrack[17].position);
	PointInTriangle(camera->GetTargetPosition(), verticesTrack[17].position, verticesTrack[1].position, verticesTrack[2].position);
	PointInTriangle(camera->GetTargetPosition(), verticesTrack[17].position, verticesTrack[2].position, verticesTrack[18].position);
	PointInTriangle(camera->GetTargetPosition(), verticesTrack[18].position, verticesTrack[2].position, verticesTrack[3].position);
	PointInTriangle(camera->GetTargetPosition(), verticesTrack[18].position, verticesTrack[3].position, verticesTrack[19].position);
	PointInTriangle(camera->GetTargetPosition(), verticesTrack[3].position, verticesTrack[20].position, verticesTrack[19].position);
	PointInTriangle(camera->GetTargetPosition(), verticesTrack[3].position, verticesTrack[4].position, verticesTrack[20].position);
	PointInTriangle(camera->GetTargetPosition(), verticesTrack[20].position, verticesTrack[4].position, verticesTrack[5].position);
	PointInTriangle(camera->GetTargetPosition(), verticesTrack[20].position, verticesTrack[5].position, verticesTrack[21].position);
	PointInTriangle(camera->GetTargetPosition(), verticesTrack[5].position, verticesTrack[22].position, verticesTrack[21].position);
	PointInTriangle(camera->GetTargetPosition(), verticesTrack[5].position, verticesTrack[6].position, verticesTrack[22].position);
	PointInTriangle(camera->GetTargetPosition(), verticesTrack[22].position, verticesTrack[7].position, verticesTrack[23].position);
	PointInTriangle(camera->GetTargetPosition(), verticesTrack[22].position, verticesTrack[6].position, verticesTrack[7].position);
	PointInTriangle(camera->GetTargetPosition(), verticesTrack[23].position, verticesTrack[0].position, verticesTrack[16].position);
	PointInTriangle(camera->GetTargetPosition(), verticesTrack[23].position, verticesTrack[7].position, verticesTrack[0].position);*/



}
void Tema1::FrameEnd()
{
	//DrawCoordinateSystem();
}

void Tema1::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	// Render an object using the specified shader and the specified position
	shader->Use();
	int location = glGetUniformLocation(shader->GetProgramID(), "Model");

	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	int viewLocation = glGetUniformLocation(shader->GetProgramID(), "View");

	glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));

	int projLocation = glGetUniformLocation(shader->GetProgramID(), "Projection");

	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));



	mesh->Render();
}




void Tema1::OnInputUpdate(float deltaTime, int mods)
{


	if (window->KeyHold(GLFW_KEY_W)) {

		glm::vec3 nextPosition = cameraPlayer->GetNextPosOfTarget(cameraSpeed * deltaTime);
		//cout << nextPosition;
		// TODO(student): Translate the camera forward

		if (InsideTrack(nextPosition)) {
			cameraPlayer->MoveForward(cameraSpeed * deltaTime);

			carPos = cameraPlayer->GetTargetPosition();
			//cout << carPos;
			glm::vec3 carPos1 = cameraPlayer->GetTargetPosition();
			cameraMiniMap->Set(carPos1 + glm::vec3(0, 5, 0), carPos1, glm::vec3(0, 0, 1));
			//cout << carPos << "          " << cameraPlayer->position;

		}
		else {
			cout << "OUTSIDE";
		}


	}

	if (window->KeyHold(GLFW_KEY_A)) {
		// TODO(student): Translate the camera to the left
		cameraPlayer->RotateThirdPerson_OY(sensivityOY * deltaTime);
		rotationAngle += sensivityOY * deltaTime;
		//carPos = cameraPlayer->GetTargetPosition();

	}

	if (window->KeyHold(GLFW_KEY_S)) {

		glm::vec3 nextPosition = cameraPlayer->GetNextPosOfTarget(-cameraSpeed * deltaTime);
		if (InsideTrack(nextPosition)) {
			cameraPlayer->MoveForward(-cameraSpeed * deltaTime);
			carPos = cameraPlayer->GetTargetPosition();
			glm::vec3 carPos1 = cameraPlayer->GetTargetPosition();
			cameraMiniMap->Set(carPos1 + glm::vec3(0, 5, 0), carPos1, glm::vec3(0, 0, 1));
			//cout << carPos << "          " << cameraPlayer->position;

		}
		else {
			cout << "OUTSIDE";
		}

	}

	if (window->KeyHold(GLFW_KEY_D)) {

		cameraPlayer->RotateThirdPerson_OY(-sensivityOY * deltaTime);
		rotationAngle += -sensivityOY * deltaTime;
	}


}


void Tema1::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_T)
	{
		renderCameraTarget = !renderCameraTarget;
	}
	if (key == (GLFW_KEY_O)) {
		projectionMatrix = glm::ortho(-orthoX, orthoX, -orthoY, orthoY, 0.01f, 200.f);
	}

	if (key == (GLFW_KEY_P)) {
		projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, 0.01f, 200.0f);
	}
}


void Tema1::OnKeyRelease(int key, int mods)
{
	// Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{

}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// Add mouse button press event
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
