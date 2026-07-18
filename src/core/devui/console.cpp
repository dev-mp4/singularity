#include "console.hpp"
#include <vector>
#include <logger/logger.hpp>
#include <imgui.h>

namespace singularity {

void Console::draw() {
    const std::vector<LogEntry>& history = LogStream::getHistory();

    ImGui::Begin("Console");

    if (ImGui::Button("Clear logs")) LogStream::clearHistory();

    ImGui::Separator();

    ImGui::BeginChild("ScrollingRegion", ImVec2(0, 0), ImGuiChildFlags_None, ImGuiWindowFlags_HorizontalScrollbar);

    for (const auto& entry : history) {
        bool colorPushed = false;

        if (std::strcmp(entry.level, "WARN") == 0) {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.79f, 0.0f, 1.0f));
            colorPushed = true;
        } 
        else if (std::strcmp(entry.level, "ERROR") == 0) {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.24f, 0.24f, 1.0f));
            colorPushed = true;
        }
        else if (std::strcmp(entry.level, "INFO") == 0) {
            colorPushed = false;
        }

        // Print the log line
        ImGui::TextUnformatted(entry.text.c_str());

        if (colorPushed) {
            ImGui::PopStyleColor();
        }
    }

    if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) {
        ImGui::SetScrollHereY(1.0f);
    }

    ImGui::EndChild();
    ImGui::End();
}

}