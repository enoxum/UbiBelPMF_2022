#include "simple_collisions.h"

#include "core/engine.h"
#include "core/game/transforms.h"
#include "../matattack/matattack.h"
#include "../matattack/events.h"

using namespace dagger;

void SimpleCollisionsSystem::Run()
{
    auto view = Engine::Registry().view<SimpleCollision, Transform>();

    auto it = view.begin();
    while(it != view.end())
    {
        // data of the first entity
        auto &collision = view.get<SimpleCollision>(*it);
        auto &transform = view.get<Transform>(*it);
        collision.colided = false;

        auto it2 = it;
        it2++;

        while(it2 != view.end())
        {
            // data of the second entity
            auto &col = view.get<SimpleCollision>(*it2);
            auto &tr = view.get<Transform>(*it2);
            col.colided = false;


            bool players_in_question = Engine::Registry().has<matattack::CharacterInfo>(*it) && Engine::Registry().has<matattack::CharacterInfo>(*it2);
            bool basic_collision_detection = collision.IsCollided(transform.position, col, tr.position);

            // ovaj if moze u drugi, ali onda 2 player-a moraju reaguju
            // kolizija 2 player-a
            if (players_in_question && basic_collision_detection) {

                PlayerCollisionEvent event;
                event.collision = true;
                Engine::Dispatcher().trigger<PlayerCollisionEvent>(event);

            }
            // ovo treba uvek se desava
            // processing one collision per frame for each colider
            // ako bar 1 od 2 entiteta ima is_collidable = true, onda moraju se colliduju, a su oboma false, onda se nece collide
            if (basic_collision_detection && (collision.is_collidable || col.is_collidable))
            {
                //Logger::trace("they are colliding!");
                collision.colided = true;
                collision.colidedWith = *it2;
                Vector2 side;
                Vector3 collision_center;

                if (collision.is_moveable) {
                    side = collision.GetCollisionSides(transform.position, col, tr.position);
                    collision_center = collision.GetCollisionCenter(transform.position, col, tr.position);

                    collision.side_x = side.x;
                    collision.side_y = side.y;

                    // collision.pos.x => stara x pozicija igraca
                    transform.position.x -= (transform.position.x - collision.pos.x) * abs(side.x);
                    transform.position.y -= (transform.position.y - collision.pos.y) * abs(side.y);
                    /*Logger::trace("Drugi side!:");
                    Logger::trace(side.x);
                    Logger::trace(side.y);*/
                }

                col.colided = true;
                col.colidedWith = *it;

                if (col.is_moveable) {
                    side = col.GetCollisionSides(tr.position, collision, transform.position);
                    collision_center = col.GetCollisionCenter(tr.position, collision, transform.position);

                    col.side_x = side.x;
                    col.side_y = side.y;
                    
                    tr.position.x -= (tr.position.x - col.pos.x) * abs(side.x);
                    tr.position.y -= (tr.position.y - col.pos.y) * abs(side.y);
                    /*Logger::trace("Drugi side!:");
                    Logger::trace(side.x);
                    Logger::trace(side.y);*/
                }

                //tr.position = chr.previous_position;
            }
            it2++;
        }
        collision.pos = transform.position;
        it++;
    }
}

// SimpleCollision

bool SimpleCollision::IsCollided(const Vector3& pos_, const SimpleCollision& other_, const Vector3& posOther_)
{
    Vector2 p(pos_.x + pivot.x * size.x, pos_.y + pivot.y * size.y);
    Vector2 p2(posOther_.x + other_.pivot.x * other_.size.x, posOther_.y + other_.pivot.y * other_.size.y);

    if (p.x < p2.x + other_.size.x &&
        p.x + size.x > p2.x &&
        p.y < p2.y + other_.size.y &&
        p.y + size.y > p2.y)
    {
        return true;
    }

    return false;
}

Vector2 SimpleCollision::GetCollisionSides(const Vector3& pos_, const SimpleCollision& other_, const Vector3& posOther_)
{
    Vector2 res(0, 0);

    Vector2 p(pos_.x + pivot.x * size.x, pos_.y + pivot.y * size.y);
    Vector2 p2(posOther_.x + other_.pivot.x * other_.size.x, posOther_.y + other_.pivot.y * other_.size.y);

    Float32 xDif = std::min(std::abs(p.x + size.x - p2.x), std::abs(p2.x + other_.size.x - p.x));
    Float32 yDif = std::min(std::abs(p.y + size.y - p2.y), std::abs(p2.y + other_.size.y - p.y));

    if (xDif < yDif)
    {
        res.x = std::abs(p.x + size.x - p2.x) < std::abs(p2.x + other_.size.x - p.x) ? 1 : -1;
    }
    else
    {
        res.y = std::abs(p.y + size.y - p2.y) < std::abs(p2.y + other_.size.y - p.y) ? 1 : -1;
    }

    return res;
}

Vector3 SimpleCollision::GetCollisionCenter(const Vector3& pos_, const SimpleCollision& other_, const Vector3& posOther_)
{
    Vector3 res;

    Vector2 p(pos_.x + pivot.x * size.x, pos_.y + pivot.y * size.y);
    Vector2 p2(posOther_.x + other_.pivot.x * other_.size.x, posOther_.y + other_.pivot.y * other_.size.y);

    res.x = (p.x + size.x / 2.f + p2.x + other_.size.x) / 2.f;
    res.y = (p.y + size.y / 2.f + p2.y + other_.size.y) / 2.f;
    res.z = 1.f;

    return res;
}
