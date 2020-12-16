#define pi 3.1415926538

// Material.
vec3 ambient_color = vec3(0.2, 0, 0);
vec3 diffuse_color = vec3(0, 1, 0);
vec3 specular_color = vec3(1.);
float shininess = 500.;

// Camera.
float pitch = 2.;

float radial_cos(vec2 xy) {
    return cos(length(xy));
}

vec3 radial_cos_normal(vec2 xy) {
    float d = length(xy);
    if(d == 0.) {
        return vec3(0., 0., 1.);
    } else {
        float r = (d + 1.) / d;
        vec3 na = vec3(r * xy.x, r * xy.y, -sin(d));
        vec3 nb = vec3(xy[1], -xy[0], 0.);
        return normalize(cross(na, nb));
    }
}

vec3 rx(vec3 p, float a) {
    float c = cos(a), s = sin(a);
    return vec3(p.x, c * p.y - s * p.z, s * p.y + c * p.z);
}

vec3 ry(vec3 p, float a) {
    float c = cos(a), s = sin(a);
    return vec3(c * p.x + s * p.z, p.y, -s * p.x + c * p.z);
}

vec3 rz(vec3 p, float a) {
    float c = cos(a), s = sin(a);
    return vec3(c * p.x - s * p.y, s * p.x + c * p.y, p.z);
}

void mainImage(out vec4 color, in vec2 fragCoord) {
    vec3 directional_light = normalize(vec3(cos(iTime), sin(iTime), -0.2));

    vec2 uv = 2. * fragCoord / iResolution.xy - 1.;

    vec3 p = vec3(0, 10, 10);
    vec3 u = normalize(rx(vec3(uv, 1), pitch));

    color = vec4(vec3(0.), 1.);

    float dt = 0.05;
    for(int i = 0; i < 3000; ++i) {
        if(p.z <= radial_cos(p.xy)) {
            color = vec4(ambient_color, 1.);
            vec3 normal = radial_cos_normal(p.xy);
            float diffuse = max(0., dot(normal, directional_light));
            float specular = pow(max(0., dot(reflect(directional_light, normal), -u)), shininess);
            color.xyz = (1. - specular) * (
                    (1. - diffuse) * ambient_color
                    + diffuse * diffuse_color
                ) + specular * specular_color;
            break;
        } else {
            p += dt * u;
        }
    }
}
