#pragma once
#include <fmod.hpp>

#include "Application.h"
#include "Camera.h"


class SoundProgramming : public Application
{
public:
    virtual bool startup();
    virtual void shutdown();
    virtual bool update();
    virtual void draw();

	bool onCreate();
    FlyCamera m_camera;
private:
	FMOD::System* m_pFmodSystem;
};