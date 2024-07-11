#pragma once

class Window
{
private:
	static float wAspect;
	static float hAspect;
	static float w;
	static float h;

public:
	static float getWidth() { return w; }
	static float getHeight() { return h; }
	static void setWidth(float value) { w = value; }
	static void setHeight(float value) { h = value; }
	static float getAspectWidth() { return wAspect; }
	static float getAspectHeight() { return hAspect; }
};