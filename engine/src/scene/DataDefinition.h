#pragma once

#include "GMath.h"

namespace RenderingDEMO
{
	struct Vertex
	{
		GMath::Vector3 Position;
		GMath::Vector3 Normal;
		GMath::Vector2 TexCoord;
	};

	struct Mesh
	{
		std::vector<Vertex> Vertices;
		std::vector<unsigned int> Indices;
	};
}