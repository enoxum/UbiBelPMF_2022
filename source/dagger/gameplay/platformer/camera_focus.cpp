#include "camera_focus.h"

#include "core/core.h"
#include "core/engine.h"
#include "core/graphics/sprite.h"
#include "core/graphics/window.h"

using namespace dagger;
using namespace platformer;

void CameraFollowSystem::Run()
{
    auto* camera = Engine::GetDefaultResource<Camera>();
    auto camPosition = (Vector2)camera->position;

    Vector2 center{};
    UInt32 count{ 0 };

    Engine::Registry().view<CameraFollowFocus, Sprite>().each([&](const CameraFollowFocus& focus_, const Sprite& sprite_)
        {
            for (UInt32 i = 0; i < focus_.weight; i++)
            {
                Logger::critical(((Vector2)sprite_.position).y);
                if (((Vector2)sprite_.position).x >= 800 ) {
                    center.x = 800;
                }
                else if (((Vector2)sprite_.position).x <= -800) {
                    center.x = -800;
                }
                else {
                    center.x = ((Vector2)sprite_.position).x;
                }

                if (((Vector2)sprite_.position).y >= 800) {
                    center.y = 800;
                }
                else if (((Vector2)sprite_.position).y <= -610) {
                    center.y = -610;
                }
                else {
                    center.y = ((Vector2)sprite_.position).y;
                }
                
            }
            count += focus_.weight;
        });

    if (count > 0)
    {
        center /= count;
        camera->position = Vector3{ glm::mix((Vector2)camera->position, center, 0.5f), 0.0f };
    }
}
