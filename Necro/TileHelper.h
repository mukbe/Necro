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

static D3DXVECTOR2 _tilePivotPos;
static POINT _mapSize;
static D3DXVECTOR2 _tileSize;