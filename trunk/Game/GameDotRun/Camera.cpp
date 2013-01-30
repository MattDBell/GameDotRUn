#include "Camera.h"
#include "Entity.h"
Camera *Camera::currentCamera = 0;

Camera::Camera()
	:tracking(0), mine(0)
{
}

GDR_Vector2 Camera::GetOffset()
{
	if(currentCamera)
	{
		return currentCamera->offset;
	}
	static GDR_Vector2 backup;
	backup.SetX(0);
	backup.SetY(0);
	return backup;
}
void Camera::UpdateCurrent(float dt)
{
	if(currentCamera)
		currentCamera->Update(dt);
}
void Camera::Update(float dt)
{
	if(mine)
	{
		offset = mine(offset, tracking, dt);
	}
	else
	{
		offset = defaultTracker(offset, tracking, dt);
	}
}
GDR_Vector2 Camera::defaultTracker(const GDR_Vector2 last, const Entity* tracking, float dt)
{
	return tracking->GetPosition();
}
void Camera::SetAsCurrent()
{
	currentCamera = this;
}
void Camera::SetToTrack(Entity *tracking)
{
	this->tracking = tracking;
}
void Camera::SetTrackingAlgo(TrackingAlgo to)
{
	mine = to;
}