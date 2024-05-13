#include "PreCompile.h"
#include "Transform.h"
#include "EngineDebug.h"


bool (*FTransform::CollisionFunction[static_cast<int>(ECollisionType::Max)][static_cast<int>(ECollisionType::Max)])(const FTransform& _Left, const FTransform& _Right);

class CollisionFunctionInit
{
public:
	CollisionFunctionInit()
	{
		FTransform::CollisionFunction[static_cast<int>(ECollisionType::CirCle)][static_cast<int>(ECollisionType::CirCle)] = FTransform::CircleToCircle;
		FTransform::CollisionFunction[static_cast<int>(ECollisionType::CirCle)][static_cast<int>(ECollisionType::Rect)] = FTransform::CircleToRect;
		FTransform::CollisionFunction[static_cast<int>(ECollisionType::CirCle)][static_cast<int>(ECollisionType::RotRect)] = FTransform::CircleToRotRect;
		FTransform::CollisionFunction[static_cast<int>(ECollisionType::CirCle)][static_cast<int>(ECollisionType::Point)] = FTransform::CircleToPoint;

		FTransform::CollisionFunction[static_cast<int>(ECollisionType::Rect)][static_cast<int>(ECollisionType::Rect)] = FTransform::RectToRect;
		FTransform::CollisionFunction[static_cast<int>(ECollisionType::Rect)][static_cast<int>(ECollisionType::CirCle)] = FTransform::RectToCircle;
		FTransform::CollisionFunction[static_cast<int>(ECollisionType::Rect)][static_cast<int>(ECollisionType::RotRect)] = FTransform::RectToRotRect;
		FTransform::CollisionFunction[static_cast<int>(ECollisionType::Rect)][static_cast<int>(ECollisionType::Point)] = FTransform::RectToPoint;

		FTransform::CollisionFunction[static_cast<int>(ECollisionType::RotRect)][static_cast<int>(ECollisionType::Rect)] = FTransform::RotRectToRect;
		FTransform::CollisionFunction[static_cast<int>(ECollisionType::RotRect)][static_cast<int>(ECollisionType::CirCle)] = FTransform::RotRectToCirCle;
		FTransform::CollisionFunction[static_cast<int>(ECollisionType::RotRect)][static_cast<int>(ECollisionType::RotRect)] = FTransform::RotRectToRotRect;
		FTransform::CollisionFunction[static_cast<int>(ECollisionType::RotRect)][static_cast<int>(ECollisionType::Point)] = FTransform::RotRectToPoint;

		FTransform::CollisionFunction[static_cast<int>(ECollisionType::Point)][static_cast<int>(ECollisionType::Rect)] = FTransform::PointToRect;
		FTransform::CollisionFunction[static_cast<int>(ECollisionType::Point)][static_cast<int>(ECollisionType::CirCle)] = FTransform::PointToCircle;
		FTransform::CollisionFunction[static_cast<int>(ECollisionType::Point)][static_cast<int>(ECollisionType::RotRect)] = FTransform::PointToRotRect;
	}
	~CollisionFunctionInit()
	{

	}
};

CollisionFunctionInit Inst;

bool FTransform::CircleToCircle(const FTransform& _Left, const FTransform& _Right)
{
	CollisionData Left = _Left.GetCollisionData2D();
	CollisionData Right = _Right.GetCollisionData2D();
	return Left.Sphere.Intersects(Right.Sphere);
}

bool FTransform::CircleToRect(const FTransform& _Left, const FTransform& _Right)
{
	CollisionData Left = _Left.GetCollisionData2D();
	CollisionData Right = _Right.GetCollisionData2D();
	return Left.Sphere.Intersects(Right.AABB);
}

bool FTransform::CircleToRotRect(const FTransform& _Left, const FTransform& _Right)
{
	CollisionData Left = _Left.GetCollisionData2D();
	CollisionData Right = _Right.GetCollisionData2D();
	return Left.Sphere.Intersects(Right.OBB);
}


bool FTransform::CircleToPoint(const FTransform& _Left, const FTransform& _Right)
{
	CollisionData Left = _Left.GetCollisionData2D();
	CollisionData Right = _Right.GetCollisionData2D();
	Right.Sphere.Radius = 0.0f;
	return Left.Sphere.Intersects(Right.Sphere);
}


bool FTransform::RectToCircle(const FTransform& _Left, const FTransform& _Right)
{
	CollisionData Left = _Left.GetCollisionData2D();
	CollisionData Right = _Right.GetCollisionData2D();
	return Left.AABB.Intersects(Right.Sphere);
}

bool FTransform::RectToRect(const FTransform& _Left, const FTransform& _Right)
{
	CollisionData Left = _Left.GetCollisionData2D();
	CollisionData Right = _Right.GetCollisionData2D();
	return Left.AABB.Intersects(Right.AABB);
}

bool FTransform::RectToRotRect(const FTransform& _Left, const FTransform& _Right)
{
	CollisionData Left = _Left.GetCollisionData2D();
	CollisionData Right = _Right.GetCollisionData2D();
	return Left.AABB.Intersects(Right.OBB);
}

bool FTransform::RectToPoint(const FTransform& _Left, const FTransform& _Right)
{
	CollisionData Left = _Left.GetCollisionData2D();
	CollisionData Right = _Right.GetCollisionData2D();
	Right.Sphere.Radius = 0.0f;
	return Left.AABB.Intersects(Right.Sphere);
}



bool FTransform::PointToCircle(const FTransform& _Left, const FTransform& _Right)
{
	return CircleToPoint(_Right, _Left);
}
bool FTransform::PointToRect(const FTransform& _Left, const FTransform& _Right)
{
	return RectToPoint(_Right, _Left);
}

bool FTransform::PointToRotRect(const FTransform& _Left, const FTransform& _Right)
{
	return RotRectToPoint(_Right, _Left);
}





bool FTransform::RotRectToRotRect(const FTransform& _Left, const FTransform& _Right)
{
	CollisionData Left = _Left.GetCollisionData2D();
	CollisionData Right = _Right.GetCollisionData2D();
	return Left.OBB.Intersects(Right.OBB);
}

bool FTransform::RotRectToCirCle(const FTransform& _Left, const FTransform& _Right)
{
	CollisionData Left = _Left.GetCollisionData2D();
	CollisionData Right = _Right.GetCollisionData2D();
	return Left.OBB.Intersects(Right.Sphere);
}
bool FTransform::RotRectToRect(const FTransform& _Left, const FTransform& _Right)
{
	CollisionData Left = _Left.GetCollisionData2D();
	CollisionData Right = _Right.GetCollisionData2D();
	return Left.OBB.Intersects(Right.AABB);
}

bool FTransform::RotRectToPoint(const FTransform& _Left, const FTransform& _Right)
{
	CollisionData Left = _Left.GetCollisionData2D();
	CollisionData Right = _Right.GetCollisionData2D();
	Right.Sphere.Radius = 0.0f;
	return Left.OBB.Intersects(Right.Sphere);
}


FTransform::FTransform() 
	: LocalScale(FVector::One)
	, LocalRotation(FVector::Zero)
	, LocalPosition(FVector::Zero)
{
}

FTransform::~FTransform() 
{
}

bool FTransform::Collision(ECollisionType _ThisType, ECollisionType _OtherType, const FTransform& _Other)
{
	if (nullptr == CollisionFunction[static_cast<int>(_ThisType)][static_cast<int>(_OtherType)])
	{
		MsgBoxAssert("아직 충돌 함수를 만들지 않은 충돌입니다");
	}

	return CollisionFunction[static_cast<int>(_ThisType)][static_cast<int>(_OtherType)](*this,_Other);
}


void FTransform::TransformUpdate()
{
	//float4 Scale;
	//float4 Rotation;
	//float4 Position;
	//float4x4 ScaleMat;
	//float4x4 RotationMat;
	//float4x4 PositionMat;
	//float4x4 World;
	//float4x4 View;
	//float4x4 Projection;
	//float4x4 WVP;

	ScaleMat.Scale(LocalScale);

	RotationMat.RotationDeg(LocalRotation);

	PositionMat.Position(LocalPosition);

	LocalWorld = ScaleMat * RotationMat * PositionMat;
	World = LocalWorld * ParentMat;

	World.Decompose(WorldScale, WorldRotation, WorldPosition);

	// 쿼터니온 상태
	WorldRotation = WorldRotation.QuaternionToDeg();

	// 크 * 자 * 이 => 월드
	// 월드 => 크 자 이
	// World

	// 최종월드 입니다.
}

void FTransform::CalculateViewAndProjection(FMatrix _View, FMatrix _Projection)
{
	View = _View;
	Projection = _Projection;
	WVP = World * _View * _Projection;
}