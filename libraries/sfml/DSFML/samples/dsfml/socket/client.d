module client;

import dsfml.system.all;
import dsfml.network.all;

version (Tango)
{
    import tango.io.Console;
    import tango.io.Stdout;
}   
else
{
    import std.stdio;
}


void main()
{
    //The TCP socket
    SocketTCP client = new SocketTCP();
    //Try to connect to server (on localhost for this sample)
    if (!client.connect(9000, IPAddress.LOCALHOST))
    {
        assert (0, "Error while connecting to server. You need to start the server first.");
    }
    
    display("Connected to server."w);
    
    //Prepare a packet with a string
    Packet p = new Packet();
    p.set("Hello from the client !"w);
    if (client.send(p) != SocketStatus.DONE) // Assert on error
        assert(0);
        
    //Clear the packet
    p.clear();
    
    //Wait for the response of the server and display it
    if (client.receive(p) != SocketStatus.DONE)
        assert(0);
    wchar[] c;
    p.get(c);
    display("Packet received : "w ~ c);
    read();
}

void display(wchar[] c)
{
    version (Tango)
    {
        Stdout(c).newline;
    }
    else
    {
        writefln("%s", c);
    }
}

void read()
{
    version (Tango)
    {
        Cin.get();
    }
    else
    {
        readln();
    }
}
