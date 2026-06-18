#include "Gizmo.h"
#include "Object.h"

void Gizmo::Init() {
	// Adding move arrows
	Arrow* arrow();
	GizmoHandleType typ = GizmoHandleType::Move;
	Vec2f ax = Vec2f(-1,0);
	GizmoHandle leftArrow(arrow, typ,ax);
}