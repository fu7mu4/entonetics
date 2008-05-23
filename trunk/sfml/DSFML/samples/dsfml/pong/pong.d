module pong;

import dsfml.audio.all;
import dsfml.graphics.all;
import dsfml.system.all;
import dsfml.window.all;

version (Tango)
{
    import tango.math.Math;
}
else
{
    import std.math;
}

static this()
{
    version (Dynamic)
    {
        dsfml.system.loader.init();
        dsfml.window.loader.init();
        dsfml.graphics.loader.init();
        dsfml.audio.loader.init();
    }
}

static ~this()
{
    
}

void main()
{
	// Defines PI
	const float PI = 3.14159f;

    // Create the window of the application
    RenderWindow app = new RenderWindow(VideoMode(800, 600, 32), "SFML Pong");
    app.setBackgroundColor(Color(255, 255, 255, 255));
    app.setFramerateLimit(100);
    
    Input i = app.getInput();
    
    // Load the sounds used in the game
    SoundBuffer BallSoundBuffer = new SoundBuffer();
    if (!BallSoundBuffer.loadFromFile("Data/ball.wav"))
    {
        return assert(0);
    }
    Sound BallSound = new Sound(BallSoundBuffer);

    // Load the images used in the game
    Image PaddleImage = new Image();
    Image BallImage = new Image();
    if (!PaddleImage.loadFromFile("Data/paddle.tga")   ||
        !BallImage.loadFromFile("Data/ball.tga"))
    {
        assert(0);
    }


	// Initialize the end text
	String End = new String(""c);
	Font font = new Font();
	font.loadFromFile("Data/cheeseburger.ttf");
    End.setFont(font);
	End.setSize(60.f);
    End.move(150.f, 200.f);
    End.setColor(Color(50, 50, 250));

    // Create the sprites of the background, the paddles and the ball
    Sprite LeftPaddle = new Sprite(PaddleImage);
    Sprite RightPaddle = new Sprite(PaddleImage);
    Sprite Ball = new Sprite(BallImage);

    LeftPaddle.move(10, (app.getView().getRect().getHeight() - LeftPaddle.getSize().y) / 2);
    RightPaddle.move(app.getView().getRect().getWidth() - RightPaddle.getSize().x - 10, (app.getView().getRect().getHeight() - RightPaddle.getSize().y) / 2);
    Ball.move((app.getView().getRect().getWidth() - Ball.getSize().x) / 2, (app.getView().getRect().getHeight() - Ball.getSize().y) / 2);

    // Define the paddles properties
    Clock AITimer = new Clock();
	const float AITime     = 0.1f;
    float LeftPaddleSpeed  = 400.f;
    float RightPaddleSpeed = 400.f;

    // Define the ball properties
    float BallSpeed = 400.f;
    float BallAngle = 0.f;
    do
    {
        // Make sure the ball initial angle is not too much vertical
        BallAngle = Randomizer.random(0.f, 2 * PI);
    } while (abs(cos(BallAngle)) < 0.7f);

	bool IsPlaying = true;

	Event evt;
    while (app.isOpened())
    {
        // Handle events
        
        while (app.getEvent(evt))
        {
            // Window closed or escape key pressed : exit
            if ((evt.Type == Event.EventType.CLOSED) || 
               ((evt.Type == Event.EventType.KEYPRESSED) && (evt.Key.Code == KeyCode.ESCAPE)))
            {
                app.close();
                break;
            }        
        }

        if (IsPlaying)
		{
			// Move the player's paddle
            if (i.isKeyDown(KeyCode.UP) && (LeftPaddle.getPosition().y > 5.f))
				LeftPaddle.move(0.f, -LeftPaddleSpeed * app.getFrameTime());
            if (i.isKeyDown(KeyCode.DOWN) && (LeftPaddle.getPosition().y < app.getView().getRect().getHeight() - LeftPaddle.getSize().y - 5.f))
				LeftPaddle.move(0.f, LeftPaddleSpeed * app.getFrameTime());
            
			// Move the computer's paddle
            if (((RightPaddleSpeed < 0.f) && (RightPaddle.getPosition().y > 5.f)) ||
                ((RightPaddleSpeed > 0.f) && (RightPaddle.getPosition().y < app.getView().getRect().getHeight() - RightPaddle.getSize().y - 5.f)))
            {
                RightPaddle.move(0.f, RightPaddleSpeed * app.getFrameTime());
            }

            // Update the computer's paddle direction according to the ball position
            if (AITimer.getElapsedTime() > AITime)
            {
                AITimer.reset();
                if ((RightPaddleSpeed < 0) && (Ball.getPosition().y + Ball.getSize().y > RightPaddle.getPosition().y + RightPaddle.getSize().y))
                    RightPaddleSpeed = -RightPaddleSpeed;
                if ((RightPaddleSpeed > 0) && (Ball.getPosition().y < RightPaddle.getPosition().y))
                    RightPaddleSpeed = -RightPaddleSpeed;
            }



			// Move the ball
			float Factor = BallSpeed * app.getFrameTime();
            Ball.move(cos(BallAngle) * Factor, sin(BallAngle) * Factor);

			// Check collisions between the ball and the screen
			if (Ball.getPosition().x < 0.f)
			{
				IsPlaying = false;
				End.setText("You lost !\n(press escape to exit)"c);
			}

			if (Ball.getPosition().x + Ball.getSize().x > app.getView().getRect().getWidth())
			{
				IsPlaying = false;
				End.setText("You won !\n(press escape to exit)"c);
			}

			if (Ball.getPosition().y < 0.f)
			{
				BallSound.play();
				BallAngle = -BallAngle;
				Ball.setY(0.1f);
			}

			if (Ball.getPosition().y + Ball.getSize().y > app.getView().getRect().getHeight())
			{
				BallSound.play();
				BallAngle = -BallAngle;
				Ball.setY(app.getView().getRect().getHeight() - Ball.getSize().y - 0.1f);
			}
			// Check the collisions between the ball and the paddles
			// Left Paddle
			if (Ball.getPosition().x < LeftPaddle.getPosition().x + LeftPaddle.getSize().x && 
				Ball.getPosition().x > LeftPaddle.getPosition().x + (LeftPaddle.getSize().x / 2.0f) &&
				Ball.getPosition().y + Ball.getSize().y >= LeftPaddle.getPosition().y &&
				Ball.getPosition().y <= LeftPaddle.getPosition().y + LeftPaddle.getSize().y)
			{
				BallSound.play();
				BallAngle = PI - BallAngle;
				Ball.setX(LeftPaddle.getPosition().x + LeftPaddle.getSize().x + 0.1f);
			}

			// Right Paddle
			if (Ball.getPosition().x + Ball.getSize().x > RightPaddle.getPosition().x &&
				Ball.getPosition().x + Ball.getSize().x < RightPaddle.getPosition().x + (RightPaddle.getSize().x / 2.0f) &&
				Ball.getPosition().y + Ball.getSize().y >= RightPaddle.getPosition().y &&
				Ball.getPosition().y <= RightPaddle.getPosition().y + RightPaddle.getSize().y)
			{
				BallSound.play();
				BallAngle = PI - BallAngle;
				Ball.setX(RightPaddle.getPosition().x - Ball.getSize().x - 0.1f);
			}
		}

        // Draw the background, paddles and ball sprites

        app.draw(LeftPaddle);
        app.draw(RightPaddle);
        app.draw(Ball);

        // If the game is over, display the end message
        if (!IsPlaying)
            app.draw(End);

        // Display things on screen
        app.display();
    }
}
