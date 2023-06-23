#include "Graphics/PointPlotData2D.hpp"

#include <gtkmm-plplot/exception.h>
#include <gtkmm-plplot/utils.h>
#include <plstream.h>

namespace LSM {

void PointPlotData2D::draw_plot_data(const Cairo::RefPtr<Cairo::Context> &cr, plstream *pls) {
    using namespace Gtk::PLplot;

    if (!is_showing())
        return;

    double *x_pl = &x[0], *y_pl = &y[0];

    change_plstream_color(pls, color);
    pls->lsty(line_style);
    pls->schr(0, line_width);
    pls->string(x.size(), x_pl, y_pl, pointMarker);

    // plot the symbols if requested
    if (!symbol.empty()) {
        change_plstream_color(pls, symbol_color);
        pls->schr(0, symbol_scale_factor);
        pls->string(x.size(), x_pl, y_pl, symbol.c_str());
    }
}

}
