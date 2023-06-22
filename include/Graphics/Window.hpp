#include <gtkmm/window.h>
#include <gtkmm-plplot.h>

namespace LSM {

class MainWindow : public Gtk::Window {
public:
    MainWindow();

    virtual ~MainWindow();

private:
    Gtk::PLplot::Canvas canvas;
    Gtk::PLplot::Plot2D *plot = nullptr;

};

}
