#include <iostream>

#include "Gizmo.h"
#include "Object.h"
#include "Transform.h"

#include <algorithm>

void Gizmo::Init() {

	// Adding movement arrows
	handles.emplace_back(std::make_unique<Arrow>(), GizmoHandleType::Move, Vec2f(-1, 0)); // Left Arrow
	handles.emplace_back(std::make_unique<Arrow>(), GizmoHandleType::Move, Vec2f(0, 1)); // Up Arrow
	handles.emplace_back(std::make_unique<Arrow>(), GizmoHandleType::Move, Vec2f(1, 0)); // Right Arrow
	handles.emplace_back(std::make_unique<Arrow>(), GizmoHandleType::Move, Vec2f(0, -1)); // Down Arrow

	//Adding rotation
	handles.emplace_back(std::make_unique<Arc>(), GizmoHandleType::Rotate, Vec2f(1.8, 1.8));

	//Adding scale
	handles.emplace_back(std::make_unique<Rectangle>(), GizmoHandleType::Scale, Vec2f(-1, -1));
	handles.emplace_back(std::make_unique<Rectangle>(), GizmoHandleType::Scale, Vec2f(1, 1));
	handles.emplace_back(std::make_unique<Rectangle>(), GizmoHandleType::Scale, Vec2f(1, -1));
	handles.emplace_back(std::make_unique<Rectangle>(), GizmoHandleType::Scale, Vec2f(-1, 1));

	std::cout << "Gizmo initialized" << std::endl;
}

void Gizmo::Show() {
	if (Rectangle* rect = dynamic_cast<Rectangle*>(target)) {
		Vec2f pos = rect->Transform.Position;
		Vec2f size = rect->Size;
		Vec2f middle = size * .5f;
		Angle rot = rect->Transform.Rotation;
		handleScale = (size.x + size.y) / 2.f;
			for (GizmoHandle& handle : handles) {
				if (Arrow* arr = dynamic_cast<Arrow*>(handle.Visual.get())) {

					Vec2f axis = handle.Axis;

					float trim = handleScale * trimScale;
					float length = handleScale * lengthScale;

					Vec2f newStart = Vec2f((middle.x + trim) * axis.x, (middle.y + trim) * axis.y);
					Vec2f newEnd = newStart + Vec2f(length * axis.x, length * axis.y);

					arr->Start = Transform::RotatePoint(newStart,rot) + pos;
					arr->End = Transform::RotatePoint(newEnd,rot) + pos;

					arr->Thickness = handleScale * lineThickness;
					
				 }
				if (Arc* arc = dynamic_cast<Arc*>(handle.Visual.get())) {

					Vec2f axis = handle.Axis;

					Vec2f arcPos = Vec2f(middle.x * axis.x, middle.y * axis.y);

					arc->Transform.Position = pos + arcPos;
					arc->Radius = handleScale * radiusMulti;

					arc->Thickness = arc->Radius * arcThickness;
			
				}
				if (Rectangle* square = dynamic_cast<Rectangle*>(handle.Visual.get())) {

					Vec2f axis = handle.Axis;

					Vec2f centerPos = Vec2f(middle.x * axis.x, middle.y * axis.y);
					Vec2f newPos = Transform::RotatePoint(centerPos, rot);

					square->Transform.Position = pos + newPos;
					square->Transform.Rotation = rot;
					square->Size = Vec2f(handleScale * scaleMulti);
				
				}
				handle.Visual.get()->Visible = true;
			}
	}

}

void Gizmo::Hide() {
	for (GizmoHandle& handle : handles) {
		Object* o = handle.Visual.get();
		o->Visible = false;
	}
}