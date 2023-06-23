#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <glibmm/refptr.h>
#include <gtkmm/button.h>
#include <gtkmm-plplot.h>
#include <gtkmm/filechooserdialog.h>
#include <vector>
#include <memory>

#include "Graphics/PointPlotData2D.hpp"
#include "LSMFunction.hpp"

namespace LSM {

class MainWindow : public Gtk::Window {
public:
    MainWindow();

    virtual ~MainWindow();

private:
    void on_button_file_clicked();
    void on_file_dialog_response(int response_id, Gtk::FileChooserDialog* dialog);

    Gtk::Grid grid;

    Gtk::Button chooseFileButton;

    std::unique_ptr<Gtk::PLplot::PlotData2D> dataPoints;
    std::unique_ptr<Gtk::PLplot::PlotData2D> funcPoints;

    Gtk::PLplot::Canvas canvas;
    Gtk::PLplot::Plot2D plot;

};

}
