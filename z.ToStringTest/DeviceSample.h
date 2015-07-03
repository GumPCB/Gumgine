#pragma once

#include "../Gumgine/Core/Core.h"

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
};

