module sound3d;

import dsfml.system.all;
import dsfml.window.all;
import dsfml.graphics.all;
import dsfml.audio.all;

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

void main()
{
    //We create our window with a limit of 100 and a white backcolor.
    RenderWindow app = new RenderWindow (VideoMode(800, 600, 32), "Sound Spatialization Sample");
    app.setBackgroundColor(Color.WHITE);
    
    Font f = new Font();
    if (!f.loadFromFile("Data/cheeseburger.ttf", 34))
        assert(0);
    
    //Some instructions
    String s = new String("Click anywhere on screen to change listener position.\nPress + or - to modify the speed of the car."c, f);
    s.setPosition(20, 30);
    s.setColor(Color.BLACK);
    
    //We prepare our images and the sound
    char[][2] images = ["Data/bluerallyecarleft.bmp", "Data/bluerallyecarright.bmp"];
    Car c = new Car(images, "Data/car_idle.wav");
    
    int carSpeed = 100;
    
    //Set default position for the car and the listener
    c.setPosition(Vector2f(0, 300));
    SoundListener.setPosition(Vector2f(400, 300));
    
    c.startPlaying();
    
    //Start the main loop
    while (app.isOpened())
    {
        Event evt;
        //The event loop
        while (app.getEvent(evt))
        {
            // if the window is closed, we can leave the game loop
            if (evt.Type == Event.EventType.CLOSED) 
                app.close();
            // we handle the click event to change listener position
            else if (evt.Type == Event.EventType.MOUSEBUTTONPRESSED && evt.MouseButton.Button == MouseButtons.LEFT)
            {
                Input i = app.getInput();
                SoundListener.setPosition(Vector2f(i.getMouseX(), i.getMouseY()));
            }
            // and eventual keys press
            else if (evt.Type == Event.EventType.KEYPRESSED)
            {
                //Change the car speed
                if (evt.Key.Code == KeyCode.ADD)
                {
                    carSpeed += 25;
                }
                else if (evt.Key.Code == KeyCode.SUBTRACT)
                {
                    carSpeed -= 25;
                }
            }
        }
        
        //We move constantly our car.
        c.move(app.getFrameTime() * carSpeed, 0);
    
        //Draw all the sprite and string on render window
        app.draw(s);
        app.draw(c.getSprite());
        app.draw(SoundListener.getSprite());
        
        //And finally display the window
        app.display();
    } 
    
    
}

// Encapsulate the listener position and the visor sprite.
// There is only one listener so all the methods are statics.
class SoundListener
{
    static Sprite m_crosshair;
    static Vector2f m_p;
    
    static this()
    {
        Image crosshairImg = new Image();
        if (!crosshairImg.loadFromFile("Data/crosshair.tga"))
            assert(0);
                
        crosshairImg.createMaskFromColor(Color.WHITE);
        m_crosshair = new Sprite(crosshairImg);
    }
    
    // Adjust position of the listener
    static void setPosition(Vector2f p)
    {
        m_p = Vector2f(p.x - (m_crosshair.getSize().x / 2), p.y - (m_crosshair.getSize().y / 2));
        Listener.setPosition(m_p.x, -2, m_p.y);
        m_crosshair.setPosition(m_p);
    }
    
    static Sprite getSprite()
    {
        return m_crosshair;
    }  
}


// Class encapsulating all data for our car
class Car
{
    Vector2f m_actual;
    Sprite m_sprite;
    Sound m_sound;
    bool reverse;
    Image[2] imgs;
    
    //Constructor with with a fixed size string array of image path, and a string for the sound path 
    this (char[][2] images, char[] soundFilename)
    {
        //load images and create filter
        imgs[0] = new Image(); imgs[1] = new Image();
        if (!imgs[0].loadFromFile(images[0]) ||
            !imgs[1].loadFromFile(images[1]))
            assert(0, "Error while loading car images");
            
        foreach(img; imgs)
            img.createMaskFromColor(Color(97, 68, 43));
        
        m_sprite = new Sprite(imgs[0]);
        
        SoundBuffer buff = new SoundBuffer();
        if (!buff.loadFromFile(soundFilename))
            assert(0, "Error while loading car sound");
        
        //load our sound with loop enabled
        m_sound = new Sound(buff, true);
        m_sound.setAttenuation(.1f);
    }
    
    // Begin the sound play
    void startPlaying()
    {
        m_sound.play();   
    }
    
    // Set the position of the car on the window
    // Used to setup the begin car window and sound location 
    void setPosition(Vector2f p)
    {
        m_sprite.setPosition(p);
        m_actual = Vector2f(p.x - m_sprite.getSize().x / 2, p.y - m_sprite.getSize().y / 2);
        m_sound.setPosition(m_actual.x, 0, m_actual.y);
    }
    
    //Move the car (visual and sound position)
    //If the car leave the screen, we change the sprite image and reverse moving
    void move(float x, float y)
    {
        // if the car is beyond the right screen limit
        if (!reverse && m_actual.x > 820)
        {
            m_sprite.setImage(imgs[1]);
            reverse = true;
        }
        // same as above but for left limit
        else if (reverse && m_actual.x + m_sprite.getSize().x < -20)
        {
            m_sprite.setImage(imgs[0]);
            reverse = false;
        }
        else
            m_actual.x += reverse ? -x : x;
        
        //Calculate sound position (Sound emitter is the middle of the sprite)
        m_sprite.setPosition(m_actual);
        
        Vector2f sp = Vector2f(m_actual.x + m_sprite.getSize().x / 2, m_actual.y + m_sprite.getSize().y / 2);
        m_sound.setPosition(sp.x , 0, sp.y);
    }

    Sprite getSprite()
    {
        return m_sprite;
    }
}







