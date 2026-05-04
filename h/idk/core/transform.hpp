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
        static glm::vec3 UP    = glm::vec3(0.0f, 1.0f, 0.0f);
    }

    struct Transform
    {
    private:
        glm::mat4 M4;
        glm::vec3 pos;
        float pitch_;
        float yaw_;
        // glm::quat rot;
        float scale;
        bool dirty;

    public:
        Transform(const glm::vec3 &p = glm::vec3(0.0f))
        :   M4(1.0f),
            pos(p),
            pitch_(0.0f),
            yaw_(0.0f),
            // rot(glm::vec3(0.0f)),
            scale(1.0f),
            dirty(false)
        {

        }

        bool isDirty()
        {
            return dirty;
        }

        const glm::mat4 &to_mat4()
        {
            if (dirty)
            {
                glm::mat4 T = glm::translate(glm::mat4(1.0f), pos);
                // glm::mat4 R = glm::rotate(glm::mat4(1.0f), pitch_, coordinate_system::RIGHT);
                //           R = glm::rotate(R, yaw_, coordinate_system::UP);
                glm::mat4 R = glm::rotate(glm::mat4(1.0f), yaw_, coordinate_system::UP);
                          R = glm::rotate(R, pitch_, coordinate_system::RIGHT);
                glm::mat4 S = glm::scale(glm::mat4(1.0f), glm::vec3(scale));

                M4 = T*R*S;
       
                dirty = false;
            }
            return M4;
        }

        glm::vec3 getPos() { return pos; }
        // glm::quat getRot() { return rot; }
        float getScale() { return scale; }

        glm::vec3 getFront() { return glm::normalize(glm::mat3(M4) * coordinate_system::FRONT); }
        glm::vec3 getRight() { return glm::normalize(glm::mat3(M4) * coordinate_system::RIGHT); }
        glm::vec3 getUp()    { return glm::normalize(glm::mat3(M4) * coordinate_system::UP);    }

        void setPos(const glm::vec3 &p)
        {
            dirty = true;
            pos = p;
        }

        // void setRot(const glm::quat &q)
        // {
        //     dirty = true;
        //     rot = q;
        // }

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

        // void rotate(float radTheta, const glm::vec3 &axis)
        // {
        //     dirty = true;
        //     rot = glm::normalize(rot * glm::angleAxis(radTheta, axis));
        // }

        void pitch(float r) { pitch_ += r; }
        void yaw  (float r) { yaw_   += r; }
    
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
