#include "src/graphics/window.h"
#include "src/graphics/shader.h"
#include "src/math/math.h"

#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/index_buffer.h"
#include "src/graphics/buffers/vertex_array.h"

#include "src/graphics/renderer_2d.h"
#include "src/graphics/simple_renderer_2d.h"
#include "src/graphics/batch_renderer_2d.h"

#include "src/graphics/static_sprite.h"
#include "src/graphics/sprite.h"

#include <vector>
#include <time.h>

#define BATCH_RENDERER 1

int main()
{
	using namespace wraith;
	using namespace graphics;
	using namespace math;

	Window window("Wraith", 960, 540);

	Matrix4 ortho = Matrix4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();

	shader.setUniformMat4("pr_matrix", ortho);

	std::vector<Renderable2D *> sprites;

	srand(time(NULL));

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

	shader.setUniform2f("light_pos", Vector2(4.0f, 1.5f));
	shader.setUniform4f("colour", Vector4(0.2f, 0.3f, 0.8f, 1.0f));

	while (!window.closed())
	{
		window.clear();
		double x, y;
		window.getMousePosition(x, y);
		shader.setUniform2f("light_pos", Vector2((float)(x * 16.0f / 960.0f), (float)(9.0f - y * 9.0f / 540.0f)));
#if BATCH_RENDERER
		renderer.begin();
#endif
		for (int i = 0; i < sprites.size(); i++)
		{
			renderer.submit(sprites[i]);
		}
#if BATCH_RENDERER
		renderer.end();
#endif

		renderer.render();
		window.update();
	}

	return 0;
}
