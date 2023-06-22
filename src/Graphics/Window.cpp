#include "Graphics/Window.hpp"
#include <valarray>

namespace LSM {

MainWindow::MainWindow() : canvas() {
    set_default_size(720, 580);
    Gdk::Geometry geometry;
    geometry.min_aspect = geometry.max_aspect = double(720)/double(580);
    set_geometry_hints(*this, geometry, Gdk::HINT_ASPECT);
    set_title("Plot test");
    canvas.set_hexpand(true);
    canvas.set_vexpand(true);

    int npts = 73;
    std::valarray<double> x_va(npts), y_va(npts);
    double xmin = 0;
    double xmax = 60.0 * 60.0 * 24.0; // Number of seconds in a day
    double ymin = 10.0;
    double ymax = 20.0;

    for (int i = 0 ; i < npts ; i++) {
        x_va[i] = xmax * ( (double) i / (double) npts );
        y_va[i] = 15.0 - 5.0 * cos( 2 * M_PI * ( (double) i / (double) npts ) );
    }
    auto plot_data = Gtk::manage(new Gtk::PLplot::PlotData2D(x_va, y_va, Gdk::RGBA("blue"), Gtk::PLplot::LineStyle::LONG_DASH_LONG_GAP, 5.0));
    plot = Gtk::manage(new Gtk::PLplot::Plot2D(*plot_data));
    plot->set_axis_time_format_x("%H:%M");
    canvas.add_plot(*plot);
    plot->hide_legend();

    add(canvas);
    show_all();
}

MainWindow::~MainWindow() = default;

}
