#include <iostream>
#include "rectangle.h"
#include "circle.h"

int main()
{
    try
    {
        std::cout << "-------Rectangle test-------\n";
        Rectangle rectangle(point_t{228, 1337}, 6, 9);
        std::cout << "width: " << rectangle.getWidth() << '\n';
        std::cout << "height: " << rectangle.getHeight() << '\n';
        std::cout << "position: ( " << rectangle.getPosition().x << " ; " << rectangle.getPosition().y << " )/n";
        std::cout << "area: " << rectangle.getArea() << '\n';

        double x1 = 123, y1 = 321;
        std::cout << "-------moving to ( " << x1 << " ; " << y1 << " )-------\n";
        std::cout << "current: ( " << rectangle.getPosition().x << " ; " << rectangle.getPosition().y << " )    ";
        std::cout << "destination: ( " << x1 << " ; " << y1 << " )\n";
        std::cout << "mooving...\n";
        rectangle.move({x1, y1});
        std::cout << "current: ( " << rectangle.getPosition().x << " ; " << rectangle.getPosition().y << " )    ";
        std::cout << "destination: ( " << x1 << " ; " << y1 << " )\n";

        std::cout << "-------moving " << x1 << " by x and" << y1 << " by y-------\n";
        std::cout << "current: ( " << rectangle.getPosition().x << " ; " << rectangle.getPosition().y << " )    ";
        std::cout << "destination: ( " << rectangle.getPosition().x + x1 << " ; " << rectangle.getPosition().y + y1
                  << " )\n";
        std::cout << "mooving...\n";
        rectangle.move(rectangle.getPosition().x + x1, rectangle.getPosition().y + y1);
        std::cout << "current: ( " << rectangle.getPosition().x << " ; " << rectangle.getPosition().y << " )    ";
        std::cout << "destination: ( " << rectangle.getPosition().x + x1 << " ; " << rectangle.getPosition().y + y1
                  << " )\n";

        std::cout << "-------Circle test-------\n";
        Circle circle(6, {3, 4});
        std::cout << "radius: " << circle.getRadius() << '\n';
        std::cout << "position: ( " << circle.getPosition().x << " ; " << circle.getPosition().y << " )\n";
        std::cout << "area: " << circle.getArea() << '\n';

        x1 = 111;
        y1 = 222;
        std::cout << "-------moving to ( " << x1 << " ; " << y1 << " )-------\n";
        std::cout << "current: ( " << circle.getPosition().x << " ; " << circle.getPosition().y << " )    ";
        std::cout << "destination: ( " << x1 << " ; " << y1 << " )\n";
        std::cout << "mooving...\n";
        circle.move({x1, y1});
        std::cout << "current: ( " << circle.getPosition().x << " ; " << circle.getPosition().y << " )    ";
        std::cout << "destination: ( " << x1 << " ; " << y1 << " )\n";

        std::cout << "-------moving " << x1 << " by x and" << y1 << " by y-------\n";
        std::cout << "current: ( " << circle.getPosition().x << " ; " << circle.getPosition().y << " )    ";
        std::cout << "destination: ( " << circle.getPosition().x + x1 << " ; " << circle.getPosition().y + y1 << " )\n";
        std::cout << "mooving...\n";
        circle.move(circle.getPosition().x + x1, circle.getPosition().y + y1);
        std::cout << "current: ( " << circle.getPosition().x << " ; " << circle.getPosition().y << " )    ";
        std::cout << "destination: ( " << circle.getPosition().x + x1 << " ; " << circle.getPosition().y + y1 << " )\n";
    }
    catch (const std::invalid_argument &)
    {
        std::cerr << "Error:invalid data" << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "Error:Unknown problem" << std::endl;
        return 2;
    }

    return 0;
}
