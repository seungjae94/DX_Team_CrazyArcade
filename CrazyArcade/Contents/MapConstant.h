#pragma once

namespace MapImgRes
{
	// BackGround
	const std::string_view play_ui_background		= "spr_play_ui_background.png";
	const std::string_view village_background		= "spr_village1_background.png";
	const std::string_view Forest_background		= "spr_forest_background.png";
	const std::string_view Pirate_background01		= "spr_Pirate_background01.png";
	const std::string_view Pirate_background02		 = "spr_Pirate_background02.png";

	
	// Wall
	const std::string_view block_vil_house_0		= "spr_vil_house_0.png";
	const std::string_view block_vil_house_1		= "spr_vil_house_1.png";
	const std::string_view block_vil_house_2		= "spr_vil_house_2.png";
	const std::string_view block_vil_tree_0			= "spr_vil_tree_0.png";

	const std::string_view block_forest_pool		= "spr_forest_pool.png";
	const std::string_view block_forest_rock		= "spr_forest_rock.png";
	
	const std::string_view block_Pirate_flag		= "spr_pirate_flag";
	const std::string_view block_Pirate_wall		= "spr_priate_wall.png";
	const std::string_view block_Pirate_labp		= "spr_pirate_labp";

	// Box
	const std::string_view block_vil_box0			= "spr_vil_Box0";
	const std::string_view block_vil_box1			= "spr_vil_Box1";
	const std::string_view block_vil_box2			= "spr_vil_Box2";
	const std::string_view block_vil_bush			= "spr_village_bush.png";

	const std::string_view block_forest_leef1		= "spr_forest_leef1";
	const std::string_view block_forest_leef2		= "spr_forest_leef2";
	const std::string_view block_forest_bush1		= "spr_forest_bush1";
	const std::string_view block_forest_bush2		= "spr_forest_bush2";
	const std::string_view block_forest_bush3		= "spr_forest_bush3";
	const std::string_view block_forest_basket		= "spr_forest_basket";


	const std::string_view block_Pirate_box0		= "spr_pirate_box0";
	const std::string_view block_Pirate_box1		= "spr_pirate_box1";
	const std::string_view block_Pirate_box2		= "spr_pirate_box2";

	// Item
	const std::string_view item_shadow				= "spr_item_shadow";
	const std::string_view item_bubble				= "spr_item_bubble.png";
	const std::string_view item_devil				= "spr_item_devil.png";
	const std::string_view item_fluid				= "spr_item_fluid.png";
	const std::string_view item_glove				= "spr_item_glove.png";
	const std::string_view item_reddevil			= "spr_item_reddevil.png";
	const std::string_view item_roller				= "spr_item_roller.png";
	const std::string_view item_shoes				= "spr_item_shoes.png";
	const std::string_view item_ultra				= "spr_item_ultra.png";
	const std::string_view item_superman			= "spr_item_superman.png";
	const std::string_view item_owl					= "spr_item_owl.png";
	const std::string_view item_turtle				= "spr_item_turtle.png";
	const std::string_view item_ufo					= "spr_item_ufo.png";
	const std::string_view item_needle				= "spr_item_needle.png";

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

namespace BlockState
{
	const std::string_view idle					= "Idle";
	const std::string_view move					= "Move";
	const std::string_view destroy				= "Destroy";
	const std::string_view shaking				= "Shaking";
}

namespace BushState
{
	const std::string_view idle					= "Idle";
	const std::string_view shaking				= "Shaking";
	const std::string_view player_in			= "Player_In";
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