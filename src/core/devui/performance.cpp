#include "performance.hpp"
#include <core/time.hpp>
#include <core/engine.hpp>
#include <imgui.h>

namespace singularity {

bool Performance::vsync;

void Performance::draw() {
    if (!Engine::getInstance()) {
        Log::error() << "No engine instance!";
        return;
    }

    static float smoothedDeltaTime = 0.0f;
    static float accumulationTimer = 0.0f;
    static int frameCounter = 0;

    accumulationTimer += Time::deltaTime;
    frameCounter++;

    if (accumulationTimer >= 0.25f) {
        smoothedDeltaTime = accumulationTimer / frameCounter;
        accumulationTimer = 0.0f;
        frameCounter = 0;
    }

    ImGui::Begin("Performance");

    ImGui::Text("%.1f ms | %.1f FPS", smoothedDeltaTime * 1000.0f, 1.0f / smoothedDeltaTime);
    if (ImGui::Checkbox("VSync", &vsync)) {
        Engine::getInstance()->getWindow().setVSync(vsync);
    }

    ImGui::End();
}

}