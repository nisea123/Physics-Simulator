#include <iostream>

#include "Gizmo.h"
#include "Object.h"

void Gizmo::Init() {
	// Adding move arrows
	handles.emplace_back(std::make_unique<Arrow>(), GizmoHandleType::Move, Vec2f(-1, 0)); // Left Arrow
	handles.emplace_back(std::make_unique<Arrow>(), GizmoHandleType::Move, Vec2f(0, 1)); // Up Arrow
	handles.emplace_back(std::make_unique<Arrow>(), GizmoHandleType::Move, Vec2f(1, 0)); // Right Arrow
	handles.emplace_back(std::make_unique<Arrow>(), GizmoHandleType::Move, Vec2f(0, -1)); // Down Arrow

	std::cout << "Gizmo initialized" << std::endl;
}

void Gizmo::Show() {
	if (Rectangle* rect = dynamic_cast<Rectangle*>(target)) {
		Vec2f pos = rect->Transform.Position;
		Vec2f size = rect->Size;
			for (GizmoHandle& handle : handles) {
				if (Arrow* arr = dynamic_cast<Arrow*>(handle.Visual.get())) {
					Vec2f axis = handle.Axis;
					Vec2f orientation = (size * .5f);
					arr->Start = Vec2f(pos.x + orientation.x * axis.x, pos.y + orientation.y * axis.y);
					arr->End = Vec2f(pos.x + (orientation.x + length) * axis.x, pos.y + (orientation.y + length) * axis.y);
					arr->Visible = true;
				 }
			}
	}

}

void Gizmo::Hide() {
	for (GizmoHandle& handle : handles) {
		Object* o = handle.Visual.get();
		o->Visible = false;
	}
}