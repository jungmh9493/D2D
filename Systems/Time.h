#pragma once

// 시간에 관련된 클래스
// delta Time : 프레임 마다의 경과 시간 (이 시간을 업데이트 해주는게 게임에서 굉장히 중요하다)
// 모든 환경에서 동일하게 동작할 수 있게 만들어주어야 한다.
// 환경에 따라서 업데이트 주기가 다르기 때문에, 이 간극을 동일하게 맞춰주어야 한다.
// fps 결과에 deltaTime을 곱해서 결과를 동일하게 만들어준다.
// 환경이 좋아서 업데이트 주기가 짧다면 deltaTime도 작아진다.
// 환경이 좋지 않아서 업데이트 주기가 길다면 deltaTime은 커진다.
// 그렇기 떄문에 업데이트 결과에 deltaTime을 곱해주면 환경에 상관없이 결과가 같아지게 된다.
// chrono 헤더를 추가해서 시간을 정밀하게 받아올 수 있다.

class Time
{
	DECLARE_SINGLETON(Time);

public:
	void Update();

	float GetDeltaTime() { return (float)deltaTime; }
	UINT GetFPS() { return fps; }
	double GetWorldTIme() { return worldTime; }

	void CheckTime() { cout << "FPS : " << fps << ", DeltaTime : " << deltaTime << ", WorldTime : " << worldTime << endl; }

private:
	chrono::steady_clock::time_point currentTime;
	chrono::steady_clock::time_point lastTime;

	double deltaTime = 0.0f;

	UINT fps = 0;
	double worldTime = 0.0;

	UINT frameCount = 0;
	double fpsTimeElapsed = 0.0;
};