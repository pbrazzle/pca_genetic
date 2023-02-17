#include "ModelInputDataVector.hpp"

using PCAGenetic::ModelInputDataVector;

ModelInputDataVector::ModelInputDataVector(std::vector<double> d) : data(d) { }

std::vector<double> ModelInputDataVector::getData() { return data; }
