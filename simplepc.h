#ifndef _SIMPLEPC_H_
    #include <bits/stdc++.h>
    
    int sc_memoryInit();
    int sc_memorySet (int address, int value);
    int sc_memoryGet (int address, int& value);
    int sc_memorySave (string filename);
    int sc_memoryLoad (string filename);
#endif 