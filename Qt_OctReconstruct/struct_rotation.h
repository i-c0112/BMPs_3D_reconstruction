#ifndef STRUCT_ROTATION_H
#define STRUCT_ROTATION_H

// abstract base class
struct rotation
{
    virtual void rotate() = 0;
    virtual ~rotation() {}
};
struct rotation_horizontal : rotation
{
    float deg;
    explicit rotation_horizontal(float d) : deg(d) {}
    virtual void rotate()
    {
        glRotatef(deg, 0.0f, 1.0f, 0.0f);
    }

    virtual ~rotation_horizontal() {}
};
struct rotation_vertical : rotation
{
    float deg;
    explicit rotation_vertical(float d) : deg(d) {}
    virtual void rotate()
    {
        // z = -1.0 => toward screen
        glRotatef(deg, 0.0f, 0.0f, -1.0f);
    }
    virtual ~rotation_vertical() {}
};

#endif // STRUCT_ROTATION_H
