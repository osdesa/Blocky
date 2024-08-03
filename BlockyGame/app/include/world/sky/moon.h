#pragma once
#include "CelestialModel.h"

namespace Blocky {
	class Moon : public CelestialModel
	{
	public:
		void Create(Camera& camera) override;
	};
}