#include "src/graphics/window.h"
#include "src/math/math.h"

int main()
{
	using namespace wraith;
	using namespace graphics;
	using namespace math;

	Window window("Wraith", 800, 600);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	Matrix4 position = Matrix4::translation(Vector3(2, 3, 4));
	position *= Matrix4::identity();
	
	Vector4 column = position.columns[3];

	std::cout << column << std::endl;

	while (!window.closed())
	{
		window.clear();

		double x, y;
		window.getMousePosition(x, y);
		//std::cout << "X: " << x << std::endl;
		//std::cout << "Y: " << y << std::endl;

		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.0f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();

		window.update();
	}

	return 0;
}
