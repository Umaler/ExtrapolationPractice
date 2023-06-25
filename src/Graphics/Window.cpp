#include "Graphics/Window.hpp"
#include "Graphics/PointPlotData2D.hpp"
#include "Loaders.hpp"
#include "LinearLSMFunc.hpp"
#include <fstream>
#include <sstream>
#include <numeric>

namespace LSM {

MainWindow::MainWindow() :
    box(Gtk::ORIENTATION_VERTICAL),
    funcBox(Gtk::ORIENTATION_VERTICAL),
    chooseFileButton("Выберите файл"),
    xChooser(Gtk::Adjustment::create(0.0, -1000, 1000, 0.1, 5)),
    setsChooser(Gtk::Adjustment::create(0.0, 1, 0, 1, 1)),
    func(std::make_unique<LSM::LinearFunction>()),
    canvas(),
    plot("X", "Y")
{
    set_default_size(720, 580);
    set_title("Extrapolation");
    canvas.set_hexpand(true);
    canvas.set_vexpand(true);

    canvas.add_plot(plot);
    plot.hide_legend();

    funcResultsBuffer = Gtk::TextBuffer::create();
    funcResults.set_buffer(funcResultsBuffer);
    funcResults.set_editable(false);

    funcCoefsBuffer = Gtk::TextBuffer::create();
    funcCoefs.set_buffer(funcCoefsBuffer);
    funcCoefs.set_editable(false);

    grid.attach(chooseFileButton, 0, 0);
    funcFrame.set_label("Функция:");
    funcBox.add(funcResults);
    funcBox.add(xChooser);
    funcFrame.add(funcBox);
    box.add(funcFrame);
    coefFrame.set_label("Коэффициенты:");
    coefFrame.add(funcCoefs);
    box.add(coefFrame);
    setsFrame.set_label("Номер набора:");
    setsFrame.add(setsChooser);
    box.add(setsFrame);
    grid.attach(box, 0, 1);
    grid.attach(canvas, 1, 0, 1, 2);

    add(grid);

    xChooser.set_digits(2);
    xChooser.signal_value_changed().connect( sigc::mem_fun(*this, &MainWindow::on_xChooser_digits_changed) );
    chooseFileButton.signal_clicked().connect( sigc::mem_fun(*this, &MainWindow::on_button_file_clicked) );
    setsChooser.signal_value_changed().connect( sigc::mem_fun(*this, &MainWindow::on_setsChooser_digits_changed) );

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

    dialog->show();
}

void MainWindow::on_file_dialog_response(int response_id, Gtk::FileChooserDialog* dialog) {
    switch(response_id) {
        case Gtk::ResponseType::RESPONSE_OK: {
            std::ifstream file(dialog->get_file()->get_path());
            sets = LSM::loadSetFromCSV(file);

            auto adj = setsChooser.get_adjustment();
            adj->set_upper(sets.size());
            setsChooser.set_adjustment(adj);

            on_setsChooser_digits_changed();

            break;
        }
        case Gtk::ResponseType::RESPONSE_CANCEL:
            break;
        default:
            break;
    }
    delete dialog;
}

void MainWindow::on_xChooser_digits_changed() {
    if(!dataPoints)
        return;
    std::stringstream ss;
    ss << "y = " << (*func)(xChooser.get_value());
    funcResultsBuffer->set_text(ss.str());
}

void MainWindow::on_setsChooser_digits_changed() {
    if(sets.size() == 0)
        return;

    const size_t setN = setsChooser.get_value() - 1;

    std::vector<double> x;
    std::vector<double> y;

    if(dataPoints)
        plot.remove_data(*dataPoints);
    for(auto i : sets[setN]) {
        x.push_back(i.x);
        y.push_back(i.y);
    }
    dataPoints.reset(new PointPlotData2D(x, y, Gdk::RGBA("blue"), Gtk::PLplot::LineStyle::CONTINUOUS, 3));
    plot.add_data(*dataPoints);

    func->findParameters(sets[setN]);
    std::stringstream ss;
    func->printCoef(ss);
    funcCoefsBuffer->set_text(ss.str());

    x.clear();
    y.clear();
    const size_t slices = sets[setN].size() + 10;
    for(size_t i = 0; i < slices; i++) {
        x.push_back(i);
        y.push_back((*func)(i));
    }

    if(funcPoints)
        plot.remove_data(*funcPoints);
    funcPoints.reset(new Gtk::PLplot::PlotData2D(x, y, Gdk::RGBA("red")));
    plot.add_data(*funcPoints);

    on_xChooser_digits_changed();
}

MainWindow::~MainWindow() = default;

}
