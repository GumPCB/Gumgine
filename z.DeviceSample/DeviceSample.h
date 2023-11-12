#pragma once

#include "../Gumgine/Core/Core.h"
#include "../Gumgine/Util/Timer.h"

class DeviceSample : public Gumgine::Core::Core
{
public:
	DeviceSample();
	virtual ~DeviceSample();

	//모든 클래스는 반드시 아래의 함수를 정의한다.
	virtual bool	Init() override;
	virtual bool	Frame() override;
	virtual bool	Render() override;
	virtual bool	Release() override;

private:
	Gumgine::Util::Timer timer;
	DirectX::XMVECTORF32 backBufferColor = DirectX::Colors::LightSteelBlue;
	std::random_device randomdevice;
	std::uniform_real_distribution< float > dist;
};

