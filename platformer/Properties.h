#ifndef PROPERTIES
#define PROPERTIES

struct Properties
{
	float FPS, PLAYER_H, PLAYER_W;
	float H_ACCEL, H_COEFF, H_OPPOSITE, H_AIR, MIN_H_VEL, MAX_H_VEL;
	float GRAVITY, V_ACCEL, V_HOLD, V_SAFE, CUT_V_VEL, MAX_V_VEL, GAP;
	int CAM_TYPE;
	float CAM_DRIFT;
	float CAM_EDGE1, CAM_EDGE2, CAM_EDGE3, CAM_EDGE4;

	bool cameraGuidesOn = false;
	void ToggleCameraGuides()
	{
		cameraGuidesOn = !cameraGuidesOn;
	}
};

#endif


