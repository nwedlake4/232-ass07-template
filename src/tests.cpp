#ifndef UNITY_H
#define UNITY_H
#include "unity.h"
#endif

#include "code.hpp"
#include <cmath>
#include <iostream>
#include <numbers>

// ============================================================
// PART 1 Tests: Shapes
// ============================================================

/// Create Circle(1), Square(2), Rectangle(2, 3).
/// Verify area() is pi, 4 and 6 (compare doubles with std::fabs(a - b) < 1e-9).
void test_shape_areas(void)
{
    Circle circle = Circle(1);
    Square square = Square(2);
    Rectangle rectangle = Rectangle(2, 3);
    TEST_ASSERT_TRUE_MESSAGE(std::fabs(circle.area() - std::numbers::pi) < 1e-9, "area is not pi");
    TEST_ASSERT_TRUE_MESSAGE(std::fabs(square.area() - 4) < 1e-9, "area is not 4");
    TEST_ASSERT_TRUE_MESSAGE(std::fabs(rectangle.area() - 6) < 1e-9, "area is not 6");
    
}

/// Create an array of three Shape* (a Circle, a Square, a Rectangle) with new.
/// Verify name() through the BASE pointer gives "Circle", "Square", "Rectangle".
/// Delete the shapes through the base pointers.
void test_shape_names_through_base_pointer(void)
{
    Shape* a[] = {new Circle(1), new Square(2), new Rectangle(2, 3)};
    TEST_ASSERT_TRUE_MESSAGE(a[0]->name() == "Circle", "Name does not equal Circle");
    TEST_ASSERT_TRUE_MESSAGE(a[1]->name() == "Square", "Name does not equal Square");
    TEST_ASSERT_TRUE_MESSAGE(a[2]->name() == "Rectangle", "Name does not equal Rectangle");

}

/// Create Square(1) and Square(2). Take two const Shape& to them.
/// Verify small < big is true, big < small is false, small < small is false.
void test_shape_operator_less(void)
{
    Square square(1);
    Square square2(2);

    const Shape& small = square;
    const Shape& big = square2;
    TEST_ASSERT_TRUE_MESSAGE((small < big) == true, "small not less than big");
    TEST_ASSERT_TRUE_MESSAGE((big < small) == false, "big not greater than small");
    TEST_ASSERT_TRUE_MESSAGE((small < small) == false, "small is less than small");
}

/// Create Square(2) and Rectangle(1, 4): both have area 4.
/// Verify that NEITHER a < b NOR b < a is true.
void test_shape_equal_area_not_less(void)
{
    Square square = Square(2);
    Rectangle rectangle = Rectangle(1, 4);
    TEST_ASSERT_TRUE_MESSAGE((square.area()) == 4, "square area does not equal 4");
    TEST_ASSERT_TRUE_MESSAGE((rectangle.area()) == 4, "rectangle area does not equal 4");
    TEST_ASSERT_TRUE_MESSAGE((square < rectangle) != true, "square < rectangle equals true");
    TEST_ASSERT_TRUE_MESSAGE((rectangle < square) != true, "rectangle < square equals true");

}

// ============================================================
// PART 2 Tests: ShapeList
// ============================================================

/// Create a ShapeList. Add new Circle(1) and new Square(2) with addShape.
/// Verify both calls return 0 and length() is 2.
/// (Do NOT delete the shapes yourself: the list owns them.)
void test_list_add_and_length(void)
{
    ShapeList list;
    
    TEST_ASSERT_TRUE_MESSAGE(list.addShape(new Circle(1)) == 0, "does not return 0");
    TEST_ASSERT_TRUE_MESSAGE(list.addShape(new Square(2)) == 0, "does not return 0");
    TEST_ASSERT_TRUE_MESSAGE(list.length() == 2, "length is not 2");
}

/// Create a ShapeList. Call addShape(nullptr).
/// Verify it returns -1 and length() stays 0.
void test_list_add_null_guard(void)
{
    ShapeList list;
    
    TEST_ASSERT_TRUE_MESSAGE(list.addShape(nullptr) == -1, "does not return -1");
    TEST_ASSERT_TRUE_MESSAGE(list.length() == 0, "length not 0");
}

/// Add Rectangle(2, 5) (area 10), Circle(1) (area 3.14), Square(2) (area 4).
/// Call insertionSort(). Verify nameAt(0), nameAt(1), nameAt(2) are
/// "Circle", "Square", "Rectangle" and isSorted() is true.
void test_insertionSort_orders_by_area(void)
{
    ShapeList list;

    list.addShape(new Rectangle(2, 5));
    list.addShape(new Circle(1));
    list.addShape(new Square(2));
    list.insertionSort();

    TEST_ASSERT_TRUE_MESSAGE(list.nameAt(0) == "Circle", "name at zero not Circle");
    TEST_ASSERT_TRUE_MESSAGE(list.nameAt(1) == "Square", "name at one not Square");
    TEST_ASSERT_TRUE_MESSAGE(list.nameAt(2) == "Rectangle", "name at two not Rectangle");
    TEST_ASSERT_TRUE_MESSAGE(list.isSorted() == true, "list not sorted");

}

/// Call insertionSort() on an EMPTY list: no crash, length() is 0.
/// Then add ONE shape and sort again: length() is 1 and nameAt(0) is unchanged.
void test_insertionSort_empty_and_single(void)
{
    ShapeList list;

    list.insertionSort();
    TEST_ASSERT_TRUE_MESSAGE(list.length() == 0, "length not zero");
    
    list.addShape(new Circle(1));
    list.insertionSort();
    TEST_ASSERT_TRUE_MESSAGE(list.length() == 1, "length not one");
    TEST_ASSERT_TRUE_MESSAGE(list.nameAt(0) == "Circle", "name at zero not Circle");
}
