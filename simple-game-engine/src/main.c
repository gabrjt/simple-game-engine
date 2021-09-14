#include "application.h"
#include "application_sample.h"

int main()
{
    // Initialize Application
    ApplicationInit(1920, 1080, "Csmple Game Engine", 60);

    // Register components, systems and create entities
    RegisterSampleApplication();
    
    // Run Game Loop
    ApplicationRun();

    // De-Initialize Application when Game Loop ends
    ApplicationQuit();

    // Exit Process
    return 0;
}
