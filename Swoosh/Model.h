#pragma once

#include <string>
#include "ObjFile.h"

class Model
{
private:
	ObjFile* obj;
	void loadModel(std::string path);
public:
	Model(std::string path);
	~Model();
	// Methods
	void scale(float x, float y ,float z);
};
