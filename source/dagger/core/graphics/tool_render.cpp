#include "tool_render.h"
#include "sprite.h"
#include "textures.h"
#include "texture.h"
#include "core/engine.h"

#include <limits>
#include <algorithm>
#include <execution>
#include <chrono>
#include <cstdint>
#include <regex>

using namespace dagger;

void ToolRenderSystem::SpinUp()
{
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &m_StaticMeshVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_StaticMeshVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_VerticesAndTexCoords), m_VerticesAndTexCoords, GL_STATIC_DRAW);

    // attribute #0: vertex position
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
        sizeof(float) * 4, (void*)0);
    glEnableVertexAttribArray(0);

    // attribute #1: tex coord
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
        sizeof(float) * 4, (void*)(sizeof(float) * 2));
    glEnableVertexAttribArray(1);

    const GLsizei dataSize = sizeof(SpriteData);

    glGenBuffers(1, &m_InstanceQuadInfoVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_InstanceQuadInfoVBO);
    glBufferData(GL_ARRAY_BUFFER, s_BufferSize, nullptr, GL_STREAM_DRAW);

    const StaticArray<Pair<UInt32, UInt32>, 9> sizesAndStrides = {
        pair(2, 0),     // #2: sub size
        pair(2, 2),     // #3: sub origin
        pair(2, 4),     // #4: sub origin
        pair(3, 6),     // #5: quad position
        pair(2, 9),     // #6: quad pivot
        pair(4, 11),    // #7: quad tint color
        pair(2, 15),    // #8: scale
        pair(1, 17),    // #9: rotation
        pair(1, 18),    // #10: is UI?
    };

    for (UInt32 i = 0; i < sizesAndStrides.size(); i++)
    {
        const UInt32 index = 2 + i;
        glVertexAttribPointer(index, sizesAndStrides[i].first, GL_FLOAT, GL_FALSE,
            dataSize, (void*)(sizeof(Float32) * sizesAndStrides[i].second));
        glEnableVertexAttribArray(index);
        glVertexAttribDivisor(index, 1);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);

    Engine::Dispatcher().sink<Render>().connect<&ToolRenderSystem::OnRender>(this);
}

void ToolRenderSystem::OnRender()
{
    static auto SortSprites = [](const Sprite& a_, const Sprite& b_)
    {
        // sorting by levels: z-order, shader, then image
        // if the values are equal on z-order level, we go to the next (shader)
        // if the shaders are also equal, we go to the texture
        // if the textures are also equal, we give up

        UInt32 aShader = a_.shader->programId;
        UInt32 bShader = b_.shader->programId;
        UInt32 aZ = a_.position.z;
        UInt32 bZ = b_.position.z;
        UInt32 aImage = a_.image == nullptr ? 0 : a_.image->TextureId();
        UInt32 bImage = b_.image == nullptr ? 0 : b_.image->TextureId();

        if (aZ == bZ)
        {
            if (aShader == bShader)
            {
                return aImage < bImage;
            }
            else
                return aShader < bShader;
        }
        else
            return aZ > bZ;
    };

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_InstanceQuadInfoVBO);

    // get a view of all the entities and their sprite components
    ViewPtr<Texture> prevTexture{ nullptr };
    ViewPtr<Shader> prevShader{ nullptr };

    if (registry != nullptr)
    {
        const auto& view = registry->view<Sprite>();
        Sequence<Sprite> sprites{ view.raw(), view.raw() + view.size() };
        std::sort(sprites.begin(), sprites.end(), SortSprites);
        UInt64 dataSize = sizeof(SpriteData) * sprites.size();
        Sequence<SpriteData> currentRender{};

        for (auto ptr = sprites.begin(); ptr != sprites.end();)
        {
            if (prevShader != ptr->shader)
            {
                prevShader = ptr->shader;
                glUseProgram(prevShader->programId);
                Engine::Dispatcher().trigger<ShaderChangeRequest>(ShaderChangeRequest(prevShader));
            }

            assert(ptr->image != nullptr);
            while (ptr != sprites.end() && ptr->image == nullptr) ptr++;
            if (ptr == sprites.end()) break;

            prevTexture = ptr->image;

            while (ptr != sprites.end() && prevTexture == ptr->image)
            {
                // look at the definition of SpriteData if you're wondering why the cast.
                // we only need some fields, to optimize on data transfer.
                currentRender.push_back((SpriteData)*ptr);
                ptr++;
            }

            const UInt32 renderSize = sizeof(SpriteData) * currentRender.size();

            m_Data = reinterpret_cast<float*>(glMapBufferRange(GL_ARRAY_BUFFER,
                0, sizeof(Sprite) * currentRender.size(), GL_MAP_WRITE_BIT));

            memcpy(m_Data, &(*currentRender.begin()), renderSize);
            glUnmapBuffer(GL_ARRAY_BUFFER);

            glBindTexture(GL_TEXTURE_2D, prevTexture->TextureId());
            glDrawArraysInstanced(GL_TRIANGLES, 0, s_VertexCount, (GLsizei)currentRender.size());
            currentRender.clear();

            if (ptr == sprites.end()) break;
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void ToolRenderSystem::WindDown()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_StaticMeshVBO);
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &m_StaticMeshVBO);

    glDeleteVertexArrays(1, &m_VAO);

    Engine::Dispatcher().sink<Render>().disconnect<&ToolRenderSystem::OnRender>(this);
}
