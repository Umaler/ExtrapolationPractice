#pragma once

#include <gtkmm/drawingarea.h>
#include <vector>
#include <memory>
#include <functional>

#include "LSMFunction.hpp"

namespace LSM {

class Plot : public Gtk::DrawingArea {
public:

    Plot();

    void addFunction(std::function<double(double)>);

    void addPoint(Point point);

    void update();

    void setCornerPosition(Point point);    //set "viewport" position.
    Point getCornerPosition() const;

    void setMaxX(double newMaxX);
    double getMaxX() const;

    ~Plot();

protected:

    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

    void drawFunction(std::function<double(double)> func, const Cairo::RefPtr<Cairo::Context>& cr);
    void drawPoint(Point point, const Cairo::RefPtr<Cairo::Context>& cr);
    void setPixel(Glib::RefPtr<Gdk::Pixbuf> imageptr, Point point, Gdk::RGBA color);

    Point realToDisplay(Point point) const; //transform coordinates from "real" to display coordinates
    Point displayToReal(Point point) const;



    double funcLineWidth = 10.0;
    Point LDCornerPosition {0.0, -1.0};    //Left Down Corner
    double maxX = 6.28;
    std::vector<Point> points;
    std::vector<std::function<double(double)>> functions;

};

}
