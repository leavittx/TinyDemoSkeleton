/* File generated with Shader Minifier 1.1.4
 * http://www.ctrl-alt-test.fr
 */
#ifndef SHADER_CODE_H_
# define SHADER_CODE_H_
# define VAR_T "y"

const char *shader_frag =
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

#endif // SHADER_CODE_H_