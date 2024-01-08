
/*
	=================================================
	====================== lines ====================
	=================================================
*/

#ifndef LINES_HPP

    #define LINES_HPP

class line2d {

public:
	vector2d points[2];

	// constructor's
	line2d();
	line2d(
		sfloat x1 , sfloat y1 , // point 1
		sfloat x2 , sfloat y2   // point 2
	);
	line2d(vector2d  point_1, vector2d  point_2);
	line2d(vector2d& point_1, vector2d& point_2);

	// destructor
	~line2d() = default;

};
// end : class line2d 

class line3d {

public:
	vector3d points[2];

	// constructor's
	line3d();
	line3d(
		sfloat x1, sfloat y1, sfloat z1, // point 1
		sfloat x2, sfloat y2, sfloat z2  // point 2
	);
	line3d(vector3d  point_1, vector3d  point_2);
	line3d(vector3d& point_1, vector3d& point_2);

	// destructor
	~line3d() = default;

};
// end : class line3d

#endif
