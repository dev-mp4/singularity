#include "developerui.hpp"
#include <core/devui/performance.hpp>
#include <core/devui/console.hpp>

namespace singularity {

void DeveloperUI::draw() {
    Console::draw();
    Performance::draw();
}

}