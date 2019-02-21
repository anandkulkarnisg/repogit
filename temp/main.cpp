#include <iostream>
#include <memory>
#include <experimental/propagate_const>
#include "widget.h"

using namespace std;
 
int main(int argc, char* argv[])
{
    widget w(7);
    const widget w2(8);
    w.draw();
    w2.draw();
}
