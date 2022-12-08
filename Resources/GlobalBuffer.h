#pragma once

#include "stdafx.h"

class WorldBuffer : public ShaderBuffer
{
	struct WorldStruct
	{
		Matrix world;
	};

public:
	WorldBuffer() : ShaderBuffer(&data, sizeof(WorldStruct)) {}

	void SetWorld(const Matrix& world) { data.world = XMMatrixTranspose(world); }

private:
	WorldStruct data;
};

class ViewProjectionBuffer : public ShaderBuffer
{
	struct ViewProjStruct
	{
		Matrix view;
		Matrix projection;
	};

public:
	ViewProjectionBuffer() : ShaderBuffer(&data, sizeof(ViewProjStruct)) {}

	void SetView(const Matrix& view) { data.view = XMMatrixTranspose(view); }
	void SetProjection(const Matrix& projection) { data.projection = XMMatrixTranspose(projection); }

private:
	ViewProjStruct data;
};

class ColorBuffer : public ShaderBuffer
{
	struct ColorStruct
	{
		Color color;
	};

public:
	ColorBuffer() : ShaderBuffer(&data, sizeof(ColorStruct)) {}

	void SetColor(const Color& color) { data.color = color; }

private:
	ColorStruct data;
};