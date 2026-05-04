#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

// #define GLM_ENABLE_EXPERIMENTAL
// #include <glm/gtx/matrix_decopose.hpp>

namespace idk
{
    namespace coordinate_system
    {
        static glm::vec3 FRONT = glm::vec3(0.0f, 0.0f, 1.0f);
        static glm::vec3 RIGHT = glm::vec3(1.0f, 0.0f, 0.0f);
        static glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f);
    }

    struct Transform
    {
    private:
        glm::mat4 M4;
        glm::vec3 pos;
        glm::quat rot;
        float scale;
        bool dirty;

    public:
        Transform(const glm::vec3 &p = glm::vec3(0.0f))
            : M4(1.0f),
              pos(p),
              rot(glm::vec3(0.0f)),
              scale(1.0f),
              dirty(false)
        {
        }

        const glm::mat4 &to_mat4()
        {
            if (dirty)
            {
                M4 = glm::translate(glm::mat4(1.0f), pos);
                M4 = glm::rotate(M4, glm::radians(rot.x), glm::vec3(1, 0, 0));
                M4 = glm::rotate(M4, glm::radians(rot.y), glm::vec3(0, 1, 0));
                M4 = glm::rotate(M4, glm::radians(rot.z), glm::vec3(0, 0, 1));
                M4 = glm::scale(M4, glm::vec3(scale));
                dirty = false;
            }
            return M4;
        }

        glm::vec3 getPos()
        {
            return pos;
        }

        glm::quat getRot()
        {
            return rot;
        }

        float getScale()
        {
            return scale;
        }

        glm::vec3 getFront()
        {
            return glm::mat3(M4) * coordinate_system::FRONT;
        }

        void setPos(const glm::vec3 &p)
        {
            dirty = true;
            pos = p;
        }

        void setRot(const glm::quat &q)
        {
            dirty = true;
            rot = q;
        }

        void setScale(float s)
        {
            dirty = true;
            scale = s;
        }

        void translate(float x, float y, float z)
        {
            dirty = true;
            pos += glm::vec3(x, y, z);
        }
        void translate(const glm::vec3 &delta)
        {
            dirty = true;
            pos += delta;
        }

        void rotate(float radTheta, const glm::vec3 &axis)
        {
            dirty = true;
            rot = glm::normalize(rot * glm::angleAxis(radTheta, axis));
        }
    };
}

// class Transformable
// {
// private:
//     Transform mT;

// public:
//     Transform &getTransform() { return mT; }

//     const glm::vec3 &getPos() { return mT.pos; }
//     const glm::quat &getRot() { return mT.rot; }
//     float getScale() { return mT.scale; }

//     void setPos(const glm::vec3 &p) { mT.pos = p; }
//     void setRot(const glm::quat &q) { mT.rot = q; }
//     void setScale(float s) { mT.scale = s; }

//     void translate(float x, float y, float z) { mT.pos += glm::vec3(x, y, z); }
//     void translate(const glm::vec3 &delta) { mT.pos += delta; }

//     void rotate(float radTheta, const glm::vec3 &axis)
//     {
//         mT.rot = glm::normalize(mT.rot * glm::angleAxis(radTheta, axis));
//     }

// };
