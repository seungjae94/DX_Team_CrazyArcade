#pragma once

namespace MapImgRes
{
	// BackGround
	const std::string_view play_ui_background	= "spr_play_ui_background.png";
	const std::string_view village_background	= "spr_village1_background.png";
	const std::string_view Forest_background = "spr_forest_background.png";
	
	// Block
	const std::string_view block_vil_house_0	= "spr_vil_house_0.png";
	const std::string_view block_vil_house_1	= "spr_vil_house_1.png";
	const std::string_view block_vil_house_2	= "spr_vil_house_2.png";
	const std::string_view block_vil_tree_0		= "spr_vil_tree_0.png";

	const std::string_view block_vil_box0		= "spr_vil_Box0";
	const std::string_view block_vil_box1		= "spr_vil_Box1";
	const std::string_view block_vil_box2		= "spr_vil_Box2";

	// Item
	const std::string_view item_shadow			= "spr_item_shadow";
	const std::string_view item_bubble			= "spr_item_bubble.png";
	const std::string_view item_devil			= "spr_item_devil.png";
	const std::string_view item_fluid			= "spr_item_fluid.png";
	const std::string_view item_glove			= "spr_item_glove.png";
	const std::string_view item_reddevil		= "spr_item_reddevil.png";
	const std::string_view item_roller			= "spr_item_roller.png";
	const std::string_view item_shoes			= "spr_item_shoes.png";
	const std::string_view item_ultra			= "spr_item_ultra.png";

	// Bomb
	const std::string_view bomb						= "spr_bomb.png";
	const std::string_view bomb_effect_center		= "spr_bomb_effect_center.png";
	const std::string_view bomb_effect_up_end		= "spr_bomb_effect_up_0.png";
	const std::string_view bomb_effect_up			= "spr_bomb_effect_up_1.png";
	const std::string_view bomb_effect_down_end		= "spr_bomb_effect_down_0.png";
	const std::string_view bomb_effect_down			= "spr_bomb_effect_down_1.png";
	const std::string_view bomb_effect_left_end		= "spr_bomb_effect_left_0.png";
	const std::string_view bomb_effect_left			= "spr_bomb_effect_left_1.png";
	const std::string_view bomb_effect_right_end	= "spr_bomb_effect_right_0.png";
	const std::string_view bomb_effect_right		= "spr_bomb_effect_right_1.png";
}

namespace MapAnim
{
	// Block
	const std::string_view block_idle			= "Block_Idle";
	const std::string_view block_destroy		= "Block_Destroy";

	// Item
	const std::string_view item_shadow			= "Item_Shadow";

	// Bomb
	const std::string_view bomb						= "Bomb";
	const std::string_view bomb_effect_center		= "Bomb_Effect_Center";
	const std::string_view bomb_effect_up_end		= "Bomb_Effect_Up_End";
	const std::string_view bomb_effect_up			= "Bomb_Effect_Up";
	const std::string_view bomb_effect_down_end		= "Bomb_Effect_Down_End.png";
	const std::string_view bomb_effect_down			= "Bomb_Effect_Donw.png";
	const std::string_view bomb_effect_left_end		= "Bomb_Effect_Left_End.png";
	const std::string_view bomb_effect_left			= "Bomb_Effect_Left.png";
	const std::string_view bomb_effect_right_end	= "Bomb_Effect_Right_End.png";
	const std::string_view bomb_effect_right		= "Bomb_Effect_Right.png";
}

namespace Const
{
	const int MaxOrder = 1000;
}

namespace BlockBaseState
{
	const std::string_view idle					= "Idle";
}

namespace BoxState
{
	const std::string_view destroy				= "Destroy";
}

namespace MoveBoxState
{
	const std::string_view move					= "Move";
	const std::string_view destroy				= "Destroy";
}

namespace ItemState
{
	const std::string_view idle					= "Idle";
}

namespace BombState
{
	const std::string_view idle					 = "Idle";
	const std::string_view explosion			 = "Explosion";
}