#include <iostream>
#include <Engine.h>
int main(int argc, const char * argv[]) {
    Engine e;
    if(!e.initialize("Straja",800,600))
        return -1;
    e.run();
    return 0;
}
