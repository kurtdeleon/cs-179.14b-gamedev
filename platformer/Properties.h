#ifndef PROPERTIES
#define PROPERTIES

struct Properties
{
	float FPS, PLAYER_H, PLAYER_W;
	float H_ACCEL, H_COEFF, H_OPPOSITE, H_AIR, MIN_H_VEL, MAX_H_VEL;
	float GRAVITY, V_ACCEL, V_HOLD, V_SAFE, CUT_V_VEL, MAX_V_VEL, GAP;
	int CAM_TYPE;
	float CAM_DRIFT;
	int CAM_EDGES[4];
	int WINDOW_H = 800;
	int WINDOW_W = 600;

	bool cameraGuidesOn = true;
	void ToggleCameraGuides()
	{
		cameraGuidesOn = !cameraGuidesOn;
	}
};

#endif