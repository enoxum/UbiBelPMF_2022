#include "simple_collisions.h"

#include "core/engine.h"
#include "core/game/transforms.h"

using namespace dagger;

void SimpleCollisionsSystem::Run()
{
    {
        auto viewSimple = Engine::Registry().view<SimpleCollision, Transform>();

        auto it = viewSimple.begin();
        while (it != viewSimple.end())
        {
            auto &collision = viewSimple.get<SimpleCollision>(*it);
            auto &transform = viewSimple.get<Transform>(*it);

            auto it2 = it;
            it2++;
            while (it2 != viewSimple.end())
            {
                auto &col = viewSimple.get<SimpleCollision>(*it2);
                auto &tr = viewSimple.get<Transform>(*it2);

                // processing one collision per frame for each colider
                if (collision.IsCollided(transform.position, col, tr.position))
                {
                    collision.colided = true;
                    collision.colidedWith = *it2;

                    col.colided = true;
                    col.colidedWith = *it;
                }
                it2++;
            }
            it++;
        }
    }
    {
        auto viewCircle = Engine::Registry().view<CircleCollision, Transform>();

        auto it = viewCircle.begin();
        while (it != viewCircle.end())
        {
            auto &col = viewCircle.get<CircleCollision>(*it);
            auto &tr = viewCircle.get<Transform>(*it);

            auto itOther = it;
            itOther++;
            while (itOther != viewCircle.end())
            {
                auto &colOther = viewCircle.get<CircleCollision>(*itOther);
                auto &trOther = viewCircle.get<Transform>(*itOther);

                if (col.isCollided(tr.position, colOther, trOther.position))
                {
                    col.colided = true;
                    col.colidedWith = *itOther;

                    colOther.colided = true;
                    colOther.colidedWith = *it;
                }

                itOther++;
            }
            it++;
        }
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

// CircleCollision

bool CircleCollision::isCollided(const Vector3& pos_, const CircleCollision& other_, const Vector3& posOther_)
{
    Vector2 p(pos_.x + pivot.x * radius, pos_.y + pivot.y * radius);
    Vector2 p2(posOther_.x + other_.pivot.x * other_.radius, posOther_.y + other_.pivot.y * other_.radius);

    if (glm::distance(p, p2) < radius + other_.radius) {
        return true;
    }     
    
    return false;
}
