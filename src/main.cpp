// @sonar.ignore.file
#include "CApp.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
    spdlog::set_pattern(R"(%^[%T] [%l] %v%$)");
    auto console = spdlog::stdout_color_mt("console");
    spdlog::set_default_logger(console);

    CApp theApp;
    return theApp.OnExecute();
}
