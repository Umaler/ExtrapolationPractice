#include "Graphics/Plot.hpp"
#include "LSMFunction.hpp"

#include <iostream>
#include <functional>
#include <type_traits>
#include <stdexcept>
#include <gdkmm/general.h>
#include <glibmm.h>

namespace LSM {

Plot::Plot() = default;

void Plot::setMaxX(double newMaxX) {
    maxX = newMaxX;
}

double Plot::getMaxX() const {
    return maxX;
}

void Plot::addFunction(std::function<double(double)> function) {
    functions.push_back(function);
}

void Plot::addPoint(Point point) {
    points.push_back(point);
}

void Plot::update() {
    queue_draw();
}

void Plot::setCornerPosition(Point point) {
    LDCornerPosition = point;
}

Point Plot::getCornerPosition() const {
    return LDCornerPosition;
}

void Plot::drawFunction(std::function<double(double)> function, const Cairo::RefPtr<Cairo::Context>& cr) {
    auto pb = Gdk::Pixbuf::create(Gdk::COLORSPACE_RGB, true, 8, get_allocated_width() + 1, get_allocated_height() + 1);

    for(int i = 0; i < get_allocated_width(); i++) {
        Point realPosition = displayToReal({static_cast<double>(i), 0});
        Point drawPosition = {static_cast<double>(i), realToDisplay({0, function(realPosition.x)}).y};
        setPixel(pb, drawPosition, Gdk::RGBA("#F00"));
    }

    Gdk::Cairo::set_source_pixbuf(cr, pb);
    cr->paint();
}

void Plot::drawPoint(Point point, const Cairo::RefPtr<Cairo::Context>& cr) {
    auto pb = Gdk::Pixbuf::create(Gdk::COLORSPACE_RGB, true, 8, get_allocated_width(), get_allocated_height());

    setPixel(pb, realToDisplay(point), Gdk::RGBA("#0F0"));

    Gdk::Cairo::set_source_pixbuf(cr, pb);
    cr->paint();
}

bool Plot::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    cr->save();
        for(auto i : functions) {
            drawFunction(i, cr);
        }
        for(auto i : points) {
            drawPoint(i, cr);
        }
    cr->restore();

    cr->save();
        cr->set_line_width(funcLineWidth);

        cr->stroke();
    cr->restore();

    return true;
}

void Plot::setPixel(Glib::RefPtr<Gdk::Pixbuf> imageptr, Point point, Gdk::RGBA color) {
    int x = point.x;
    int y = point.y;
    if(x < 0 || x > imageptr->property_width() ||
       y < 0 || y > imageptr->property_height()
    ) {
        return;
    }

    Gdk::Pixbuf & image = *imageptr.operator->(); // just for convenience

    int offset = y*image.get_rowstride() + x*image.get_n_channels(); // 2 dimensional array; each cell represents 1 pixel's color channel
    guchar* pixel = &image.get_pixels()[ offset ]; // get pixel pointer

    pixel[0] = color.get_red_u();
    pixel[1] = color.get_green_u();
    pixel[2] = color.get_blue_u();
    pixel[3] = color.get_alpha_u();
}

Point Plot::displayToReal(Point point) const {
    point.y = get_allocated_height() - point.y + LDCornerPosition.y;

    double xPerPixel = maxX / static_cast<double>(get_allocated_width());
    point.x *= xPerPixel;
    point.y *= xPerPixel;

    point.x += LDCornerPosition.x;

    return point;
}

Point Plot::realToDisplay(Point point) const {
    point.y -= LDCornerPosition.y;

    double xPerPixel = maxX / static_cast<double>(get_allocated_width());
    point.x /= xPerPixel;
    point.y /= xPerPixel;

    point.x -= LDCornerPosition.x;
    point.y = get_allocated_height() - point.y;

    return point;
}

Plot::~Plot() = default;

}
