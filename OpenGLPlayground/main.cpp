#include "Apps.h"




int main(void)
{
	glApp* app = new GLAPP_CLASS();
	app->Startup();
	app->Loop();
	app->Cleanup();
	delete app;

	return 0;
}