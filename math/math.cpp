

#ifndef MATH_HPP
	#include "math.hpp"
#endif

#ifndef MATH_CPP
    
#define MATH_CPP

/*
    global vector operators
*/
vec2d operator + (vec2d const& a, vec2d const& b) {
    return {
        a.x + b.x,
        a.y + b.y
    };
}

vec3d operator + (vec3d const& a, vec3d const& b) {
    return {
      a.x + b.x,
      a.y + b.y,
      a.z + b.z
    };
}

vec2d operator - (vec2d const& a, vec2d const& b) {
    return {
        a.x - b.x,
        a.y - b.y
    };
}

vec3d operator - (vec3d const& a, vec3d const& b) {
    return {
      a.x - b.x,
      a.y - b.y,
      a.z - b.z
    };
}

sfloat operator * (vec2d const& a, vec2d const& b) {
    return (a.x * b.x) + (a.y * b.y);
}

sfloat operator * (vec3d const& a, vec3d const& b) {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}


namespace math {

uint16_t max_slope = 1024;
const sfloat pi = 3.14159265359;

namespace vector {

    sfloat cross_product(
        vec2d const& target, vec2d const& p1, vec2d const& p2
    ) {

        // 1 - move to (0,0) using v0
        vec2d a = { p2.x - p1.x , p2.y - p1.y };
        vec2d b = { target.x - p1.x , target.y - p1.y };

        // 2 - calc normal.z : a x b
        return (a.x * b.y) - (a.y * b.x);
    }

    sfloat cross_product(
        vec3d const& target, vec3d const& p1, vec3d const& p2
    ) {

        return NULL;
    }

    void scale(vec2d& a, sfloat scalar) {
        a.x *= scalar;
        a.y *= scalar;
    }
    void scale(vec3d& a, sfloat scalar) {
        a.x *= scalar;
        a.y *= scalar;
        a.z *= scalar;
    }

    sfloat length(vec2d const& a) {
        return std::sqrtf(
            (a.x * a.x) + (a.y * a.y)
        );
    }

    vec2d unit(vec2d const& a) {

        sfloat length = math::vector::length(a);

        if (length == 0) return {0,0};

        return {
            a.x / length ,
            a.y / length
        };

    }

    vec2d left_normal(vec2d const& p1, vec2d const& p2) {

        return { -(p1.y - p2.y) ,  (p1.x - p2.x) };
    }

    vec2d right_normal(vec2d const& p1, vec2d const& p2) {
 
        return { (p1.y - p2.y) ,  -(p1.x - p2.x) };
    }

    // TODO : implements those functions 

    vec3d left_normal(vec3d const& p1, vec3d const& p2) {
        std::runtime_error("not implemented yet :(");
        return { 0,0,0 };
    }

    vec3d right_normal(vec3d const& p1, vec3d const& p2) {
        std::runtime_error("not implemented yet :(");
        return { 0,0,0 };
    }

    vec3d unit(vec3d const& a) {
        std::runtime_error("not implemented yet :(");
        return {0,0,0};
    }


} 
// end : namespace vector


/* 
    3d rotate function's 
*/
void x_rotate(vec3d const& origin, vec3d& point , sfloat rad_angle) {
    
    // move to origin
    point.x -= origin.x;
    point.y -= origin.y;
    point.z -= origin.z;

    // rotate process
    sfloat cos = std::cosf(rad_angle);
    sfloat sin = std::sinf(rad_angle);

    // to avoid classic problem
    sfloat py = point.y;

    point.y = point.y * cos - point.z * sin;
    point.z = py * sin + point.z * cos;

    // move back
    point.x += origin.x;
    point.y += origin.y;
    point.z += origin.z;

}

void y_rotate(vec3d const& origin, vec3d& point ,sfloat rad_angle) {
    
    // move to origin
    point.x -= origin.x;
    point.y -= origin.y;
    point.z -= origin.z;

    // rotate process
    sfloat cos = std::cosf(rad_angle);
    sfloat sin = std::sinf(rad_angle);

    // to avoid classic problem we have to use old x while calcute new y
    sfloat px = point.x;

    point.x = point.x * cos - point.z * sin;
    point.z = px * sin + point.z * cos;

    // move back
    point.x += origin.x;
    point.y += origin.y;
    point.z += origin.z;

}

void z_rotate(vec3d const& origin, vec3d& point, sfloat rad_angle) {

    // move to origin
    point.x -= origin.x;
    point.y -= origin.y;
    point.z -= origin.z;

    // rotate process
    sfloat cos = cosf(rad_angle);
    sfloat sin = sinf(rad_angle);
    
    // to avoid classic problem we have to use old x while calcute new y
    sfloat px = point.x; 

    point.x = point.x * cos - point.y * sin;
    point.y = px * sin + point.y * cos;

    // move back
    point.x += origin.x;
    point.y += origin.y;
    point.z += origin.z;

}

/*
    math function's    
*/
sfloat to_radian(sfloat degree_value) {
    return degree_value * math::pi / 180;
}

sfloat to_degree(sfloat radian_value) {
    return radian_value * 180 / math::pi;
}

// deltha = v1 - v2
sfloat deltha(sfloat v1, sfloat v2) {
    return v1 - v2;
}

// slope = dy / dx 
sfloat slope2d(vec2d const& a, vec2d const& b) {
    sfloat dx = (b.x - a.x);
    return (dx == 0) ? max_slope : (b.y - a.y) / dx;
}

// distance = sqrt((b.x - a.x)² + (b.y - a.y)²)
sfloat distance2d(vec2d const& a, vec2d const& b) {
    return std::sqrtf( 
        (sfloat)std::pow(b.x - a.x , 2) 
                    + 
        (sfloat)std::pow(b.y - a.y , 2)
    );
}

// y = slope * x + y_at_x0
sfloat y_intercept_2d(sfloat x, sfloat slope, sfloat y_at_x0) {
    return (slope * x) + y_at_x0;
}

// x = (y - y_at_x0) / slope
sfloat x_intercept_2d(sfloat y, sfloat slope, sfloat y_at_x0) {
    return (y - y_at_x0) / (slope != 0 ? slope : math::max_slope);
}

// Y = p.y - (slope * p.x)
sfloat y_intercept_at_x0_2d(vec2d const& point, sfloat slope) {
    return point.y - (slope * point.x);
}

// X = (y - y_at_x0) / slope
sfloat x_intercept_at_y0_2d(sfloat y_at_x0, sfloat slope) {
    return math::x_intercept_2d(0, slope, y_at_x0);
}

vec2d tow_points_intersection(
    vec2d const& p1, sfloat p1_slope,
    vec2d const& p2, sfloat p2_slope
){
    sfloat C = math::y_intercept_at_x0_2d(p1, p1_slope);
    sfloat X = (p2.y - p1.y + p1_slope * p1.x - p2_slope * p2.x) / (p1_slope - p2_slope);

    return create_vec2d( X , X * p1_slope + C );
}

bool is_point_inside_triangle(
    vec2d const& target_point ,
    vec2d const& p1, vec2d const& p2, vec2d const& p3,
    bool ignore_point_on_the_line
) {

    if(ignore_point_on_the_line){

        if(math::vector::cross_product(target_point, p1, p2 ) <= 0) return false;

        if(math::vector::cross_product(target_point, p2, p3 ) <= 0) return false;

        if(math::vector::cross_product(target_point, p3, p1 ) <= 0) return false;

    }
    else{

        if (math::vector::cross_product(target_point, p1, p2) < 0) return false;

        if (math::vector::cross_product(target_point, p2, p3) < 0) return false;

        if (math::vector::cross_product(target_point, p3, p1) < 0) return false;

    }

    return true;
}

vec2d centroid(
    vec2d const& p1, vec2d const& p2, vec2d const& p3
) {
    return vec2d{
        (p1.x + p2.x + p3.x) / 3,
        (p1.y + p2.y + p3.y) / 3
    };
}

// formula1 : p = (a+b+c) / 3
// formula2 : area = sqrt( p * (p - A) * (p - B) * (p - C) )
sfloat triangle_area(
    vec2d const& p1, vec2d const& p2, vec2d const& p3
) {

    sfloat A = math::distance2d(p2, p1);
    sfloat B = math::distance2d(p3, p2);
    sfloat C = math::distance2d(p3, p1);

    sfloat p = (A + B + C) / 2;

    return std::sqrtf(p * (p - A) * (p - B) * (p - C));
}

/*
        TODO : 3D MATH !!!!!
*/

sfloat slope3d(vec3d const& a, vec3d const& b) {
    throw std::runtime_error("not implemented yet :(");
    return 0;
}

sfloat distance3d(vec3d const& a, vec3d const& b) {
    throw std::runtime_error("not implemented yet :(");
    return 0;
}

bool is_point_inside_triangle(
    vec3d const& target_point,
    vec3d const& p1, vec3d const& p2, vec3d const& p3,
    bool ignore_point_on_the_line
) {
    throw std::runtime_error("not implemented yet :(");
    return false;
}

vec3d centroid(
    vec3d const& p1, vec3d const& p2, vec3d const& p3
) {
    throw std::runtime_error("not implemented yet :(");
    return vec3d{};
}

sfloat triangle_area(
    vec3d const& p1, vec3d const& p2, vec3d const& p3
) {
    throw std::runtime_error("not implemented yet :(");
    return 0;
}

/*
    random class function's
*/

uint8_t math::random::uint8(uint8_t min, uint8_t max){
    //srand(time(0));
    return (uint8_t)(std::rand() % (max - min + 1) + min);
}

int8_t math::random::int8(int8_t min, int8_t max) {
    //srand(time(0));
    return (int8_t)(std::rand() % (max - min + 1) + min);
}

uint16_t math::random::uint16(uint16_t min, uint16_t max) {
    //srand(time(0));
    return (uint16_t)(std::rand() % (max - min + 1) + min);
}

int16_t math::random::int16(int16_t min, int16_t max) {
    //srand(time(0));
    return (int16_t)(std::rand() % (max - min + 1) + min);
}

uint32_t math::random::uint32(uint32_t min, uint32_t max) {
    //srand(time(0));
    return (uint32_t)(std::rand() % (max - min + 1) + min);
}

int32_t math::random::int32(int32_t min, int32_t max) {
    //srand(time(0));
    return (int32_t)(std::rand() % (max - min + 1) + min);
}

uint64_t math::random::uint64(uint64_t min, uint64_t max) {
    //srand(time(0));
    return (uint64_t)(std::rand() % (max - min + 1) + min);
}

int64_t math::random::int64(int64_t min, int64_t max) {
    //srand(time(0));
    return (int64_t)(std::rand() % (max - min + 1) + min);
}

} 
// end : namespace math

#endif
