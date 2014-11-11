#ifdef __GNUC__
#pragma implementation
#endif
#define GRAPHICS_IMPLEMENTATION
#include <iostream>
#include <iomanip>
#include <Viewport.h>

std::ostream &
operator<<(std::ostream &os, const Bounds2d &bounds_2d)
{
    os << "#Bounds2d ";
    os << bounds_2d.xmin;
    os << " " << bounds_2d.ymin;
    os << " " << bounds_2d.xmax;
    os << " " << bounds_2d.ymax;
    os << "\n";
    return os;
}

std::istream &
operator>>(std::istream &is, Bounds2d &bounds_2d)
{
    const int NCHAR = sizeof("#Bounds2d");
    char s[NCHAR];
    is >> std::setw(NCHAR) >> s;
    is >> bounds_2d.xmin;
    is >> bounds_2d.ymin;
    is >> bounds_2d.xmax;
    is >> bounds_2d.ymax;
    return is;
}

std::ostream &
operator<<(std::ostream &os, const Bounds3d &bounds_3d)
{
    os << "#Bounds3d ";
    os << bounds_3d.xmin;
    os << " " << bounds_3d.ymin;
    os << " " << bounds_3d.zmin;
    os << " " << bounds_3d.xmax;
    os << " " << bounds_3d.ymax;
    os << " " << bounds_3d.zmax;
    os << "\n";
    return os;
}

std::istream &
operator>>(std::istream &is, Bounds3d &bounds_3d)
{
    const int NCHAR = sizeof("#Bounds3d");
    char s[NCHAR];
    is >> std::setw(NCHAR) >> s;
    is >> bounds_3d.xmin;
    is >> bounds_3d.ymin;
    is >> bounds_3d.zmin;
    is >> bounds_3d.xmax;
    is >> bounds_3d.ymax;
    is >> bounds_3d.zmax;
    return is;
}


