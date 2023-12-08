#include "pch.h"
#include "Mesh.h"
#include "GeometryHelper.h"

Mesh::Mesh() : Super(ResourceType::Mesh)
{

}

Mesh::~Mesh()
{

}

void Mesh::CreateQuad()
{
    _geometry = make_shared<Geometry<VertexTextureNormalTangentData>>();
    GeometryHelper::CreateQuad(_geometry);
    CreateBuffers();
}

void Mesh::CreateCube()
{
    _geometry = make_shared<Geometry<VertexTextureNormalTangentData>>();
    GeometryHelper::CreateCube(_geometry);
    CreateBuffers();
}

void Mesh::CreateGrid(int32 sizeX, int32 sizeZ)
{
    _geometry = make_shared<Geometry<VertexTextureNormalTangentData>>();
    GeometryHelper::CreateGrid(_geometry, sizeX, sizeZ);
    CreateBuffers();
}

void Mesh::CreateSphere()
{
    _geometry = make_shared<Geometry<VertexTextureNormalTangentData>>();
    GeometryHelper::CreateSphere(_geometry);
    CreateBuffers();
}

void Mesh::CreateBuffers()
{
    _vertexBuffer = make_shared<VertexBuffer>();
    _vertexBuffer->Create(_geometry->GetVertices());
    _indexBuffer = make_shared<IndexBuffer>();
    _indexBuffer->Create(_geometry->GetIndices());
}

// ========================================================================================================

SimpleMesh::SimpleMesh() : Super(ResourceType::Mesh)
{
}

SimpleMesh::~SimpleMesh()
{
}

void SimpleMesh::CreateCube()
{
    GeometryHelper::CreateCube(_geometry, Color(1.f, 0.3f, 0.3f, 0.8f));
    CreateBuffers();
}

void SimpleMesh::CreateBuffers()
{
    _vertexBuffer = make_shared<VertexBuffer>();
    _vertexBuffer->Create(_geometry.GetVertices());
    _indexBuffer = make_shared<IndexBuffer>();
    _indexBuffer->Create(_geometry.GetIndices());
}