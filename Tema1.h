#pragma once

#include <vector>

#include "components/simple_scene.h"
#include "lab_m1/Tema1/tema_camera.h"


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        struct ViewportArea
        {
            ViewportArea() : x(0), y(0), width(1), height(1) {}
            ViewportArea(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };
        ~Tema1();

        void Init() override;

    private:
        Mesh* CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices);
        //void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) override;
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        
        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        bool PointInTriangle(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c);
        bool InsideTrack(glm::vec3 car);
        bool SameSide(glm::vec3 p1, glm::vec3 p2, glm::vec3 a, glm::vec3 b);
        void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) override;
        void RenderScene();
        //void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) override;
    protected:
        Mesh* car;
        Mesh* track;
        Mesh* terrain;
        Mesh* enemy1;
        Mesh* tree1;
        Mesh* tree;
        float left;
        float right;
        float top;
        float bottom;
        glm::mat3 modelMatrix;
        float translateX = 0;
        float translateY = 0;
        float translateZ = 0;
        glm::vec3 carPos;
        glm::vec3 position = glm::vec3(0, 0, 0.20);
        bool renderCameraTarget;
        int fov;
        float orthoX, orthoY;
        float rotationAngle = 0;
        implemented::Camera* camera;
        implemented::Camera * cameraPlayer;
        implemented::Camera* cameraMiniMap;
        glm::mat4 projectionMatrix;
        std::vector<VertexFormat> verticesTrack;
        std::vector<VertexFormat>verticesTrackOpponent;
        std::vector<unsigned int> indicesTrack;
        std::vector<VertexFormat>verticesTerrain;
        std::vector<unsigned int> indicesTerrain;

        std::vector<VertexFormat>allVertices;
        
        float indexForX;
        float indexForZ;
        float posX;
        float posZ;
        float sensivityOY = 1.5f;
        float cameraSpeed = 10.0f;
        glm::vec3 nextPosition;
        ViewportArea miniViewportArea;
       // bool SameSide(glm::vec3 xCar, glm::vec3 zCar, glm::vec3 p1Track, glm::vec3 p2Track);
       
        //float traingleArea(glm::vec3 a, glm::vec3 b, glm::vec3 c);
    };
}
