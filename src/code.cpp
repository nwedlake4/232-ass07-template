// ============================================================
// CSCI 232 Assignment 07 – Shapes, Polymorphism and Insertion Sort
// Student Implementation
// ============================================================

#include "code.hpp"
#include <iostream>
#include <iterator>
#include <numbers>

// Uncomment the author block below and fill in your name:

std::string AUTHOR_NAME       = "Nolan Wedlake";
std::string AUTHOR_AUTHORSHIP = "I acknowledge that I have worked on this "
"assignment independently, except where explicitly noted and referenced. "
"Any collaboration or use of external resources has been properly cited. "
"I am fully aware of the consequences of academic dishonesty and agree "
"to abide by the university's academic integrity policy.";

// ============================================================
// PART 1: Shape, Circle, Square, Rectangle
// ============================================================

/// True if THIS shape has a strictly smaller area() than other.
bool Shape::operator<(const Shape &other) const
{
    if (this->area() < other.area()) {
        return true;
    }
    return false;
}

/// Constructor with a member initializer list.
Circle::Circle(double newRadius) : radius (newRadius) {}

/// pi * radius * radius, use std::numbers::pi
double Circle::area() const
{
    return std::numbers::pi * this->radius * this->radius;
}

/// Return exactly "Circle".
std::string Circle::name() const
{
    return "Circle";
}

Square::Square(double newSide) : side (newSide) {}

/// side * side
double Square::area() const
{
    return side * side;
}

/// Return exactly "Square".
std::string Square::name() const
{
    return "Square";
}

Rectangle::Rectangle(double newWidth, double newHeight) : width (newWidth) , height (newHeight){}

/// width * height
double Rectangle::area() const
{
    return width * height;
}

/// Return exactly "Rectangle".
std::string Rectangle::name() const
{
    return "Rectangle";
}

// ============================================================
// PART 2: ShapeList
// ============================================================

/// RAII: delete EVERY shape, then clear the list.
ShapeList::~ShapeList()
{
    for (Shape* x : data) {
        delete x;
    }
    data.clear();
}

/// Append at the end. Return -1 if newShapePtr is nullptr, 0 on success.
int ShapeList::addShape(Shape *newShapePtr)
{
    if (newShapePtr == nullptr){
        return -1;
    }
    data.push_back(newShapePtr);
    return 0;
}

/// Delete the first shape and remove it from the list.
/// Return false if the list is empty, true otherwise.
bool ShapeList::removeFirst()
{
    if (data.empty()){
        return false;
    }
    data.pop_front();
    return true;
}

/// Number of shapes in the list.
int ShapeList::length() const
{
    return data.size();
}

/// Sum of area() of all shapes (0.0 if empty).
double ShapeList::totalArea() const
{
    if (data.empty()) return 0.0;
    
    double total = 0;
    for (Shape* x : data){
        total += x->area();
    }
    return total;
}

/// One line per shape: name, one space, area. Return the number of shapes.
int ShapeList::printList() const
{
    for (Shape* x : data){
        std::cout << x->name() << " " << x->area() << "\n";
    }
    return data.size();
}

/// area() of the shape at index, or std::nullopt if index is out of range.
/// Hint: std::next(data.begin(), index)
std::optional<double> ShapeList::areaAt(int index) const
{
    if (data.size() <= index) return std::nullopt;
    auto x = std::next(data.begin(), index);
    return std::optional<double>((*x)->area());
}

/// name() of the shape at index, or std::nullopt if index is out of range.
std::optional<std::string> ShapeList::nameAt(int index) const
{
    if (data.size() <= index) return std::nullopt;
    auto x = std::next(data.begin(), index);
    return std::optional<std::string>((*x)->name());
}

/// Your own STABLE insertion sort, smallest area first.
/// Compare shapes with operator< (dereference the pointers!).
/// Hint: for every element, walk left while the previous shape is bigger,
/// then move the element there with data.splice(...).
void ShapeList::insertionSort()
{
    auto key = std::next(data.begin());

    while (key != data.end()) {
        auto keyAfter = std::next(key);

        auto position = key;
        while (position != data.begin()) {
            auto previous = std::prev(position);

            // Move key left only if key is strictly smaller than previous.
            // Equal areas remain in their original relative positions.
            if (!(**position < **previous)) {
                break;
            }

            position = previous;
        }

        if (position != key) {
            data.splice(position, data, key);
        }

        key = keyAfter;
    }
}

/// True if no shape is smaller than the one before it.
bool ShapeList::isSorted() const
{
    auto previous = data.begin();

    if (previous == data.end()) {
        return true;
    }

    
    auto current = std::next(previous);
    while (current != data.end()) {
        // Descending or unsorted if current is smaller than previous.
        if (**current < **previous) {
            return false;
        }

        previous = current;
        current = std::next(current);
    }

    return true;
}
