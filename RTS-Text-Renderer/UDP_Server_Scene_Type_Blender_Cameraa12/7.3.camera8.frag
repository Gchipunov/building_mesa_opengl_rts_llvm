#version 330 core

// ------------------- Uniforms and Inputs -------------------
uniform vec3 iResolution;
uniform float iTime;
uniform int iFrame;
uniform vec4 iMouse;


out vec4 FragColor;

in vec2 TexCoord;
in float vvtype;
// texture samplers

uniform int iUniformsRenderType;

uniform mat4 projection;
uniform mat4 view;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform sampler2D texture4;
uniform sampler2D texture5;

uniform sampler2D texture6;


#if HW_PERFORMANCE==0
#define AA 1
#else
#define AA 2  // Set AA to 1 if your machine is too slow
#endif


// https://iquilezles.org/articles/smin
float smax( float a, float b, float k )
{
    float h = max(k-abs(a-b),0.0);
    return max(a, b) + h*h*0.25/k;
}

// https://iquilezles.org/articles/distfunctions
float sdSphere( in vec3 p, in float r )
{
    return length(p)-r;
}

float sdVerticalSemiCapsule( vec3 p, float h, float r )
{
    p.y = max(p.y-h,0.0);
    return length( p ) - r;
}

// https://iquilezles.org/articles/distfunctions2d
float sdCross( in vec2 p, in vec2 b, float r ) 
{
    p = abs(p); p = (p.y>p.x) ? p.yx : p.xy;
    
	vec2  q = p - b;
    float k = max(q.y,q.x);
    vec2  w = (k>0.0) ? q : vec2(b.y-p.x,-k);
    
    return sign(k)*length(max(w,0.0)) + r;
}

// https://www.shadertoy.com/view/MlycD3
float dot2( in vec2 v ) { return dot(v,v); }
float sdTrapezoid( in vec2 p, in float r1, float r2, float he )
{
    vec2 k1 = vec2(r2,he);
    vec2 k2 = vec2(r2-r1,2.0*he);

	p.x = abs(p.x);
    vec2 ca = vec2(max(0.0,p.x-((p.y<0.0)?r1:r2)), abs(p.y)-he);
    vec2 cb = p - k1 + k2*clamp( dot(k1-p,k2)/dot2(k2), 0.0, 1.0 );
    
    float s = (cb.x < 0.0 && ca.y < 0.0) ? -1.0 : 1.0;
    
    return s*sqrt( min(dot2(ca),dot2(cb)) );
}

// https://iquilezles.org/articles/intersectors
vec2 iSphere( in vec3 ro, in vec3 rd, in float rad )
{
	float b = dot( ro, rd );
	float c = dot( ro, ro ) - rad*rad;
	float h = b*b - c;
	if( h<0.0 ) return vec2(-1.0);
    h = sqrt(h);
	return vec2(-b-h, -b+h );
}

//----------------------------------

float dents( in vec2 q, in float tr, in float y )
{
    const float an = 6.283185/12.0;
    float fa = (atan(q.y,q.x)+an*0.5)/an;
    float sym = an*floor(fa);
    vec2 r = mat2(cos(sym),-sin(sym), sin(sym), cos(sym))*q;
    
#if 1
    float d = length(max(abs(r-vec2(0.17,0))-tr*vec2(0.042,0.041*y),0.0));
#else
    float d = sdTrapezoid( r.yx-vec2(0.0,0.17), 0.085*y, 0.028*y, tr*0.045 );
#endif

	return d - 0.005*tr;
}

vec4 gear(vec3 q, float off, float time)
{
    {
    float an = 2.0*time*sign(q.y) + off*6.283185/24.0;
    float co = cos(an), si = sin(an);
    q.xz = mat2(co,-si,si,co)*q.xz;
    }
    
    q.y = abs(q.y);
    
    float an2 = 2.0*min(1.0-2.0*abs(fract(0.5+time/10.0)-0.5),1.0/2.0);
    vec3 tr = min( 10.0*an2 - vec3(4.0,6.0,8.0),1.0);
    
    // ring
    float d = abs(length(q.xz) - 0.155*tr.y) - 0.018;

    // add dents
    float r = length(q);
    d = min( d, dents(q.xz,tr.z, r) );

    
    // slice it
    float de = -0.0015*clamp(600.0*abs(dot(q.xz,q.xz)-0.155*0.155),0.0,1.0);
    d = smax( d, abs(r-0.5)-0.03+de, 0.005*tr.z );

    // add cross
    float d3 = sdCross( q.xz, vec2(0.15,0.022)*tr.y, 0.02*tr.y );
    vec2 w = vec2( d3, abs(q.y-0.485)-0.005*tr.y );
    d3 = min(max(w.x,w.y),0.0) + length(max(w,0.0))-0.003*tr.y;
    d = min( d, d3 ); 
        
    // add pivot
    d = min( d, sdVerticalSemiCapsule( q, 0.5*tr.x, 0.01 ));

    // base
    d = min( d, sdSphere(q-vec3(0.0,0.12,0.0),0.025) );
    
    return vec4(d,q.xzy);
}

vec2 rot( vec2 v )
{
    return vec2(v.x-v.y,v.y+v.x)*0.707107;
}
    
vec4 map( in vec3 p, float time )
{
    // center sphere
    vec4 d = vec4( sdSphere(p,0.12), p );
    
    // gears. There are 18, but we only evaluate 4    
    vec3 qx = vec3(rot(p.zy),p.x); if(abs(qx.x)>abs(qx.y)) qx=qx.zxy;
    vec3 qy = vec3(rot(p.xz),p.y); if(abs(qy.x)>abs(qy.y)) qy=qy.zxy;
    vec3 qz = vec3(rot(p.yx),p.z); if(abs(qz.x)>abs(qz.y)) qz=qz.zxy;
    vec3 qa = abs(p); qa = (qa.x>qa.y && qa.x>qa.z) ? p.zxy : 
                           (qa.z>qa.y             ) ? p.yzx :
                                                      p.xyz;
    vec4 t;
    t = gear( qa,0.0,time ); if( t.x<d.x ) d=t;
    t = gear( qx,1.0,time ); if( t.x<d.x ) d=t;
    t = gear( qz,1.0,time ); if( t.x<d.x ) d=t;
    t = gear( qy,1.0,time ); if( t.x<d.x ) d=t;
    
	return d;
}

 #define ZERO min(iFrame,0)

//#define ZERO min( int( iTime)/1000 ,0)

// https://iquilezles.org/articles/normalsSDF
vec3 calcNormal( in vec3 pos, in float time )
{
#if 0
    vec2 e = vec2(1.0,-1.0)*0.5773;
    const float eps = 0.00025;
    return normalize( e.xyy*map( pos + e.xyy*eps, time ).x + 
					  e.yyx*map( pos + e.yyx*eps, time ).x + 
					  e.yxy*map( pos + e.yxy*eps, time ).x + 
					  e.xxx*map( pos + e.xxx*eps, time ).x );
#else
    // klems's trick to prevent the compiler from inlining map() 4 times
    vec3 n = vec3(0.0);
    for( int i=ZERO; i<4; i++ )
    {
        vec3 e = 0.5773*(2.0*vec3((((i+3)>>1)&1),((i>>1)&1),(i&1))-1.0);
        n += e*map(pos+0.0005*e,time).x;
    }
    return normalize(n);
#endif    
}

float calcAO( in vec3 pos, in vec3 nor, in float time )
{
	float occ = 0.0;
    float sca = 1.0;
    for( int i=ZERO; i<5; i++ )
    {
        float h = 0.01 + 0.12*float(i)/4.0;
        float d = map( pos+h*nor, time ).x;
        occ += (h-d)*sca;
        sca *= 0.95;
    }
    return clamp( 1.0 - 3.0*occ, 0.0, 1.0 );
}

// https://iquilezles.org/articles/rmshadows
float calcSoftshadow( in vec3 ro, in vec3 rd, in float k, in float time )
{
    float res = 1.0;
    
    // bounding sphere
    vec2 b = iSphere( ro, rd, 0.535 );
	if( b.y>0.0 )
    {
        // raymarch
        float tmax = b.y;
        float t    = max(b.x,0.001);
        for( int i=0; i<64; i++ )
        {
            float h = map( ro + rd*t, time ).x;
            res = min( res, k*h/t );
            t += clamp( h, 0.012, 0.2 );
            if( res<0.001 || t>tmax ) break;
        }
    }
    
    return clamp( res, 0.0, 1.0 );
}

vec4 intersect( in vec3 ro, in vec3 rd, in float time )
{
    vec4 res = vec4(-1.0);
    
    // bounding sphere
    vec2 tminmax = iSphere( ro, rd, 0.535 );
	if( tminmax.y>0.0 )
    {
        // raymarch
        float t = max(tminmax.x,0.001);
        for( int i=0; i<128 && t<tminmax.y; i++ )
        {
            vec4 h = map(ro+t*rd,time);
            if( h.x<0.001 ) { res=vec4(t,h.yzw); break; }
            t += h.x;
        }
    }
    
    return res;
}

mat3 setCamera( in vec3 ro, in vec3 ta, float cr )
{
	vec3 cw = normalize(ta-ro);
	vec3 cp = vec3(sin(cr), cos(cr),0.0);
	vec3 cu = normalize( cross(cw,cp) );
	vec3 cv =          ( cross(cu,cw) );
    return mat3( cu, cv, cw );
}

vec3 mainImageSphereGears( in vec2 fragCoord)
{
 vec3 tot = vec3(0.0);
    
    #if AA>1
    for( int m=ZERO; m<AA; m++ )
    for( int n=ZERO; n<AA; n++ )
    {
        // pixel coordinates
        vec2 o = vec2(float(m),float(n)) / float(AA) - 0.5;
        vec2 p = (2.0*(fragCoord+o)-iResolution.xy)/iResolution.y;
        float d = 0.5*sin(fragCoord.x*147.0)*sin(fragCoord.y*131.0);
        float time = iTime - 0.5*(1.0/24.0)*(float(m*AA+n)+d)/float(AA*AA-1);
        #else    
        vec2 p = (2.0*fragCoord-iResolution.xy)/iResolution.y;
        float time = iTime;
        #endif

	    // camera	
        float an = 6.2831*time/40.0;
        vec3 ta = vec3( 0.0, 0.0, 0.0 );
        vec3 ro = ta + vec3( 1.3*cos(an), 0.5, 1.2*sin(an) );
        
        ro += 0.005*sin(92.0*time/40.0+vec3(0.0,1.0,3.0));
        ta += 0.009*sin(68.0*time/40.0+vec3(2.0,4.0,6.0));
        
        // camera-to-world transformation
        mat3 ca = setCamera( ro, ta, 0.0 );
        
        // ray direction
        float fl = 2.0;
        vec3 rd = ca * normalize( vec3(p,fl) );

        // background
        vec3 col = vec3(1.0+rd.y)*0.03;
        
        // raymarch geometry
        vec4 tuvw = intersect( ro, rd, time );
        if( tuvw.x>0.0 )
        {
            // shading/lighting	
            vec3 pos = ro + tuvw.x*rd;
            vec3 nor = calcNormal(pos, time);
                        
            vec3 te = 0.5*texture( texture1, tuvw.yz*2.0 ).xyz+
                      0.5*texture( texture1, tuvw.yw*1.0 ).xyz;
            
            vec3 mate = 0.22*te;
            float len = length(pos);
            
            mate *= 1.0 + vec3(2.0,0.5,0.0)*(1.0-smoothstep(0.121,0.122,len) ) ;
            
            float focc  = 0.1+0.9*clamp(0.5+0.5*dot(nor,pos/len),0.0,1.0);
                  focc *= 0.1+0.9*clamp(len*2.0,0.0,1.0);
            float ks = clamp(te.x*1.5,0.0,1.0);
            vec3  f0 = mate;
            float kd = (1.0-ks)*0.125;
            
            float occ = calcAO( pos, nor, time ) * focc;
            
            col = vec3(0.0);
            
            // side
            {
            vec3  lig = normalize(vec3(0.8,0.2,0.6));
            float dif = clamp( dot(nor,lig), 0.0, 1.0 );
            vec3  hal = normalize(lig-rd);
            float sha = 1.0; if( dif>0.001 ) sha = calcSoftshadow( pos+0.001*nor, lig, 20.0, time );
            vec3  spe = pow(clamp(dot(nor,hal),0.0,1.0),16.0)*(f0+(1.0-f0)*pow(clamp(1.0+dot(hal,rd),0.0,1.0),5.0));
            col += kd*mate*2.0*vec3(1.00,0.70,0.50)*dif*sha;
            col += ks*     2.0*vec3(1.00,0.80,0.70)*dif*sha*spe*3.14;
            }

            // top
            {
            vec3  ref = reflect(rd,nor);
            float fre = clamp(1.0+dot(nor,rd),0.0,1.0);
            float sha = occ;
            col += kd*mate*25.0*vec3(0.19,0.22,0.24)*(0.6 + 0.4*nor.y)*sha;
            col += ks*     25.0*vec3(0.19,0.22,0.24)*sha*smoothstep( -1.0+1.5*focc, 1.0-0.4*focc, ref.y ) * (f0 + (1.0-f0)*pow(fre,5.0));
            }
            
            // bottom
            {
            float dif = clamp(0.4-0.6*nor.y,0.0,1.0);
            col += kd*mate*5.0*vec3(0.25,0.20,0.15)*dif*occ;
            }
        }
        
        // compress        
        // col = 1.2*col/(1.0+col);
        
        // vignetting
        col *= 1.0-0.1*dot(p,p);
        
        // gamma        
	    tot += pow(col,vec3(0.45) );
    #if AA>1
    }
    tot /= float(AA*AA);
    #endif

    // s-curve    
    tot = min(tot,1.0);
    tot = tot*tot*(3.0-2.0*tot);
    
    // cheap dithering
    tot += sin(TexCoord.x*114.0)*sin(TexCoord.y*211.1)/512.0;
    return tot;

}



#define PI acos(-1.)

float exponentialSmoothMmin(float a, float b, float k)
{
    float res = exp( -k*a ) + exp( -k*b );
    return -log( res )/k;
}

float polynomialSmoothMmin( float a, float b, float k )
{
    float h = clamp( 0.5+0.5*(b-a)/k, 0.0, 1.0 );
    return mix( b, a, h ) - k*h*(1.0-h);
}

float segmentDistance(vec2 p, vec2 a, vec2 b, out float h)
{
	vec2 ap = p - a;
	vec2 ab = b - a;
	h = clamp(dot(ap, ab) / dot(ab, ab), 0., 1.);
	return length(ap - ab * h);
}

vec4 limb(vec2 p, vec2 a, vec2 b, float ra, float rb, float fill, float k)
{
	float da = length(a - p) - ra;
	float db = length(b - p) - rb;
    float h;
    float dmid = segmentDistance(p, a, b, h);

    float bump = sin(2.*PI * (pow(h, 0.9) - 0.25)) * 0.5 + 0.5;
    dmid -= mix(ra, rb, h + fill * bump);

    float d = exponentialSmoothMmin(dmid, min(da, db), k);
    return vec4(d, da, db, dmid);
}

// See: https://www.shadertoy.com/view/XcVGRR
vec3 debugDistance(vec3 iResolution, float d, vec3 color)
{
    float refWidth = iResolution.y / 1080.;

    float dd1 = fwidth(d);
    float width1 = 2.5 * dd1 * refWidth;
    float iso1 = smoothstep(1. - width1 - dd1, 1. - width1 + dd1, abs(fract(d) * 2. - 1.));

    float dd5 = fwidth(5. * d);
    float width5 = 0.75 * dd5 * refWidth;
    float iso5 = smoothstep(1. - width5 - dd5, 1. - width5 + dd5, abs(fract(5.*d) * 2. - 1.));

    float dd0 = fwidth(d);
    float width0 = 3. * dd0 * refWidth;
    float iso0 = smoothstep(1. - width0 - dd0, 1. - width0 + dd0, 1. - abs(d));

    float isoLines = max(iso0, max(iso1, iso5));

    vec3 background = (d > 0. ? vec3(1.) : mix(vec3(0.8), color, 0.1));
    vec3 lineColor = mix(color * (d > 0. ? 1. : 0.8), vec3(0.), iso0);

    return mix(background, lineColor, isoLines);
}


vec3 mainImageButton2( in vec2 fragCoord )
{
	vec2 uv = 8.*fragCoord.xy / iResolution.y;

    vec2 p1 = vec2(sin(2.*iTime), cos(iTime))+vec2(3.);
    vec2 p2 = vec2(sin(3.*iTime), cos(1.2*iTime))+vec2(10., 4.);
    
    vec4 d = limb(uv, p1, p2, 0.85, 1.5, 0.8, 5.);

    
    vec3 color = 1.
        * debugDistance(iResolution, d.x, vec3(0.8, 0.8, 0.8))
        * debugDistance(iResolution, d.y, vec3(0.8, 0.5, 1.))
        * debugDistance(iResolution, d.z, vec3(0.5, 0.8, 1.))
        * debugDistance(iResolution, d.w, vec3(0.5, 1.0, 0.5))
        ;
        return color;
	//fragColor = vec4(color,1.0);
}







// b.x = half width
// b.y = half height
// r.x = roundness top-right  
// r.y = roundness boottom-right
// r.z = roundness top-left
// r.w = roundness bottom-left
float sdRoundBox( in vec2 p, in vec2 b, in vec4 r ) 
{
    r.xy = (p.x>0.0)?r.xy : r.zw;
    r.x  = (p.y>0.0)?r.x  : r.y;
    vec2 q = abs(p)-b+r.x;
    return min(max(q.x,q.y),0.0) + length(max(q,0.0)) - r.x;
}

vec3 mainImageButton3(  in vec2 fragCoord )
{
	vec2 p = (2.0*fragCoord-iResolution.xy)/iResolution.y;
    vec2 m = (2.0*iMouse.xy-iResolution.xy)/iResolution.y;

	vec2 si = vec2(0.9,0.6) + 0.3*cos(iTime+vec2(0,2));
    vec4 ra = 0.3 + 0.3*cos( 2.0*iTime + vec4(0,1,2,3) );
    ra = min(ra,min(si.x,si.y));

	float d = sdRoundBox( p, si, ra );

    vec3 col = (d>0.0) ? vec3(0.9,0.6,0.3) : vec3(0.65,0.85,1.0);
	col *= 1.0 - exp2(-20.0*abs(d));
	col *= 0.8 + 0.2*cos(120.0*d);
	col = mix( col, vec3(1.0), 1.0-smoothstep(0.0,0.01,abs(d)) );

    if( iMouse.z>0.001 )
    {
    d = sdRoundBox(m, si, ra );
    col = mix(col, vec3(1.0,1.0,0.0), 1.0-smoothstep(0.0, 0.005, abs(length(p-m)-abs(d))-0.0025));
    col = mix(col, vec3(1.0,1.0,0.0), 1.0-smoothstep(0.0, 0.005, length(p-m)-0.015));
    }
    return col;
	//fragColor = vec4(col,1.0);
}

//



// We'll use uniforms to pass parameters, which is the standard
// GLSL way to handle constant data from the application.
// For this example, we'll keep them as #defines for simplicity,
// similar to the original code.

#define BrickColor vec3(0.8, 0.2, 0.1)
#define MortarColor vec3(0.7, 0.7, 0.7)
//#define BrickSize vec2(40.0, 10.0)
//#define BrickPct vec2(0.75, 0.8)

//#define BrickSize vec2(0.40, 0.10)
//#define BrickPct vec2(0.75, 0.8)
#define BrickSize vec2(0.20, 0.05)
#define BrickPct vec2(0.95, 0.8)

#define LightIntensity 0.8

// GLSL uses 'in' for vertex shader outputs.
// vPosition is the texture coordinate passed from the vertex shader.
//in vec2 vPosition;

// The final output color is written to this variable.
//out vec4 FragColor;

vec3 mainProceduralBrick(in vec2 fragCoord)
{
    // The vPosition is the screen-space position of the pixel.
   // vec2 MCposition = vPosition;
    vec2 MCposition = fragCoord;
    MCposition.x = MCposition.x + sin(iTime);
    // Calculate brick pattern
    vec2 position = MCposition / BrickSize;

    // Offset every other row for staggered brick pattern
    if(fract(position.y * 0.5) > 0.5)
    {
        position.x += 0.5;
    }

    // Get fractional part for pattern repetition
    position = fract(position);

    // Determine brick vs mortar areas
    vec2 useBrick = step(vec2(position), BrickPct);

    // Mix colors based on brick pattern
    vec3 color = mix(MortarColor, BrickColor, useBrick.x * useBrick.y);

    // Apply lighting
    color *= LightIntensity;

    // Ensure color values stay in a valid range.
    // The GLSL equivalent of HLSL's saturate() is clamp().
    color = clamp(color, 0.0, 1.0);
    return color;
    // Output the final color to FragColor.
  //  FragColor = vec4(color, 1.0);
}


// A simple pseudo-random noise function
// This function creates a repeatable noise value based on the input coordinates
// and a time component for animation.
float noise(in vec2 p, in float t) {
    // Combine coordinates and time, and use the fractional part
    return fract(sin(dot(p, vec2(12.9898, 78.233)) + t) * 43758.5453);
}

vec3 mainImageNoiseUIPanel( in vec2 fragCoord )
{
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = fragCoord / iResolution.xy;

    // Base color is a clean white
    vec3 col = vec3(1.0, 1.0, 1.0);

    // Collision logic from the original code (unchanged)
    int iCollision = 0;
    if (uv.x < 0.075 && uv.y < 0.075) {
        col = vec3(1.0, sin(uv.x), 0.0);
        iCollision = 1;
    }

    if (uv.x + uv.y < 0.1) {
        col = vec3(0.0, 0.0, 0.0);
        iCollision = iCollision + 1;
    }

    if (iCollision == 2) {
        col = vec3(0.0, sin(uv.x), 1.0);
    }

    float yuv = 1.0 - uv.y;
    if (uv.x + yuv < 0.1) {
        col = vec3(0.0, 0.0, 0.0);
    }

    float xuv = 1.0 - uv.x;
    if (xuv + uv.y < 0.1) {
        col = vec3(0.0, 0.0, 0.0);
    }

    if (xuv + yuv < 0.1) {
        col = vec3(0.0, 0.0, 0.0);
    }

    // --- Gradient and Noise Effects ---

    // Calculate the distance from each edge
    float distToLeft = uv.x;
    float distToRight = 1.0 - uv.x;
    float distToTop = uv.y;
    float distToBottom = 1.0 - uv.y;

    // Find the minimum distance to any edge
    float minEdgeDist = min(min(distToLeft, distToRight), min(distToTop, distToBottom));

    // Create a smooth gradient using smoothstep
    // The gradient will transition smoothly from 0.0 to 1.0
    // close to the edges and in the center, respectively.
    float gradient = smoothstep(0.0, 0.2, minEdgeDist);

    // Generate electronic noise
    // The noise function is called with a scaled UV coordinate and time to make it animate.
    float electronicNoise = noise(uv * 100.0, iTime * 50.0);
    // Apply a threshold to make the noise appear as flickering dots or static.
    electronicNoise = step(0.7, electronicNoise);

    // Combine the base color, the gradient, and the noise
    // A cool purple-blue color is used for the gradient
    vec3 gradientColor = vec3(0.5, 1.0, 0.0) * (1.0 - gradient);

    // Apply the gradient color to the base color
    col = mix(col, gradientColor, 0.8);

    // Add the electronic noise
    // The noise is mixed in as a light flickering effect.
    col = mix(col, vec3(electronicNoise), 0.15);

    return col;
    // Output to screen
  //  fragColor = vec4(col, 1.0);
}


vec3 mainImageNoiseUIPanel2( in vec2 fragCoord )
{
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = fragCoord / iResolution.xy;

    // Base color is a clean white
    vec3 col = vec3(1.0, 1.0, 1.0);

   

    // --- Gradient and Noise Effects ---

    // Calculate the distance from each edge
    float distToLeft = uv.x;
    float distToRight = 1.0 - uv.x;
    float distToTop = uv.y;
    float distToBottom = 1.0 - uv.y;

    // Find the minimum distance to any edge
    float minEdgeDist = min(min(distToLeft, distToRight), min(distToTop, distToBottom));

    // Create a smooth gradient using smoothstep
    // The gradient will transition smoothly from 0.0 to 1.0
    // close to the edges and in the center, respectively.
    float gradient = smoothstep(0.0, 0.2, minEdgeDist);

    // Generate electronic noise
    // The noise function is called with a scaled UV coordinate and time to make it animate.
    float electronicNoise = noise(uv * 100.0, iTime * 50.0);
    // Apply a threshold to make the noise appear as flickering dots or static.
    electronicNoise = step(0.7, electronicNoise);

    // Combine the base color, the gradient, and the noise
    // A cool purple-blue color is used for the gradient
    vec3 gradientColor = vec3(0.5, 1.0, 0.0) * (1.0 - gradient);

    // Apply the gradient color to the base color
    col = mix(col, gradientColor, 0.8);

    // Add the electronic noise
    // The noise is mixed in as a light flickering effect.
    col = mix(col, vec3(electronicNoise), 0.15);

     // Collision logic from the original code (unchanged)
    int iCollision = 0;
    if (uv.x < 0.075 && uv.y < 0.075) {
        col = vec3(1.0, sin(uv.x), 0.0);
        iCollision = 1;
    }

    if (uv.x + uv.y < 0.1) {
        col = vec3(0.0, 0.0, 0.0);
        iCollision = iCollision + 1;
    }

    if (iCollision == 2) {
        col = vec3(0.0, sin(uv.x), 1.0);
    }

    float yuv = 1.0 - uv.y;
    if (uv.x + yuv < 0.1) {
        col = vec3(0.0, 0.0, 0.0);
    }

    float xuv = 1.0 - uv.x;
    if (xuv + uv.y < 0.1) {
        col = vec3(0.0, 0.0, 0.0);
    }

    if (xuv + yuv < 0.1) {
        col = vec3(0.0, 0.0, 0.0);
    }

    return col;
    // Output to screen
  //  fragColor = vec4(col, 1.0);
}


void main()
{
 // linearly interpolate between both textures (80% container, 20% awesomeface)
 // FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);

 /// FragColor = mix(texture(texture3, TexCoord), texture(texture2, TexCoord), 0.2);

// FragColor = mix(texture(texture1, TexCoord), texture(texture3, TexCoord), 0.2);
 // FragColor = texture(texture3, TexCoord);
// FragColor = mix(texture(texture3, TexCoord), texture(texture4, TexCoord), 0.2);

vec4 color1=    mix(texture(texture3, TexCoord), texture(texture2, TexCoord), 0.2);
vec4 color2=    mix(texture(texture4, TexCoord), texture(texture1, TexCoord), 0.2);
vec4 color3=    mix(texture(texture4, TexCoord), texture(texture1, TexCoord), 0.02);

//FragColor = mix(color2, color1, 0.2);

    if(vvtype > 76.5 && vvtype < 77.5)
	{
    vec4 CursorColor =  texture(texture5, TexCoord);
    if(CursorColor.w < 0.9)
    {
    discard;
    }
    

        FragColor = texture(texture5, TexCoord);

    }
    else if(iUniformsRenderType == 4)
    {

        //if(vvtype == 11.0)
        if(vvtype > 10.5 && vvtype < 11.5)
        {
        FragColor = color3; //mix(color2, color1, 0.2);
        //FragColor = vec4(1.0, 0.0 , 0.0 , 1.0);
        }
        //else if(vvtype == 22.0)
        else if(vvtype > 21.5 && vvtype < 22.5)
        {
        FragColor = color1;
        //FragColor = mix(texture(texture4, TexCoord), texture(texture2, TexCoord), 0.2);
        //FragColor = vec4(0.0, 1.0 , 0.0 , 1.0);
        //FragColor = vec4(TexCoord.x, TexCoord.y , vvtype , 1.0);


        }
        //else if(vvtype == 33.0)
        else if(vvtype >  32.5 && vvtype < 33.5)
        {
        //FragColor = texture(texture3, TexCoord);
        //FragColor = vec4(0.0, 0.0 , 1.0 , 1.0);
        //FragColor = texture(texture1, TexCoord);
        float alphacube = 0.7f;
        //if(texture(texture2, TexCoord).r < 0.1 && texture(texture2, TexCoord).b < 0.1 && texture(texture2, TexCoord).b < 0.1)
        //{
        //alphacube = 0.0f;
        //discard;
        //}

        FragColor = vec4(texture(texture2, TexCoord).rgb,alphacube);

        }









        // ------------------------------------------------------------------------


           else if(vvtype > 532.5 && vvtype < 533.5)
            {
            int onlyOddFragments = 1;
             //   if (onlyOddFragments == 1 && ((int(gl_FragCoord.x) + int(gl_FragCoord.y)) % 2) == 1)
           //  if (onlyOddFragments== 1 && mod(gl_FragCoord.x + gl_FragCoord.y, 1.0) == 0.0)

          //  float sum = gl_FragCoord.x + gl_FragCoord.y;
           // float fractional_part = mod(sum, 0.1);
            //float epsilon = 0.2501; // A small tolerance value

           // if (onlyOddFragments == 1  && abs(fractional_part - 0.5) < epsilon)
           // {          discard;
           // }
         //  if (onlyOddFragments == 1 && ((int(gl_FragCoord.x) + int(gl_FragCoord.y+cos(iTime))) % int(2.0-sin(iTime)*2.0)) == 1)
         if (onlyOddFragments == 1 && ((int(gl_FragCoord.x) + int(gl_FragCoord.y+cos(iTime*20.0)))/(1+ int(10.0 * sin(iTime/2) ) ) % 2) == 1)
           {
            discard;
           }
                 FragColor = vec4(0.5,0.0, 0.0, 1.0);
            }
            else if(vvtype > 533.5 && vvtype < 534.5)
            {
            int onlyOddFragments2 =1;
                if (onlyOddFragments2  == 1 && ((int(gl_FragCoord.x * sin(iTime)) + int(gl_FragCoord.y)) % 3) == 1)
                 discard;
                 FragColor = vec4(0.0,0.5, 1.0, 1.0);
            }



            else if(vvtype >1019.5f && vvtype < 1027.5f)
	        {
            FragColor = vec4(1.0,0.5, 1.0, 1.0);
            }












        // ------------------------------------------------------------


        else
        {
        //FragColor = texture(texture4, TexCoord);
        FragColor =  vec4(0.25 , 0.25, 0.25 , 0.75); //texture(texture4, TexCoord);
        }

    }
    else if(iUniformsRenderType == 3)
    {

        if(vvtype == 11.0)
        //if(vvtype > 10.5 && vvtype < 11.5)
        {
        FragColor = color2; //mix(color2, color1, 0.2);
        //FragColor = vec4(1.0, 0.0 , 0.0 , 1.0);
        }
        //else if(vvtype == 22.0)
        else if(vvtype > 21.5 && vvtype < 22.5)
        {

        FragColor = mix(texture(texture4, TexCoord), texture(texture2, TexCoord), 0.2);
        //FragColor = vec4(0.0, 1.0 , 0.0 , 1.0);
        //FragColor = vec4(TexCoord.x, TexCoord.y , vvtype , 1.0);


        }
        //else if(vvtype == 33.0)
        else if(vvtype >  32.5 && vvtype < 33.5)
        {
        //FragColor = texture(texture3, TexCoord);
        //FragColor = vec4(0.0, 0.0 , 1.0 , 1.0);
        FragColor = texture(texture1, TexCoord);
        }
        else if(vvtype >  43.5 && vvtype < 44.5)
        {
        //FragColor = texture(texture3, TexCoord);

         //  vec2 pattern_coords = mod(vec2(projection[0].x , projection[1].y) , vec2(1.0, 1.0));
         //  vec2 pattern_coords = mod(vec2(TexCoord.x , TexCoord.y) , vec2(1.0, 1.0));

            // Combine the x and y coordinates to get a single value for the step function.
            // This value will range from 0.0 to 1.0 within each grid cell.
         //   float pattern_value = pattern_coords.x + pattern_coords.y;

            // Use a step function to create a sharp cutoff.
            // The user requested to discard 70% of the positions.
            // Since our pattern_value ranges from 0.0 to 2.0, we'll check if it's
            // greater than 0.7, creating a diagonal discard pattern.
         //   if (step(1.0, pattern_value) > 0.5) {
                // Discard the fragment if the pattern value is above the threshold.
                // This is a binary "cut-off" transparency, not a true blend.
          //      discard;
         //   }

        FragColor = vec4(0.0, 0.0 , 1.0 , 0.7);
        //FragColor = texture(texture1, TexCoord);
        }
        else if(vvtype >  54.5 && vvtype < 55.5)
        {
        //FragColor = texture(texture3, TexCoord);

         // float pattern_coords = mod(TexCoord.x - TexCoord.y , 0.1);
         float pattern_coords = mod(TexCoord.x  ,  TexCoord.y);
         if(pattern_coords > 0.05)
         {
         discard;
         }

        FragColor = vec4(0.0, 1.0 , 0.0 , 0.7);
        //FragColor = texture(texture1, TexCoord);
        }
        else if(vvtype > 65.5 && vvtype < 66.5)
        {
        float pattern_scale = 1.0;
          float remainder = mod(abs(TexCoord.x - TexCoord.y) * pattern_scale, 1.0);

            // If the remainder is greater than a certain threshold, we discard the fragment.
            // This creates the "cutout" or "transparent" effect.
            if (remainder > 0.1)
            {
                discard;
            }

        FragColor = vec4(0.0,1.0, 0.0, 0.7);
        }
         
        else if(vvtype >  110.5 && vvtype < 111.5)
        {
                          //  FragColor = vec4(0.75, 0.05 , 0.35 , 1.0);
                               // Normalized pixel coordinates (from 0 to 1)
                        vec2 uv = TexCoord; // fragCoord/iResolution.xy;

                        // Time varying pixel color
                        vec3 col = vec3(1.0,1.0,1.0);// 0.5 + 0.5*cos(iTime+uv.xyx+vec3(0,2,4));
                    //if(length(uv) > 0.5)
                    if(uv.x > 0.9)
                    {
                    //discard;
                      col = sin(iTime+uv.xyx+vec3(4,2,0));
                    }
                    if(uv.x < 0.1)
                    {
                     col = cos(iTime+uv.xyx+vec3(4,2,0));
                    }
                    if(uv.x > 0.11 && uv.x < 0.89 && uv.y > 0.11 && uv.y < 0.89)
                    {

               //     col = vec3(0.0,0.0,1.0);
               //   col = mainImageSphereGears( uv );
               col = mainImageButton3( uv );

                    }

                    if(uv.x > 0.8905 && uv.x < 0.8985 && uv.y > 0.11 && uv.y < 0.89)
                    {
                    //col = vec3( uv.x*uv.x*0.5,sin(iTime)+ uv.x*uv.x*0.5,cos(iTime/2.0) + uv.x*uv.x*0.5 );
                    float position = uv.x - 0.8905;
                     // position = position * 125.0 * sin(iTime);
                      position = position * 125.0;
  
                     //col = vec3(position ,  position, position  );
                     col = vec3(1.0 - position ,  1.0 - position, 1.0 -  position  );
 
                    }

                    if(uv.x > 0.1005 && uv.x < 0.1085 && uv.y > 0.11 && uv.y < 0.89)
                    {
                    //col = vec3( uv.x*uv.x*0.5,sin(iTime)+ uv.x*uv.x*0.5,cos(iTime/2.0) + uv.x*uv.x*0.5 );
                    float position = uv.x - 0.1005;
                     // position = position * 125.0 * sin(iTime);
                      position = position * 125.0;
  
                     //col = vec3(position ,  position, position  );
                     col = vec3( position ,  position,   position  );
 
                    }
                    if(uv.y >  0.8905 && uv.y < 0.8985 && uv.x > 0.11 && uv.x < 0.89)
                    {
                    //col = vec3(0.0,0.0,0.0 );
                    float position = uv.y - 0.8905;
                     // position = position * 125.0 * sin(iTime);
                      position = position * 125.0;
  
                     //col = vec3(position ,  position, position  );
                     col = vec3( position ,  position,   position  );

                    }

                    if(uv.y >  0.1005 && uv.y < 0.1085 && uv.x > 0.11 && uv.x < 0.89)
                    {
                    //col = vec3(0.0,0.0,0.0 );
                    float position = uv.y - 0.1005;
                     // position = position * 125.0 * sin(iTime);
                      position = position * 125.0;
  
                     //col = vec3(position ,  position, position  );
                  //   col = vec3( position ,  position,   position  );
                    col = vec3(0.0,1.0,0.0 );

                    }
                    if(col.r > 0.99  && col.g > 0.99  && col.b > 0.99  )
                    {
                    discard;
                    }
                        // Output to screen
                        FragColor = vec4(col,1.0);


        }
         else if(vvtype >  221.5 && vvtype < 222.5)
        {
         FragColor = vec4(0.5,1.0, 0.0, 0.7);
        }
        // Settings Options Dialog
            else if(vvtype > 332.5 && vvtype < 333.5)
	        {
		
	        //	gl_Position =  vec4(aPos, 1.0f);
           vec3 SettingsNoisePanel = mainImageNoiseUIPanel( TexCoord );

		    //FragColor = vec4(0.5,1.0, 0.0, 0.7);
	        
            FragColor = vec4(SettingsNoisePanel, 0.7);
            }
	        else if(vvtype > 352.5 && vvtype < 353.5)
	        {
		
	        //	gl_Position =  vec4(aPos, 1.0f);
	        	FragColor = vec4(0.9,0.1, 0.0, 0.7);
	        }

             else if(vvtype > 532.5 && vvtype < 533.5)
            {
            int onlyOddFragments = 1;
             //   if (onlyOddFragments == 1 && ((int(gl_FragCoord.x) + int(gl_FragCoord.y)) % 2) == 1)
           //  if (onlyOddFragments== 1 && mod(gl_FragCoord.x + gl_FragCoord.y, 1.0) == 0.0)

          //  float sum = gl_FragCoord.x + gl_FragCoord.y;
           // float fractional_part = mod(sum, 0.1);
            //float epsilon = 0.2501; // A small tolerance value

           // if (onlyOddFragments == 1  && abs(fractional_part - 0.5) < epsilon)
           // {          discard;
           // }
         //  if (onlyOddFragments == 1 && ((int(gl_FragCoord.x) + int(gl_FragCoord.y+cos(iTime))) % int(2.0-sin(iTime)*2.0)) == 1)
         if (onlyOddFragments == 1 && ((int(gl_FragCoord.x) + int(gl_FragCoord.y+cos(iTime*20.0)))/10 % 2) == 1)
           {
            discard;
           }
                 FragColor = vec4(0.5,0.0, 0.0, 1.0);
            }
            else if(vvtype > 533.5 && vvtype < 534.5)
            {
            int onlyOddFragments2 =1;
                if (onlyOddFragments2  == 1 && ((int(gl_FragCoord.x * sin(iTime)) + int(gl_FragCoord.y)) % 3) == 1)
                 discard;
                 FragColor = vec4(0.0,0.5, 1.0, 1.0);
            }

              else if(vvtype >1019.5f && vvtype < 1027.5f)
	        {
             vec2 uv = TexCoord; 
             vec3 col = vec3(1.0,1.0,1.0);//0.5 + 0.5*cos(iTime+uv.xyx+vec3(0,2,4));

float outlinepercent = 0.01;//float outlinepercent = 1.0%;
if(uv.x > 1.0 - outlinepercent)
{
col = vec3(0.0,0.0,0.0);
}
if(uv.x < outlinepercent)
{
col = vec3(0.0,0.0,0.0);
}
if(uv.y > 1.0 - outlinepercent)
{
col = vec3(0.0,0.0,0.0);
}
if(uv.y < outlinepercent)
{
col = vec3(0.0,0.0,0.0);
}

    // Output to screen
 //   fragColor = vec4(col,1.0);
            
              if(vvtype >1020.5f && vvtype < 1021.5f)
              {
              FragColor =  texture(texture6, TexCoord);
              }
              else
              {
              FragColor = vec4(col,1.0);
              }
           
           }

        else
        {
        //FragColor = texture(texture4, TexCoord);
        FragColor =  vec4(1.0 , 1.0, 1.0 , 1.0); //texture(texture4, TexCoord);
        }

    }
    else if(iUniformsRenderType == 1)
    {
        //if(vvtype == 11.0)
        if(vvtype > 10.5 && vvtype < 11.5)
        {
        //FragColor = mix(color2, color1, 0.2);
        FragColor = vec4(1.0, 0.0 , 0.0 , 1.0);
        }
        //else if(vvtype == 22.0)
        else if(vvtype > 21.5 && vvtype < 22.5)
        {

        //FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
        //FragColor = vec4(0.0, 1.0 , 0.0 , 1.0);


      //  FragColor = vec4(TexCoord.x, TexCoord.y , vvtype , 1.0);
      vec3  col33 = mainImageSphereGears( TexCoord );
      FragColor = vec4(col33 , 1.0);

        }
        //else if(vvtype == 33.0)
        else if(vvtype >  32.5 && vvtype < 33.5)
        {
        //FragColor = texture(texture3, TexCoord);
        FragColor = vec4(0.0 + sin(view[0][0]) /2.0, 0.0 + cos(view[1][1])/ 2.0 , 1.0 , 1.0);
        }

        else if(vvtype >  33.5 && vvtype < 34.5)
        {
        //FragColor = texture(texture3, TexCoord);
        FragColor = vec4(1.0, TexCoord.x , 0.0 , 1.0);
        }

        else if(vvtype >  65.5 && vvtype < 66.5)
        {
        //FragColor = texture(texture3, TexCoord);

         // float pattern_coords = mod(abs( TexCoord.x- projection[0].x)  - TexCoord.y , 0.1);
         //float pattern_coords = mod( abs( TexCoord.x- view[0].x) ,  TexCoord.y);
         float sphereRadius = 0.1;
          vec2 uvCenter = vec2(0.5, 0.5);

            // Calculate the distance of the current fragment's TexCoord from the center.
            // We can use the GLSL built-in 'distance' function.
            float distFromCenter = distance(TexCoord, uvCenter);


       //  if(abs( (TexCoord.x*TexCoord.x) - (TexCoord.y * TexCoord.y) ) < 0.1)
        if (distFromCenter <= sphereRadius)
         {
     //     OK
      FragColor = vec4(0.7, 0.0 , 1.0 , 0.7);
         }
          else       if(TexCoord.x > 0.05 && TexCoord.x < 0.95)
         {
         discard;
         }
         else if(TexCoord.y > 0.05 && TexCoord.y < 0.95)
         {
         discard;
         }
         else
         {
         FragColor = vec4(0.0, 0.0 , 1.0 , 0.7);
         }

    
        //FragColor = texture(texture1, TexCoord);
        }


        else if(vvtype >  110.5 && vvtype < 111.5)
        {
                          //  FragColor = vec4(0.75, 0.05 , 0.35 , 1.0);
                               // Normalized pixel coordinates (from 0 to 1)
                        vec2 uv = TexCoord; // fragCoord/iResolution.xy;

                        // Time varying pixel color
                        vec3 col = vec3(1.0,1.0,1.0);// 0.5 + 0.5*cos(iTime+uv.xyx+vec3(0,2,4));
                    //if(length(uv) > 0.5)
                    if(uv.x > 0.9)
                    {
                    //discard;
                      col = sin(iTime+uv.xyx+vec3(4,2,0));
                    }
                    if(uv.x < 0.1)
                    {
                     col = cos(iTime+uv.xyx+vec3(4,2,0));
                    }
                    if(uv.x > 0.11 && uv.x < 0.89 && uv.y > 0.11 && uv.y < 0.89)
                    {
                    col = vec3(1.0,0.0,0.0);
                 //  col = mainImageSphereGears( uv );

                    }

                    if(uv.x > 0.8905 && uv.x < 0.8985 && uv.y > 0.11 && uv.y < 0.89)
                    {
                    //col = vec3( uv.x*uv.x*0.5,sin(iTime)+ uv.x*uv.x*0.5,cos(iTime/2.0) + uv.x*uv.x*0.5 );
                    float position = uv.x - 0.8905;
                     // position = position * 125.0 * sin(iTime);
                      position = position * 125.0;
  
                     //col = vec3(position ,  position, position  );
                     col = vec3(1.0 - position ,  1.0 - position, 1.0 -  position  );
 
                    }

                    if(uv.x > 0.1005 && uv.x < 0.1085 && uv.y > 0.11 && uv.y < 0.89)
                    {
                    //col = vec3( uv.x*uv.x*0.5,sin(iTime)+ uv.x*uv.x*0.5,cos(iTime/2.0) + uv.x*uv.x*0.5 );
                    float position = uv.x - 0.1005;
                     // position = position * 125.0 * sin(iTime);
                      position = position * 125.0;
  
                     //col = vec3(position ,  position, position  );
                     col = vec3( position ,  position,   position  );
 
                    }
                    if(uv.y >  0.8905 && uv.y < 0.8985 && uv.x > 0.11 && uv.x < 0.89)
                    {
                    //col = vec3(0.0,0.0,0.0 );
                    float position = uv.y - 0.8905;
                     // position = position * 125.0 * sin(iTime);
                      position = position * 125.0;
  
                     //col = vec3(position ,  position, position  );
                     col = vec3( position ,  position,   position  );

                    }

                    if(uv.y >  0.1005 && uv.y < 0.1085 && uv.x > 0.11 && uv.x < 0.89)
                    {
                    //col = vec3(0.0,0.0,0.0 );
                    float position = uv.y - 0.1005;
                     // position = position * 125.0 * sin(iTime);
                      position = position * 125.0;
  
                     //col = vec3(position ,  position, position  );
                     col = vec3( position ,  position,   position  );
                    //col = vec3(0.0,0.0,0.0 );
                    }

                        // Output to screen
                        FragColor = vec4(col,1.0);


        }
        else if(vvtype >  111.5 && vvtype < 112.5)
        {
        discard;
        }
        else if(vvtype >  221.5 && vvtype < 222.5)
        {
        discard;
       // FragColor = vec4(0.05, 0.05 , 0.35 , 1.0);
        
        }
        else if(vvtype >  222.5 && vvtype < 223.5)
        {
        FragColor = vec4(0.05, 0.05 , 0.35 , 1.0);
        
        }

        else if(vvtype > 332.5 && vvtype < 333.5)
        {
         discard;// invisiable SettingsOptionsPanel Buttons
        
        }
         else if(vvtype > 352.5 && vvtype < 353.5)
	        {
		discard; // invisiable SettingsOptionsPanel Sitting_Panel
            }


             else if(vvtype > 333.5 && vvtype < 334.5)
        {
        //FragColor = mainProceduralBrick(uv);
        vec3 brickColor = mainProceduralBrick(TexCoord);
        FragColor = vec4(brickColor, 1.0);
        
        }
         else if(vvtype > 353.5 && vvtype < 354.5)
	        {
		
	        //	gl_Position =  vec4(aPos, 1.0f);
           vec3 SettingsNoisePanel = mainImageNoiseUIPanel2( TexCoord );

           if(SettingsNoisePanel.r > 0.99 && SettingsNoisePanel.g > 0.99 && SettingsNoisePanel.b > 0.99)
           {
           discard;
           }
		    //FragColor = vec4(0.5,1.0, 0.0, 0.7);
	        
            FragColor = vec4(SettingsNoisePanel, 0.7);
            }

            else if(vvtype > 532.5 && vvtype < 533.5)
            {
            int onlyOddFragments = 1;
                if (onlyOddFragments == 1 && ((int(gl_FragCoord.x) + int(gl_FragCoord.y)) % 2) == 1)
                 discard;
                 FragColor = vec4(0.5,0.0, 0.0, 1.0);
            }
            else if(vvtype > 533.5 && vvtype < 534.5)
            {
            int onlyOddFragments2 =1;
                if (onlyOddFragments2  == 1 && ((int(gl_FragCoord.x) + int(gl_FragCoord.y)) % 2) == 1)
                 discard;
                 FragColor = vec4(0.0,0.5, 1.0, 1.0);
            }

        else
        {
        FragColor = texture(texture4, TexCoord);
        }

    }
    else
    {



    //if(vvtype == 11.0)
        if(vvtype > 10.5 && vvtype < 11.5)
        {
        FragColor = mix(color2, color1, 0.2);
        //FragColor = vec4(1.0, 0.0 , 0.0 , 1.0);
        }
        //else if(vvtype == 22.0)
        else if(vvtype > 21.5 && vvtype < 22.5)
        {

        FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
        //FragColor = vec4(0.0, 1.0 , 0.0 , 1.0);


        }
        //else if(vvtype == 33.0)
        else if(vvtype >  32.5 && vvtype < 33.5)
        {
        FragColor = texture(texture3, TexCoord);
        //FragColor = vec4(0.0, 0.0 , 1.0 , 1.0);
        }

        else if(vvtype >  54.5 && vvtype < 55.5)
        {
        //FragColor = texture(texture3, TexCoord);

         // float pattern_coords = mod(abs( TexCoord.x- projection[0].x)  - TexCoord.y , 0.1);
         float pattern_coords = mod( abs( TexCoord.x- view[0].x) ,  TexCoord.y);
         if(pattern_coords > 0.05)
         {
         discard;
         }

        FragColor = vec4(0.0, 1.0 , 0.0 , 0.7);
        //FragColor = texture(texture1, TexCoord);
        }
        else if(vvtype >  55.5 && vvtype < 56.5)
        {
        //FragColor = texture(texture3, TexCoord);

         // float pattern_coords = mod(abs( TexCoord.x- projection[0].x)  - TexCoord.y , 0.1);
         float pattern_coords = mod( abs( TexCoord.x- view[0].x) ,  TexCoord.y);
         if(pattern_coords > 0.05)
         {
         discard;
         }

        FragColor = vec4(0.3, 0.0 , 0.5 , 0.7);
        //FragColor = texture(texture1, TexCoord);
        }
        else if(vvtype >  65.5 && vvtype < 66.5)
        {
        //FragColor = texture(texture3, TexCoord);

         // float pattern_coords = mod(abs( TexCoord.x- projection[0].x)  - TexCoord.y , 0.1);
         //float pattern_coords = mod( abs( TexCoord.x- view[0].x) ,  TexCoord.y);
        // if(abs((TexCoord.x*TexCoord.x) - (TexCoord.y * TexCoord.y)) < 0.1)
        // {
         // OK
         //}
          //else 
          if(TexCoord.x > 0.05 && TexCoord.x < 0.95)
         {
         discard;
         }
         else if(TexCoord.y > 0.05 && TexCoord.y < 0.95)
         {
         discard;
         }

        FragColor = vec4(0.0, 0.0 , 1.0 , 0.7);
        //FragColor = texture(texture1, TexCoord);
        }


        else if(vvtype >  110.5 && vvtype < 111.5)
        {
        FragColor = vec4(0.75, 0.05 , 0.35 , 1.0);
        
        }
        
        else if(vvtype >  221.5 && vvtype < 222.5)
        {
        FragColor = vec4(0.05, 0.05 , 0.35 , 1.0);
        
        }
        else
        {
        //FragColor = texture(texture4, TexCoord);
        FragColor = vec4(0.75, 0.75 , 0.75 , 1.0);

        }




}




//FragColor = texture(texture1, TexCoord);

}