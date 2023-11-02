#include "main.h"

namespace Tasks {
    static void loop() {
        for (;;) {
            //dummy
        }
    }

    void init() {
        //dummy
    }

}

extern "C" {
    void SystemStart() {
        Tasks::init();
        Tasks::loop();
    }
}
