uniform vec2 u_resolution;
uniform float u_time;

uniform sampler2D OctTree;
uniform vec2 OctTreeBufferResolution;
uniform int OctTreeItemSize;

const int MAX_RAY_STEPS = 200;

struct Material {
  vec3 ambient;
};

struct Ray {
  ivec3 mapPos;
  bool hit;
  bvec3 mask;
};

vec2 rotate2d(vec2 v, float a) {
	float sinA = sin(a);
	float cosA = cos(a);
	return vec2(v.x * cosA - v.y * sinA, v.y * cosA + v.x * sinA);	
}

//memory access functions----------------------------------------------------------
vec4 accessMemoryParameter(sampler2D inBuffer, int index, int parameter, vec2 bufferResolution, int itemSize) {
  int maxIndexPerRow = int(bufferResolution.x/float(itemSize));

  int rowPosition = index/maxIndexPerRow;
  int colPosition = (index-rowPosition*maxIndexPerRow)*itemSize + parameter;

  return texelFetch(inBuffer, ivec2(colPosition, rowPosition), 0);
}

vec4 accessOctTreeParameter(int index, int parameter) {
  return accessMemoryParameter(OctTree, index, parameter, OctTreeBufferResolution, OctTreeItemSize);
}
//end------------------------------------------------------------------------------


float sdSphere(vec3 p, float d) { return length(p) - d; } 

float sdBox( vec3 p, vec3 b )
{
  vec3 d = abs(p) - b;
  return min(max(d.x,max(d.y,d.z)),0.0) +
         length(max(d,0.0));
}
	
bool isVoxel(ivec3 c) {
	vec3 p = vec3(c) + vec3(0.5);
	float d = max(-sdSphere(p, 7.5), sdBox(p, vec3(6.0)));
  d = min(sdBox(p-vec3(0.0, -10, 0.0), vec3(500, 2, 500)), d);
	return d < 0.0;
}

/*
Material getVoxel(ivec3 c) {

}
*/

Ray raycast(vec3 rayPos, vec3 rayDir) {
  Ray castRay = Ray(ivec3(floor(rayPos)), false, bvec3(false));

  vec3 deltaDist = abs(vec3(length(rayDir))/rayDir);

  ivec3 rayStep = ivec3(sign(rayDir));

  vec3 sideDist = (sign(rayDir) * (vec3(castRay.mapPos) - rayPos) + (sign(rayDir) * 0.5) + 0.5) * deltaDist;
  bvec3 mask;

  for (int i = 0; i < MAX_RAY_STEPS; i++) {
    if (isVoxel(castRay.mapPos)) {
      castRay.hit = true;
      break;
    }
    if (sideDist.x < sideDist.y) {
				if (sideDist.x < sideDist.z) {
					sideDist.x += deltaDist.x;
					castRay.mapPos.x += rayStep.x;
					mask = bvec3(true, false, false);
				}
				else {
					sideDist.z += deltaDist.z;
					castRay.mapPos.z += rayStep.z;
					mask = bvec3(false, false, true);
				}
			}
			else {
				if (sideDist.y < sideDist.z) {
					sideDist.y += deltaDist.y;
					castRay.mapPos.y += rayStep.y;
					mask = bvec3(false, true, false);
				}
				else {
					sideDist.z += deltaDist.z;
					castRay.mapPos.z += rayStep.z;
					mask = bvec3(false, false, true);
				}
			}
  }

  castRay.mask = mask;

  return castRay;
}

void main() {
  vec2 uv = (gl_FragCoord.xy-.5*u_resolution.xy)/u_resolution.y;
  vec3 backgroundColor = vec3(0.5, 0.5, 1.0);

  vec3 rayPos = vec3(0.0, 0.0, -50.0);
  vec3 rayDir = normalize(vec3(uv, 1.02));
		
	rayPos.xz = rotate2d(rayPos.xz, u_time);
	rayDir.xz = rotate2d(rayDir.xz, u_time);

  Ray castRay = raycast(rayPos, rayDir);

  vec3 outColor;
  if (castRay.hit) {
    vec3 lightPosition = rayPos;
    vec3 lightDirection = normalize(lightPosition-vec3(castRay.mapPos));
    
    vec3 normals = vec3(castRay.mask) * -sign(rayDir);
    
    float diff = clamp(dot(normals, lightDirection), 0.3, 1.0);
	
	  vec3 color = vec3(1.0);
    outColor = color*diff;
  } else {
    outColor = backgroundColor;
  }

  gl_FragColor = vec4(outColor, 1.0);
	
}