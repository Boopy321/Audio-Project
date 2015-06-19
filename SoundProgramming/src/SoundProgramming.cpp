#include "SoundProgramming.h"
#include <fmod.h>
#include <fmod_errors.h>

#include "gl_core_4_4.h"
#include "GLFW/glfw3.h"
#include "Gizmos.h"

#include <iostream>
 
//using namespace FMOD::STUDIO;


bool SoundProgramming::startup()
{
    if (Application::startup() == false)
    {
        return false;
    }

    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    Gizmos::create();

    m_camera = FlyCamera(1280.0f / 720.0f, 10.0f);
    m_camera.setLookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
    m_camera.sensitivity = 3;

	
    return true;
}

void SoundProgramming::shutdown()
{
    Gizmos::destroy();

    Application::shutdown();
}

bool SoundProgramming::update()
{
	FMOD_RESULT result;
    if (Application::update() == false)
    {
        return false;
    }

    Gizmos::clear();

    float dt = (float)glfwGetTime();
    glfwSetTime(0.0);

    vec4 white(1);
    vec4 black(0, 0, 0, 1);
    for (int i = 0; i <= 20; ++i)
    {
        Gizmos::addLine(vec3(-10 + i, -0.01, -10), vec3(-10 + i, -0.01, 10),
            i == 10 ? white : black);
        Gizmos::addLine(vec3(-10, -0.01, -10 + i), vec3(10, -0.01, -10 + i),
            i == 10 ? white : black);
    }

    m_camera.update(dt);

	FMOD::Sound* pSound;
	result = m_pFmodSystem->createSound("jaguar.wav", FMOD_DEFAULT, 0, &pSound);


    return true;
}

void SoundProgramming::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Gizmos::draw(m_camera.proj, m_camera.view);

    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

bool SoundProgramming::onCreate()
{
	
	// Initialize FMOD
	FMOD_RESULT result;
	m_pFmodSystem = NULL;
	// Create the main system object.
	result = FMOD::System_Create(&m_pFmodSystem);
	if (result != FMOD_OK){
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		return false;
	}
	// Initialize FMOD with 512 channels
	result = m_pFmodSystem->init(512, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK){
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		return false;
	}
}

void SoundProgramming::PlaySound(char string,  )