#pragma once
#include "stdafx.h"

enum AttributeType
{
	AttributeTypeStart = 0,
	ObjNone,					//�ϰ͵� ���� Ÿ��
	ObjStatic,					//���� Ÿ��, �ı� �Ұ�
	ObjDestructable,			//���� Ÿ��, �ı� ����
	AttributeTypeEnd
};

static const POINT defaultMapSize = { 10,10 };
static const D3DXVECTOR2 defaultTileSize = { 52.f, 52.f };