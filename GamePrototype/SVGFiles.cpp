#include "pch.h"
#include "SVGFiles.h"
#include "SVGParser.h"
#include "iostream"
#include "Matrix2x3.h"
#include "utils.h"


SVGFiles::SVGFiles()

{
	if (!SVGParser::GetVerticesFromSvgFile("Map3.svg", m_VerticesMain))
	{
		std::cout << "ERROR LOADING SVGFILE";

	}
	
}

std::vector<std::vector<Point2f>> SVGFiles::GetVertices() const
{
	return m_VerticesMain;
}

void SVGFiles::Draw()
{
	utils::SetColor(Color4f(0.f, 0.f, 1.f, 1.f));
	for (int idx{}; idx < m_VerticesMain.size(); ++idx)
	{
		for (int idx2{}; idx2 < m_VerticesMain[idx].size(); ++idx2)
		{
			utils::DrawPoint(m_VerticesMain[idx][idx2], 4.f);
		}
	}
}
void SVGFiles::TransformPointsLeft()
{
	Matrix2x3 rotationMat{};
	Matrix2x3 transformMat{};
	Matrix2x3 translateMat{};
	translateMat.SetAsTranslate(533.f, 0);
	rotationMat.SetAsRotate(90);
	transformMat = translateMat * rotationMat;
	for (int idx{}; idx < m_VerticesMain.size(); ++idx)
	{
		m_VerticesMain[idx] = transformMat.Transform(m_VerticesMain[idx]);
	}
}

void SVGFiles::TransformpointsRight()
{
	Matrix2x3 rotationMat{};
	Matrix2x3 transformMat{};
	Matrix2x3 translateMat{};
	translateMat.SetAsTranslate(0, 534.f);
	rotationMat.SetAsRotate(-90);
	transformMat = translateMat * rotationMat;
	for (int idx{}; idx < m_VerticesMain.size(); ++idx)
	{
		m_VerticesMain[idx] = transformMat.Transform(m_VerticesMain[idx]);
	}
}

