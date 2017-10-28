#ifndef CAMERA_H
#define CAMERA_H

#include "obj.h"
#include "math_abstracts.h"

class Camera : public BaseObject
{
protected:
    MathVector view_axis;
    MathVector right_axis;
    MathVector up_axis;
    double distance_to_screen;

public:
    Camera();
    Camera(const Camera&);
    Camera(Camera&&);
    Camera(double, double, double);

    Camera& operator = (const Camera&);
    Camera& operator = (Camera&&);

    // Геттеры
    double getDistanceToScreen() const { return distance_to_screen; }

    double getViewAxisX() const;
    double getViewAxisY() const;
    double getViewAxisZ() const;
    MathVector getViewAxis() const;

    double getRightAxisX() const;
    double getRightAxisY() const;
    double getRightAxisZ() const;
    MathVector getRightAxis() const;

    double getUpAxisX() const;
    double getUpAxisY() const;
    double getUpAxisZ() const;
    MathVector getUpAxis() const;

    // Сеттеры
    void setDistanceToScreen(double in) { distance_to_screen = in; }

    void setViewAxisX(double in) { view_axis.setX(in); }
    void setViewAxisY(double in) { view_axis.setY(in); }
    void setViewAxisZ(double in) { view_axis.setZ(in); }
    void setViewAxis(double in_1, double in_2, double in_3) { setViewAxisX(in_1); setViewAxisY(in_2); setViewAxisZ(in_3); }
    void setViewAxis(MathVector &in) { view_axis = in; }

    void setRightAxisX(double in) { right_axis.setX(in); }
    void setRightAxisY(double in) { right_axis.setY(in); }
    void setRightAxisZ(double in) { right_axis.setZ(in); }
    void setRightAxis(double in_1, double in_2, double in_3) { setRightAxisX(in_1); setRightAxisY(in_2); setRightAxisZ(in_3); }
    void setRightAxis(MathVector &in) { right_axis = in; }

    void setUpAxisX(double in) { up_axis.setX(in); }
    void setUpAxisY(double in) { up_axis.setY(in); }
    void setUpAxisZ(double in) { up_axis.setZ(in); }
    void setUpAxis(double in_1, double in_2, double in_3) { setUpAxisX(in_1); setUpAxisY(in_2); setUpAxisZ(in_3); }
    void setUpAxis(MathVector &in) { up_axis = in; }


    void moveToWorldCenter();
    virtual void clear() override;

    bool isPolyViz(const Points3D&) const;
    bool isOnDisplay(const DotForDrawer&) const;
    bool isOnDisplay(const double) const;
};

#endif // CAMERA_H
