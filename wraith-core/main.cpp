#include "src/graphics/Window.h"
#include "src/graphics/Shader.h"
#include "src/math/Math.h"

#include "src/graphics/buffers/Buffer.h"
#include "src/graphics/buffers/IndexBuffer.h"
#include "src/graphics/buffers/VertexArray.h"

#include "src/graphics/Renderer2D.h"
#include "src/graphics/SimpleRenderer2D.h"
#include "src/graphics/BatchRenderer2D.h"

#include "src/graphics/StaticSprite.h"
#include "src/graphics/Sprite.h"

#include "src/utils/timer.h"

#include <vector>
#include <time.h>

#define BATCH_RENDERER 1

int main()
{
	using namespace Wraith;
	using namespace Graphics;
	using namespace Math;

	Window window("Wraith", 960, 540);

	Matrix4 ortho = Matrix4::Orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.Enable();

	shader.SetUniformMat4("pr_matrix", ortho);

	std::vector<Renderable2D *> sprites;

	srand((unsigned int)time(NULL));

	for (float y = 0; y < 9.0f; y += 0.05f)
	{
		for (float x = 0; x < 16.0f; x += 0.05f)
		{
			sprites.push_back(new
#if BATCH_RENDERER
				Sprite(x, y, 0.04f, 0.04f, Vector4(rand() % 1000 / 1000.0f, 0, 1, 1)));
#else
				StaticSprite(x, y, 0.04f, 0.04f, Vector4(rand() % 1000 / 1000.0f, 0, 1, 1), shader));
#endif
		}
	}

#if BATCH_RENDERER
	BatchRenderer2D renderer;

#else
	SimpleRenderer2D renderer;
#endif

	shader.SetUniform2f("light_pos", Vector2(4.0f, 1.5f));
	shader.SetUniform4f("colour", Vector4(0.2f, 0.3f, 0.8f, 1.0f));

	while (!window.Closed())
	{
		window.Clear();
		Vector2 mousePos = window.GetMousePosition();
		shader.SetUniform2f("light_pos", Vector2((float)(mousePos.x * 16.0f / 960.0f), (float)(9.0f - mousePos.y * 9.0f / 540.0f)));
#if BATCH_RENDERER
		renderer.Begin();
#endif
		for (int i = 0; i < sprites.size(); i++)
		{
			renderer.Submit(sprites[i]);
		}
#if BATCH_RENDERER
		renderer.End();
#endif

		renderer.Render();

		window.Update();
	}

	return 0;
}
