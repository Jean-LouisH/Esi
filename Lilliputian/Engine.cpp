#include "Engine.hpp"

Lilliputian::Engine::Engine()
{
	this->game = NULL;
	this->aiEngine = NULL;
	this->animationEngine = NULL;
	this->audioEngine = NULL;
	this->hapticEngine = NULL;
	this->physicsEngine = NULL;
	this->renderingEngine = NULL;
	this->osWindow = NULL;
	this->platform = NULL;
	this->frameCount = 0;
	this->FPS = 0;
	this->msPerComputeUpdate = 8;
	this->targetFPS = 60;

}

Lilliputian::Engine::~Engine()
{

}

void Lilliputian::Engine::sleep()
{

}

void Lilliputian::Engine::benchmark()
{

}

void Lilliputian::Engine::input()
{

}

void Lilliputian::Engine::logic()
{
	this->game->executeStartLogic();
	this->game->executeInputLogic();
	this->game->executeFrameLogic();
}

void Lilliputian::Engine::compute()
{

	this->game->executeLateLogic();
	this->game->executeFinalLogic();
}

void Lilliputian::Engine::output()
{
	if (this->renderingEngine != NULL)
	{

	}

	if (this->audioEngine != NULL)
	{

	}

	if (this->hapticEngine != NULL)
	{

	}
}

void Lilliputian::Engine::initialize()
{
	//this->state.setInitializing();
	this->game = new Game();

	for (int i = 0; i < this->sceneDefinerCallbacks.size(); i++)
	{
		if (this->sceneDefinerCallbacks.at(i) != nullptr)
			this->sceneDefinerCallbacks.at(i)(this->game->getEditor());
	}
}

void Lilliputian::Engine::shutdown()
{
	delete this->game;
}

void Lilliputian::Engine::run()
{
	//do
	{
		this->initialize();
		this->game->initialize();

		//while(this->state.isRunning())
		{
			this->input();
			this->logic();
			this->compute();
			this->output();
			this->sleep();
			this->frameCount++;
			this->benchmark();
		}

		this->game->deinitialize();
		this->shutdown();
	}// while (this->state.isRestarting());
}

void Lilliputian::Engine::setMillisecondsPerComputeUpdate(uint32_t msPerComputeUpdate)
{

}

void Lilliputian::Engine::setTargetFPS(uint32_t targetFPS)
{
	if (targetFPS > 0)
		this->targetFPS = targetFPS;
	else
		this->targetFPS = 1;
}

void Lilliputian::Engine::addSceneDefiner(SceneDefinerCallback sceneDefinerCallback)
{
	this->sceneDefinerCallbacks.push_back(sceneDefinerCallback);
}