#pragma once
#include "Program.h"

class ProgramM : public Program
{
protected:
	GLuint modelId;
	GLuint viewId;
	GLuint isBackgroundShaderId;
	GLuint resolutionId;
	GLuint timeId;

public:
	ProgramM() {}

	GLuint getModelId() { return this->modelId; }
	GLuint getViewId() { return this->viewId; }
	GLuint getIsBackgroundShaderId() { return this->isBackgroundShaderId; }
	GLuint getResolutionId() { return this->resolutionId; }
	GLuint getTimeId() { return this->timeId; }
	void initUniforms();
};

