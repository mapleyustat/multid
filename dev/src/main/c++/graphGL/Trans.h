#ifndef _Trans_h
#define _Trans_h
#ifdef __GNUC__
#pragma interface
#endif

class Trans
/*
    Encapsulates two transformation matrices, performs vdc->wc transformations,
    and manages model/view transformations.
*/
{
public:

// Sets the correct transformation matrices and clipping planes
// for rendering.
    void repaint(void);

protected:
    Trans(int);
    virtual ~Trans(void);


// Clip plane equations
    double **equation;

    double projection_matrix[16],modelview_matrix[16];

private:

// Control variable to manage clip code in this base class, since it's
// very similar for 2d and 3d.
    int is_3d_;
    Trans(const Trans &trans);      // Do not define.
    Trans &operator=(const Trans &trans);   // Do not define.
};

#endif
