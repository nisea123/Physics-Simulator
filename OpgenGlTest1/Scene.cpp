#include "Scene.h"
#include "Renderer.h"
#include "Object.h"

#include <algorithm>

void Scene::Draw(Renderer& renderer) {
	for (auto& object : objects.objects) {

		if (object->Visible) {
			object->Draw(renderer);
		}


	}
	for (auto& object : ui.ui) {
		UiElement* o = object.get();

		if (!o->Visible) continue;

		if (auto* r = dynamic_cast<UiFrame*>(o))
			renderer.Draw(*r);
		else if (auto* c = dynamic_cast<UiButton*>(o))
			renderer.Draw(*c);
		else if (auto* t = dynamic_cast<UiSlider*>(o))
			renderer.Draw(*t);
		else if (auto* y = dynamic_cast<UiText*>(o))
			renderer.Draw(*y);
	}

	for (GizmoHandle& handle : gizmo.handles) {
		Object* o = handle.Visual.get();

		if (o->Visible) {
			o->Draw(renderer);
		}

	}
}

void Scene::Update(float dt) {
	physicsWorld.ApplyVectors(dt);
	UpdateHover(mouse);
	UpdateSelection(mouse);
	UpdateDragging(mouse);
	UpdateGizmo(mouse);
}

void Scene::UpdateHover(Mouse& mouse) {

	hoveredObject = nullptr;
	hoveredUi = nullptr;
	hoveredHandle = nullptr;

	for (auto& ui : ui.ui)
	{
		if (ui->Contains(mouse.position))
		{
			hoveredUi = ui.get();
		}
	}

	if (!hoveredUi) {
		for (auto& object : objects.objects)
		{
			if (object->Contains(mouse.position))
			{
				hoveredObject = object.get();
				break;
			}
		}
		for (GizmoHandle& handle : gizmo.handles) {
			Object* o = handle.Visual.get();
			if (o->Contains(mouse.position)) {
				hoveredHandle = &handle;

			}
		}
	}

}

void Scene::UpdateSelection(Mouse& mouse) {
	if (mouse.m1Pressed)
	{
		if (hoveredUi) {
			if (hoveredUi->OnClick) {
				hoveredUi->OnClick();
			}
		}
		else if (hoveredObject) {
			selectedObject = hoveredObject;
			holdingObject = hoveredObject;
			mouse.dragOffset = mouse.position - holdingObject->Transform.Position;
		}
		else if (!hoveredObject && !hoveredHandle) {
			selectedObject = nullptr;
		}
		else if (hoveredHandle) {
			holdingHandle = hoveredHandle;
			holdingHandle->MouseStartPosition = mouse.position;
			holdingHandle->GizmoStartAngle = gizmo.target->Transform.Rotation;
		}
	}
}

void Scene::UpdateDragging(Mouse& mouse) {

	if (mouse.m1 && holdingObject) {
		holdingObject->Transform.Position = mouse.position - mouse.dragOffset;
	}

	if (!mouse.m1) {
		holdingObject = nullptr;
	}
}

void Scene::UpdateGizmo(Mouse& mouse) {

	if (selectedObject) {
		gizmo.target = selectedObject;
		gizmo.Show();
	}
	else {
		gizmo.Hide();
	}

	if (hoveredHandle) {

		if (hoveredHandle->Type == GizmoHandleType::Move) {
			if (Arrow* arr = As<Arrow>(hoveredHandle->Visual.get())) {
				arr->Thickness = gizmo.handleScale * gizmo.lineThickness * 1.5f;	
			}
		}
		if (hoveredHandle->Type == GizmoHandleType::Rotate) {
			if (Arc* arc = As<Arc>(hoveredHandle->Visual.get())) {
				arc->Radius = gizmo.handleScale * gizmo.radiusMulti * 1.2f;
			}
		}

		if (hoveredHandle->Type == GizmoHandleType::Scale) {
			if (Rectangle* rect = As<Rectangle>(hoveredHandle->Visual.get())) {
				rect->Size = Vec2f(gizmo.handleScale * gizmo.scaleMulti * 1.2f);
			}
		}

		lastHoveredHandle = hoveredHandle;
	}

	if (holdingHandle && mouse.m1) {

		if (holdingHandle->Type == GizmoHandleType::Move) {
			if (Arrow* arr = As<Arrow>(holdingHandle->Visual.get())) {
				arr->Thickness = gizmo.handleScale * gizmo.lineThickness * 1.5f;
			}

			Vec2f axis = holdingHandle->Axis;
			Vec2f offset = mouse.position - holdingHandle->MouseStartPosition;

			
			Angle rot = gizmo.target->Transform.Rotation;

			Vec2f newAxis = Transform::RotatePoint(axis, rot);

			float dist = Dot(offset, newAxis);
			Vec2f movement = newAxis * dist;
		
			gizmo.target->Transform.Position += movement;
			holdingHandle->MouseStartPosition = mouse.position;
		}
		else if (holdingHandle->Type == GizmoHandleType::Rotate) {
			if (Arc* arc = As<Arc>(holdingHandle->Visual.get())) {
				Vec2f dist1 = arc->Transform.Position - mouse.position;
				Angle angle = Angle::Radians(atan2f(dist1.x, dist1.y));

				arc->Transform.Rotation.radians += holdingHandle->GizmoStartAngle.AsRadians() - angle.AsRadians();
				gizmo.target->Transform.Rotation.radians += holdingHandle->GizmoStartAngle.AsRadians() - angle.AsRadians();

				holdingHandle->GizmoStartAngle.radians = angle.AsRadians();
				holdingHandle->MouseStartPosition = mouse.position;
			}
		}
		else if (holdingHandle->Type == GizmoHandleType::Scale) {
			if (Rectangle* rect = As<Rectangle>(holdingHandle->Visual.get())) {
				if (Rectangle* target = As<Rectangle>(gizmo.target)) {
					rect->Size = Vec2f(gizmo.handleScale * gizmo.scaleMulti * 1.2f);

					Vec2f axis = holdingHandle->Axis;

					
					Vec2f offset = mouse.position - holdingHandle->MouseStartPosition;

					Vec2f localOffset = Transform::RotatePoint(offset, -target->Transform.Rotation);

					Vec2f sizeChange = localOffset * axis;
					Vec2f oldSize = target->Size;

					target->Size += sizeChange;
					target->Size = { max(gizmo.minimumObjSize, target->Size.x),
									 max(gizmo.minimumObjSize, target->Size.y) };

					Vec2f actualChange = target->Size - oldSize;
					Vec2f actualHandleMovement = actualChange * axis;

					Vec2f worldChange = Transform::RotatePoint(actualHandleMovement, target->Transform.Rotation);

					target->Transform.Position += worldChange * 0.5f;

					holdingHandle->MouseStartPosition = mouse.position;
				}
			}
		}
	}
	else {
		holdingHandle = nullptr;
	}
}