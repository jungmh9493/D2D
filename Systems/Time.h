#pragma once

// �ð��� ���õ� Ŭ����
// delta Time : ������ ������ ��� �ð� (�� �ð��� ������Ʈ ���ִ°� ���ӿ��� ������ �߿��ϴ�)
// ��� ȯ�濡�� �����ϰ� ������ �� �ְ� ������־�� �Ѵ�.
// ȯ�濡 ���� ������Ʈ �ֱⰡ �ٸ��� ������, �� ������ �����ϰ� �����־�� �Ѵ�.
// fps ����� deltaTime�� ���ؼ� ����� �����ϰ� ������ش�.
// ȯ���� ���Ƽ� ������Ʈ �ֱⰡ ª�ٸ� deltaTime�� �۾�����.
// ȯ���� ���� �ʾƼ� ������Ʈ �ֱⰡ ��ٸ� deltaTime�� Ŀ����.
// �׷��� ������ ������Ʈ ����� deltaTime�� �����ָ� ȯ�濡 ������� ����� �������� �ȴ�.
// chrono ����� �߰��ؼ� �ð��� �����ϰ� �޾ƿ� �� �ִ�.

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