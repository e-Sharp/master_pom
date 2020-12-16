
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

// +x is side, +y is up, +z is forward.
vec3 aircraft_rot(vec3 v, float yaw, float pitch, float roll) {
    return roty(rotx(rotz(v, roll), pitch), yaw);
}

////////////////////////////////////////////////////////////////////////////////
// Signed distance functions.

float sphere_sd(vec3 p, float r) {
    return length(p) - r;
}

////////////////////////////////////////////////////////////////////////////////

vec3 directional_light = normalize(vec3(-1., -1., -1.));

vec3 sphere_position = vec3(0., 1., 0.);

void mainImage(out vec4 c4, in vec2 coords) {
    vec2 uv = 2. * coords / iResolution.x - 1.; // [-1, 1]

    vec3 o = vec3(-sin(iTime / 3.) * 1.8, 3., -cos(iTime / 3.) * 1.8);
    vec3 u = aircraft_rot(vec3(uv, 1.f), iTime / 3., 0.8, 0.);

    vec3 c3 = vec3(0.);

    // Sphere.
    vec3 r = o;
    float mind = 1e10;
    for(int i = 0; i < 50; ++i) {
        float d = sphere_sd(r - sphere_position, 1.);
        mind = min(mind, d);
        r += d * u;
    }

    if(mind < 0.01) {
        vec3 normal = normalize(r - sphere_position);
        float dif = max(dot(normal, -directional_light), 0.);
        c3 = (0.8 * dif + 0.2) * vec3(1., 0., 0.);

    }

    // Plane.
    if(u.y < 0.) {
        float d = -o.y / u.y;
        if(d < distance(o, r)) {
            r = o + d * u;
            c3 = (mod(floor(r.x) + floor(r.z), 2.) < 1.)
                ? vec3(0.4) : vec3(0.5);
            // Shadow.
            vec3 rs = r;
            float ds = 0.;
            for(int i = 0; i < 50; ++i) {
                float d = sphere_sd(rs - sphere_position, 1.);
                ds += d;
                rs -= d * directional_light;
            }

            c3 *= - 1. / (2. * ds + 0.2) + 1.;
        }
    }

    c4 = vec4(c3, 1.);
}
