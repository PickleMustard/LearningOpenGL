#include "PolygonInputFileParser.h"
#include "../VectorMathAndObjects/Vector2D.h"
#include <string>
#include <fstream>

VectorSpace2D::Polygon2D pif::readPolygonInputFile(const std::string &file_name){
    int num_of_vertices, pos;
    VectorSpace2D::Polygon2D constructedPolygon {};
    std::ifstream input_file(file_name, std::ifstream::in);
    std::string input_string;
    std::vector<VectorSpace2D::Pointf2D> point_list;
    std::vector<std::string> parsed_input_string {};
    char* pEnd;

    std::getline(input_file, input_string);
    const char& nov = input_string.at(0);
    num_of_vertices = std::atoi(&nov);
    constructedPolygon.num_of_points = num_of_vertices;
    while(std::getline(input_file, input_string)){
        pos = 0;
        parsed_input_string.erase(parsed_input_string.begin(), parsed_input_string.end());

        while(pos < input_string.size()) {
            pos = input_string.find("|");
            std::string s = input_string.substr(0, pos);
            parsed_input_string.push_back(input_string.substr(0, pos));
            if(input_string.size()) {
                input_string.erase(0, pos+1);
            }
        }
        parsed_input_string.push_back(input_string);

        point_list.push_back({std::strtof(parsed_input_string[0].c_str(), &pEnd),
                std::strtof(parsed_input_string[1].c_str(), &pEnd),
                std::strtof(parsed_input_string[2].c_str(), &pEnd)});

    }

    constructedPolygon.p_points = new VectorSpace2D::Pointf2D[point_list.size()];

    std::copy(point_list.begin(), point_list.end(), constructedPolygon.p_points);

    return constructedPolygon;

}
