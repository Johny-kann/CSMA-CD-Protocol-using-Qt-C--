# CSMA/CD 1-presistent Protocol
Event Driven simulation of CSMA/CD protocol in computer networks

1-persistant CSMA/CD is transmission method in the data link layer that senses Collision Detection in the channel medium. The application uses event driven simulation to demonstrate the transmission between nodes.
Every frame is constructed using bits with headers specifying source and destination.

The operations involves
- The nodes will sense the network before the data is transmitted to the destination. 
- If network is free or idle, the source device or node will send the data to the destination device or node. 
- This will reduce the collision in the channel but these method will not eliminate the collision in the channel.
- All the nodes has three states Listening state (listens to all bits), Transmission state(transmits the bits) and Receiving state(receives the bit once the nodes configures that the frames in the channel belong to itself)

Simulated components for the CSMA/CD protocol
- Controller ( controls the overall simulation )
- Timer ( universal timer that aids the bit wise transmission in the medium )
- Station ( each node is defined as a station )
- Buffer ( Buffer to input and output in every station )
- Frame ( Frames that fill the input and the output buffer )

Programming Language : C++ / Qt framework with MVC design pattern
