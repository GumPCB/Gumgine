#pragma once
#include "GeStd.h"

class DeviceSample : public Gumgine::Core::Core
{
public:
	DeviceSample();
	virtual ~DeviceSample();

	//��� Ŭ������ �ݵ�� �Ʒ��� �Լ��� �����Ѵ�.
	virtual bool	Init() override;
	virtual bool	Frame() override;
	virtual bool	Render() override;
	virtual bool	Release() override;

private:
	Gumgine::Util::Timer timer;
	std::random_device randomdevice;
	std::uniform_real_distribution< float > dist;
};

