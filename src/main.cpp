#include <iostream>
#include <Engine.h>
int main(int argc, const char * argv[]) {
    Engine e;
    if(!e.initialize("Straja",1600,1300))
        return -1;
    e.run();
    return 0;
}
