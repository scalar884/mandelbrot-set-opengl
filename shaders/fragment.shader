#version 330 core
out vec4 FragColor; /* out pixel color */

void main() {
	vec2 c = (gl_FragCoord.xy / vec2(1200, 1200) - 0.5) * 3.0; /* gl_FragCoord.xy - current pixel coord, vec2(800, 600) - window size */

	c.x -= 0.5;
	vec2 z = vec2(0.0);
	int count = 0; /* need for color */
	/* 100 - max attempts size for one pixel */
	for(int i = 0; i < 100; i++) {
	/* z = z^2 + c */
		z = vec2(z.x*z.x - z.y*z.y, 2.0*z.x*z.y) + c;
		if(dot(z, z) > 4.0) break;
		count++;
	}
	/* draw color */
	if (count > 95) {
    	FragColor = vec4(0.0, 0.0, 0.0, 1.0);
	} else {
    float t = float(count) / 100.0;
    FragColor = vec4(
        0.5 + 0.5 * cos(3.0 + t * 10.0),  // R
        0.5 + 0.5 * cos(2.0 + t * 7.0),   // G  
        0.5 + 0.5 * cos(1.0 + t * 5.0),   // B
        1.0
    );
	}
}
		
