


#include "../shell/api.h"
#include "../shell/lib/builtins.h"


int main(int argc, char **argv) {
    World::Ptr world(new World(builtins, {}));
    set_world(world);
    Interpreter(world).interactive_loop(std::cin, std::cout);
}

