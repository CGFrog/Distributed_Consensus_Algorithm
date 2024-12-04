# distributed_consensus
This project is an introductory for me into many concepts such as multi-threading and developing distributed systems.
![Global Consensus 2](https://github.com/user-attachments/assets/9f81687e-cde7-4374-9b3d-308ff5921434)
This simulation is the ideal graph for achieving consensus. All agents (nodes), iterate simultaneously, and there are no byzantine agents (nodes that will give inaccurate numbers). 

This project taught me a lot about threads. Beforehand I knew what a thread did but I never considered what complications could arise. Specifically, I had a for-loop initialize each thread into an array. The problem was that each thread would be several calculations ahead of the following thread meaning that the global average would not remain the same and shift. Another issue is that when multiple threads try to access the same resource, this can cause unintended behavior requiring mutex. When a thread creates mutex it is essentially a message to other threads saying “Hey, hold on a second, I need this.”

Creating the cyclic shape of the graph was also fun. It wasn’t really a challenge, but it was neat to see how high-school trigonometry truly can come in handy in computer science. I hope to explore applications that intersect geometry and computer science more in the future.


![Global Consensus](https://github.com/user-attachments/assets/f7cc9aec-b4e6-4a92-a3c3-8f26dd524b82)
