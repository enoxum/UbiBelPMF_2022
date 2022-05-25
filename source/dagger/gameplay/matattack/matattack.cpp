#include "matattack.h"

#include "core/core.h"
#include "core/engine.h"
#include "core/input/inputs.h"
#include "core/graphics/sprite.h"
#include "core/graphics/animation.h"
#include "core/graphics/shaders.h"
#include "core/graphics/window.h"
#include "core/game/transforms.h"

#include "gameplay/common/simple_collisions.h"

#include "movementsystem.h"
#include "controllersystem.h"
#include "gravitysystem.h"
#include "jumpsystem.h"
#include "attacksystem.h"
#include "knockbacksystem.h"
#include "specialabilitysystem.h"
#include "tools.h"
#include "levelchangesystem.h" 

using namespace dagger;
using namespace matattack;

void Matattack::GameplaySystemsSetup()
{
    auto& engine = Engine::Instance();
	engine.AddPausableSystem<SimpleCollisionsSystem>();
	engine.AddPausableSystem<ControllerSystem>();
	engine.AddPausableSystem<MovementSystem>();
	engine.AddPausableSystem<GravitySystem>();
	engine.AddPausableSystem<JumpSystem>();
    engine.AddPausableSystem<AttackSystem>();
    engine.AddPausableSystem<KnockbackSystem>();
    engine.AddPausableSystem<SpecialAbilitySystem>();
	engine.AddPausableSystem<Tools>();
	engine.AddSystem<LevelChangeSystem>();

}

void setCamera()
{
	auto* camera = Engine::GetDefaultResource<Camera>();
	camera->mode = ECameraMode::FixedResolution;
	camera->size = { 1920, 1080 };
	camera->zoom = 1.25;
	camera->position = { 0, 0, 0 };
	camera->Update();
}

struct Arrow
{
	Entity entity;
	ArrowInfo& arrow_info;
	Sprite& sprite;
	Transform& transform;

	static Arrow Get(Entity entity)
	{
		auto& reg = Engine::Registry();
		auto& arrow_info = reg.get_or_emplace<ArrowInfo>(entity);
		auto& sprite = reg.get_or_emplace<Sprite>(entity);
		auto& transform = reg.get_or_emplace<Transform>(entity);

		return Arrow{ entity, arrow_info, sprite, transform };
	}

	static Arrow Create(Vector2 position_ = { 0, 0 }, String sprite_ = "matattack:items:arrow")
	{
		auto& reg = Engine::Registry();
		auto entity = reg.create();
		auto arrow = Arrow::Get(entity);

		arrow.sprite.scale = { 1.5, 1.5 };
		arrow.sprite.position = { position_, 0.0f };
		arrow.sprite.size = { 50, 50 };
		arrow.transform.position = { position_, 0.0f };
		AssignSprite(arrow.sprite, sprite_);

		return arrow;
	}
};

struct Heart
{
	Entity entity;
	HeartInfo& heart_info;
	Sprite& sprite;
	Transform& transform;

	static Heart Get(Entity entity)
	{
		auto& reg = Engine::Registry();
		auto& heart_info = reg.get_or_emplace<HeartInfo>(entity);
		auto& sprite = reg.get_or_emplace<Sprite>(entity);
		auto& transform = reg.get_or_emplace<Transform>(entity);

		return Heart{ entity, heart_info, sprite, transform };
	}

	static Heart Create(Vector3 position_ = { 0, 0, 0 }, String sprite_ = "matattack:items:6")
	{
		auto& reg = Engine::Registry();
		auto entity = reg.create();
		auto hearts = Heart::Get(entity);

		hearts.sprite.scale = { 1.8, 1.8 };
		hearts.sprite.position = { position_ };
		hearts.sprite.size = { 150, 50 };
		hearts.transform.position = { position_ };
		AssignSprite(hearts.sprite, sprite_);

		return hearts;
	}
};

struct HealthBar
{
	Entity entity;
	HealthInfo& health_info;
	Sprite& sprite;
	Transform& transform;

	static HealthBar Get(Entity entity)
	{
		auto& reg = Engine::Registry();
		auto& health_info = reg.get_or_emplace<HealthInfo>(entity);
		auto& sprite = reg.get_or_emplace<Sprite>(entity);
		auto& transform = reg.get_or_emplace<Transform>(entity);

		return HealthBar{ entity, health_info, sprite, transform };
	}

	static HealthBar Create(Vector3 position_ = { 0, 0, 0 }, String sprite_ = "matattack:items:health_bar100")
	{
		auto& reg = Engine::Registry();
		auto entity = reg.create();
		auto healthbar = HealthBar::Get(entity);

		healthbar.sprite.scale = { 0.65, 0.65 };
		healthbar.sprite.position = { position_ };
		healthbar.sprite.size = { 180, 30 };
		healthbar.transform.position = { position_ };
		AssignSprite(healthbar.sprite, sprite_);

		return healthbar;
	}
};

struct SpecialBarBack
{
	Entity entity;
	Sprite& sprite;
	Transform& transform;
	SpecialBarBackInfo& bar_back_info;

	static SpecialBarBack Get(Entity entity)
	{
		auto& reg = Engine::Registry();
		auto& sprite = reg.get_or_emplace<Sprite>(entity);
		auto& transform = reg.get_or_emplace<Transform>(entity);
		auto& info = reg.get_or_emplace<SpecialBarBackInfo>(entity);

		return SpecialBarBack{ entity, sprite, transform, info };
	}

	static SpecialBarBack Create(Vector3 position_ = { 0, 0, 0 }, String sprite_ = "matattack:items:health_bar100")
	{
		auto& reg = Engine::Registry();
		auto entity = reg.create();
		auto specialBarBack = SpecialBarBack::Get(entity);

		specialBarBack.sprite.scale = { 0.23, 0.40 };

		specialBarBack.sprite.position = { position_ };

		specialBarBack.sprite.size = { 180, 30 };

		specialBarBack.transform.position = { position_ };

		AssignSprite(specialBarBack.sprite, sprite_);

		return specialBarBack;
	}
};

struct SpecialBar
{
	Entity entity;
	SpecialBarInfo& special_bar_info;
	Sprite& sprite;
	Transform& transform;

	static SpecialBar Get(Entity entity)
	{
		auto& reg = Engine::Registry();
		auto& special_bar_info = reg.get_or_emplace<SpecialBarInfo>(entity);
		auto& sprite = reg.get_or_emplace<Sprite>(entity);
		auto& transform = reg.get_or_emplace<Transform>(entity);

		return SpecialBar{ entity, special_bar_info, sprite, transform };
	}

	static SpecialBar Create(Vector3 position_ = { 0, 0, 0 }, String sprite_ = "matattack:items:health_bar100")
	{
		auto& reg = Engine::Registry();
		auto entity = reg.create();
		auto specialBar = SpecialBar::Get(entity);

		specialBar.special_bar_info.full_scale = 0.225;

		specialBar.sprite.scale = { specialBar.special_bar_info.full_scale, 0.40 };

		specialBar.sprite.position = { position_ };

		specialBar.sprite.size = { 180, 30 };

		specialBar.transform.position = { position_ };

		AssignSprite(specialBar.sprite, sprite_);

		return specialBar;
	}
};

struct Character
{
    Entity entity;
    Sprite& sprite;
    InputReceiver& input;
    CharacterInfo& char_info;
    Transform& transform;
    SimpleCollision& simple_collision;
    Animator& animator;
    Gravity& gravity;
    UpSpeed& upspeed;
    AttackInfo& attack_info;
    KnockbackInfo& knockback_info;
    SpecialInfo& special_info;

    static Character Get(Entity entity)
    {
        auto& reg = Engine::Registry();
        auto& sprite = reg.get_or_emplace<Sprite>(entity);
        auto& input = reg.get_or_emplace<InputReceiver>(entity);
        auto& char_info = reg.get_or_emplace<CharacterInfo>(entity);
        auto& transform = reg.get_or_emplace<Transform>(entity);
        auto& simple_collision = reg.get_or_emplace<SimpleCollision>(entity);
        auto& anim = reg.get_or_emplace<Animator>(entity);
        auto& gravity = reg.get_or_emplace<Gravity>(entity);
        auto& upspeed = reg.get_or_emplace<UpSpeed>(entity);
        auto& attack_info = reg.get_or_emplace<AttackInfo>(entity);
        auto& knockback_info = reg.get_or_emplace<KnockbackInfo>(entity);
        auto& special_info = reg.get_or_emplace<SpecialInfo>(entity);

        return Character{ entity, sprite, input, char_info, transform, simple_collision, anim, gravity, upspeed, attack_info, knockback_info, special_info };
    }

	static Character Create(String input_ = "", Vector2 position_ = { 0, 0 }, SpecialAbilities special_name = SpecialAbilities::ATTACK_BOOST,
		String sprite_path = "matattack:characters:fox:idle:idle1", String animation_name = "fox")
    {

        auto& reg = Engine::Registry();
        auto entity = reg.create();

        ATTACH_TO_FSM(FSMCharacterController, entity);
        ATTACH_TO_FSM(FSMCharacterJump, entity);


        auto chr = Character::Get(entity);
		if (animation_name == "otter")
			chr.sprite.scale = { 0.5, 0.5 };
        else
			chr.sprite.scale = { 1.5, 1.5 };
        chr.sprite.position = { position_, 1.0f };
        chr.sprite.size = { 50, 50 };

		AssignSprite(chr.sprite, sprite_path);
		AnimatorPlay(chr.animator, "matattack:idle:" + animation_name);

        if (input_ != "")
            chr.input.contexts.push_back(input_);

        chr.transform.position = { position_, 1.0f };

        chr.simple_collision.size = { 50, 50 };
		   chr.simple_collision.pos = chr.transform.position;
        chr.simple_collision.is_collidable = false;
        chr.simple_collision.is_moveable = true;

        chr.char_info.speed = 200.0F;
		chr.char_info.animationName = animation_name;

        chr.gravity.increase = 1200.0F;
        chr.gravity.speed = 0.0F;

        chr.upspeed.jumpSpeed = 800.0F;
        chr.upspeed.cutoff = 2.0F;

        chr.attack_info.attack_damage = 10;
        chr.attack_info.hp = 100;
        chr.attack_info.base_imunity_duration = 100;

        chr.knockback_info.base_horizontal_speed = 1000.0F;
        chr.knockback_info.horizontal_decrease = 10.0F;
        chr.knockback_info.base_vertical_speed = 300.0F;

        chr.special_info.name = special_name;
        Engine::GetDefaultResource<SpecialAbilitySystem>()->specialAbilities[special_name]->Init(chr.entity);

        return chr;
    }
};


void setSingleBlock(int x, int y, int z, String path_to_sprite, unsigned size_x, unsigned size_y, bool is_collidable, bool is_moveable) {

	auto& engine = Engine::Instance();
	auto& reg = engine.Registry();
	{
		auto block = reg.create();
		auto& sprite = reg.get_or_emplace<Sprite>(block);

		AssignSprite(sprite, path_to_sprite);
		sprite.size = { size_x, size_y };
		sprite.position = { x, y, z };
		auto& simple_collision = reg.emplace<SimpleCollision>(block);
		simple_collision.size = sprite.size;
		simple_collision.pos = sprite.position;
		simple_collision.is_collidable = is_collidable;
		simple_collision.is_moveable = is_moveable;

		auto& transform = reg.emplace<Transform>(block);
		transform.position = sprite.position;
	}
}

void setPlatform(int start_x, int start_y, int start_z, unsigned num_of_iterations, String path) {
	for (unsigned i = 0u; i < num_of_iterations; ++i)
	{
		setSingleBlock(start_x, start_y, start_z, path, 50, 50, true, false);
		start_x += 50;
	}
}

void createBackdrop(String background_path)
{
	auto& engine = Engine::Instance();
	auto& reg = engine.Registry();
	float zPos = 1.f;
	{
		auto back = reg.create();
		auto& sprite = reg.get_or_emplace<Sprite>(back);
		AssignSprite(sprite, background_path);
		sprite.position.z = 10;
	}
}

void matattack::EndGame(String char_won)
{
	auto& engine = Engine::Instance();
	auto& reg = engine.Registry();
	auto back = reg.create();
	auto& sprite = reg.get_or_emplace<Sprite>(back);
	AssignSprite(sprite, "matattack:background:win_screen");
	sprite.position.z = 0;
	setSingleBlock(0, 0 , 0 , "matattack:characters:" + char_won + ":idle:idle1", 200, 200, false, false);
}

void setMap1() {

	createBackdrop("matattack:background:sky");
	setSingleBlock(-300, -225, 10, "matattack:tiles:tree", 100, 100, false, false);
	setSingleBlock(600, -50, 10, "matattack:tiles:tree", 100, 100, false, false);
	setSingleBlock(200, 120, 10, "matattack:tiles:bush", 50, 40, false, false);
	setSingleBlock(-200, 120, 10, "matattack:tiles:big_crate", 40, 40, false, false);
	setSingleBlock(300, -255, 10, "matattack:tiles:big_crate", 40, 40, false, false);
	setSingleBlock(400, 250, 10, "matattack:tiles:cloud2", 200, 100, false, false);
	setSingleBlock(-470, 250, 10, "matattack:tiles:cloud1", 130, 100, false, false);
	setSingleBlock(0, 300, 10, "matattack:tiles:cloud3", 120, 100, false, false);
	setPlatform(-350, -300, 1, 16, "matattack:tiles:tile_with_grass");
	setPlatform(-600, -125, 1, 6, "matattack:tiles:tile_with_grass");
	setPlatform(400, -125, 1, 6, "matattack:tiles:tile_with_grass");
	setPlatform(-350, 75, 1, 16, "matattack:tiles:tile_with_grass");

}

void setMap2() {
	createBackdrop("matattack:background:desert");
	setSingleBlock(-300, -250, 10, "matattack:tiles:skeleton", 100, 50, false, false);
	setSingleBlock(300, -225, 10, "matattack:tiles:cactus", 80, 100, false, false);
	setSingleBlock(600, -80, 10, "matattack:tiles:skeleton", 100, 50, false, false);
	setSingleBlock(200, 120, 10, "matattack:tiles:bush_desert", 75, 50, false, false);
	setSingleBlock(-200, 120, 10, "matattack:tiles:bush_desert", 75, 50, false, false);
	setPlatform(-350, -300, 1, 16, "matattack:tiles:tile_rock");
	setPlatform(-600, -125, 1, 6, "matattack:tiles:tile_rock");
	setPlatform(400, -125, 1, 6, "matattack:tiles:tile_rock");
	setPlatform(-350, 75, 1, 16, "matattack:tiles:tile_rock");
}

void setMap3() {
	createBackdrop("matattack:background:forest");
	setSingleBlock(-250, -200, 10, "matattack:tiles:tree_forest", 125, 150, false, false);
	setSingleBlock(300, 175, 10, "matattack:tiles:tree_forest", 125, 150, false, false);
	setSingleBlock(300, -260, 10, "matattack:tiles:rock", 50, 30, false, false);
	setSingleBlock(600, -85, 10, "matattack:tiles:rock", 50, 30, false, false);
	setPlatform(-350, -300, 1, 16, "matattack:tiles:tile_stone");
	setPlatform(-600, -125, 1, 6, "matattack:tiles:tile_stone");
	setPlatform(400, -125, 1, 6, "matattack:tiles:tile_stone");
	setPlatform(-350, 75, 1, 16, "matattack:tiles:tile_stone");
}

void setLevel(int lvl, String fstCharAnimation, String sndCharAnimation) {


	setSingleBlock(-730, 380, 10, "matattack:characters:" + fstCharAnimation + ":idle:idle1", 100, 100, false, false);
	auto heathbar1 = HealthBar::Create({-670, 340, 10}, "matattack:items:health_bar100");
	auto hearts1 = Heart::Create({-640, 380, 10}, "matattack:items:3");
	auto specialbarback1 = SpecialBarBack::Create({ -670, 315, 10 }, "matattack:items:special_back");
	auto specialbar1_1 = SpecialBar::Create({ -670, 315, 10 }, "matattack:items:special_bar");
	specialbar1_1.transform.position = { specialbar1_1.transform.position - Vector3(specialbar1_1.sprite.scale.x *  388/ 2+2,0,0) };
	auto specialbar1_2 = SpecialBar::Create({ -670, 315, 10 }, "matattack:items:special_bar");
	specialbar1_2.transform.position = { specialbar1_2.transform.position + Vector3(specialbar1_2.sprite.scale.x * 388 / 2+2,0,0) };
	
	setSingleBlock(590, 380, 10, "matattack:characters:" + sndCharAnimation + ":idle:idle1", 100, 100, false, false);
	auto heathbar2 = HealthBar::Create({650, 340, 10 }, "matattack:items:health_bar100");
	auto hearts2 = Heart::Create({ 680, 380, 10 }, "matattack:items:3");
	auto specialbarback2 = SpecialBarBack::Create({ 650, 315, 10 }, "matattack:items:special_back");
	auto specialbar2_1 = SpecialBar::Create({ 650, 315, 10 }, "matattack:items:special_bar");
	specialbar2_1.transform.position = { specialbar2_1.transform.position - Vector3(specialbar2_1.sprite.scale.x * 388 / 2 + 2,0,0) };
	auto specialbar2_2 = SpecialBar::Create({ 650, 315, 10 }, "matattack:items:special_bar");
	specialbar2_2.transform.position = { specialbar2_2.transform.position + Vector3(specialbar2_2.sprite.scale.x * 388 / 2 + 2,0,0) };
	

	switch (lvl)
	{
	case 1:
		setMap1(); break;
	case 2:
		setMap2(); break;
	case 3:
		setMap3(); break;
	default:
		break;
	}

}

void matattack::SetLevelChooser()
{
	auto& reg = Engine::Registry();
	reg.clear();
	auto arrow = Arrow::Create({-200, -100}, "matattack:items:arrow");
	createBackdrop("matattack:background:select_screen");
	setSingleBlock(-200, 50, 0, "matattack:items:sky_level", 175, 125, false, false);
	setSingleBlock(0, 50, 0, "matattack:items:desert_level", 175, 125, false, false);
	setSingleBlock(200, 50, 0, "matattack:items:forest_level", 175, 125, false, false);
	
}

void setCharacterOption(int x, int y, int z, String path_to_sprite, String animation_name, unsigned size_x, unsigned size_y)
{
	auto& reg = Engine::Registry();
	auto entity = reg.create();

	auto block = reg.create();
	auto& sprite = reg.get_or_emplace<Sprite>(block);

	auto& animator = reg.get_or_emplace<Animator>(block);

	sprite.size = { size_x, size_y };
	sprite.position = { x, y, z };
	if (animation_name == "otter")
		sprite.scale = { 0.6, 0.6 };
	else 
		sprite.scale = { 2, 2 };

	AssignSprite(sprite, path_to_sprite);
	AnimatorPlay(animator, "matattack:idle:" + animation_name);
}

void setCharacterSelect()
{
	createBackdrop("matattack:background:select_screen");
	setCharacterOption(-150, 25, 0, "matattack:characters:fox:idle:idle1", "fox", 50, 50);
	setSingleBlock(-150, -25, 0, "matattack:items:fox_text", 60, 15, false, false);
	auto arrow = Arrow::Create({-150,-75}, "matattack:items:arrow1");
	setCharacterOption(-50, 25, 0, "matattack:characters:dude_monster:idle:idle1", "dude_monster", 50, 50);
	setSingleBlock(-50, -25, 0, "matattack:items:dude_monster_text", 60, 25, false, false);
	setCharacterOption(50, 25, 0, "matattack:characters:chickboy:idle:idle1", "chickboy", 50, 50);
	setSingleBlock(50, -25, 0, "matattack:items:meowknight_text", 60, 20, false, false);
	setCharacterOption(150, 25, 0, "matattack:characters:otter:idle:idle1", "otter", 50, 50);
	setSingleBlock(150, -25, 0, "matattack:items:otter_text", 60, 15, false, false);
}

void matattack::SetupWorld(int lvl, String fstCharSprite = "matattack:characters:fox:idle:idle1", String sndCharSprite = "matattack:characters:fox:idle:idle1", String fstCharAnimation = "fox", String sndCharAnimation = "fox", SpecialAbilities specAttack1 = HEAL, SpecialAbilities specAttack2 = HEAL)
{
	auto& reg = Engine::Registry();
	reg.clear();

	setCamera();
	setLevel(lvl, fstCharAnimation, sndCharAnimation);

	auto fstChar = Character::Create("ASDW", { -100, 250 }, specAttack1, fstCharSprite, fstCharAnimation);
	auto sndChar = Character::Create("Arrows", { 100, 250 }, specAttack2, sndCharSprite, sndCharAnimation);

}

void Matattack::WorldSetup()
{

	ShaderSystem::Use("standard");
	setCharacterSelect();       
}


