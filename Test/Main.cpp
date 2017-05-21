/**
* \file Main.cpp

* Copyright (c) 2016, Kevin Knifsend, https://nullbreak.wordpress.com/

* Permission to use, copy, modify, and/or distribute this software for any
* purpose with or without fee is hereby granted, provided that the above
* copyright notice and this permission notice appear in all copies.

* THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
* WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
* ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
* WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
* ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
* OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#include <iostream>
#include <chrono>
#include <thread>

using namespace std;


#include <vector>
#include <iostream>

//#include "Emblem/Expression.h"

#include "Emblem\Internal\Collection\BinaryTree.h"

//using namespace Emblem;
//
//double eval(Emblem::Expression<double>::ValueMap& values)
//{
//    double x, y, z;
//    x = values.at("x");
//    y = values.at("y");
//    z = values.at("z");
//
//    return sin(((x * y) + (z - x) / 5) + z);
//}


int main()
{
    Emblem::Collection::BinaryTree<double> tree;
    /*tree.insertToHead(1.0);
    tree.insertToHead(2.0);
    tree.insertToHead(3.0);
    tree.insertToHead(4.0);*/

    Emblem::Collection::BinaryTree<double> tree2;
    /*tree2.insertToHead(1.0);
    tree2.insert<Emblem::Collection::InsertDirection::LEFT>(tree2.head(), tree);*/

    //Emblem::Expression<double>::ValueMap values;
//   values["x"] = 4.0;
//   values["y"] = 3.0;
    //values["z"] = 2.0;

    //Emblem::Symbol<double> x("x"), y("y"), z("z");
    //Emblem::Expression<double> expr = sin(((x * y) + (z - x) / 5) + z);
    ////Emblem::Expression<double> expr = (x * y) - (z + x);
    //std::cout << expr << '\n';

    //const double result = expr.evaluate(values);
    //const double trueResult = eval(values);
    //std::cout << "Result = " << result << ", True Result = " << trueResult << '\n';

    std::cout << "\nProgram finished..\n";
    cin.get();
    return 0;
}