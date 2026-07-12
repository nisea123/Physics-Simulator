#include "Scene.h"
#include "Renderer.h"
#include "Object.h"

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

void Scene::Update(Mouse& mouse) {
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


		if (Arrow* arr = As<Arrow>(hoveredHandle->Visual.get())) {
			arr->Thickness = gizmo.thickness * 1.5f;
		}
		lastHoveredHandle = hoveredHandle;
	}



	if (holdingHandle && mouse.m1) {

		if (Arrow* arr = As<Arrow>(holdingHandle->Visual.get())) {
			arr->Thickness = gizmo.thickness * 1.5f;
		}

		Vec2f axis = holdingHandle->Axis;
		Vec2f offset = holdingHandle->MouseStartPosition - mouse.position;
		holdingHandle->MouseStartPosition = mouse.position;
		Angle rot = gizmo.target->Transform.Rotation;
		Transform transform;
		Vec2f newAxis = transform.RotatePoint(axis,rot);
		float dist = -Dot(offset,newAxis);
		Vec2f movement = newAxis * dist;
		cout << offset.x << " " << offset.y << " " << dist << " " << movement.x << " " << movement.y << endl;
		gizmo.target->Transform.Position = gizmo.target->Transform.Position + movement;
	}
	else {
		holdingHandle = nullptr;
	}
}