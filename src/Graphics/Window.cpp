#include "Graphics/Window.hpp"
#include "Graphics/PointPlotData2D.hpp"
#include "Loaders.hpp"
#include "LinearLSMFunc.hpp"
#include <fstream>

namespace LSM {

MainWindow::MainWindow() :
    chooseFileButton("Выберите файл"),
    canvas(),
    plot("X", "Y")
{
    set_default_size(720, 580);
    set_title("Plot test");
    canvas.set_hexpand(true);
    canvas.set_vexpand(true);

    canvas.add_plot(plot);
    plot.hide_legend();

    grid.attach(chooseFileButton, 0, 0);
    grid.attach(canvas, 1, 0);

    add(grid);

    chooseFileButton.signal_clicked().connect( sigc::mem_fun(*this, &MainWindow::on_button_file_clicked) );

    show_all();
}

void MainWindow::on_button_file_clicked() {
    auto dialog = new Gtk::FileChooserDialog("Выберите файл");
    dialog->set_transient_for(*this);
    dialog->set_modal(true);
    dialog->signal_response().connect(sigc::bind(sigc::mem_fun(*this, &MainWindow::on_file_dialog_response), dialog));

    dialog->add_button("_Cancel", Gtk::ResponseType::RESPONSE_CANCEL);
    dialog->add_button("_Open", Gtk::ResponseType::RESPONSE_OK);

    auto filter_text = Gtk::FileFilter::create();
    filter_text->set_name("Text files");
    filter_text->add_mime_type("text/plain");
    dialog->add_filter(filter_text);

    auto filter_csv = Gtk::FileFilter::create();
    filter_csv->set_name("CSV files");
    filter_csv->add_mime_type("text/csv");
    dialog->add_filter(filter_csv);

    auto filter_any = Gtk::FileFilter::create();
    filter_any->set_name("Any files");
    filter_any->add_pattern("*");
    dialog->add_filter(filter_any);

    dialog->show();
}

void MainWindow::on_file_dialog_response(int response_id, Gtk::FileChooserDialog* dialog) {
    switch(response_id) {
        case Gtk::ResponseType::RESPONSE_OK: {
            std::vector<double> x;
            std::vector<double> y;

            std::ifstream file(dialog->get_file()->get_path());
            auto arr = (LSM::loadStringFromCSV(file));
            for(auto i : arr) {
                x.push_back(i.x);
                y.push_back(i.y);
            }
            if(dataPoints)
                plot.remove_data(*dataPoints);
            dataPoints.reset(new PointPlotData2D(x, y, Gdk::RGBA("blue"), Gtk::PLplot::LineStyle::CONTINUOUS, 3));
            plot.add_data(*dataPoints);

            LSM::LinearFunction func;
            func.findParameters(arr);

            const int slices = x.size() + 20;

            x.clear();
            y.clear();
            for(int i = 0; i < slices; i++) {
                x.push_back(i);
                y.push_back(func(i));
            }
            if(funcPoints)
                plot.remove_data(*funcPoints);
            funcPoints.reset(new Gtk::PLplot::PlotData2D(x, y, Gdk::RGBA("red")));
            plot.add_data(*funcPoints);
            break;
        }
        case Gtk::ResponseType::RESPONSE_CANCEL:
            break;
        default:
            break;
    }
    delete dialog;
}

MainWindow::~MainWindow() = default;

}
