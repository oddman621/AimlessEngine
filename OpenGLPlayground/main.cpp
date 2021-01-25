#include "glApp.h"



int main(void)
{
	glApp* app = new GLAPP_CLASS();
	app->Startup();
	app->Loop();
	app->Cleanup();

	return 0;
}