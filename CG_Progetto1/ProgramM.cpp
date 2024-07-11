#include "ProgramM.h"

void ProgramM::initUniforms()
{
	this->projectionId = glGetUniformLocation(this->getProgramId(), "projection");
	this->modelId = glGetUniformLocation(this->getProgramId(), "model");
	this->viewId = glGetUniformLocation(this->getProgramId(), "view");
	
	this->isBackgroundShaderId = glGetUniformLocation(this->getProgramId(), "isBackgroundShader");
	this->resolutionId = glGetUniformLocation(this->getProgramId(), "resolution");
	this->timeId = glGetUniformLocation(this->getProgramId(), "time");
}