//--------------------------------------------------------------

//--------------------------------------------------------------

#ifndef GAME_H
#define GAME_H

#include "Engine.h"
#include "MathEngine.h"
#include "AnimTimer.h"

namespace Azul
{
	class Game : public Engine
	{
	public:
		Game(const char *const pName, int width, int height);

		Game() = delete;
		Game(const Game &) = delete;
		Game &operator = (const Game &) = delete;
		virtual ~Game();

		virtual bool LoadContent() override;
		static void CreateMouseArmy();
		virtual void UnloadContent() override;
		virtual void Update(float deltaTime) override;
		virtual void Render() override;
		virtual	void ClearDepthStencilBuffer() override;

		// Rendering
		float GetAspectRatio() const;
		void SetDefaultTargetMode();

		// Nice and Clean
		AnimTimer	intervalTimer;
		AnimTimer	globalTimer;
	};
}

#endif

// --- End of File ---

