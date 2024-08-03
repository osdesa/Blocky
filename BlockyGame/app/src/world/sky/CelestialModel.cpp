#include "world/sky/CelestialModel.h"

namespace Blocky{
	void CelestialModel::Create(Camera& camera)
	{

	}

	void CelestialModel::Draw(Camera& cam, float DT)
	{
		// Gets where the player is
		Vec3 Center = cam.GetPosition();
		// Sets up the translation to move the object to where the player is
		Vec3 translate = Vec3((-Center.z * 2) + scaleFactor / 2, 0, (-Center.x * 2) + scaleFactor / 2);
		// shifts the sun to very far above the player
		Vec3 Shift = Vec3{ 0 , distance + Center.y, 0 };

		// sets the scale of the object
		Vec3 scale = Vec3{ scaleFactor,0,scaleFactor };

		// Gets the basic matrix for model
		auto model = cam.GetModel();
		// translates the matrix
		model = Matrix::Translate(model, translate);
		model = Matrix::Rotate(model, (float)DEG_TO_RAD(-90.0f), Vec3{ 0,1,0 });
		model = Matrix::Rotate(model, angle, Vec3{ 1,0,0 });
		model = Matrix::Translate(model, Shift);
		model = Matrix::Scale(model, scale);

		// binds the texture
		texture.Bind();
		shader.Bind();
		// Sends the matrix data to the gpu
		shader.SetMatrix4("u_Model", model);
		shader.SetMatrix4("u_Projection", cam.GetProjection());
		shader.SetMatrix4("u_View", cam.GetView());
		shader.SetUniform1i("uTexture", 0);
		// Draws all the indices to the screen
		DrawElements(va, ib, shader);
		// Increments the angle
		angle += 0.1 * DT;

		// makes sure the angle between 0 and TWOPI
		if (angle > TWOPI) {
			angle = 0;
		}
	}
}