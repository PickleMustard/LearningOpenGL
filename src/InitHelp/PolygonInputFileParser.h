#pragma once
#ifndef POLYGONINPUTFILEPARSER_H
#define POLYGONINPUTFILEPARSER_H

#include <string>
#include "../VectorMathAndObjects/Vector2D.h"

namespace pif{
   VectorSpace2D::Polygon2D readPolygonInputFile(const std::string& file_name);
}
#endif

