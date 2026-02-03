#include <raylib.h>
#include <vector>
#include <cmath>
#include "vec2Math.h"

const int screenWidth = 1600;
const int screenHeight = 900;
const float gravity = 400.0f;
const float elasticity = 0.8f;

struct Ball 
{
	Vector2 position;
	Vector2 velocity;
	float radius;
	Color color;
};

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

		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
		{
			for (size_t i = 0; i < balls.size(); i++)
			{
				float distance = sqrt((GetMousePosition().x - balls[i].position.x) * (GetMousePosition().x - balls[i].position.x) + (GetMousePosition().y - balls[i].position.y) * (GetMousePosition().y - balls[i].position.y));
				if (distance <= balls[i].radius)
				{
					balls.erase(balls.begin() + i);
				}
			}
		}

		for (size_t i = 0; i < balls.size(); i++)
		{
			Ball& ball = balls[i];
			ball.velocity.y += gravity * GetFrameTime();
			ball.position.x += ball.velocity.x * GetFrameTime();
			ball.position.y += ball.velocity.y * GetFrameTime();

			//Handle collisions with borders of window

			//Collision with bottom
			if (ball.position.y + ball.radius >= screenHeight)
			{
				ball.position.y = screenHeight - ball.radius;
				ball.velocity.y *= -elasticity;
			}
			//Collision with right border
			if (ball.position.x + ball.radius >= screenWidth)
			{
				ball.position.x = screenWidth - ball.radius;
				ball.velocity.x *= -elasticity;
			}
			//Collision with left border
			if (ball.position.x - ball.radius <= 0)
			{
				ball.position.x = ball.radius;
				ball.velocity.x *= -elasticity;
			}

			//Handle collisions with other balls 
			for (size_t j = i + 1; j < balls.size(); j++)
			{
				Ball& other = balls[j];
				Vector2 delta = { other.position.x - ball.position.x, other.position.y - ball.position.y };
				float distance = sqrt(delta.x * delta.x + delta.y * delta.y);
				float overlap = ball.radius + other.radius - distance;

				if (overlap > 0)
				{
					//Seperate balls
					Vector2 collisionNormal = delta / distance;
					ball.position -= collisionNormal * overlap / 2;
					other.position += collisionNormal * overlap / 2;

					//Resolve collision
					Vector2 relativeVelocity = other.velocity - ball.velocity;
					float velocityAlongNormal = relativeVelocity.x * collisionNormal.x + relativeVelocity.y * collisionNormal.y;
					float impulse = (-(1 + elasticity) * velocityAlongNormal) / (1 / ball.radius + 1 / other.radius);
					ball.velocity -= collisionNormal * (impulse / ball.radius);
					other.velocity += collisionNormal * (impulse / other.radius);
				}
			}
		}

		BeginDrawing();
		ClearBackground({ 31,31,31,255 });

		//Show controls
		int controlsText1Width = MeasureText("Left Click to spawn a ball", 20);
		DrawText("Left Click to spawn a ball", (screenWidth / 2 - controlsText1Width / 2), 50, 20, WHITE);
		int controlsText2Width = MeasureText("Right Click on a ball to remove it", 20);
		DrawText("Right Click on a ball to remove it", (screenWidth / 2 - controlsText2Width / 2), 80, 20, WHITE);

		//Show ball counter
		const char* bCountText = TextFormat("Ball Counter: %d", (int)balls.size());
		int bCountTextWidth = MeasureText(bCountText, 20);
		DrawText(bCountText, (screenWidth - bCountTextWidth - 20), 20, 20, WHITE);
		
		DrawFPS(20, 20);

		//Draw balls
		for (const Ball& ball : balls)
		{
			DrawCircleV(ball.position, ball.radius, ball.color);
		}

		EndDrawing();
	}

	CloseWindow();
}
