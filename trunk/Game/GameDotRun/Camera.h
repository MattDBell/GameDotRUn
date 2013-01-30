#ifndef CAMERA_H
#define CAMERA_H

//////////////////////////////////////////////////////////////////////////
//	Summary: Where the renderer gets it's vector2 with which to offset all draws
//	
//	Responsibilities: For now the Camera will mainly be in charge of tracking 
//	whatever should be focused (ten bucks it's the player!).  Later it will
//	handle constraints and effects (most importantly... CAMERA SSHSHSHHSHSHAKE!)
#include "GDRVector2.h"
class Entity;
typedef GDR_Vector2 (*TrackingAlgo)(const GDR_Vector2 last, const Entity* tracking, float dt); 

class Camera
{
	static Camera* currentCamera;
	GDR_Vector2 offset; //best to use GDR_Vector2 even if it painfully needs to be worked on
	Entity * tracking; // this is a bit dangerous but fuck that noise.
	TrackingAlgo mine;
	static GDR_Vector2 defaultTracker(const GDR_Vector2 last, const Entity* tracking, float dt);
	void Update(float dt);
public:
	Camera();
	enum TrackingAlgos { HARD_FOLLOW, TOTAL};
	static void UpdateCurrent(float dt);
	static GDR_Vector2 GetOffset();
	void SetAsCurrent();
	void SetToTrack(Entity * track);
	void SetTrackingAlgo(TrackingAlgo to);
};

#endif