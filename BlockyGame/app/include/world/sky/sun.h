#pragma once

#include "math/BMath.h"
#include <camera.h>
#include <graphics/renderer.h>
#include <graphics/Texture.h>
#include "CelestialModel.h"

namespace Blocky {
	class Sun : public CelestialModel
	{
	public:
		void Create(Camera& camera) override;
	};
}