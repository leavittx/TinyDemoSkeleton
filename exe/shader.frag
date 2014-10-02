uniform float t;

#define PRECISION 0.01
#define DEPTH 1000.0
#define STEPS 32

vec2 uv;
vec3 eye = vec3(0,1,-5);
vec3 light = vec3(0,2,-3);

bool hit = false;

float sky;
float water;

//float t = gl_Color.x;
vec2 iResolution = vec2(1680, 1050);

float map(vec3 p);
float udBox(vec3 p, vec3 s) { return length(max(abs(p)-s,0.0)); }

// Marching
vec3 getNormal(vec3 p){vec2 e=vec2(PRECISION,0);return(normalize(vec3(map(p+e.xyy)-map(p-e.xyy),map(p+e.yxy)-map(p-e.yxy),map(p+e.yyx)-map(p-e.yyx))));}
vec3 march(vec3 ro,vec3 rd){float t=0.0,d;for(int i=0;i<STEPS;i++){d=map(ro+rd*t);if(d<PRECISION){hit=true;}if(hit==true||t>DEPTH){break;}t+=d;}return(ro+rd*t);}
vec3 lookAt(vec3 o,vec3 t){vec3 d=normalize(t-o),u=vec3(0,1,0),r=cross(u,d);return(normalize(r*uv.x+cross(d,r)*uv.y+d));}

float f(float t) { return 6.0*t*t*t*t*t-15.0*t*t*t*t+10.0*t*t*t; }

vec2 noise(vec2 p){
	return (vec2(
		fract(sin(dot(p.xy, vec2(50159.91193,49681.51239))) * 73943.1699),
		fract(sin(dot(p.xy, vec2(90821.40973,2287.62201))) * 557.96557)
	)-0.5)*2.0;
}

float perlin(vec2 p)
{
	int X = int(floor(p.x));
	int Y = int(floor(p.y));
	
	p.x -= float(X);
	p.y -= float(Y);
	
	vec2 g00 = noise(vec2(X  , Y  ));
	vec2 g01 = noise(vec2(X  , Y+1));
	vec2 g10 = noise(vec2(X+1, Y  ));
	vec2 g11 = noise(vec2(X+1, Y+1));
	
	float q00 = dot(g00, vec2(p.x    , p.y    ));
	float q01 = dot(g01, vec2(p.x    , p.y-1.0));
	float q10 = dot(g10, vec2(p.x-1.0, p.y    ));
	float q11 = dot(g11, vec2(p.x-1.0, p.y-1.0));

	p.x = f(p.x);
	p.y = f(p.y);
	
	float qx0 = mix(q00, q10, p.x);
	float qx1 = mix(q01, q11, p.x);
	float qxy = mix(qx0, qx1, p.y);

	return qxy+0.5;
}

vec3 getColor(vec3 p)
{
	float d = 1e10;
	
	vec3 n = getNormal(p);
	vec3 l = normalize(light-p);
	vec3 col = vec3(1);
	
	float dist = length(p-light);
	float diff = max(dot(n, normalize(light-p)),0.0);
	float spec = pow(diff, 10.0);

	if (sky<d)
	{
		float h = perlin(vec2(p.x+t,p.z))*perlin(p.xx);
		col = vec3(h)*vec3(0,1,0.5); 
		d = sky;
	}

	if(water<d)
	{
		col *= vec3(diff)*vec3(0.7,0.9,1)+spec;
		col *= 1.0/dist;
		col *= exp(1.0/length(p-light));
	}

	return col;
}

float map(vec3 p)
{
	float d = 1e10;
	float h = perlin(p.xz*vec2(1,5)*2.0+t);
	
	sky = (-p.z-p.y);
	water = p.y-h*0.1;

	d = min(d,sky);
	d = min(d,water);

	return d;
}

void main()
{
	uv = (2.0*gl_FragCoord.xy-iResolution.xy)/iResolution.xx;
	vec3 p = march(eye,lookAt(eye,vec3(0)));
	
	vec3 col = vec3(0);
	if (hit == true) { col = getColor(p); }

	gl_FragColor = vec4(col,1.0);
}

