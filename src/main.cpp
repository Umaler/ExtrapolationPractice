#include <iostream>
#include <vector>
#include <fstream>
#include <gtkmm.h>
#include <cmath>
#include "LinearLSMFunc.hpp"
#include "Loaders.hpp"
#include "Graphics/Plot.hpp"

int main(int argc, char** argv) {
    //auto data = LSM::loadStringFromCSV(std::cin);
    //LSM::LinearFunction func;
    //func.findParameters(data);

    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

    Gtk::Window win;
    win.set_title("Extrapolation");

    LSM::Plot plot;
    //for(auto i : data) {
    //    plot.addPoint(i);
    //}
    plot.addFunction([](double x) -> double {return std::sin(x);});
    win.add(plot);
    plot.show();

    return app->run(win);
}
