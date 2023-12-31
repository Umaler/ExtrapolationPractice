#include <glibmm/refptr.h>
#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm/button.h>
#include <gtkmm-plplot.h>
#include <gtkmm/filechooserdialog.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/textview.h>
#include <gtkmm/textbuffer.h>
#include <gtkmm/frame.h>
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
    void on_xChooser_digits_changed();
    void on_setsChooser_digits_changed();

    Gtk::Grid grid;
    Gtk::Box box;
    Gtk::Frame funcFrame;
    Gtk::Box funcBox;
    Gtk::Frame coefFrame;
    Gtk::Frame setsFrame;

    Gtk::Button chooseFileButton;
    Gtk::SpinButton xChooser;
    Gtk::TextView funcResults;
    Glib::RefPtr<Gtk::TextBuffer> funcResultsBuffer;
    Gtk::TextView funcCoefs;
    Glib::RefPtr<Gtk::TextBuffer> funcCoefsBuffer;
    Gtk::SpinButton setsChooser;

    std::unique_ptr<LSM::Function> func;
    std::unique_ptr<Gtk::PLplot::PlotData2D> dataPoints;
    std::unique_ptr<Gtk::PLplot::PlotData2D> funcPoints;

    std::vector<std::vector<LSM::Point>> sets;

    Gtk::PLplot::Canvas canvas;
    Gtk::PLplot::Plot2D plot;

};

}
