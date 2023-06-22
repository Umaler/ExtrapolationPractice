#include "Graphics/Plot.hpp"
#include "LSMFunction.hpp"

#include <functional>
#include <type_traits>
#include <stdexcept>
#include <gdkmm/general.h>

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

void Plot::drawFunction(std::function<double(double)> function, const Cairo::RefPtr<Cairo::Context>& cr) {
    auto pb = Gdk::Pixbuf::create(Gdk::COLORSPACE_RGB, true, 8, get_allocated_width() + 1, get_allocated_height() + 1);

    double delta = maxX / static_cast<double>(get_allocated_width());
    for(int i = 0; i < get_allocated_width(); i++) {
        setPixel(pb, i, get_allocated_height() - function(static_cast<double>(i) * delta) / delta, Gdk::RGBA("#F00"));
    }

    Gdk::Cairo::set_source_pixbuf(cr, pb);
    cr->paint();
}

void Plot::drawPoint(Point point, const Cairo::RefPtr<Cairo::Context>& cr) {
    auto pb = Gdk::Pixbuf::create(Gdk::COLORSPACE_RGB, true, 8, get_allocated_width(), get_allocated_height());

    setPixel(pb, point.x, get_allocated_width() - point.y, Gdk::RGBA("#0F0"));

    Gdk::Cairo::set_source_pixbuf(cr, pb);
    cr->paint();
}

bool Plot::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    for(auto i : functions) {
        drawFunction(i, cr);
    }
    for(auto i : points) {
        drawPoint(i, cr);
    }
    return true;
}

void Plot::setPixel(Glib::RefPtr<Gdk::Pixbuf> imageptr, int x, int y, Gdk::RGBA color) {
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

Plot::~Plot() = default;

}
