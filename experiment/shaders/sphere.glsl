vec3 light = vec3(10, 10, 0);

vec3 ambient_color = vec3(0., 0.2, 0);
vec3 diffuse_color = vec3(0, 1, 0);

float sphere_sd(vec3 p, float r) {
    return length(p) - r;
}

void mainImage( out vec4 color, in vec2 fragCoord ) {
    vec2 uv = 2. * fragCoord / iResolution.xy - 1.;

    vec3 p = vec3(0, 0, 0);
    vec3 u = normalize(vec3(uv, 1));

    float md = 1000.;

    // Sphere.
    for(int i = 0; i < 20; ++i) {
        float d = sphere_sd(p - vec3(0, 0, 5), 1.);
        p += d * u;
        md = min(md, d);
    }

    if(md < 0.01) {
        color = vec4(ambient_color, 1.);
        float diffuse = max(0., dot(normalize(p - vec3(0, 0, 5)), normalize(light - vec3(0, 0, 5))));
        color.xyz += diffuse * diffuse_color;
    } else {
        color = vec4(vec3(0.), 1.);
    }
}
