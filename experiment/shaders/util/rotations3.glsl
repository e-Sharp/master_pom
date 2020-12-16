////////////////////////////////////////////////////////////////////////////////
// 3D rotations.

vec3 rotx(vec3 v, float a) {
    float c = cos(a), s = sin(a);
    return vec3(v.x, c * v.y - s * v.z, s * v.y + c * v.z);
}

vec3 roty(vec3 v, float a) {
    float c = cos(a), s = sin(a);
    return vec3(c * v.x + s * v.z, v.y, -s * v.x + c * v.z);
}

vec3 rotz(vec3 v, float a) {
    float c = cos(a), s = sin(a);
    return vec3(c * v.x - s * v.y, s * v.x + c * v.y, v.z);
}

// x is side, y is forward, z is up.
vec3 aircraft_rot(vec3 v, float yaw, float pitch, float roll) {
    return roty(rotx(rotz(v, roll), pitch), yaw);
}
