#pragma once

#include <gtkmm/drawingarea.h>
#include <vector>
#include <memory>
#include <functional>

namespace LSM {

class Point;

class Plot : public Gtk::DrawingArea {
public:

    Plot();

    void addFunction(std::function<double(double)>);

    void addPoint(Point point);

    void update();

    void setMaxX(double newMaxX);
    double getMaxX() const;

    ~Plot();

protected:

    void drawFunction(std::function<double(double)> func, const Cairo::RefPtr<Cairo::Context>& cr);
    void drawPoint(Point point, const Cairo::RefPtr<Cairo::Context>& cr);

    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

    void setPixel(Glib::RefPtr<Gdk::Pixbuf> imageptr, int x, int y, Gdk::RGBA color);



    double maxX = 10;

    std::vector<Point> points;
    std::vector<std::function<double(double)>> functions;

};

}
