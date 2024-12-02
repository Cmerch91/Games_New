#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

const Keyboard::Key controls[4] = {
    Keyboard::A,   // Player1 UP
    Keyboard::Z,   // Player1 Down
    Keyboard::Up,  // Player2 UP
    Keyboard::Down // Player2 Down
};

const Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;
const float paddleOffsetWall = 10.f;
const float velocityMultiplier = 1.05f; // Multiplier to increase speed on bounce

CircleShape ball;
RectangleShape paddles[2];
Vector2f ballVelocity(200.f, 200.f); // Initial ball velocity
Font font;
Text text;
int player1Score = 0;
int player2Score = 0;
bool isSinglePlayer = true;  // Toggle for single player vs. two players

void Reset() {
    // Reset paddles
    for (auto& p : paddles) {
        p.setSize(paddleSize);
        p.setOrigin(paddleSize / 2.f); // The origin is set to the center of the paddle
    }

    // Set size and origin of ball
    ball.setRadius(ballRadius);
    ball.setOrigin(ballRadius, ballRadius); // The origin is set to the center of the ball

    // Reset paddle positions
    paddles[0].setPosition(Vector2f(paddleOffsetWall + paddleSize.x / 2.f, gameHeight / 2.f)); // Player 1 paddle
    paddles[1].setPosition(Vector2f(gameWidth - paddleOffsetWall - paddleSize.x / 2.f, gameHeight / 2.f)); // Player 2 paddle

    // Reset Ball Position and velocity
    ball.setPosition(gameWidth / 2.f, gameHeight / 2.f); // Ball is placed in the center of the screen
    ballVelocity = Vector2f(200.f, 200.f); // Reset ball velocity to initial value
}

void Update(RenderWindow& window) {
    // Reset clock, recalculate deltaTime
    static Clock clock;
    float dt = clock.restart().asSeconds();

    // Check and consume events
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
            return;
        }
    }

    // Quit via ESC key
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        window.close();
    }

    // Handle Player 1 (Left paddle) movement
    float directionP1 = 0.0f;
    if (Keyboard::isKeyPressed(controls[0])) {
        directionP1--; // Move up
    }
    if (Keyboard::isKeyPressed(controls[1])) {
        directionP1++; // Move down
    }
    paddles[0].move(Vector2f(0.f, directionP1 * paddleSpeed * dt));

    // Handle Player 2 (Right paddle) movement or AI
    if (isSinglePlayer) {
        // AI movement (Player 2)
        float aiDirection = 0.0f;

        // AI follows the ball's Y position (try to match it)
        if (paddles[1].getPosition().y < ball.getPosition().y) {
            aiDirection = 1.0f; // Move down
        }
        else if (paddles[1].getPosition().y > ball.getPosition().y) {
            aiDirection = -1.0f; // Move up
        }

        // Move AI paddle with delta time, but respect paddle speed
        paddles[1].move(Vector2f(0.f, aiDirection * paddleSpeed * dt));
    }
    else {
        // Player 2 (Right paddle) manual control
        float directionP2 = 0.0f;
        if (Keyboard::isKeyPressed(controls[2])) {
            directionP2--; // Move up
        }
        if (Keyboard::isKeyPressed(controls[3])) {
            directionP2++; // Move down
        }
        paddles[1].move(Vector2f(0.f, directionP2 * paddleSpeed * dt));
    }

    // Ball Movement and Collision Check
    ball.move(ballVelocity * dt);

    // Ball Collision with top or bottom wall
    const float bx = ball.getPosition().x;
    const float by = ball.getPosition().y;
    if (by > gameHeight) { // Bottom wall
        ballVelocity.y *= -velocityMultiplier; // Reverse and speed up ball
        ball.move(Vector2f(0.f, -10.f)); // Push ball slightly above the bottom wall
    }
    else if (by < 0) { // Top wall
        ballVelocity.y *= -velocityMultiplier; // Reverse and speed up ball
        ball.move(Vector2f(0.f, 10.f)); // Push ball slightly below the top wall
    }

    // Ball collision with left or right walls (score walls)
    if (bx > gameWidth) { // Right wall (Player 1 scores)
        player1Score++;
        Reset(); // Reset the game
    }
    else if (bx < 0) { // Left wall (Player 2 scores)
        player2Score++;
        Reset(); // Reset the game
    }

    // Ball and Paddle Collision
    for (int i = 0; i < 2; ++i) {
        const float px = paddles[i].getPosition().x;
        const float py = paddles[i].getPosition().y;
        const float paddleHeight = paddles[i].getSize().y;

        // Check if the ball is intersecting with the paddle
        if (bx - ballRadius < px + paddleSize.x / 2.f && bx + ballRadius > px - paddleSize.x / 2.f) {
            if (by - ballRadius < py + paddleHeight / 2.f && by + ballRadius > py - paddleHeight / 2.f) {
                // Ball hits paddle, reverse the X velocity
                ballVelocity.x *= -velocityMultiplier;

                // Position the ball just outside the paddle to avoid it sticking
                if (i == 0) {
                    // Player 1 paddle (left side)
                    ball.setPosition(px + paddleSize.x / 2.f + ballRadius, by);
                }
                else {
                    // Player 2 paddle (right side)
                    ball.setPosition(px - paddleSize.x / 2.f - ballRadius, by);
                }
            }
        }
    }

    // Update the score text
    text.setString("Player 1: " + to_string(player1Score) + "  Player 2: " + to_string(player2Score));
    text.setPosition((gameWidth * .5f) - (text.getLocalBounds().width * .5f), 0);
}

void Render(RenderWindow& window) {
    // Draw everything
    window.draw(paddles[0]);
    window.draw(paddles[1]);
    window.draw(ball);
    window.draw(text); // Draw the score text
}

int main() {
    RenderWindow window(VideoMode(gameWidth, gameHeight), "PONG");

    // Load font for score
    if (!font.loadFromFile("C:/Users/Cmerc/Games_Games/Games_New/res/fonts/RobotoMono-Regular.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return -1;
    }

    // Set up the text object for score
    text.setFont(font);
    text.setCharacterSize(24); // Set the character size to 24 pixels
    text.setFillColor(Color::White); // Set the color of the text to white

    Reset(); // Initialize the game state

    while (window.isOpen()) {
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }

    return 0;
}
