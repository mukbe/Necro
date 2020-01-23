#pragma once
enum Pivot
{
	LEFT_TOP, CENTER, BOTTOM, TOP, Pivot_End,
};
enum RigidType : short
{
	Dynamic = 0, Static, RigidType_End
};
enum ObjectMoveType
{
	MoveType_Beat, MoveType_Control ,MoveType_Custom
};