#pragma once
#include "vector"
class SVGFiles
{
public:
	explicit SVGFiles();
	std::vector<std::vector<Point2f>> GetVertices()const;
	void Draw();
	void TransformPoints();

private:
	std::vector<std::vector<Point2f>> m_VerticesMain;
	std::vector<std::vector<Point2f>> m_VerticesPlatform1;
	std::vector<std::vector<Point2f>> m_VerticesPlatform2;
	std::vector<std::vector<Point2f>> m_VerticesPlatform3;
	std::vector<std::vector<Point2f>> m_VerticesPlatform4;
	

};

