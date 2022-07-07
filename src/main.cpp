#include <iostream>
#include <Vector.h>
#include <VertexBuffer.h>
#include <Application.h>
int main(int argc, const char * argv[]) {
    Application a;
    if(!a.initialize("Straja", 800, 600))
        return -1;
    a.run();
    return 0;
}
