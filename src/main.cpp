#include <iostream>
#include <vector>
#include <fstream>
#include <gtkmm.h>
#include <cmath>
#include "LinearLSMFunc.hpp"
#include "Loaders.hpp"
#include "Graphics/Window.hpp"

int main(int argc, char** argv) {

    auto app = Gtk::Application::create(argc, argv);

    LSM::MainWindow win;

    return app->run(win);
}
