#ifndef VERTEX_H
#define VERTEX_H

#include <DirectXMath.h>

#include "../../types.h"

namespace R2{

	struct point2d_t
	{
		point2d_t(void) { pos = {}; }
		point2d_t(const f32 x, const f32 y) { pos.x = x; pos.y = y; }
		point2d_t(const DirectX::XMFLOAT2A& pos) : pos(pos) {}
		~point2d_t(void) {}
		DirectX::XMFLOAT2A pos;
	} typedef vec2;

}

namespace R3{

	struct point3d_t
	{
		point3d_t(void) { pos = {}; }
		point3d_t(const f32 x, const f32 y, const f32 z) { pos.x = x; pos.y = y; pos.z = z; }
		point3d_t(const DirectX::XMFLOAT3A& pos) : pos(pos) {}
		~point3d_t(void) {}
		DirectX::XMFLOAT3A pos;
	} typedef vec3;

}

#endif // !VERTEX_H
