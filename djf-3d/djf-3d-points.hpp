/* Note that although this is supposed to be for 3d rendering,
it does not include SDL or any other graphics libraray, or
indeed any libraries at all. This is because all that this file
is meant to do is abstract away the calculations needed to put
3d points on a 2d screen; actually visibly displaying those
points is up to the 2d graphics API of the programmer's choice.
*/

class ThreeDeePoint {
    // These private variables store various data about
    // the ThreeDeePoint.
    private:
        float x_pos; // left-and-right distance
        float y_pos; // up-and-down distance
        float z_pos; // distance from the viewer
        float display_centerpoint_x; // these two values define
        float display_centerpoint_y; // the vanishing point
        int fudge_value = 200; // needed to adjust Z-position

    // Being able to know and modify the data in the private
    // variables above is kind of important, so we have plenty
    // of public methods for getting and setting them.
    public:
        // The set methods return 0 if successful and 1 if
        // there's an error (that is, if the variable they're
        // trying to set does not equal what they're trying to
        // set it to after being called).
        int set_display_centerpoint(float _x_val,
                                    float _y_val) {
            display_centerpoint_x = _x_val;
            display_centerpoint_y = _y_val;
            if (display_centerpoint_x == _x_val
                && display_centerpoint_y == _y_val) {
                return 0;
            } else {
                return 1;
            }
        }

        int set_x_pos(float _x_pos) {
            x_pos = _x_pos;
            if (x_pos == _x_pos) {
                return 0;
            } else {
                return 1;
            }
        }

        float get_x_pos() {
            float _x_pos = x_pos;
            return _x_pos;
        }

        int set_y_pos(float _y_pos) {
            y_pos = _y_pos;
            if (y_pos == _y_pos) {
                return 0;
            } else {
                return 1;
            }
        }

        float get_y_pos() {
            float _y_pos = y_pos;
            return _y_pos;
        }

        int set_z_pos(float _z_pos) {
            // Without the fudge value, our Z-coordinate gets
            // changed too much by the set method. The fudge
            // value makes it so that changing the Z-coordinate
            // by a given amount looks like about as much of
            // a change onscreen as changing the X- or
            // Y-coordinate by the same amount.
            int return_val;
            z_pos = _z_pos / fudge_value;
            if (z_pos == _z_pos * fudge_value) {
                return 0;
            } else {
                return 1;
            }
        }

        float get_z_pos() {
            float _z_pos = z_pos;
            return _z_pos * fudge_value;
        }

        // Since the set methods are a bit clunky to use
        // individually, this method does all of them at once.
        int set_position(float x, float y, float z) {
            int error_val = 0;
            error_val += set_x_pos(x);
            error_val += set_y_pos(y);
            error_val += set_z_pos(z);
            return error_val;
        }

    // It will be assumed that the X-axis runs left and right,
    // the Y-axis runs up and down, and the Z-axis is
    // perpendicular to the screen. Higher Z-values mean that
    // the object looks further away; negative Z-values are
    // allowed but lead to really weird effects.

    // These private methods calculate where on a 2-d screen
    // the point would have to go in order to look like it's
    // in a 3-d space at its X, Y, and Z coordinates.
    private:
        float _shift_x(float x, float z) {
            return (x + (display_centerpoint_x * z)) / (z + 1);
        }

        float _shift_y(float y, float z) {
            return (y + (display_centerpoint_y * z)) / (z + 1);
        }

    // These public methods call the private methods defined
    // above.
    public:
        float apparent_x() {
            return _shift_x(x_pos, z_pos);
        }

        float apparent_y() {
            return _shift_y(y_pos, z_pos);
        }
};
