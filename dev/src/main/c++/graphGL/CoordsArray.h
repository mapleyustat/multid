#ifndef _CoordsArray_h
#define _CoordsArray_h
#ifdef __GNUC__
#pragma interface
#endif

class CoordsArray
/*
    Implements a display list, containing Vertex2? or Vertex3? commands.
*/
{
public:
    CoordsArray(void);
    CoordsArray(int _dim, int _n_points, const double *_coords);
// TODO:  bounding boxes
// What about bounding boxes?

    void init(int _dim, int _n_points, const double *_coords);
    void flush() const;

    const double* coords() const;
    int dim(void) const;
    int n_points(void) const;

private:

    const double* coords_;
    int n_points_;
    int dim_;

};

inline
CoordsArray::CoordsArray(void)
            :coords_(0),
             n_points_(0),
             dim_(0)
{
}

inline
CoordsArray::CoordsArray(int _dim, int _n_points, const double *_coords)
	:coords_(_coords),
	n_points_(_n_points),
	dim_(_dim)
{
}

inline const double *
CoordsArray::coords() const
{
    return coords_;
}

inline int
CoordsArray::dim(void) const
{
    return dim_;
}

inline int
CoordsArray::n_points(void) const
{
    return n_points_;
}

#endif
