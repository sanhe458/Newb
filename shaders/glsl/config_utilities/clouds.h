// Newb shader

/*""""""""""""""""""""""""""""""""""""""*/
/* SMOOTH CLOUDS */

// Value - Cloud size when raining (0-1)
#define rain_cloud_size 0.9

// Value - Normal cloud size (0-1)
#define normal_cloud_size 0.4

// Value - Cloud map size (0-100)
#define cloud_noise_size 36.0

// Value - Cloud depth (0-3)
#define cloud_depth 1.3

// Value - Cloud movement speed
#define cloud_speed 0.04

// Value - Cloud shadow intensity (0-1)
#define cloud_shadow 0.78

// Value - Cloud transparency (0-1)
#define cloud_alpha 0.92

// Toggle - Double layer clouds (Harrington style)
#define DOUBLE_LAYER_CLOUDS

// Value - Cloud cell frequency scale (higher = denser/smaller cells; 1.0 = Newb default density)
#define cloud_cell_scale 1.0

/*""""""""""""""""""""""""""""""""""""""*/


/*""""""""""""""""""""""""""""""""""""""*/
/* AURORA EFFECT */

//️ Toggle - Enable aurora effect for night sky
//️ Value - Aurora borealis brightness
#define AURORA 0.0

/*""""""""""""""""""""""""""""""""""""""*/



// Code starts here - Users shouldn't mess down here
// Clouds noise

// max 保护：用户若将 cloud_noise_size 配置为 0 会触发除零导致着色器编译失败
const vec2 cloud_size = vec2(0.7,1.0)/max(cloud_noise_size, 1.0);

const float start_rain = 1.0-rain_cloud_size;
const float start_normal = 1.0-normal_cloud_size;

// Harrington-style hash for cloud shapes (seed vec2(28.,48.))
highp float cloudRand(highp vec2 n){
	return fract(sin(dot(n, vec2(28.0,48.0))) * 43758.5453);
}

// time-of-day factors for cloud coloring (ported from Harrington timeset)
// returns vec3(fday, fsun, fnight); rain is passed in separately
vec3 cloudTimeFactors(float rain){
	float fday = clamp(FOG_COLOR.r+FOG_COLOR.g, 0.0, 1.0);
	float fnight = 1.0-fday;
	float fsun = pow(clamp(1.0-FOG_COLOR.b*1.2,0.0,1.0),0.5)*(1.0-fnight)*(1.0-rain);
	return vec3(fday, fsun, fnight);
}

// 2D cloud noise - used by clouds and water reflection
// Harrington cell-hash cloud shape, adapted to Newb cloud plane
float cloudNoise2D(vec2 p, highp float t, float rain){

	// compensate Harrington's *35 base frequency so cell size ~ cloud_noise_size (world)
	vec2 uv = p * cloud_cell_scale / 35.0;
	float draw = 0.0;
	float opacity = 1.0;

	// double layer (upper, sparser)
	#ifdef DOUBLE_LAYER_CLOUDS
		for(int i = 0; i < 8; i++){
			uv /= 1.01;
			float shape2 = step(0.83, cloudRand(floor(uv*50.0 - vec2(0.0, t*cloud_speed*0.02))));
			draw = mix(draw, opacity-0.3, shape2);
		}
		float dshape2 = step(0.83, cloudRand(floor(uv*50.0 - vec2(0.0, t*cloud_speed*0.02))));
		draw = mix(draw, (opacity-0.3)*0.85, dshape2);
	#endif

	// main layer (10 iterations scaling up for multi-scale detail)
	vec2 uv2 = uv;
	for(int i = 0; i < 10; i++){
		uv2 *= 1.01;
		float shape = cloudRand(floor(uv2*35.0 - vec2(0.0, t*cloud_speed*0.06)));
		draw = mix(draw, opacity, mix(step(0.7,shape), step(0.35,shape), rain));
	}
	float dshape = cloudRand(floor(uv*35.0 - vec2(0.0, t*cloud_speed*0.06)));
	draw = mix(draw, opacity*0.78, mix(step(0.7,dshape), step(0.35,dshape), rain));

	// threshold using Newb's rain/normal cloud size (rain => more coverage)
	float start = start_normal + (normal_cloud_size)*(0.1+0.1*sin(t*cloud_speed + p.y*0.3));
	start = mix(start, start_rain, rain);
	draw = clamp((draw-start)*3.4, 0.0, 1.0);
	return draw*draw;
}

// simple cloud - Harrington shape + time-of-day coloring, adapted to Newb plane
vec4 renderClouds(vec4 color, vec2 uv, highp float t, float rain){

	float cloudAlpha = cloudNoise2D(uv,t,rain);
	float cloudShadow = cloudNoise2D(uv,(t+0.16),rain)*0.2;

	cloudAlpha = max(cloudAlpha-cloudShadow,0.0);

	// time-of-day factors (a=fsun, b=fnight, c=rain)
	vec3 tf = cloudTimeFactors(rain);
	float fsun = tf.y;
	float fnight = tf.z;
	float l_uv = clamp(length(uv*0.5),0.0,1.0);

	// Harrington cloud color by time-of-day
	vec4 cloudCol = mix(
		mix(mix(vec4(1.0,1.1,1.1,0.85), vec4(0.53), rain),
		    mix(mix(vec4(1.0,0.5,0.2,0.75), vec4(1.25,0.55,0.0,0.95)*1.23, l_uv), vec4(1.0), max(rain,fnight)),
		    fsun),
		mix(vec4(0.15,0.3,0.4,0.65), vec4(0.22), rain),
		fnight);

	// cloud shadow on underlying color
	color.rgb *= (1.0-cloudShadow*3.0*cloud_shadow);

	return vec4(mix(color.rgb, cloudCol.rgb, cloudAlpha), cloudAlpha);
}

// simple northern night sky effect
vec4 renderAurora(vec2 uv, highp float t, float rain){
	float auroraCurves = sin(uv.x*0.09 + 0.07*t) + 0.3*sin(uv.x*0.5 + 0.09*t) + 0.03*sin((uv.x+uv.y)*3.0 + 0.2*t);
	float auroraBase = uv.y*0.4 + 2.0*auroraCurves;
	float auroraFlow = 0.5+0.5*sin(uv.x*0.3 + 0.07*t + 0.7*sin(auroraBase*0.9) );

	float auroraCol = sin(uv.y*0.06 + 0.07*t);
	auroraCol = abs(auroraCol*auroraCol*auroraCol);

	float aurora = sin(auroraBase)*sin(auroraBase*0.3);
	aurora = abs(aurora*auroraFlow);

	return vec4(
		0.0,
		(1.0-auroraCol)*aurora,
		auroraCol*aurora,
		aurora*aurora*(0.5-0.5*rain) );
}
