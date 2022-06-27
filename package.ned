package section1;

@license(LGPL);
//
// TODO documentation
//
network Network
{
    parameters:
        int N = default(2);
        double delay =default(0);
        int window = default(3);
    submodules:
        node0[N]: Node0;
        coordinator: Coordinator;
    connections:
        for i = 0..N-1{
            coordinator.outs++ --> node0[i].innode0++;
            node0[i+1].out-->node0[i].innode0++ if i%2 == 0;
            node0[i-1].out --> node0[i].innode0++ if i%2 ==1;
            
        }
       
}

