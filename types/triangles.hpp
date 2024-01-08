
/*
	===================================================
	====================== triangles ==================
	===================================================
*/

#ifndef TRIANGLES_HPP

	#define TRIANGLES_HPP

class triangle2d {

public :
	
	vector2d points[3];

	// constructor's
	triangle2d();

	triangle2d(
		sfloat x1, sfloat y1, // point 1
		sfloat x2, sfloat y2, // point 2  
		sfloat x3, sfloat y3  // point 3
	);

	triangle2d(
		vector2d point_1, 
		vector2d point_2, 
		vector2d point_3
	);

	triangle2d(
		vector2d& point_1, 
		vector2d& point_2, 
		vector2d& point_3
	);

	// destructor
	~triangle2d() = default;

};
// end : class triangle2d

class triangle3d {

public:

	vector3d points[3];

	// constructor's
	triangle3d();

	triangle3d(
		sfloat x1, sfloat y1, sfloat z1, // point 1
		sfloat x2, sfloat y2, sfloat z2, // point 2
		sfloat x3, sfloat y3, sfloat z3  // point 3
	);

	triangle3d(
		vector3d point_1, 
		vector3d point_2, 
		vector3d point_3
	);

	triangle3d(
		vector3d& point_1, 
		vector3d& point_2, 
		vector3d& point_3
	);

	// destructor
	~triangle3d() = default;

};
// end : class triangle3d

#endif

