#ifndef SHADER_H_
# define SHADER_H_

#if 1 // Nordlicht 2014
const char *fragmentShader = \
"uniform float y;\n"
"#define PRECISION 0.01\n"
"#define DEPTH 1000.0\n"
"#define STEPS 32\n"
"vec2 v;"
"vec3 f=vec3(0,1,-5),x=vec3(0,2,-3);"
"bool d=false;"
"float m,r;"
"vec2 l=vec2(1680,1050);"
"float t(vec3 v,vec3 y)"
"{"
"return length(max(abs(v)-y,0.));"
"}"
"vec3 n(vec3 y,vec3 x)"
"{"
"vec3 f=normalize(x-y),d=vec3(0,1,0),r=cross(d,f);"
"return normalize(r*v.x+cross(f,r)*v.y+f);"
"}"
"float n(float y)"
"{"
"return 6.*y*y*y*y*y-15.*y*y*y*y+10.*y*y*y;"
"}"
"vec2 t(vec2 v)"
"{"
"return(vec2(fract(sin(dot(v.xy,vec2(50159.9,49681.5)))*73943.2),fract(sin(dot(v.xy,vec2(90821.4,2287.62)))*557.966))-.5)*2.;"
"}"
"float e(vec2 v)"
"{"
"int y=int(floor(v.x)),x=int(floor(v.y));"
"v.x-=float(y);"
"v.y-=float(x);"
"vec2 f=t(vec2(y,x)),d=t(vec2(y,x+1)),r=t(vec2(y+1,x)),m=t(vec2(y+1,x+1));"
"float s=dot(f,vec2(v.x,v.y)),l=dot(d,vec2(v.x,v.y-1.)),N=dot(r,vec2(v.x-1.,v.y)),e=dot(m,vec2(v.x-1.,v.y-1.));"
"v.x=n(v.x);"
"v.y=n(v.y);"
"float i=mix(s,N,v.x),h=mix(l,e,v.x),S=mix(i,h,v.y);"
"return S+.5;"
"}"
"float s(vec3 v)"
"{"
"float f=1e+10,x=e(v.xz*vec2(1,5)*2.+y);"
"m=-v.z-v.y;"
"r=v.y-x*.1;"
"f=min(f,m);"
"f=min(f,r);"
"return f;"
"}"
"vec3 h(vec3 v)"
"{"
"vec2 f=vec2(PRECISION,0);"
"return normalize(vec3(s(v+f.xyy)-s(v-f.xyy),s(v+f.yxy)-s(v-f.yxy),s(v+f.yyx)-s(v-f.yyx)));"
"}"
"vec3 e(vec3 v,vec3 y)"
"{"
"float x=0.,f;"
"for(int r=0;r<STEPS;r++)"
"{"
"f=s(v+y*x);"
"if(f<PRECISION)"
"d=true;"
"if(d==true||x>DEPTH)"
"{"
"break;"
"}"
"x+=f;"
"}"
"return v+y*x;"
"}"
"vec3 i(vec3 v)"
"{"
"float f=1e+10;"
"vec3 d=h(v),l=normalize(x-v),i=vec3(1);"
"float s=length(v-x),N=max(dot(d,normalize(x-v)),0.),n=pow(N,10.);"
"if(m<f)"
"{"
"float S=e(vec2(v.x+y,v.z))*e(v.xx);"
"i=vec3(S)*vec3(0,1,.5);"
"f=m;"
"}"
"if(r<f)"
"i*=vec3(N)*vec3(.7,.9,1)+n,i*=1./s,i*=exp(1./length(v-x));"
"return i;"
"}"
"void main()"
"{"
"v=(2.*gl_FragCoord.xy-l.xy)/l.xx;"
"vec3 y=e(f,n(f,vec3(0))),x=vec3(0);"
"if(d==true)"
"x=i(y);"
"gl_FragColor=vec4(x,1.);"
"}";

#elif 1 // Hypercube
const char *fragmentShader = \
//"float v=gl_Color.x;"
"uniform float iGlobalTime;"
"float v=iGlobalTime;"
"vec2 m=vec2(1280,720);\n"
"#define PRECISION 0.01\n"
"#define DEPTH 1000.0\n"
"#define STEPS 32\n"
"#define STEPS 32\n"
"#define PRECISION 0.01\n"
"#define DEPTH 10.0\n"
"vec3 f=vec3(0,0,-2.5);"
"vec2 r;"
"bool i=false;"
"float e,x=.025,y=mod(v,1.),N=(sin(v*.5)+1.)/2.*.15+.15;"
"const vec3 P=vec3(-.5,-.5,-.5),d=vec3(.5,-.5,-.5),s=vec3(-.5,-.5,.5),n=vec3(.5,-.5,.5),c=vec3(-.5,.5,-.5),o=vec3(.5,.5,-.5),t=vec3(-.5,.5,.5),a=vec3(.5,.5,.5);"
"vec3 S=vec3(-.5+N,-.5+N,-.5+N),l=vec3(.5-N,-.5+N,-.5+N),E=vec3(-.5+N,-.5+N,.5-N),u=vec3(.5-N,-.5+N,.5-N),g=vec3(-.5+N,.5-N,-.5+N),I=vec3(.5-N,.5-N,-.5+N),C=vec3(-.5+N,.5-N,.5-N),T=vec3(.5-N,.5-N,.5-N),H=mix(P,S,y),R=mix(c,g,y),O=mix(s,E,y),z=mix(t,C,y),F=mix(n,s,y),D=mix(d,P,y),b=mix(o,c,y),p=mix(a,t,y),k=mix(S,l,y),h=mix(E,u,y),w=mix(g,I,y),Z=mix(C,T,y),Y=mix(u,n,y),X=mix(l,d,y),W=mix(I,o,y),V=mix(T,a,y);"
"float U(vec3 m,vec3 e,vec3 v)"
"{"
"vec3 N=m-e,y=v-e;"
"float i=clamp(dot(N,y)/dot(y,y),0.,1.);"
"return length(N-y*i)-x;"
"}"
"mat3 U(float e)"
"{"
"float N=sin(e),U=cos(e);"
"return mat3(U,-N,0,N,U,0,0,0,1);"
"}"
"mat3 Q(float e)"
"{"
"float N=sin(e),y=cos(e);"
"return mat3(1,0,0,0,y,N,0,-N,y);"
"}"
"mat3 M(float e)"
"{"
"float N=sin(e),y=cos(e);"
"return mat3(y,0,-N,0,1,0,N,0,y);"
"}"
"vec3 M(vec3 e,vec3 y)"
"{"
"vec2 N=(2.*gl_FragCoord.xy-m.xy)/m.xx;"
"vec3 U=normalize(y-e),v=vec3(0,1,0),p=cross(v,U);"
"return normalize(p*N.x+cross(U,p)*N.y+U);"
"}"
"float L(vec3 N)"
"{"
"return N*=Q(.785),e=1e+10,e=min(e,U(N,H,D)),e=min(e,U(N,O,F)),e=min(e,U(N,R,b)),e=min(e,U(N,z,p)),e=min(e,U(N,H,O)),e=min(e,U(N,R,z)),e=min(e,U(N,H,R)),e=min(e,U(N,O,z)),e=min(e,U(N,D,F)),e=min(e,U(N,b,p)),e=min(e,U(N,D,b)),e=min(e,U(N,F,p)),e=min(e,U(N,k,h)),e=min(e,U(N,w,Z)),e=min(e,U(N,k,w)),e=min(e,U(N,h,Z)),e=min(e,U(N,h,Y)),e=min(e,U(N,k,X)),e=min(e,U(N,w,W)),e=min(e,U(N,Z,V)),e=min(e,U(N,X,W)),e=min(e,U(N,Y,V)),e=min(e,U(N,X,Y)),e=min(e,U(N,W,V)),e=min(e,U(N,V,p)),e=min(e,U(N,X,D)),e=min(e,U(N,Y,F)),e=min(e,U(N,W,b)),e=min(e,U(N,w,R)),e=min(e,U(N,Z,z)),e=min(e,U(N,k,H)),e=min(e,U(N,h,O)),e;"
"}"
"vec3 K(vec3 e)"
"{"
"vec2 N=vec2(PRECISION,0);"
"return normalize(vec3(L(e+N.xyy)-L(e-N.xyy),L(e+N.yxy)-L(e-N.yxy),L(e+N.yyx)-L(e-N.yyx)));"
"}"
"vec3 K(vec3 N,vec3 y)"
"{"
"float e=0.,m;"
"i=false;"
"for(int v=0;v<STEPS;v++)"
"{"
"m=L(N+y*e);"
"if(m<PRECISION)"
"{"
"i=true;"
"break;"
"}"
"if(e>DEPTH)"
"{"
"break;"
"}"
"e+=m;"
"}"
"return N+y*e;"
"}"
"vec3 J(vec3 N)"
"{"
"vec3 e=K(N),y=normalize(f-N);"
"float v=1e+10,U=max(dot(e,y),0.),k=pow(U,1.);"
"return vec3(100,0,10)*U*max(.5-k,.01);"
"}"
"void main()"
"{"
"f*=Q(v)*U(v);"
"r=(2.*gl_FragCoord.xy-m.xy)/m.xx;"
"vec3 e=K(f,M(f,vec3(0))),N=J(e);"
"if(i==false)"
"N=vec3(1.-length(r)*vec3(1.2,1.2,1)*.5);"
"gl_FragColor=vec4(N,1.);"
"}";

#elif 0 // Infinite city

const char *fragmentShader =
"float v=gl_Color.x;"
"vec2 m=vec2(100.,100.),z=vec2(1280.,720.);\n"
"#define R_0 4096.0\n"
"#define R_1 512.0\n"
"vec2 n(vec2 z)"
"{"
"z/=vec2(1e+07,1e+09);"
"float v=R_0*sin(dot(vec3(z,1.),vec3(17.,59.4,15.)));"
"vec3 f;"
"f.z=fract(R_1*v);"
"v*=.125;"
"f.x=fract(R_1*v);"
"v*=.125;"
"f.y=fract(R_1*v);"
"return f.xz;"
"}"
"vec3 n(vec2 z,vec2 x)"
"{"
"float y=.1+sin(v*.5);"
"vec2 m=floor(z)+x,s=(n(m)-.5)*y,i=m+.5+s;"
"float f=length(i-z);"
"return vec3(i,f);"
"}"
"vec3 x(vec2 z)"
"{"
"vec3 v=vec3(-1,0,1),m[9];"
"m[0]=n(z,v.xx);"
"m[1]=n(z,v.yx);"
"m[2]=n(z,v.zx);"
"m[3]=n(z,v.xy);"
"m[4]=n(z,v.yy);"
"m[5]=n(z,v.zy);"
"m[6]=n(z,v.xz);"
"m[7]=n(z,v.yz);"
"m[8]=n(z,v.zz);"
"vec3 f;"
"f.z=min(min(min(min(m[0].z,m[1].z),min(m[2].z,m[3].z)),min(min(m[4].z,m[5].z),min(m[6].z,m[7].z))),m[8].z);"
"f.xy=m[8].xy;"
"for(int y=0;y<8;y++)"
"{"
"if(f.z==m[y].z)"
"f=m[y],m[y]=m[8];"
"}"
"float y;"
"y=min(min(min(m[0].z,m[1].z),min(m[2].z,m[3].z)),min(min(m[4].z,m[5].z),min(m[6].z,m[7].z)));"
"return vec3(f.xy,y-f.z);"
"}"
"float x(vec3 m,float z)"
"{"
"vec3 f=x(m.xz);"
"vec2 y=n(f.xy*4.);"
"float i=(.2+.3*y.y-f.z)*.5,s=y.x*2.5*sin(v*.5);"
"s=mix(.2,2.,pow(s,2.));"
"s=m.y-s;"
"s=max(min(s,.008*z),m.y-2.);"
"if(i>0.&&s>0.)"
"i=sqrt(i*i+s*s);"
"else"
" i=max(i,s);"
"i=min(i,m.y);"
"return i;"
"}"
"float f(vec3 z)"
"{"
"return x(z,10.);"
"}"
"vec3 t(vec3 z)"
"{"
"vec3 v;"
"vec2 y=vec2(0,1);"
"\n#ifdef FIRST_PERSON\n"
"y*=.004;"
"\n#else\n"
"y*=.04;"
"\n#endif\n"
"v.x=f(z+y.yxx)-f(z-y.yxx);"
"v.y=f(z+y.xyx)-f(z-y.xyx);"
"v.z=f(z+y.xxy)-f(z-y.xxy);"
"if(dot(v,v)==0.)"
"v.y+=1.;"
"return normalize(v);"
"}"
"void main()"
"{"
"vec2 y=m.xy/z.xy;"
"float f;"
"\n#ifdef FIRST_PERSON\n"
"vec2 i=vec2(-.2,0.)+vec2(6.28,-1.5)*y;"
"vec3 s=vec3(0,.03,0)+v*vec3(-.02,0,.02);"
"f=1.;"
"for(int r=0;r<20;r++)"
"{"
"if(f<.01)"
"break;"
"f=x(s.xz).z*.3;"
"s.xz+=f;"
"}"
"float r=.7;"
"\n#else\n"
"vec2 R=vec2(-.2,.28)+vec2(1.6,.5)*y;"
"vec3 e=vec3(0,5,0)+vec3(1,0,1)*v+vec3(0,6,0)*y.y;"
"e+=-10.*vec3(sin(R.x),0,cos(R.x));"
"float c=.4;"
"\n#endif\n"
"vec3 d=normalize(vec3(gl_FragCoord.xy-z.xy*.5,z.x*c));"
"d.yz=d.yz*cos(R.y)+d.zy*sin(R.y)*vec2(-1,1);"
"d.xz=d.xz*cos(R.x)+d.zx*sin(R.x)*vec2(1,-1);"
"float g=0.;"
"f=1.;"
"for(int F=0;F<100;F++)"
"{"
"if(f<.003)"
"break;"
"f=x(e+d*g,g);"
"g+=f;"
"}"
"vec3 F=e+d*g,w=t(F),a=x(F.xz);"
"vec2 p=n(a.xy).xy;"
"vec4 b=mix(mix(vec4(.9,.2,0.,0),vec4(1,1,1,0),p.x),mix(vec4(0,.2,.8,1),vec4(0,0,0,1),p.x),p.y);"
"if(fract(F.y*8.)<.4&&w.y<.6)"
"b=mix(vec4(0,0,0,0),vec4(1,1,1,0),p.x);"
"b.w=mix(b.w,0.,step(.2,w.y));"
"b=mix(vec4(.05,.05,.05,0),b,step(.07,abs(a.z-.08)));"
"vec3 k=max(0.,dot(w,normalize(vec3(-2,3,-1))))*vec3(1,.9,.8);"
"k+=vec3(.2);"
"vec3 o=b.xyz*k;"
"float l=pow(1.+dot(w,d),5.);"
"if(l>1.)"
"l=0.;"
"l=mix(.2,1.,l);"
"if(f>.01)"
"o=mix(vec3(.3),vec3(.85,1.,1.2),smoothstep(-.1,.1,d.y));"
"o*=mix(.2,1.,smoothstep(0.,.7,F.y));"
"o*=pow(vec3(.7,.57,.3),vec3(g*.02));"
"o+=vec3(.7,.9,1.2)*(1.-exp(-g*.02));"
"gl_FragColor=vec4(o,1);"
"}";


#elif 1 // Ice cave

const char *fragmentShader =
"#define PI 3.14159265359\nstruct Ray{vec3 origin;vec3 direction;};struct Object{vec3 position;float distance;int material;};"
"vec3 v=vec3(0,0,0),f=vec3(0,0,1);"
"float m=gl_Color.x*.7+15.;"
"vec2 d=vec2(1280.,720.);"
"float n(vec3 v,float n)"
"{"
"return length(v.yx)-n;"
"}"
"mat3 n(float v)"
"{"
"float c=sin(v),y=cos(v);"
"return mat3(1,0,0,0,y,c,0,-c,y);"
"}"
"mat3 s(float v)"
"{"
"float c=sin(v),y=cos(v);"
"return mat3(y,0,-c,0,1,0,c,0,y);"
"}"
"vec3 e(vec2 v)"
"{"
"vec2 m=vec2(.01,0);"
"vec3 n=normalize(vec3(1.,0.,1.));"
"return n;"
"}"
"Object c(vec3 v)"
"{"
"vec3 c=vec3(v.x+sin(v.z),v.y+sin(v.z),v.z);"
"c.xy*=vec2(sin(v.z+c.x+c.y)*sin(v.z*2.-c.y*v.y)*sin(c.z-v.x*2.)*mix(v.x-c.y,v.y,c.y*v.x)+c.y*v.x);"
"float y=max(n(c,.2),-n(c,.1));"
"return Object(v,y,0);"
"}"
"vec3 t(vec3 v)"
"{"
"vec2 n=vec2(.0001,0);"
"vec3 m=normalize(vec3(c(v+n.xyy).distance-c(v-n.xyy).distance,c(v+n.yxy).distance-c(v-n.yxy).distance,c(v+n.yyx).distance-c(v-n.yyx).distance));"
"return m;"
"}"
"void main()"
"{"
"v.z+=m;"
"f.z+=m;"
"v.y=f.y=-sin(v.z);"
"v.x=f.x=-sin(v.z);"
"vec2 y=(2.*gl_FragCoord.xy-d.xy)/d.xx;"
"vec3 x=normalize(f-v),r=vec3(0,1,0),z=cross(r,x);"
"Ray i=Ray(v,normalize(z*y.x+cross(x,z)*y.y+x));"
"i.direction*=n(-cos(v.z+.4));"
"i.direction*=s(cos(v.z));"
"float O=0.;"
"Object l;"
"for(int R=0;R<128;R++)"
"{"
"l=c(i.origin+i.direction*O);"
"if(l.distance<.0001||O>50.)"
"{"
"break;"
"}"
"O+=l.distance;"
"}"
"float R=5.;"
"vec3 o=vec3(.2,.1,.8),a=e(l.position.xz*R),g=-normalize(t(l.position)+a);"
"float p=length(f-l.position),u=max(dot(g,reflect(normalize(f-l.position),g)),0.),b=pow(u,50.);"
"o+=u*vec3(0,.5,1)+b*vec3(1,.5,0);"
"o*=min(1.,1./p);"
"gl_FragColor=vec4(o,1.);"
"}";



#else // Test uv

const char *fragmentShader =
"void main() {"
"vec2 uv = gl_FragCoord.xy / vec2(1280.0, 720.0);"
"gl_FragColor = vec4(uv,0.4,1);"
"}";

#endif

#endif // SHADER_H_
