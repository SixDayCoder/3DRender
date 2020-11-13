#pragma once
#include "math3d/Mesh.h"


class BoxDemo
{
private:
	BoxDemo();
	BoxDemo(const BoxDemo&);
	~BoxDemo() {}
public:
	static  Mesh CreateBox(real width, real height, real depth);
};