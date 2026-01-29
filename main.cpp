#include <raylib.h>
#include <vector>
#include <iostream>
#include <cmath>

const int screenWidth = 1280;
const int screenHeight = 720;
const float gravity = 400.0f;
const float elasticity = 0.8f;

struct Ball {
	Vector2 position;
	Vector2 velocity;
	float radius; //bigger radius makes balls heavier (move less)
	Color color;
};

bool operator==(const Vector2& v1, const Vector2& v2)
{
	return (v1.x == v2.x) && (v1.y == v2.y);
}

Vector2 operator*(const Vector2& v, float f)
{
	return { v.x * f, v.y * f };
}

Vector2& operator*=(Vector2& v, float f)
{
	v.x *= f;
	v.y *= f;
	return v;
}

Vector2 operator/(const Vector2& v, float f)
{
	return { v.x / f, v.y / f };
}

Vector2& operator/=(Vector2& v, float f)
{
	v.x /= f;
	v.y /= f;
	return v;
}

Vector2 operator-(const Vector2& v1, const Vector2& v2)
{
	return { v1.x - v2.x, v1.y - v2.y };
}

Vector2& operator-=(Vector2& v1, const Vector2& v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	return v1;
}

Vector2& operator+=(Vector2& v1, const Vector2& v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	return v1;
}

int main()
{
	InitWindow(screenWidth, screenHeight, "Physics Simulation");

	std::vector<Ball> balls;

	while (!WindowShouldClose())
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			Ball b;
			b.position = GetMousePosition();
			b.velocity =
			{
				(float)GetRandomValue(-200,200),
				(float)GetRandomValue(-200,0)
			};
			b.radius = GetRandomValue(10, 70);
			b.color =
			{
				(unsigned char)GetRandomValue(50,255),
				(unsigned char)GetRandomValue(50,255),
				(unsigned char)GetRandomValue(50,255),
				255
			};
			balls.push_back(b);
		}

		for (size_t i = 0; i < balls.size(); i++)
		{
			Ball& ball = balls[i];
			ball.velocity.y += gravity * GetFrameTime();
			ball.position.x += ball.velocity.x * GetFrameTime();
			ball.position.y += ball.velocity.y * GetFrameTime();

			//handle collisions with borders of window

			//collision with bottom
			if (ball.position.y + ball.radius >= screenHeight)
			{
				ball.position.y = screenHeight - ball.radius;
				ball.velocity.y *= -elasticity;
			}
			//collision with right border
			if (ball.position.x + ball.radius >= screenWidth)
			{
				ball.position.x = screenWidth - ball.radius;
				ball.velocity.x *= -elasticity;
			}
			//collision with left border
			if (ball.position.x - ball.radius <= 0)
			{
				ball.position.x = ball.radius;
				ball.velocity.x *= -elasticity;
			}

			//handle collisions with other balls 
			for (int j = i + 1; j < balls.size(); j++)
			{
				Ball& other = balls[j];
				Vector2 delta = { other.position.x - ball.position.x, other.position.y - ball.position.y }; //vector that connects the centers
				float distance = sqrt(delta.x * delta.x + delta.y * delta.y); //length of vector that connects the centers (delta)
				float overlap = ball.radius + other.radius - distance;

				if (overlap > 0)
				{
					//seperate balls
					Vector2 collisionNormal = delta / distance;
					ball.position -= collisionNormal * overlap / 2;
					other.position += collisionNormal * overlap / 2;

					Vector2 relativeVelocity = other.velocity - ball.velocity;
					float velocityAlongNormal = relativeVelocity.x * collisionNormal.x + relativeVelocity.y * collisionNormal.y;
					float impulse = (-(1 + elasticity) * velocityAlongNormal) / (1 / ball.radius + 1 / other.radius);

					//Newtons third law (equal and opposite reaction)
					ball.velocity -= collisionNormal * (impulse / ball.radius);
					other.velocity += collisionNormal * (impulse / other.radius);
				}
			}
		}

		BeginDrawing();
		ClearBackground({ 31,31,31,255 });

		int textWidth = MeasureText("Click to spawn a ball", 20);
		DrawText("Click to spawn a ball", (screenWidth / 2 - textWidth / 2), 50, 20, WHITE);
		DrawFPS(20, 20);

		for (const Ball& ball : balls)
		{
			DrawCircleV(ball.position, ball.radius, ball.color);
		}

		EndDrawing();
	}

	CloseWindow();
}
