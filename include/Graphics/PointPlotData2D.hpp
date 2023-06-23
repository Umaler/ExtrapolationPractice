#pragma once
#include <gtkmm-plplot/plotdata2d.h>

namespace LSM {

class PointPlotData2D : public Gtk::PLplot::PlotData2D {
public:
    using Gtk::PLplot::PlotData2D::PlotData2D;

    void draw_plot_data(const Cairo::RefPtr<Cairo::Context> &cr, plstream *pls) override;

protected:
    const char* pointMarker = "\u00B7";

};

}
